import torch, os, pickle
import torch.nn as nn, numpy as np, torchvision.transforms as transforms, PIL.Image as Image

device = torch.device("cuda" if torch.cuda.is_available() else "cpu") # 是否使用GPU

class MyCifar10(torch.utils.data.Dataset): # MyCifar10

    def __init__(self, root, train = True, transform = None): # 文件目录，训练/验证，预处理
        self.root = os.path.expanduser(root)
        self.transform = transform
        if train: self.lis = ['data_batch_1', 'data_batch_2', 'data_batch_3', 'data_batch_4', 'data_batch_5'] # 训练集
        else: self.lis = ['test_batch'] # 验证集
        self.data, self.targets = [], []
        for name in self.lis:
            path = os.path.join(self.root, name)
            with open(path, 'rb') as f:
                entry = pickle.load(f, encoding = 'latin1') # CIFAR10用的是encoding = 'latin1'
                self.data.append(entry['data']) # 图片数据
                self.targets.extend(entry['labels']) # 标签（注意是extend）
        self.data = np.vstack(self.data).reshape(-1, 3, 32, 32).transpose((0, 2, 3, 1)) # numpy.ndarray高维矩阵的表示:H,W,C
        
    def __getitem__(self, index):
        img, target = self.data[index], self.targets[index] # 获取数据和标签
        img = Image.fromarray(img)
        if self.transform is not None: img = self.transform(img) # 预处理
        return img, target

    def __len__(self):
        return len(self.data)

train_dataset = MyCifar10('CNN/data', train = True, transform = transforms.Compose([ # 加载数据
    transforms.RandomCrop(32, padding = 4), # 随机扩展裁剪
    transforms.RandomHorizontalFlip(), # 随机水平翻转
    transforms.ToTensor(), # [0,255]->[0,1]
    transforms.Normalize((0.4914, 0.4822, 0.4465), (0.2023, 0.1994, 0.2010)), # [0,1]->[-1,1]
]))

test_dataset = MyCifar10('CNN/data', train = False, transform = transforms.Compose([
    transforms.ToTensor(),
    transforms.Normalize((0.4914, 0.4822, 0.4465), (0.2023, 0.1994, 0.2010)),
]))

# torch.utils.data.DataLoader: 包装数据
# shuffle: 洗牌(多用于训练)
# batch_size: 包装大小(一般2^n)
train_loader = torch.utils.data.DataLoader(train_dataset, shuffle = True, batch_size = 64, num_workers = 2)
test_loader = torch.utils.data.DataLoader(test_dataset, batch_size = 64, num_workers = 2)

class Net(nn.Module):
    
    def __init__(self):
        super(Net,self).__init__()
        self.conv1 = nn.Conv2d(3, 64, kernel_size = 3, padding = 1) # 卷积层1
        self.conv2 = nn.Conv2d(64, 128, kernel_size = 3, padding = 1) # 卷积层2
        self.conv3 = nn.Conv2d(128, 256, kernel_size = 3, padding = 1) # 卷积层3
        self.conv4 = nn.Conv2d(256, 512, kernel_size = 3, padding = 1) # 卷积层4
        self.bn1 = nn.BatchNorm2d(64) # 批量标准化1
        self.bn2 = nn.BatchNorm2d(128) # 批量标准化2
        self.bn3 = nn.BatchNorm2d(256) # 批量标准化3
        self.bn4 = nn.BatchNorm2d(512) # 批量标准化4
        self.mp = nn.MaxPool2d(2, 2) # 最大池化层
        self.relu = nn.ReLU() # 激活函数: Relu
        self.fc1 = nn.Linear(512*4*4,1024) # 全连接层1
        self.fc2 = nn.Linear(1024,512) # 全连接层2
        self.fc3 = nn.Linear(512,10) # 全连接层3
        
    def forward(self,x):
        out = self.mp(self.relu(self.bn1(self.conv1(x)))) # 1:卷积->BN->激活->池化
        out = self.mp(self.relu(self.bn2(self.conv2(out)))) # 2:卷积->BN->激活->池化
        out = self.mp(self.relu(self.bn3(self.conv3(out)))) # 3:卷积->BN->激活->池化
        out = self.relu(self.bn4(self.conv4(out))) # 4:卷积->BN->激活
        out = out.view(-1, 512*4*4) # 展开成一维
        out = self.relu(self.fc1(out)) # 全连接层1
        out = self.relu(self.fc2(out)) # 全连接层2
        out = self.fc3(out) # 全连接层3
        return out

