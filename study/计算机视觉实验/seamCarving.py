# 放在data文件夹同目录下~

import cv2, imageio, os, numpy as np

def seamCarving(index, out_height, out_width):
    # 初始化
    inImage = cv2.imread('data/imgs/' + index + '.png').astype(np.float64)
    mask = cv2.imread('data/gt/' + index + '.png', 0).astype(np.float64)
    inHeight, inWidth = inImage.shape[: 2]
    outImage = np.copy(inImage)
    if not os.path.exists('data/seamCarvingOut'): os.mkdir('data/seamCarvingOut')
    if not os.path.exists('data/seamCarvingOut/' + index + 'gif'): os.mkdir('data/seamCarvingOut/' + index + 'gif')
    cnt = 1
    # 删列
    for _ in range(inWidth - out_width):
        energyMap = forward(outImage, mask)          # forward算法计算各列的能量
        seam = getSeam(energyMap)                    # 找一条能量最低的列（seam为这一列各个点横坐标的序列）
        cnt = getImage(index, outImage, seam, cnt)   # 生成gif的帧
        outImage = deleteSeam(outImage, seam)        # 图像删列
        mask = deleteMaskSeam(mask, seam)            # mask删列
    # 旋转图像，删行变成删列
    outImage, mask = np.rot90(outImage), np.rot90(mask)
    # 删行（实际上是删列）
    for _ in range(inHeight - out_height): 
        energyMap = forward(outImage, mask)
        seam = getSeam(energyMap)
        cnt = getImage(index, outImage, seam, cnt, 1)
        outImage = deleteSeam(outImage, seam)
        mask = deleteMaskSeam(mask, seam)
    # 旋转回来
    outImage = np.rot90(outImage, -1)
    # 输出图像和gif
    cv2.imwrite('data/seamCarvingOut/' + index + '.png', outImage.astype(np.uint8))
    getGif(index, cnt)

def cal(outImage, kernel): # 下面要用到的滤波操作
    b, g, r = cv2.split(outImage)
    return np.absolute(cv2.filter2D(b, -1, kernel)) + \
            np.absolute(cv2.filter2D(g, -1, kernel)) + \
            np.absolute(cv2.filter2D(r, -1, kernel))

def forward(outImage, mask):

    b, g, r = cv2.split(outImage) # BGR
    energyMap = np.absolute(cv2.Sobel(b, -1, 1, 0)) + np.absolute(cv2.Sobel(b, -1, 0, 1)) + \
                np.absolute(cv2.Sobel(g, -1, 1, 0)) + np.absolute(cv2.Sobel(g, -1, 0, 1)) + \
                np.absolute(cv2.Sobel(r, -1, 1, 0)) + np.absolute(cv2.Sobel(r, -1, 0, 1))
    energyMap[np.where(mask > 0)] = 1000000 # 保护的部分能量放大

    # 通过滤波核和滤波操作得到计算公式
    kernel1 = np.array([[0., 0., 0.], [-1., 0., 1.], [0., 0., 0.]], dtype=np.float64) # |cal(i, j+1) - cal(i, j-1)|
    kernel2 = np.array([[0., 0., 0.], [0., 0., 1.], [0., -1., 0.]], dtype=np.float64) # |cal(i, j+1) - cal(i+1, j)|
    kernel3 = np.array([[0., 0., 0.], [1., 0., 0.], [0., -1., 0.]], dtype=np.float64) # |cal(i, j-1) - cal(i+1, j)|
    matrix1, matrix2, matrix3 = cal(outImage, kernel1), cal(outImage, kernel2), cal(outImage, kernel3)
    
    # DP
    m, n = energyMap.shape
    for row in range(1, m):
        for col in range(n):
            e1 = 1e9 if col == 0 else energyMap[row-1, col-1] + matrix1[row-1, col-1] + matrix2[row-1, col-1]
            e2 = energyMap[row-1, col] + matrix1[row-1, col]
            e3 = 1e9 if col == n - 1 else energyMap[row-1, col+1] + matrix1[row-1, col+1] + matrix3[row-1, col+1]
            energyMap[row, col] += min(e1, e2, e3)
    return energyMap

def getSeam(energyMap): # 找到能量最小的路径
    m, n = energyMap.shape
    seam = np.zeros(m, dtype=np.uint32) # 存储最后路径的一个列表
    seam[-1] = np.argmin(energyMap[-1])
    for row in range(m-2, -1, -1): # 从后往前找
        prev = seam[row+1]
        if prev == 0:
            seam[row] = np.argmin(energyMap[row, :2])
        elif prev == n-1:
            seam[row] = np.argmin(energyMap[row, prev-1:n]) - 1 + prev
        else: # np.argmin() 返回 [0, 1, 2], 之后-1变成 [-1, 0, 1], 即左中右, 最后加上原来的x坐标得到真实坐标
            seam[row] = np.argmin(energyMap[row, prev-1:prev+2]) - 1 + prev
    return seam

def getImage(index, outImage, seam, cnt, m=0):
    for i in range(outImage.shape[0]):
        for k in range(3):
            outImage[i, seam[i], k] = 255 if k == 2 else 0 # 删除部分涂红
    if m: outImage = np.rot90(outImage, -1)
    cv2.imwrite('data/seamCarvingOut/' + index + 'gif/' + index + '_' + str(cnt) + '.png', outImage.astype(np.uint8))
    return cnt+1 # 返回下一张图的index

def deleteSeam(outImage, seam): # 删除图片的一列
    for i in range(outImage.shape[0]):
        for k in range(3):
            outImage[i, :-1, k] = np.delete(outImage[i, :, k], seam[i])
    return np.delete(outImage, -1, axis=1)

def deleteMaskSeam(mask, seam): # 删除mask的一列
    for i in range(mask.shape[0]):
        mask[i, :-1] = np.delete(mask[i, : ], seam[i])
    return np.delete(mask, -1, axis=1)

def getGif(index, cnt):
    gif_images = []
    for i in range(1, cnt):
        gif_images.append(imageio.imread('data/seamCarvingOut/' + index + 'gif/' + index + '_' + str(i) + '.png'))
    imageio.mimsave('data/seamCarvingOut/' + index + '.gif', gif_images, fps=10) # 1秒10张图

seamCarving('946', 80, 150) # index, height, width