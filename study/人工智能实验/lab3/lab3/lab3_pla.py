def read(f,t): # 读取训练集、验证集
    data = []
    for l in range(t):
        line = [float(x) for x in f.readline().strip('\n').split(',')]
        if line[-1] == 0: # 修改标签为-1
            line[-1] = -1
        data.append(line)
    return data

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
        print("time: ",i+1)
        for x in data:
            ans = 0
            for j in range(40): ans += w[j]*x[j]
            if ans+b > 0: print(1,end=" ")
            else: print(-1,end=" ")
        print("")

def validation(vali,w,b):
    num = 0
    for x in vali:
        ans = 0
        for j in range(40): ans += w[j]*x[j]
        if (ans+b)*x[-1] > 0: num += 1
    print("{:.2f}%".format(num/len(vali)*100))
    
if __name__ == '__main__':
    f = open('lab3验收数据.csv')
    count,eta = 10,1
    n,t = 5,5
    data = read(f,t)
    PLA(data,eta,count)
    
