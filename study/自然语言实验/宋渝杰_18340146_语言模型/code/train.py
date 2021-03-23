import codecs, torch
import torch.autograd as autograd, torch.nn as nn, torch.optim as optim
from tqdm import tqdm

EMBEDDING_DIM = 256
HIDDEN_DIM = 1024

device = torch.device("cuda" if torch.cuda.is_available() else "cpu") # 是否使用GPU

def read(root): # 训练集数据+标签
    f = codecs.open(root, 'r', encoding = 'utf-8')
    data = []
    for s in f.readlines():
        data.append(s.strip('\n').split()+["<STOP>"])
    return data

train = read('trainset.txt')[1000:3560]

word_to_ix, ix_to_word = {}, {} # 词->数值字典
for sentence in train:
    for word in sentence:
        if word not in word_to_ix:
            word_to_ix[word] = len(word_to_ix)
            ix_to_word[len(ix_to_word)] = word
#print(len(word_to_ix))

def pre(seq, to_ix): # 句子->数值列表
    seqs = torch.tensor([to_ix[w] if w in to_ix else 0 for w in seq[0:len(seq)-1]], dtype = torch.long)
    tags = torch.tensor([to_ix[w] if w in to_ix else 0 for w in seq[1:]], dtype = torch.long)
    return seqs.to(device), tags.to(device)

def test(l):
    count = 30
    while count:
        count -= 1
        sentence = torch.tensor([word_to_ix[w] if w in word_to_ix else 0 for w in l], dtype = torch.long).to(device)
        out = model(sentence)
        _, predicted = torch.max(out.data, 1) # 返回每一行中的最大值及其索引
        l.append(ix_to_word[predicted.cpu().numpy()[-1]])
        if l[-1] == "<STOP>": break
    return l

class myLSTM(nn.Module):

    def __init__(self, vocab_size, embedding_dim, hidden_dim):
        super(myLSTM, self).__init__()
        self.word_embeds = nn.Embedding(vocab_size, embedding_dim) # 字嵌入
        self.lstm = nn.GRU(embedding_dim, hidden_dim, num_layers = 1, batch_first = True)
        self.hidden2tag = nn.Linear(hidden_dim, vocab_size) # 全连接层输出各个标签的预测分值

    def forward(self, sentence):
        embeds = self.word_embeds(sentence).unsqueeze(dim=0)
        lstm_out, _ = self.lstm(embeds)
        lstm_feats = self.hidden2tag(lstm_out.squeeze())
        if len(sentence) == 1: lstm_feats = lstm_feats.unsqueeze(0) # 句子长度为1时，需要加一维
        return lstm_feats

'''      
model = torch.load('model_100_GRU.pkl').to(device) # GPU
'''
model = myLSTM(len(word_to_ix), EMBEDDING_DIM, HIDDEN_DIM).to(device)
loss_func = nn.CrossEntropyLoss() # 损失函数: 交叉熵
optimizer = optim.SGD(model.parameters(), lr = 0.01, momentum = 0.9, weight_decay = 5e-4) # 优化方式: SGDM
progressive = tqdm(range(100), total = 100, ncols = 50, leave = False, unit = "b") # 可视化进度条

bestAcc, Acc = 1e9, []
for epoch in progressive:
    if epoch == 40: optimizer = optim.SGD(model.parameters(), lr = 0.001, momentum = 0.9, weight_decay = 5e-4)
    if epoch == 80: optimizer = optim.SGD(model.parameters(), lr = 0.0001, momentum = 0.9, weight_decay = 5e-4)
    ans = 0.0
    for i in range(len(train)):
        sentence_in_pad, targets_pad = pre(train[i], word_to_ix)
        out = model(sentence_in_pad) # 正向传播
        loss = loss_func(out, targets_pad)
        optimizer.zero_grad()
        loss.backward()
        optimizer.step()
        ans += loss.item()
    print('\n', ans/len(train))
    Acc.append(ans/len(train))
    print(''.join(test(["我们"])))
    print(''.join(test(["一些"])))
    print(''.join(test(["发展"])))
    if (epoch+1) % 10 == 0: 
        torch.save(model, 'model_'+str(epoch+1)+'_GRU.pkl')  # 存储模型
    
def text(filename, data): # 保存数据用于作图
    file = open(filename,'w')
    for i in data: file.write(str(i)+', ')
    file.close()
    
text('Loss_GRU.txt', Acc)
       
print(''.join(test(["我们"])))
print(''.join(test(["一些"])))
print(''.join(test(["发展"])))
