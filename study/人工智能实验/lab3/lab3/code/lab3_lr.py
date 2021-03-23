from math import exp,log
from time import sleep

def read(f,t,v): # 读取训练集、验证集
    data,vali = [],[]
    for l in range(t):
        line = [float(x) for x in f.readline().strip('\n').split(',')]
        line.insert(-1,1) # 添加一维常数项1
        data.append(line)
    for l in range(v):
        line = [float(x) for x in f.readline().strip('\n').split(',')]
        line.insert(-1,1) # 添加一维常数项1
        vali.append(line)
    return data,vali

def dot(w,x): # 向量点积
    ans = 0
    for i in range(41): ans += w[i]*x[i]
    return ans

def Exp(t):
    if t >= 100: return 1e40
    elif t <= -100: return 1e-40
    else: return exp(t)

def pi(w,x): # pi(x)
    return 1/(1+Exp(-dot(w,x))) # 1/(1+exp(-w*x))

def L(data,w): # 对数似然函数
    ans = 0
    for x in data: # sum(y*w*x-log(1+exp(w*x))
        t = dot(w,x)
        ans += x[-1]*t-log(1+Exp(t))
    return ans

def Gra(data,w): # 梯度
    ans = [0 for i in range(41)]
    for x in data: 
        t = x[-1]-pi(w,x) # -sum((y-pi(x))*x)
        for i in range(41): ans[i] -= t*x[i]
    return ans

def update(data,w,eta): # 更新
    g = Gra(data,w) 
    for i in range(41): w[i] -= eta*g[i] # 梯度下降

def LR(data,eta,count): # 逻辑回归count次
    w = [0 for i in range(41)]
    for i in range(count):
        Lost = L(data,w)
        update(data,w,eta)
        if abs(Lost-L(data,w)) < 1e-2: break
    return w

def validation(vali,w):
    num = 0
    for x in vali:
        if x[-1] == 1 and pi(w,x) > 0.5: num += 1
        elif x[-1] == 0 and pi(w,x) < 0.5: num += 1
    print('{:.2f}%'.format(num/len(vali)*100))

if __name__ == '__main__':
    f = open('train.csv')
    count,eta = 100,0.00002
    n,t = 8000,6000
    v = n-t
    data,vali = read(f,t,v)
    w = LR(data,eta,count)
    validation(vali,w)