class BasicBlock(nn.Module): # 残差块
    
    def __init__(self, in_planes, planes, stride=1):
        super(BasicBlock, self).__init__()
        self.conv1 = nn.Conv2d(in_planes, planes, kernel_size = 3, stride = stride, padding = 1, bias = False) # 卷积层1
        self.bn1 = nn.BatchNorm2d(planes) # 批量标准化1
        self.conv2 = nn.Conv2d(planes, planes, kernel_size = 3, stride = 1, padding = 1, bias = False) # 卷积层2
        self.bn2 = nn.BatchNorm2d(planes) # 批量标准化2
        self.relu = nn.ReLU() # 激活函数: Relu
        self.shortcut = nn.Sequential()
        if stride != 1 or in_planes != planes: # 需要降维
            self.shortcut = nn.Sequential(
                nn.Conv2d(in_planes, planes, kernel_size = 1, stride = stride, bias = False), # 卷积层3
                nn.BatchNorm2d(planes) # 批量标准化3
            )

    def forward(self, x):
        out = self.relu(self.bn1(self.conv1(x))) # 1:卷积->BN->激活
        out = self.bn2(self.conv2(out)) # 2:卷积->BN
        out += self.shortcut(x) # 残差
        out = self.relu(out) # 激活
        return out
    
class ResNet(nn.Module):
    
    def __init__(self, num_blocks, k=4):
        super(ResNet, self).__init__()
        self.in_planes = 16
        self.conv1 = nn.Conv2d(3, 16, kernel_size = 3, padding = 1, bias = False) # 卷积层
        self.bn1 = nn.BatchNorm2d(16) # 批量标准化
        self.layer1 = self._make_layer(num_blocks[0], 16*k, 1) # 残差层1
        self.layer2 = self._make_layer(num_blocks[1], 32*k, 2) # 残差层2
        self.layer3 = self._make_layer(num_blocks[2], 64*k, 2) # 残差层3
        self.layer4 = self._make_layer(num_blocks[3], 128*k, 2) # 残差层4
        self.relu = nn.ReLU() # 激活函数: Relu
        self.avg_pool = nn.AvgPool2d(4) # 平均池化层
        self.linear = nn.Linear(128*k, 10) # 全连接层

    def _make_layer(self, num_block, planes, stride): # 新建残差层
        strides, layers = [stride]+[1]*(num_block-1), []
        for stride in strides:
            layers.append(BasicBlock(self.in_planes, planes, stride)) # 每层num_block个残差块
            self.in_planes = planes
        return nn.Sequential(*layers)

    def forward(self, x):
        out = self.relu(self.bn1(self.conv1(x))) # 卷积->BN->激活
        out = self.layer1(out) # 4层残差层
        out = self.layer2(out)
        out = self.layer3(out)
        out = self.layer4(out)
        out = self.avg_pool(out)
        out = out.view(out.size(0), -1) # 展开成一维
        out = self.linear(out) # 全连接层
        return out
    
# CNN = Net().to(device) # Normal
CNN = ResNet([2,2,2,2]).to(device) # ResNet18
# CNN = ResNet([3,4,6,3]).to(device) # ResNet34
# CNN = ResNet([2,2,2,2], 10).to(device) # WideResNet18
# CNN = ResNet([3,4,6,3], 10).to(device) # WideResNet34

loss_func = nn.CrossEntropyLoss() # 损失函数: 交叉熵
optimizer = torch.optim.SGD(CNN.parameters(), lr = 0.1, momentum = 0.9, weight_decay = 5e-4) # 优化方式: SGDM

# training...
bestAcc, Acc = 0, []
for i in range(150):
    CNN.train() # nn.Module训练模式
    running_loss = 0.0
    for t, (data, target) in enumerate(train_loader): # 遍历训练集
        data, target = data.to(device), target.to(device) # 数据、标签(GPU) 
        out = CNN(data) # 正向传播
        loss = loss_func(out, target) # 计算误差
        optimizer.zero_grad() # 清空上一步的残余更新参数值
        loss.backward() # 误差反向传播
        optimizer.step() # 更新参数
        running_loss += loss.item() # 计算误差并打印
        if t%100 == 99:
            print('[%d, %d] loss=%.3f' % (i+1,t+1,running_loss/100))
            running_loss = 0.0
    # validating...
    CNN.eval() # nn.Module验证模式
    correct, total = 0, 0
    for data, target in test_loader: # 遍历验证集
        data, target = data.to(device), target.to(device) # 数据、标签(GPU) 
        out = CNN(data) # 正向传播
        _,predicted = torch.max(out.data, 1) # 返回每一行中的最大值及其索引
        total += target.size(0)
        correct += (predicted == target).sum().item()
    print('Test Accuracy: %.2f%%' % (100*correct/total))
    Acc.append(100*correct/total) # 记录当次验证准确率
    if i == 60: optimizer = torch.optim.SGD(CNN.parameters(), lr = 0.01, momentum = 0.9, weight_decay = 5e-4)
    if i == 100: optimizer = torch.optim.SGD(CNN.parameters(), lr = 0.001, momentum = 0.9, weight_decay = 5e-4)
    if i == 135: optimizer = torch.optim.SGD(CNN.parameters(), lr = 0.0001, momentum = 0.9, weight_decay = 5e-4)
    if i > 120 and 100*correct/total > bestAcc:
        bestAcc = 100*correct/total
        torch.save(CNN, 'CNN/ResNet18.pkl')  # 存储最优模型

def text(filename, data): # 保存数据用于作图
    file = open(filename,'w')
    for i in data: file.write(str(i)+', ')
    file.close()
    
text('CNN/ResNet18.txt',Acc)
