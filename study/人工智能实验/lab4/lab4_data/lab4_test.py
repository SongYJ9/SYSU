from random import uniform
from math import exp
from copy import deepcopy

q = 5 # 隐层神经元数量

def read(f,n): # 读取训练集
    data = []
    hour = [10,13,11,10,2,3,21,50,109,81,46,56,79,80,76,82,82,125,107,72,41,41,21,20]
    weekday = [33,61,71,54,0,0,43]
    workingday = [38,63]
    weathersit = [55,47,36,0]
    f.readline() # 去除无用行
    for l in range(n):
        line = [x for x in f.readline().strip('\n').split(',')]
        line = line[2:] # 去除无用数据
        for i in range(len(line)-1): line[i] = float(line[i])
        line[3] = hour[int(line[3])]/100
        line[5] = weekday[int(line[5])]/100
        line[6] = workingday[int(line[6])]/100
        line[7] = weathersit[int(line[7])-1]/100
        line[-1] = int(line[-1])
        data.append(line) # 训练集
    return data

def read2(f,n): # 读取训练集、验证集
    data = []
    hour = [10,13,11,10,2,3,21,50,109,81,46,56,79,80,76,82,82,125,107,72,41,41,21,20]
    weekday = [33,61,71,54,0,0,43]
    workingday = [38,63]
    weathersit = [55,47,36,0]
    f.readline() # 去除无用行
    for l in range(n):
        line = [x for x in f.readline().strip('\n').split(',')]
        line = line[2:] # 去除无用数据
        for i in range(len(line)-1): line[i] = float(line[i])
        line[3] = hour[int(line[3])]/100
        line[5] = weekday[int(line[5])]/100
        line[6] = workingday[int(line[6])]/100
        line[7] = weathersit[int(line[7])-1]/100
        data.append(line) # 训练集
    return data

def init(): # 随机初始化参数
    v = [[uniform(0,1) for j in range(q)] for i in range(12)]
    gamma = [uniform(0,1) for i in range(q)]
    w = [uniform(0,1) for i in range(q)]
    theta = uniform(0,1)
    return v,gamma,w,theta

def mul1(x,v,gamma): # 输入层->隐层
    alpha = []
    for i in range(q): alpha.append(sum([x[j]*v[j][i] for j in range(len(x)-1)])+gamma[i])
    return alpha

def mul2(b,w,theta): # 隐层->输出层
    beta = theta
    for i in range(q): beta += w[i]*b[i]
    return beta

def Exp(x): # exp防爆
    if x > 100: return 1e40
    elif x < 100: return 1e-40
    else: return exp(x)

# 四种激活函数及其导数

def sig(alpha): # f(x) = 1/(1+e^-x)
    return 1/(1+Exp(-alpha))

def dsig(alpha): # f'(x) = f(x)*(1-f(x))
    return sig(alpha)*(1-sig(alpha))

def tanh(alpha): # f(x) = (e^x-e^-x)/(e^x+e^-x) = 2sigmoid(2x)-1
    return 2*sig(2*alpha)-1

def dtanh(alpha): # f'(x) = 1-f(x)^2
    return 1-tanh(alpha)**2

def elu(alpha): # f(x) = x if x > 0 else a(e^x-1)
    return alpha if alpha > 0 else 0.1*(Exp(alpha)-1)

def delu(alpha): # f'(x) = 1 if x > 0 else a*e^x
    return 1 if alpha > 0 else 0.1*(Exp(alpha))

def Relu(beta): # f(x) = max(x,0)
    return beta if beta > 0 else 0

def dRelu(beta): # f'(x) = 1 if x > 0 else 0
    return 1 if beta > 0 else 0

def BGD(data,eta,v,gamma,w,theta): # 批梯度下降
    w1 = [0 for i in range(q)]
    v1 = [[0 for i in range(q)] for j in range(12)]
    gamma1,theta1,E = [0 for i in range(q)],0,0
    for x in data:
        alpha,b = mul1(x,v,gamma),[] # 隐层输入和输出
        for i in range(q): b.append(elu(alpha[i])) # 激活函数：elu
        beta = mul2(b,w,theta) # 输出层输入
        y = round(Relu(beta)) # 激活函数：Relu，并转换成整数值
        g = dRelu(beta)*(x[-1]-y) # 输出层梯度
        e = []
        for i in range(q): e.append(delu(alpha[i])*w[i]*g) # 隐层梯度
        for i in range(q): w1[i] += g*b[i] # 累加各更新量
        theta1 += g
        for i in range(len(x)-1):
            for j in range(q):
                v1[i][j] += e[j]*x[i]
        for i in range(q): gamma1[i] += e[i]
    for i in range(q): w[i] += eta*w1[i]/len(data) # 批梯度下降
    theta += eta*theta1/len(data)
    for i in range(len(x)-1):
        for j in range(q):
            v[i][j] += eta*v1[i][j]/len(data)
    for i in range(q): gamma[i] += eta*gamma1[i]/len(data)
    return v,gamma,w,theta # 返回参数

