import torch
import torch.nn as nn

class DQN(nn.Module):

    def __init__(self):
        super(DQN, self).__init__()
        self.conv1 = nn.Conv2d(1, 32, kernel_size = 3, padding = 1) # 64
        self.conv2 = nn.Conv2d(32, 64, kernel_size = 3, padding = 1) # 16
        self.conv3 = nn.Conv2d(64, 128, kernel_size = 3, padding = 1) # 4
        self.bn1 = nn.BatchNorm2d(32) # 批量标准化1
        self.bn2 = nn.BatchNorm2d(64) # 批量标准化2
        self.bn3 = nn.BatchNorm2d(128) # 批量标准化3
        self.mp = nn.MaxPool2d(2, 2) # 最大池化层
        self.relu = nn.ReLU() # 激活函数: Relu
        self.fc1 = nn.Linear(128*2*2,512) # 全连接层1
        # self.fc2 = nn.Linear(128*2*2,512) # 全连接层2
        # self.fc3 = nn.Linear(512,1) # 全连接层3
        self.fc4 = nn.Linear(512,64) # 全连接层4

    def forward(self,x):
        out = self.mp(self.relu(self.bn1(self.conv1(x)))) # 1:卷积->BN->激活->池化
        out = self.mp(self.relu(self.bn2(self.conv2(out)))) # 2:卷积->BN->激活->池化
        out = self.relu(self.bn3(self.conv3(out))) # 3:卷积->BN->激活->池化
        out = out.view(-1, 128*2*2) # 展开成一维
        # x1 = self.fc3(self.relu(self.fc1(out))).expand(out.size(0), 64) # 状态价值
        # x2 = self.fc4(self.relu(self.fc2(out))) # 动作价值
        # return x1+x2-x2.mean(1).unsqueeze(1).expand(out.size(0), 64)
        return self.fc4(self.relu(self.fc1(out)))