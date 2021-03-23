from random import uniform
from math import exp
from copy import deepcopy

q = 5 # 隐层神经元数量

def read(f,n,t): # 读取训练集、验证集
    data,vali = [],[]
    season = [72,157,187,152] # 数据预处理
    month = [55,74,87,131,182,199,189,186,177,166,142,118]
    hour = [43,26,18,10,5,14,57,157,263,164,130,155,189,190,182,188,234,350,322,236,173,134,104,69]
    holiday = [144,125]
    weekday = [143,145,147,137,142,147,142]
    workingday = [141,144]
    weathersit = [155,135,86,36]
    f.readline() # 去除无用行
    for l in range(n):
        line = [x for x in f.readline().strip('\n').split(',')]
        line = line[2:] # 去除无用数据
        for i in range(len(line)-1): line[i] = float(line[i])
        line[0] = season[int(line[0])-1]/100 # 数据预处理
        line[2] = month[int(line[2])-1]/100
        line[3] = hour[int(line[3])]/100
        line[4] = holiday[int(line[4])]/100
        line[5] = weekday[int(line[5])]/100
        line[6] = workingday[int(line[6])]/100
        line[7] = weathersit[int(line[7])-1]/100
        line[-1] = int(line[-1])
        if l%100 < t: data.append(line) # 训练集
        else: vali.append(line) # 验证集
    return data,vali

def read2(f,n): # 读取训练集、验证集
    data = []
    season = [72,157,187,152] # 数据预处理
    month = [55,74,87,131,182,199,189,186,177,166,142,118]
    hour = [43,26,18,10,5,14,57,157,263,164,130,155,189,190,182,188,234,350,322,236,173,134,104,69]
    holiday = [144,125]
    weekday = [143,145,147,137,142,147,142]
    workingday = [141,144]
    weathersit = [155,135,86,36]
    f.readline() # 去除无用行
    for l in range(n):
        line = [x for x in f.readline().strip('\n').split(',')]
        line = line[2:] # 去除无用数据
        for i in range(len(line)-1): line[i] = float(line[i])
        line[0] = season[int(line[0])-1]/100 # 数据预处理
        line[2] = month[int(line[2])-1]/100
        line[3] = hour[int(line[3])]/100
        line[4] = holiday[int(line[4])]/100
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
    m,c = 100,0 # Mini-batch大小
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

def BPNN(data,vali,eta,count,f): # 误差反向传播算法
    v,gamma,w,theta = init() # 随机初始化参数
    bestv,bestgamma,bestw,besttheta,bestindex = v[:],gamma[:],w[:],theta,0
    minEv = 1e6
    for c in range(count):
        v,gamma,w,theta = f(data,eta,v,gamma,w,theta) # 更新一次参数
        Et = validation(data,v,gamma,w,theta) # 计算验证集损失函数
        Ev = validation(vali,v,gamma,w,theta) # 计算验证集损失函数
        if c%10==9: print("time: ",c+1," Ev: ",Ev,Et)
        if Ev <= 0.995*minEv:
            bestv,bestgamma,bestw,besttheta,bestindex = deepcopy(v),gamma[:],w[:],theta,c
            minEv = Ev
        elif Ev > 1.005*minEv or c-bestindex > 10:
            print(c+1)
            break # 早停算法
    return bestv,bestgamma,bestw,besttheta

def validation2(vali,v,gamma,w,theta): # 对验证集(也可对训练集)求损失函数
    for x in vali:
        alpha,b = mul1(x,v,gamma),[] # 隐层输入和输出
        for i in range(q): b.append(elu(alpha[i])) # 激活函数：elu
        beta = mul2(b,w,theta) # 输出层输入
        y = round(Relu(beta)) # 激活函数：Relu，并转换成整数值
        print(y) # 14 28 77 11 74

if __name__ == '__main__':
    f = open('train2.csv')
    f2 = open('test.csv')
    count,eta = 1000,0.0001 # 0.001 0.0001 0.000002
    n,t = 8619,70
    data,vali = read(f,n,t)
    v,gamma,w,theta = BPNN(data,vali,eta,count,MGD) # 梯度下降方法：MGD
    vali2 = read2(f2,5)
    validation2(vali2,v,gamma,w,theta)
