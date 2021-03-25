import torch
import torch.nn as nn

device = torch.device("cuda" if torch.cuda.is_available() else "cpu")

q = 128
batch = 128

def read(t): # 读取训练集、验证集
    f, trainData, testData, trainTarget, testTarget, l = open('train.csv'), [], [], [], [], 0
    f.readline() # 去除无用行
    for line in f.readlines():
        line = line.strip('\n').split(',')[2:]
        for i in range(len(line)): line[i] = float(line[i])
        if l%100 < t: 
            trainData.append(line[:len(line)-1]) # 训练集
            trainTarget.append([line[-1]]) # 训练集
        else: 
            testData.append(line[:len(line)-1]) # 验证集
            testTarget.append([line[-1]]) # 验证集
        l = (l+1)%100
    return trainData, testData, trainTarget, testTarget

def read2():
    f1, f2, trainData, testData, trainTarget = open('train.csv'), open('test.csv'), [], [], []
    f1.readline() # 去除无用行
    f2.readline() # 去除无用行
    for line in f1.readlines():
        line = line.strip('\n').split(',')[2:]
        for i in range(len(line)): line[i] = float(line[i])
        trainData.append(line[:len(line)-1]) # 训练集
        trainTarget.append([line[-1]]) # 训练集
    for line in f2.readlines():
        line = line.strip('\n').split(',')[2:]
        for i in range(len(line)-1): line[i] = float(line[i])
        testData.append(line[:len(line)-1]) # 验证集
    return trainData[0:100], testData, trainTarget[0:100]

class Net(nn.Module):
    
    def __init__(self):
        super(Net,self).__init__()
        self.relu = nn.ReLU() # 激活函数: Relu
        self.fc1 = nn.Linear(12, q) # 全连接层1
        self.fc2 = nn.Linear(q, 1) # 全连接层2
        
    def forward(self,x):
        out = self.relu(self.fc1(x)) # 全连接层1
        out = self.fc2(out) # 全连接层2
        return out

trainData, testData, trainTarget, testTarget = read(70)
# 声明神经网络、损失函数、优化器
model = Net().to(device)
loss_func = nn.MSELoss() # 损失函数: 交叉熵
optimizer = torch.optim.Adam(model.parameters(), lr = 0.01) # 优化方式: Adam

# 训练、测试
for step in range(1000):
    # 训练
    for i in range(len(trainData)//batch):
        data, target = torch.FloatTensor(trainData[i*batch:(i+1)*batch]).to(device), torch.FloatTensor(trainTarget[i*batch:(i+1)*batch]).to(device)
        out = model(data)
        loss = loss_func(out, target)
        optimizer.zero_grad() # BP三部曲
        loss.backward()
        optimizer.step()
        
    if (step+1)%10 == 0: 
        data, target = torch.FloatTensor(testData).to(device), torch.FloatTensor(testTarget).to(device)
        out = model(data)
        loss = loss_func(out, target)
        print(step+1, loss.cpu())  
    
    if step == 500: optimizer = torch.optim.Adam(model.parameters(), lr = 0.001)

'''
trainData, testData, trainTarget = read2()

model = Net().to(device)
loss_func = nn.MSELoss() # 损失函数: 交叉熵
optimizer = torch.optim.Adam(model.parameters(), lr = 0.01) # 优化方式: Adam

for step in range(1000):
    # 训练
    for i in range(len(trainData)):
        data, target = torch.FloatTensor(trainData[i]).to(device), torch.FloatTensor(trainTarget[i]).to(device)
        out = model(data)
        loss = loss_func(out, target)
        optimizer.zero_grad() # BP三部曲
        loss.backward()
        optimizer.step()
    if (step+1)%10 == 0: 
        data, target = torch.FloatTensor(trainData).to(device), torch.FloatTensor(trainTarget).to(device)
        out = model(data)
        loss = loss_func(out, target)
        print(step+1, loss.cpu())
    if (step+1)%100 == 0: 
        data = torch.FloatTensor(testData).to(device)
        out = model(data)
        print(out)
'''