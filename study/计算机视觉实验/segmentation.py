# 放在data文件夹同目录下~

import cv2, os, numpy as np, random

def cal(x, y):
    return ((x[0]-y[0])**2 + (x[1]-y[1])**2 + (x[2]-y[2])**2) ** (1/2)

def find(fa, k):
    if fa[k] != k:
        fa[k] = find(fa, fa[k])
    return fa[k]

def getMiddle(index, p):
    n, m = p.shape[:2]
    middleImage, l, s = np.zeros((n, m, 3), dtype=np.uint32), [], []
    for i in range(n):
        for j in range(m):
            if p[i, j] not in l: l.append(p[i, j])
    for i in range(len(l)):
        s.append((random.randint(0, 255), random.randint(0, 255), random.randint(0, 255)))
    for i in range(n):
        for j in range(m):
            middleImage[i, j, :] = s[l.index(p[i, j])]
    cv2.imwrite('data/segmentationOut/' + index + '_middle.png', middleImage.astype(np.float64))
 
def test(index, k):
    # 初始化
    inImage = cv2.imread('data/imgs/' + index + '.png').astype(np.float64)
    mask = cv2.imread('data/gt/' + index + '.png', 0).astype(np.uint32)
    if not os.path.exists('data/segmentationOut'): os.mkdir('data/segmentationOut')
    n, m = inImage.shape[:2]
    fa, size, threshold = np.zeros(n*m, dtype=np.uint32), np.zeros(n*m, dtype=np.uint32), np.zeros(n*m, dtype=np.float)
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
    p, l = np.zeros((n, m), dtype=np.uint32), []
    for i in range(n):
        for j in range(m):
            p[i, j] = find(fa, i*m+j)
            if p[i, j] not in l: l.append(p[i, j])
    getMiddle(index, p)
    # 判断区域是否为前景/背景
    l1, l2, l3 = [0] * len(l), [0] * len(l), [0] * len(l)
    for i in range(n):
        for j in range(m):
            if mask[i, j] == 255: l1[l.index(p[i, j])] += 1
            else: l2[l.index(p[i, j])] += 1
    for i in range(len(l)):
        if l1[i]+l2[i] > 0 and l1[i] / (l1[i]+l2[i]) >= 0.5: l3[i] = 255
        else: l3[i] = 0
    # 计算IOU
    a, b, c = 0, 0, 0
    for i in range(n):
        for j in range(m):
            p[i, j] = l3[l.index(p[i, j])]
            if p[i, j] == 255 and mask[i, j] == 255: c += 1
            elif p[i, j] == 255: a += 1
            elif mask[i, j] == 255: b += 1
    return p, len(l), c/(a+b+c)

def segment(index):
    k = 500
    p, l, IOU = test(index, k)
    while l < 50 or l > 70:
        if l > 70: k += 50
        else: k -= 50
        p, l, IOU = test(index, k)
    cv2.imwrite('data/segmentationOut/' + index + '.png', p.astype(np.float64))
    mask = cv2.imread('data/gt/' + index + '.png', 0).astype(np.uint32)
    cv2.imwrite('data/segmentationOut/' + index + '_mask.png', mask.astype(np.float64))
    print(l, k, IOU)

segment('46')
segment('146')
segment('246')
segment('346')
segment('446')
segment('546')
segment('646')
segment('746')
segment('846')
segment('946')