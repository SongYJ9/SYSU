import codecs, torch
import torch.autograd as autograd, torch.nn as nn, torch.optim as optim
from tqdm import tqdm

START_TAG, STOP_TAG, PAD_TAG = "<START>", "<STOP>", "<PAD>"
EMBEDDING_DIM = 256
HIDDEN_DIM = 256
BATCH = 256

device = torch.device("cuda" if torch.cuda.is_available() else "cpu") # 是否使用GPU

def read(root): # 训练集数据+标签
    f = codecs.open(root, 'r', encoding = 'utf-8')
    data = []
    for s in f.readlines():
        s = s.strip('\n').split()
        l, l1 = [], []
        for x in s:
            if len(x) == 1: l1.append(0)
            else:
                l1.append(1)
                for i in range(len(x)-2): l1.append(2)
                l1.append(3)
        l.append(list(''.join(s)))
        l.append(l1)
        data.append(l)
    return data

def test_data(root): # 验证集数据
    f = codecs.open(root, 'r', encoding = 'utf-8')
    data = []
    for s in f.readlines():
        data.append(list(s.strip('\n').strip('\r')))
    return data

def test_tags(root): # 验证集标签
    f = codecs.open(root, 'r', encoding = 'utf-8')
    data = []
    for s in f.readlines():
        s, l = s.strip('\n').split(), []
        for x in s:
            if len(x) == 1: l.append(0)
            else:
                l.append(1)
                for i in range(len(x)-2): l.append(2)
                l.append(3)
        data.append(l)
    return data

def pre(seq, to_ix): # 句子->数值列表
    return torch.tensor([to_ix[w] if w in to_ix else 0 for w in seq], dtype = torch.long)

def pre_batch(data ,word_to_ix, tag_to_ix): # 批处理数据
    seqs, tags = [i[0] for i in data], [i[1] for i in data]
    max_len = max([len(seq) for seq in seqs]) # 计算一批数据中最长值
    seqs_pad, tags_pad = [], []
    for seq,tag in zip(seqs, tags):
        seq_pad = seq + ['<PAD>'] * (max_len-len(seq)) # 对其他句子加上无效标签
        tag_pad = tag + ['<PAD>'] * (max_len-len(tag))
        seqs_pad.append(seq_pad)
        tags_pad.append(tag_pad)
    idxs_pad = torch.tensor([[word_to_ix[w] for w in seq] for seq in seqs_pad], dtype = torch.long)
    tags_pad = torch.tensor([[tag_to_ix[t] for t in tag] for tag in tags_pad], dtype = torch.long)
    return idxs_pad, tags_pad

train = read('msr_training.utf8')
test1 = test_data('msr_test.utf8')
test2 = test_tags('msr_test_gold.utf8')