def MGD(data,eta,v,gamma,w,theta): # Mini-batch梯度下降
    m,c = 10,0 # Mini-batch大小
    w1 = [0 for i in range(q)]
    v1 = [[0 for i in range(q)] for j in range(12)]
    gamma1,theta1,E = [0 for i in range(q)],0,0
    for x in data:
        alpha,b = mul1(x,v,gamma),[] # 隐层输入和输出
        for i in range(q): b.append(elu(alpha[i])) # 激活函数：elu
        beta = mul2(b,w,theta) # 输出层输入
        y = round(Relu(beta)) # 激活函数：Relu，并转换成整数值
        g = dRelu(beta)*(x[-1]-y) # 输出层梯度
        e = []
        for i in range(q): e.append(delu(alpha[i])*w[i]*g) # 隐层梯度
        for i in range(q): w1[i] += g*b[i] # 累加各更新量
        theta1 += g
        for i in range(len(x)-1):
            for j in range(q):
                v1[i][j] += e[j]*x[i]
        for i in range(q): gamma1[i] += e[i]
        c += 1
        if c == m: # 达到一次Mini-batch数据集大小
            for i in range(q): w[i] += eta*w1[i]/c # 梯度下降
            theta += eta*theta1/c
            for i in range(len(x)-1):
                for j in range(q):
                    v[i][j] += eta*v1[i][j]/c
            for i in range(q): gamma[i] += eta*gamma1[i]/c
            w1 = [0 for i in range(q)] # 重置各更新量为0
            v1 = [[0 for i in range(q)] for j in range(12)]
            gamma1,theta1 = [0 for i in range(q)],0
            c = 0
    if c != 0: # 对剩下的数据也进行一次梯度下降
        for i in range(q): w[i] += eta*w1[i]/c
        theta += eta*theta1/c
        for i in range(len(x)-1):
            for j in range(q):
                v[i][j] += eta*v1[i][j]/c
        for i in range(q): gamma[i] += eta*gamma1[i]/c
    return v,gamma,w,theta

def SGD(data,eta,v,gamma,w,theta): # 随机梯度下降
    E = 0
    for x in data:
        alpha,b = mul1(x,v,gamma),[] # 隐层输入和输出
        for i in range(q): b.append(elu(alpha[i])) # 激活函数：elu
        beta = mul2(b,w,theta) # 输出层输入
        y = round(Relu(beta)) # 激活函数：Relu，并转换成整数值
        g = dRelu(beta)*(x[-1]-y) # 输出层梯度
        e = []
        for i in range(q): e.append(delu(alpha[i])*w[i]*g) # 隐层梯度
        for i in range(q): w[i] += eta*g*b[i] # 梯度下降
        theta += eta*g
        for i in range(len(x)-1):
            for j in range(q):
                v[i][j] += eta*e[j]*x[i]
        for i in range(q): gamma[i] += eta*e[i]
    return v,gamma,w,theta

def validation(vali,v,gamma,w,theta): # 对验证集(也可对训练集)求损失函数
    E = 0
    for x in vali:
        alpha,b = mul1(x,v,gamma),[] # 隐层输入和输出
        for i in range(q): b.append(elu(alpha[i])) # 激活函数：elu
        beta = mul2(b,w,theta) # 输出层输入
        y = round(Relu(beta)) # 激活函数：Relu，并转换成整数值
        E += (x[-1]-y)**2 # 计算均方误差(MSE)
    return E/len(vali)

def BPNN(data,eta,count,f): # 误差反向传播算法
    v,gamma,w,theta = init() # 随机初始化参数
    bestv,bestgamma,bestw,besttheta,bestindex = v[:],gamma[:],w[:],theta,0
    minEt = 1e6
    for c in range(count):
        v,gamma,w,theta = f(data,eta,v,gamma,w,theta) # 更新一次参数
        Et = validation(data,v,gamma,w,theta) # 计算验证集损失函数
        if c%10==9: print("time: ",c+1," Et: ",Et)
        if Et <= minEt:
            bestv,bestgamma,bestw,besttheta,bestindex = deepcopy(v),gamma[:],w[:],theta,c
            minEt = Et
        #elif Et > 1.005*minEt or c-bestindex > 10: break # 早停算法
    return bestv,bestgamma,bestw,besttheta

def validation2(vali,v,gamma,w,theta): # 对验证集(也可对训练集)求损失函数
    for x in vali:
        alpha,b = mul1(x,v,gamma),[] # 隐层输入和输出
        for i in range(q): b.append(elu(alpha[i])) # 激活函数：elu
        beta = mul2(b,w,theta) # 输出层输入
        y = round(Relu(beta)) # 激活函数：Relu，并转换成整数值
        print(y) # 14 28 77 11 74

def pre(data):
    avg,cou = [0 for i in range(24)],[0 for j in range(24)]
    for x in data:
        avg[int(x[7])-1] += x[-1]
        cou[int(x[7])-1] += 1
    for i in range(4):
        if cou[i] == 0: print(0,0)
        else: print(avg[i]/cou[i],cou[i])

if __name__ == '__main__':
    f = open('train.csv')
    f2 = open('test.csv')
    count,eta = 150,0.0001 # 0.001 0.0001 0.000002
    data = read(f,100)
    vali = read2(f2,5)
    #pre(data)
    v,gamma,w,theta = BPNN(data,eta,count,MGD) # 梯度下降方法：MGD
    validation2(vali,v,gamma,w,theta)
