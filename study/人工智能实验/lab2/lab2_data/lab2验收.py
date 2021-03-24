# -*- coding: utf-8 -*-

from math import log
import copy

def splitData(data,index,value): # 筛选特征index等于value的数据
    rData = []
    for l in data: # 遍历原数据所有行
        if l[index] == value:
            rData.append(l[:index]+l[index+1:]) # 同时删除特征index
    return rData

def splitData2(data,index,value): # 筛选特征index不等于value的数据
    rData = []
    for l in data: # 遍历原数据所有行
        if l[index] != value:
            rData.append(l[:index]+l[index+1:]) # 同时删除特征index
    return rData

def selectData(data,index,value): # 筛选特征index等于value的数据
    rData = []
    for l in data: # 遍历原数据所有行
        if l[index] == value:
            rData.append(l[:]) # 不删除特征index
    return rData

def selectData2(data,index,value): # 筛选特征index不等于value的数据
    rData = []
    for l in data: # 遍历原数据所有行
        if l[index] != value:
            rData.append(l[:]) # 不删除特征index
    return rData

def cnt(node): # 叶节点判断，多数原则
    return '0' if node.count('0') >= node.count('1') else '1'

def readTrain(f,t): # 读取训练数据
    feature = ['buying', 'maint', 'doors', 'persons', 'lug_boot', 'safety', 'Label'] # 读取特征
    data = []
    for i in range(t):
        data.append(f.readline().strip('\n').split(',')) # 读取数据
    return data,feature

def validation(vali,tree,m,data): # 验证
    num = 0 # 正确个数
    for row in vali: # 遍历验证集所有行
        copyTree = copy.deepcopy(tree)
        copyData = copy.deepcopy(data)
        while 1:
            j = 0 # 判断是否有路可走
            k = list(copyTree.keys())[0]
            for k2 in copyTree[k].keys(): # 遍历目前节点所有分支
                #print(k,vali[m[k]],k2) # 当前节点、要走的分支、当前遍历的分支
                if row[m[k]] == k2 or (k2.split(' ')[0] == 'not' and row[m[k]] != k2.split(' ')[1]): # 验证特征与该分支符合
                    copyTree = copyTree[k][k2] # 走到下一个节点
                    copyData = selectData(copyData,m[k],k2) # 筛选出满足走过的路所有条件的数据集
                    j = 1
                    break
            if j == 0: # 无路可走
                node = [l[-1] for l in copyData] # 统计标签
                if row[-1] == cnt(node): # 多数原则判断后和验证标签相同
                    num += 1
                break
            if type(copyTree) == str: # 走到叶节点
                if copyTree == row[-1]:
                    num += 1
                break
    return num/len(vali) # 返回正确率

def test(vali,tree,m,data): # 测试
    fr = open('18340146_songyujie_test.csv',mode='w')
    for row in vali: # 遍历测试集所有行
        copyTree = copy.deepcopy(tree)
        copyData = copy.deepcopy(data)
        while 1:
            j = 0 # 判断是否有路可走
            k = list(copyTree.keys())[0]
            for k2 in copyTree[k].keys(): # 遍历目前节点所有分支
                #print(k,row[m[k]],k2) # 当前节点、要走的分支、当前遍历的分支
                if row[m[k]] == k2 or (k2.split(' ')[0] == 'not' and row[m[k]] != k2.split(' ')[1]): # 测试特征与该分支符合
                    copyTree = copyTree[k][k2] # 走到下一个节点
                    copyData = selectData(copyData,m[k],k2) # 筛选出满足走过的路所有条件的数据集
                    j = 1
                    break
            if j == 0: # 无路可走
                node = [l[-1] for l in copyData] # 统计标签
                fr.write(str(row[0:6])+','+cnt(node)+'\n')
                break
            if type(copyTree) == str: # 走到叶节点
                fr.write(str(row[0:6])+','+copyTree+'\n')
                break
    fr.close()

def HD(data): # 信息熵 H(D)
    D = {}
    for l in data: # 统计0和1的个数
        if l[-1] not in D.keys(): 
            D[l[-1]] = 0
        D[l[-1]] += 1
    ans = 0.0
    for key in D:
        p = D[key]/len(data) # 按照公式算～
        ans -= p*log(p,2) # p(d)log(p(d))，这里以2为底
    return ans

def HD_A(data,index): # 条件熵 H(D|A)
    Vals = set([l[index] for l in data]) # 计算特征index有多少取值
    ans = 0.0
    for value in Vals: # 遍历a
        subData = splitData(data,index,value) # 划分出关于特征index的子数据集
        p = len(subData)/len(data) # p(a)
        ans += p*HD(subData) # p(a)*H(D|A=a)
    return ans

def GD_A(data,index): # 信息增益 g(D,A)
    return HD(data) - HD_A(data,index)

