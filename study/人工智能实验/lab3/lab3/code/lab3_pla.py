def read(f,t,v): # 读取训练集、验证集
    data,vali = [],[]
    for l in range(t):
        line = [float(x) for x in f.readline().strip('\n').split(',')]
        if line[-1] == 0: # 修改标签为-1
            line[-1] = -1
        data.append(line)
    for l in range(v):
        line = [float(x) for x in f.readline().strip('\n').split(',')]
        if line[-1] == 0: # 修改标签为-1
            line[-1] = -1
        vali.append(line)
    return data,vali

def PLA(data,eta,count): # PLA
    w,b = [0 for i in range(40)],0
    for i in range(count): # 最大迭代count次
        judge = 0
        for x in data:
            ans = 0
            for j in range(40): ans += w[j]*x[j]
            if (ans+b)*x[-1] <= 0: # 误判断点
                for j in range(40): w[j] += eta*x[-1]*x[j] # 更新参数
                b += eta*x[-1]
                judge = 1
                break
        if judge == 0: break # 没有误分类点
    return w,b

def validation(vali,w,b):
    num = 0
    for x in vali:
        ans = 0
        for j in range(40): ans += w[j]*x[j]
        if (ans+b)*x[-1] > 0: num += 1
    print("{:.2f}%".format(num/len(vali)*100))
    
if __name__ == '__main__':
    f = open('train.csv')
    count,eta = 18000,1
    n,t = 8000,5600
    v = n-t
    data,vali = read(f,t,v)
    w,b = PLA(data,eta,count)
    validation(vali,w,b)
    
