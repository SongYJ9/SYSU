import torch, re
import torch.nn as nn, torch.nn.functional as F
from torch.autograd import Variable

device = torch.device("cuda" if torch.cuda.is_available() else "cpu") # 是否使用GPU

def read(root, Laptops_trial_data = False): 
    data, replacelist = [], [',','.','!','(',')','-- ','?',':','"','\'','- ','/','*','=','\\','$',';','+','%','#','>','[','@',']']
    with open(root,'r') as f:
        f.readline() # 头几行是无效数据
        if Laptops_trial_data == False: f.readline()
        while (1):
            l = []
            l1 = f.readline()
            if l1[1] == '/': break # </sentences>
            l1 = f.readline().strip('\n')
            if len(l1)<8: # <test>和句子不在同一行
                l1 = f.readline().strip('\n')
                f.readline().strip('\n')
            else: # 在同一行
                l1 = re.split('<text>|</text>',l1)[1] # 从<text></text>中读取句子
            for c in replacelist: l1 = l1.replace(c, ' ') # 去除无用字符
            l1 = l1.lower().split() # 转换为小写，再分割成单词列表
            l.append(l1)
            l2 = [0 for i in range(len(l1))] # 默认为0（不是关键词）
            s = f.readline().strip()
            if s[1] == '/': # </sentence>
                l.append(l2)
                data.append(l)
                continue
            s = f.readline().strip()
            while s[1] == 'a': # <aspectTerms>
                s = s.split('"')[1].replace('&quot;',' ') # 读取关键词
                for c in replacelist: s = s.replace(c,' ') # 去除无用字符
                s = s.lower().split() # 转换为小写，再分割成单词列表
                for x in s:
                    if x in l1: l2[l1.index(x)] = 1 # 标识关键词为1
                s = f.readline().strip()
            l.append(l2)
            data.append(l)
            s = f.readline() # </sentence>
    with open('RNN/glove.6B.300d.txt','r') as f: # 读取词向量形成字典
        dic = {}
        for l in f.readlines():
            s = l.strip('\n').split(' ')
            dic[s[0]] = [float(x) for x in s[1:]]
    for i in range(len(data)):
        for j in range(len(data[i][0])):
            if data[i][0][j] in dic: data[i][0][j] = dic[data[i][0][j]] # 如果字典有这个单词，则转换成对应的词向量
            else: data[i][0][j] = [0 for x in range(300)] # 没有该单词，则默认为全0
    return data

train = read('RNN/Laptops_Train.xml') # 训练集
test = read('RNN/Laptops_Test.xml', True) # 验证集

class MyRNN(nn.Module):
    def __init__(self, n_dim, n_hidden):
        super(MyRNN, self).__init__()
        self.rnn = nn.GRU(n_dim, n_hidden, batch_first = True, bidirectional = True) # 神经元：GRU
        self.linear1 = nn.Linear(n_hidden*2, 2) # 全连接层
 
    def forward(self, x):
        x = x.unsqueeze(0) # 二维->三维
        x, _ = self.rnn(x) # rnn
        x = x.squeeze(0) # 三维->二维
        x = self.linear1(x) # 全连接层
        y = F.log_softmax(x, dim = 1) # log_softmax求对数概率
        return y

RNN = MyRNN(300, 256).to(device)
loss_func = nn.CrossEntropyLoss() # 损失函数: 交叉熵
optimizer = torch.optim.SGD(RNN.parameters(), lr = 0.01, momentum = 0.9, weight_decay = 5e-4) # 优化方式: SGDM

# training...
bestAcc, Acc = 0, []
for i in range(40):
    running_loss = 0.0
    for data, target in train: # 遍历训练集
        data, target = torch.FloatTensor(data).to(device), torch.LongTensor(target).to(device) # 数据、标签(GPU)
        out = RNN(data) # 正向传播
        loss = loss_func(out, target) # 计算误差
        optimizer.zero_grad() # 清空上一步的残余更新参数值
        loss.backward() # 误差反向传播
        optimizer.step() # 更新参数
        running_loss += loss.item() # 计算误差并打印
    print('[%d] loss=%.3f' % (i+1,running_loss/len(train)))
    # validating...
    correct, total = 0, 0
    for data, target in test: # 遍历验证集
        data, target = torch.FloatTensor(data).to(device), torch.LongTensor(target).to(device) # 数据、标签(GPU)
        out = RNN(data) # 正向传播
        _,predicted = torch.max(out.data, 1) # 返回每一行中的最大值及其索引
        predicted = predicted.cpu().numpy()
        total += len(target)
        for j in range(len(target)):
            if predicted[j] == target[j]: correct += 1
    print('Test Accuracy: %.2f%%' % (100*correct/total))
    Acc.append(100*correct/total) # 记录当次验证准确率
    if i == 20: optimizer = torch.optim.SGD(RNN.parameters(), lr = 0.001, momentum = 0.9, weight_decay = 5e-4)
    if i == 30: optimizer = torch.optim.SGD(RNN.parameters(), lr = 0.0001, momentum = 0.9, weight_decay = 5e-4)
    #if i == 135: optimizer = torch.optim.SGD(RNN.parameters(), lr = 0.0001, momentum = 0.9, weight_decay = 5e-4)
#'''
    if i > 20 and 100*correct/total > bestAcc:
        bestAcc = 100*correct/total
        torch.save(RNN, 'RNN/Final.pkl')  # 存储最优模型
#'''
        
def text(filename, data): # 保存数据用于作图
    file = open(filename,'w')
    for i in data: file.write(str(i)+', ')
    file.close()
    
text('RNN/Final.txt',Acc)
'''
i = 0;
for data, target in test: # 遍历验证集
    data, target = torch.FloatTensor(data).to(device), torch.LongTensor(target).to(device) # 数据、标签(GPU)
    out = RNN(data) # 正向传播
    _,predicted = torch.max(out.data, 1) # 返回每一行中的最大值及其索引
    predicted = predicted.cpu().numpy()
    print('predicted : ',predicted)
    print('target    : ',target.cpu().numpy())
    i += 1
    if i == 10: break
'''
