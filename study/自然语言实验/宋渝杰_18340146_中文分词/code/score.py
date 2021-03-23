import codecs, torch
import torch.autograd as autograd, torch.nn as nn, torch.optim as optim
from tqdm import tqdm

def test_tags(root): # 验证集标签
    f = codecs.open(root, 'r', encoding = 'utf-8')
    data = []
    for s in f.readlines():
        s, l = s.strip('\n').split(), []
        for x in s:
            if len(x) == 1: l.append(0)
            else:
                l.append(1)
                for i in range(len(x)-2): l.append(2)
                l.append(3)
        data.append(l)
    return data

test1 = test_tags('result.txt')
test2 = test_tags('msr_test_gold.utf8')

def cou(l): # 返回词数
    return l.count(0)+l.count(1)

def correct(l1, l2): # 返回正确判断词数
    num = 0
    for i in range(min(len(l1),len(l2))):
        if l1[i] == l2[i] and l1[i] == 0: num += 1 # 'S'
        elif l1[i] == l2[i] and l1[i] == 1: # 'B'
            j = i
            while 1:
                j += 1
                if l1[j] == l2[j] and l1[j] == 3: # 'E' 
                    num += 1
                    break
                elif l1[j] == l2[j] and l1[j] == 2: continue # 'M'
                else: break
    return num

ans = 0.    
for i in range(len(test1)):
    p, r = correct(test1[i], test2[i])/cou(test1[i]), correct(test1[i], test2[i])/cou(test2[i]) # 两个指标
    if not p+r == 0: ans += (2*p*r)/(p+r) # F1（防止除0）
ans = round(ans/len(test1), 3)
print('F1 Score: ', ans)