def ID3(data): # ID3
    maxGD_A = 0.0
    bestIndex = -1 # 信息增益最大的特征下标
    for index in range(len(data[0])-1): # 遍历所有特征
        gd_a = GD_A(data,index) # 计算信息增益
        if gd_a > maxGD_A:
            maxGD_A = gd_a
            bestIndex = index
    return bestIndex # 返回决策点特征下标

def SplitInfo(data,index): # SplitInfo(D,A)
    Vals = set([l[index] for l in data]) # 计算特征index有多少取值
    ans = 0.0
    for value in Vals: # 遍历a
        subData = splitData(data,index,value) # 划分出关于特征index的子数据集
        p = len(subData)/len(data) # p(a)
        ans -= p*log(p,2) # p(a)*log(p(a))，这里以2为底
    return ans

def C45(data): # C4.5
    maxGD_A_Split = 0.0
    bestIndex = -1 # 信息增益率最大的特征下标
    for index in range(len(data[0])-1): # 遍历所有特征
        gd_a_Split = GD_A(data,index)/SplitInfo(data,index) # 计算信息增益率
        if gd_a_Split > maxGD_A_Split:
            maxGD_A_Split = gd_a_Split
            bestIndex = index
    return bestIndex # 返回决策点特征下标

def GINI(data,index):
    Vals = set([l[index] for l in data]) # 计算特征index有多少取值
    bestGINI = 1e6
    bestVal = -1
    for value in Vals: # 遍历a
        subData1 = splitData(data,index,value) # 划分出关于特征index的子数据集
        subData2 = splitData2(data,index,value) # 划分出关于特征index的子数据集
        p1 = len(subData1)/len(data) # p(a)
        p2 = len(subData2)/len(data) # p(a)
        if p1 == 1: # 说明之前成为过最优分割点
            continue
        num1 = [l[-1] for l in subData1]
        num2 = [l[-1] for l in subData2]
        ans = p1*(2*num1.count('1')/len(subData1)*num1.count('0')/len(subData1))
        ans += p2*(2*num2.count('1')/len(subData2)*num2.count('0')/len(subData2))
        print(index,value,ans)
        if ans < bestGINI:
            bestGINI = ans
            bestVal = value
    return bestGINI,bestVal

def CART(data): # CART
    minCART = 1e6
    bestIndex = -1 # 基尼指数最小的特征下标
    bestVal = -1
    for index in range(len(data[0])-1): # 遍历所有特征
        cart,val = GINI(data,index)
        if cart < minCART:
            minCART = cart
            bestIndex = index
            bestVal = val
    return bestIndex,bestVal # 返回决策点特征下标

def builtTree(data,feature,Func):
    node = [l[-1] for l in data]
    if node.count(node[0]) == len(node): # 全为一种特征
        return node[0]
    if len(data[0]) == 1: # 只剩一种特征
        return cnt(node)
    bestIndex = Func(data) # 选出决策点
    bestFeature = feature[bestIndex] # 决策点特征
    tree = {bestFeature:{}}
    Vals = set([l[bestIndex] for l in data]) # 这个特征的所有取值
    for value in Vals:
        copyFeature = feature[:bestIndex]+feature[bestIndex+1:] # 去除这个特征
        tree[bestFeature][value] = builtTree(splitData(data,bestIndex,value),copyFeature,Func) # 递归建树
    return tree

def builtTreeUsingCART(data,feature): # CART
    node = [l[-1] for l in data]
    if node.count(node[0]) == len(node): # 全为一种标签
        return node[0]
    bestIndex,bestVal = CART(data) # 选出决策点，最优切分点
    if bestIndex == -1: # 无法继续切分
        return cnt(node) # 多数原则判断标签
    print(bestIndex,bestVal,'\n')
    bestFeature = feature[bestIndex] # 决策点特征
    tree = {bestFeature:{}}
    data1 = selectData(data,bestIndex,bestVal) # 划分子数据集（A=a）
    tree[bestFeature][bestVal] = builtTreeUsingCART(data1,feature) # 递归建树
    data2 = selectData2(data,bestIndex,bestVal) # 划分子数据集（A!=a）
    tree[bestFeature]['not '+bestVal] = builtTreeUsingCART(data2,feature) # 递归建树
    return tree

if __name__ == '__main__':
    f = open('DecisionTree验收数据.csv')
    n,t = 18,15 # 总数、测试集大小
    v = n-t # 验证集大小
    data,feature = readTrain(f,t) # 读取训练数据
    tree = builtTreeUsingCART(data,feature) # CART树
    m = dict(zip(feature,range(7))) # 存一下特征和下标的映射
    vali = [] # 验证集
    for i in range(v):
        vali.append(f.readline().strip('\n').split(','))
    print(tree)
    test(vali,tree,m,data) # CART树
    f.close()
