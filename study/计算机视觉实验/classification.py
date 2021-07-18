# 放在data文件夹同目录下~

import cv2, torch, os, numpy as np
import torch.nn as nn
from sklearn.cluster import KMeans

def cal(x, y):
    return ((x[0]-y[0])**2 + (x[1]-y[1])**2 + (x[2]-y[2])**2) ** (1/2)

def find(fa, k):
    if fa[k] != k:
        fa[k] = find(fa, fa[k])
    return fa[k]
 
def test(index, k):
    # 初始化
    inImage = cv2.imread('data/imgs/' + index + '.png').astype(np.float64)
    mask = cv2.imread('data/gt/' + index + '.png', 0).astype(np.uint32)
    n, m = inImage.shape[:2]
    fa, size, threshold = np.zeros(n*m, dtype=np.uint32), np.zeros(n*m, dtype=np.uint32), np.zeros(n*m, dtype=np.float64)
    for i in range(n*m):
        fa[i], size[i], threshold[i] = i, 1, k
    # 分割区域
    lis = []
    for i in range(n):
        for j in range(m-1):
            lis.append((i, j, i, j+1, cal(inImage[i, j], inImage[i, j+1])))
    for i in range(n-1):
        for j in range(m):
            lis.append((i, j, i+1, j, cal(inImage[i, j], inImage[i+1, j])))
    lis.sort(key=lambda edge: edge[4])
    for edge in lis:
        a, b = find(fa, edge[0]*m+edge[1]), find(fa, edge[2]*m+edge[3])
        if a != b and edge[4] <= threshold[a] and edge[4] <= threshold[b]:
            fa[b] = a
            size[a] += size[b]
            threshold[a] = edge[4] + k/size[a]
    # 合并<50的区域
    for edge in lis:
        a, b = find(fa, edge[0]*m+edge[1]), find(fa, edge[2]*m+edge[3])
        if a != b and (size[a] < 50 or size[b] < 50):
            fa[b] = a
            size[a] += size[b]
    # 区域标号
    p, l = np.zeros((n, m), dtype=np.uint32), {}
    for i in range(n):
        for j in range(m):
            p[i, j] = find(fa, i*m+j)
            if p[i, j] not in l: l[p[i, j]] = len(l)
    # 判断区域是否为前景/背景
    l1, l2, label = [0] * len(l), [0] * len(l), [0] * len(l)
    for i in range(n):
        for j in range(m):
            if mask[i, j] == 255: l1[l[p[i, j]]] += 1
            else: l2[l[p[i, j]]] += 1
    for i in range(len(l)):
        if l1[i]+l2[i] > 0 and l1[i] / (l1[i]+l2[i]) >= 0.5: label[i] = 255
        else: label[i] = 0
    # 区域的512维特征
    v, s = np.zeros((len(l), 8, 8, 8), dtype=np.float64), np.zeros(len(l), dtype=np.uint32)
    inImage = inImage.astype(np.uint32)
    for i in range(n):
        for j in range(m):
            v[l[p[i, j]], inImage[i, j, 0]//32, inImage[i, j, 1]//32, inImage[i, j, 2]//32] += 1
            s[l[p[i, j]]] += 1
    v = np.reshape(v, (len(l), 512))
    for i in range(len(l)): v[i] /= s[i] # 归一化
    return len(l), v, label # 返回区域个数、每个区域512维、区域的标签

def segment(index): # 图像分割
    k = 500
    l, v, label = test(index, k) # 自适应阈值
    while l < 50 or l > 70:
        if l > 70: k += 50
        else: k -= 50
        l, v, label = test(index, k)
    return l, v, label # 返回区域个数、每个区域512维、区域的标签

def PCA(v): # PCA算法降维
    v -= np.mean(v, axis=0) # 去均值
    mat = np.cov(v, rowvar=0) # 协方差矩阵
    val, vec = np.linalg.eig(mat) # 特征值、特征向量
    e = [(np.abs(val[i]), vec[:,i]) for i in range(v.shape[1])] 
    e.sort(reverse=True, key=lambda p: p[0]) # 根据特征值降序排序
    feature = np.array([ele[1] for ele in e[:20]]) # 取前20个特征向量
    v = np.dot(v, np.transpose(feature)) # 构建新的数据
    return v.astype(np.float64)

def get20(index): # 得到一张图的所有区域的20维特征
    inImage = cv2.imread('data/imgs/' + index + '.png').astype(np.uint32)
    v1, (n, m) = np.zeros((8, 8, 8), dtype=np.float64), inImage.shape[:2]
    for i in range(n):
        for j in range(m):
            v1[inImage[i, j, 0]//32, inImage[i, j, 1]//32, inImage[i, j, 2]//32] += 1
    v1 = np.reshape(v1, 512) / (n * m) # 原图的512维特征
    l, v2, label = segment(index) # 区域的512维特征
    v = np.zeros((l, 1024), dtype=np.float64)
    for i in range(l):
        v[i, 0:512], v[i, 512:1024] = v1, v2[i] # 拼接为1024维
    v = PCA(v) # PCA算法降维
    return l, v, label

def get200_20(): # 得到200张图所有区域的20维特征
    l, v, label = 0, [], []
    for i in range(1, 201):
        l1, v1, label1 = get20(str(i)) # 得到一张图
        l += l1
        for j in range(l1):
            v.append(v1[j, :]) # 整合
            label.append(label1[j])
        print('get:', i)
    if not os.path.exists('data/classification'): os.mkdir('data/classification')
    f = open('data/classification/200_20.txt', 'w') # 文件保存
    for i in range(l):
        for j in range(20):
            f.write('{:.4f} '.format(v[i][j]))
        f.write(str(label[i]) + '\n')
        
def getVisualWord(): # 得到视觉词袋模型20维特征
    f = open('data/classification/200_20.txt', 'r')
    lis = []
    for l in f.readlines():
        lis.append([float(x) for x in l.strip().split()[0:20]])

    kmeans = KMeans(n_clusters=50, random_state=0).fit(np.array(lis)) # Kmeans算法聚类

    v, siz = np.zeros((50, 20), dtype=np.float64), np.zeros(50, dtype=np.uint32)
    for i in range(len(lis)):
        for j in range(20):
            v[kmeans.labels_[i], j] += lis[i][j] # 求类的特征
        siz[kmeans.labels_[i]] += 1
    for i in range(50):
        for j in range(20):
            v[i, j] /= siz[i]

    f = open('data/classification/visualWord.txt', 'w') # 文件保存
    for i in range(50):
        for j in range(20):
            f.write('{:.6f} '.format(v[i, j]))
        f.write('\n')
        
def getTrainData(): # 得到训练集
    f = open('data/classification/200_20.txt', 'r') # 读取图片区域20维特征
    v, label = [], []
    for l in f.readlines():
        v.append([float(x) for x in l.strip().split()[0:20]])
        label.append(l.strip().split()[20])
        
    f = open('data/classification/visualWord.txt', 'r') # 读取词袋模型20维特征
    word = []
    for l in f.readlines():
        word.append([float(x) for x in l.strip().split()])
    
    for i in range(len(v)): # 做点积操作，20维扩展成70维
        for j in range(50):
            v[i].append(np.dot(np.array(v[i][0:20]), np.array(word[j])))
          
    f = open('data/classification/trainData.txt', 'w') # 文件保存
    for i in range(len(v)):
        for j in range(70):
            f.write('{:.6f} '.format(v[i][j]))
        f.write(str(label[i]) + '\n')

def getTestData():
    v, label = [], []
    for i in range(46, 1000, 100): # 计算训练集20维特征
        l, v1, label1 = get20(str(i))
        for j in range(l):
            v.append(v1[j, :].tolist())
            label.append(label1[j])
        print('get:', i)
        
    f = open('data/classification/visualWord.txt', 'r') # 读取词袋模型20维特征
    word = []
    for l in f.readlines():
        word.append([float(x) for x in l.strip().split()])
    
    for i in range(len(v)): # 做点积操作，20维扩展成70维
        for j in range(50):
            v[i].append(np.dot(np.array(v[i][0:20]), np.array(word[j])))
          
    f = open('data/classification/testData.txt', 'w') # 文件保存
    for i in range(len(v)):
        for j in range(70):
            f.write('{:.6f} '.format(v[i][j]))
        f.write(str(label[i]) + '\n')
        
class Net(nn.Module):
    
    def __init__(self):
        super(Net,self).__init__()
        self.relu = nn.ReLU() # 激活函数: Relu
        self.fc1 = nn.Linear(70, 256) # 全连接层1
        self.fc2 = nn.Linear(256, 64) # 全连接层2
        self.fc3 = nn.Linear(64, 2) # 全连接层3
        
    def forward(self,x):
        out = self.relu(self.fc1(x)) # 全连接层1
        out = self.relu(self.fc2(out)) # 全连接层2
        out = self.fc3(out) # 全连接层3
        return out

def read(root): # 读入数据集
    f, data, target = open(root), [], []
    f.readline()
    for line in f.readlines():
        l = line.strip().split()
        target.append(0 if l[-1] == '0' else 1)
        l = [float(l[i]) for i in range(70)]
        data.append(l)
    return data, target

def classification():
    device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
    trainData, trainTarget = read('data/classification/trainData.txt')
    testData, testTarget = read('data/classification/testData.txt')

    model = Net().to(device) # 神经网络
    loss_func = nn.CrossEntropyLoss() # 损失函数: 交叉熵
    optimizer = torch.optim.Adam(model.parameters(), lr = 0.001, weight_decay = 5e-5) # 优化方式: Adam

    for step in range(1000): # 训练
        out = model(torch.FloatTensor(trainData).to(device))
        loss = loss_func(out, torch.LongTensor(trainTarget).to(device))
        optimizer.zero_grad() # BP三部曲
        loss.backward()
        optimizer.step()
    out = model(torch.FloatTensor(testData).to(device)) # 测试
    _, predicted = torch.max(out.data, 1)
    correct = (predicted == torch.LongTensor(testTarget).to(device)).sum().item()
    print('Step: %d   Train Loss: %.4f   Test Accuracy: %.4f%%' % (step+1, loss.item(), (100*correct/len(testTarget))))

def main():
    # get200_20()
    # getVisualWord()
    # getTrainData()
    # getTestData()
    classification()

main()