class BiLSTM_CRF(nn.Module):

    def __init__(self, vocab_size, tag_to_ix, embedding_dim, hidden_dim):
        super(BiLSTM_CRF, self).__init__()
        self.embedding_dim = embedding_dim
        self.hidden_dim = hidden_dim
        self.vocab_size = vocab_size
        self.tag_to_ix = tag_to_ix
        self.tagset_size = len(tag_to_ix)
        self.word_embeds = nn.Embedding(vocab_size, embedding_dim) # 字嵌入
        self.lstm = nn.LSTM(embedding_dim, hidden_dim // 2, num_layers = 1, bidirectional = True, batch_first = True)
        self.hidden2tag = nn.Linear(hidden_dim, self.tagset_size) # 全连接层输出各个标签的预测分值
        self.transitions = nn.Parameter(torch.randn(self.tagset_size, self.tagset_size)) # 转移矩阵（随机初始化）
        # 这两个语句强制执行了这样的约束，我们不会将其转移到开始标记，也不会将其转移到停止标记
        self.transitions.data[tag_to_ix[START_TAG], :] = -10000
        self.transitions.data[:, tag_to_ix[STOP_TAG]] = -10000
        self.hidden = self.init_hidden()

    def init_hidden(self): # 隐藏层随机初始化
        return (torch.randn(2, 1, self.hidden_dim // 2).to(device),
                torch.randn(2, 1, self.hidden_dim // 2).to(device))

    def forward_LSTM(self, sentence): # BiLSTM前向传播（验证）
        self.hidden = self.init_hidden()
        embeds = self.word_embeds(sentence).unsqueeze(dim=0)
        lstm_out, self.hidden = self.lstm(embeds)
        lstm_out = lstm_out.squeeze()
        lstm_feats = self.hidden2tag(lstm_out)
        if len(sentence) == 1: lstm_feats = lstm_feats.unsqueeze(0) # 句子长度为1时，需要加一维
        return lstm_feats
    
    def forward_LSTM_parallel(self, sentence): # BiLSTM前向传播（训练）
        self.hidden = self.init_hidden()
        embeds = self.word_embeds(sentence)
        lstm_out, self.hidden = self.lstm(embeds)
        lstm_feats = self.hidden2tag(lstm_out)
        return lstm_feats
    
    def forward_CRF_parallel(self, feats): # 损失函数中的 logsumexp 部分（训练）
        init_alphas = torch.full([feats.shape[0], self.tagset_size], -10000.)
        init_alphas[:, self.tag_to_ix[START_TAG]] = 0. # 开始符号

        forward_var_list = []
        forward_var_list.append(init_alphas)
        for feat_index in range(feats.shape[1]): # 句子长度
            gamar_r_l = torch.stack([forward_var_list[feat_index]] * feats.shape[2]).transpose(0, 1) # 上一步
            t_r1_k = torch.unsqueeze(feats[:, feat_index, :], 1).transpose(1, 2) # 发射分值
            aa = gamar_r_l.to(device) + t_r1_k.to(device) + torch.unsqueeze(self.transitions, 0) # 上一步+发射分值+转移概率
            forward_var_list.append(torch.logsumexp(aa, dim = 2)) # 先计算到词 w_i 的 logsumexp
        terminal_var = forward_var_list[-1] + self.transitions[self.tag_to_ix[STOP_TAG]].repeat([feats.shape[0], 1]) # 最后只将最后一个单词的 forward var 与转移 stop_tag 的概率相加 
        alpha = torch.logsumexp(terminal_var, dim = 1)
        return alpha
    
    def score_parallel(self, feats, tags): # 损失函数中的 S(X,y) 部分（训练）
        score = torch.zeros(tags.shape[0]).to(device)
        tags = torch.cat([torch.full([tags.shape[0],1],self.tag_to_ix[START_TAG]).long().to(device), tags], dim = 1)
        for i in range(feats.shape[1]):
            feat = feats[:,i,:]
            score = score + self.transitions[tags[:,i + 1], tags[:,i]] + feat[range(feat.shape[0]),tags[:,i + 1]] # 转移概率+非归一化发射概率
        score = score + self.transitions[self.tag_to_ix[STOP_TAG], tags[:,-1]] # 加入结束标签
        return score
    
    def neg_log_likelihood_parallel(self, sentences, tags): # 训练，并返回误差（训练）
        feats = self.forward_LSTM_parallel(sentences) # 经过了LSTM+Linear矩阵后的输出，之后作为CRF的输入
        forward_score = self.forward_CRF_parallel(feats)
        gold_score = self.score_parallel(feats, tags)
        return torch.sum(forward_score - gold_score)/BATCH # 损失函数：根据这个差值，反向传播

    def viterbi_decode(self, feats): # 维特比解码，输出路径值（验证）
        backpointers = []
        init_vvars = torch.full((1, self.tagset_size), -10000.)
        init_vvars[0][self.tag_to_ix[START_TAG]] = 0

        forward_var_list = []
        forward_var_list.append(init_vvars)

        for feat_index in range(feats.shape[0]):
            gamar_r_l = torch.stack([forward_var_list[feat_index]] * feats.shape[1])
            gamar_r_l = torch.squeeze(gamar_r_l)
            next_tag_var = gamar_r_l.to(device) + self.transitions
            viterbivars_t, bptrs_t = torch.max(next_tag_var, dim = 1) # 返回最大值及其下标

            t_r1_k = torch.unsqueeze(feats[feat_index], 0) # 非归一化发射概率/发射得分
            forward_var_new = torch.unsqueeze(viterbivars_t, 0) + t_r1_k # 加入发射得分

            forward_var_list.append(forward_var_new)
            backpointers.append(bptrs_t.tolist()) # 保存部分最短路径

        terminal_var = forward_var_list[-1] + self.transitions[self.tag_to_ix[STOP_TAG]] # 加入转移至结束符号的概率
        best_tag_id = torch.argmax(terminal_var).tolist()

        best_path = [best_tag_id]
        for bptrs_t in reversed(backpointers): # 从后向前走，找到一个最优路径
            best_tag_id = bptrs_t[best_tag_id]
            best_path.append(best_tag_id)
        start = best_path.pop() # 不要开始符号
        best_path.reverse() # 反向->正向
        return best_path

    def forward(self, sentence): # 只是用来预测/验证（验证）
        lstm_feats = self.forward_LSTM(sentence)
        tag_seq = self.viterbi_decode(lstm_feats)
        return tag_seq
    
word_to_ix = {} # 字->数值字典
word_to_ix['<PAD>'] = 0
for sentence, _ in train:
    for word in sentence:
        if word not in word_to_ix:
            word_to_ix[word] = len(word_to_ix)
word_to_ix[''] = 0 # 训练集中不存在的字默认为0
            
tag_to_ix = {0: 0, 1: 1, 2: 2, 3: 3, START_TAG: 4, STOP_TAG: 5, PAD_TAG: 6} # 标签字典

model = torch.load('model.pkl').to(device) # GPU

data = []
for i in range(len(test1)):
    sentence = pre(test1[i], word_to_ix).to(device)
    l, s = model(sentence), ''
    for j in range(len(l)):
        if l[j] == 0 or l[j] == 3: s = s + test1[i][j] + ' '
        else: s = s + test1[i][j]
    data.append(s)
    
def text(filename, data): # 保存数据用于作图
    file = open(filename,'w')
    for i in data: file.write(i+'\n')
    file.close()
    
text('result.txt', data)
    
