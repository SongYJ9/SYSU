import torch, copy

def check(matrix, chess): # 判断哪些位置可行
    matrix, l = matrix[0, 0], []
    for i in range(8):
        for j in range(8):
            if matrix[i][j] == 0: # 首先需要是空位置
                if i+1 < 8 and matrix[i+1][j] == -chess: # 下方为对方棋子
                    for k in range(i+2, 8): # 往棋盘下方遍历
                        # 如果是对方棋子，则继续
                        if matrix[k][j] == chess: # 如果是我方棋子，则(i,j)位置可行
                            l.append(i * 8 + j)
                            break
                        elif matrix[k][j] == 0: break # 如果是空位，则该位置不可行
                # 剩余七个方向同理，此处不再赘述
                if i-1 >= 0 and matrix[i-1][j] == -chess:
                    for k in range(i-2, -1, -1):
                        if matrix[k][j] == chess:
                            l.append(i * 8 + j)
                            break
                        elif matrix[k][j] == 0: break
                if j+1 < 8 and matrix[i][j+1] == -chess:
                    for k in range(j+2, 8):
                        if matrix[i][k] == chess:
                            l.append(i * 8 + j)
                            break
                        elif matrix[i][k] == 0: break
                if j-1 >= 0 and matrix[i][j-1] == -chess:
                    for k in range(j-2, -1, -1):
                        if matrix[i][k] == chess:
                            l.append(i * 8 + j)
                            break
                        elif matrix[i][k] == 0: break
                if i+1 < 8 and j+1 < 8 and matrix[i+1][j+1] == -chess:
                    for k in range(2, min(8-i, 8-j)):
                        if matrix[i+k][j+k] == chess:
                            l.append(i * 8 + j)
                            break
                        elif matrix[i+k][j+k] == 0: break
                if i+1 < 8 and j-1 >= 0 and matrix[i+1][j-1] == -chess:
                    for k in range(2, min(8-i, j+1)):
                        if matrix[i+k][j-k] == chess:
                            l.append(i * 8 + j)
                            break
                        elif matrix[i+k][j-k] == 0: break
                if i-1 >= 0 and j+1 < 8 and matrix[i-1][j+1] == -chess:
                    for k in range(2, min(i+1, 8-j)):
                        if matrix[i-k][j+k] == chess:
                            l.append(i * 8 + j)
                            break
                        elif matrix[i-k][j+k] == 0: break
                if i-1 >= 0 and j-1 >= 0 and matrix[i-1][j-1] == -chess:
                    for k in range(2, min(i+1, j+1)):
                        if matrix[i-k][j-k] == chess:
                            l.append(i * 8 + j)
                            break
                        elif matrix[i-k][j-k] == 0: break
    return list(set(l)) # 去重

class Env(object):

    def __init__(self):
        self.matrix = torch.zeros((1, 1, 8, 8), dtype=torch.int8)
        self.matrix[0, 0, 3, 3] = self.matrix[0, 0, 4, 4] = -1
        self.matrix[0, 0, 3, 4] = self.matrix[0, 0, 4, 3] = 1

    def reset(self): # 重置棋盘
        self.matrix = torch.zeros((1, 1, 8, 8), dtype=torch.int8)
        self.matrix[0, 0, 3, 3] = self.matrix[0, 0, 4, 4] = -1
        self.matrix[0, 0, 3, 4] = self.matrix[0, 0, 4, 3] = 1
        return copy.deepcopy(self.matrix), 1 # 返回棋盘，1代表黑棋先手

    def reverse(self, x, y, chess): # 翻转棋盘
        if x+1 < 8 and self.matrix[0, 0, x+1, y] == -chess: # 下方为对方棋子
            for k in range(x+2, 8): # 往棋盘下方遍历
                # 如果是对方棋子，则继续
                if self.matrix[0, 0, k, y] == chess: # 如果是我方棋子
                    for l in range(x+1, k): self.matrix[0, 0, l, y] = chess # 翻转
                    break
                elif self.matrix[0, 0, k, y] == 0: break # 如果是空位，则这一段不可翻转
        # 剩余七个方向同理，此处不再赘述
        if x-1 >= 0 and self.matrix[0, 0, x-1, y] == -chess:
            for k in range(x-2, -1, -1):
                if self.matrix[0, 0, k, y] == chess:
                    for l in range(x-1, k, -1): self.matrix[0, 0, l, y] = chess
                    break
                elif self.matrix[0, 0, k, y] == 0: break
        if y+1 < 8 and self.matrix[0, 0, x, y+1] == -chess:
            for k in range(y+2, 8):
                if self.matrix[0, 0, x, k] == chess:
                    for l in range(y+1, k): self.matrix[0, 0, x, l] = chess
                    break
                elif self.matrix[0, 0, x, k] == 0: break
        if y-1 >= 0 and self.matrix[0, 0, x, y-1] == -chess:
            for k in range(y-2, -1, -1):
                if self.matrix[0, 0, x, k] == chess:
                    for l in range(y-1, k, -1): self.matrix[0, 0, x, l] = chess
                    break
                elif self.matrix[0, 0, x, k] == 0: break
        if x+1 < 8 and y+1 < 8 and self.matrix[0, 0, x+1, y+1] == -chess:
            for k in range(2, min(8-x, 8-y)):
                if self.matrix[0, 0, x+k, y+k] == chess:
                    for l in range(1, k): self.matrix[0, 0, x+l, y+l] = chess
                    break
                elif self.matrix[0, 0, x+k, y+k] == 0: break
        if x+1 < 8 and y-1 >= 0 and self.matrix[0, 0, x+1, y-1] == -chess:
            for k in range(2, min(8-x, y+1)):
                if self.matrix[0, 0, x+k, y-k] == chess:
                    for l in range(1, k): self.matrix[0, 0, x+l, y-l] = chess
                    break
                elif self.matrix[0, 0, x+k, y-k] == 0: break
        if x-1 >= 0 and y+1 < 8 and self.matrix[0, 0, x-1, y+1] == -chess:
            for k in range(2, min(x+1, 8-y)):
                if self.matrix[0, 0, x-k, y+k] == chess:
                    for l in range(1, k): self.matrix[0, 0, x-l, y+l] = chess
                    break
                elif self.matrix[0, 0, x-k, y+k] == 0: break
        if x-1 >= 0 and y-1 >= 0 and self.matrix[0, 0, x-1, y-1] == -chess:
            for k in range(2, min(x+1, y+1)):
                if self.matrix[0, 0, x-k, y-k] == chess:
                    for l in range(1, k): self.matrix[0, 0, x-l, y-l] = chess
                    break
                elif self.matrix[0, 0, x-k, y-k] == 0: break
    
    def getReward(self, x, y): # 人工评定收益
        matrix, place = self.matrix[0, 0], x*8+y
        if place in [0, 7, 56, 63]: reward = 200 # 角落位置
        elif place in [1, 8, 9, 6, 14, 15, 48, 49, 57, 54, 55, 62]: reward = -150 # 角落旁的3个危险位置
        elif place in [2, 5, 16, 23, 40, 47, 58, 61]: reward = 100 # 边路的优势位置
        else: reward = 0
        return reward
    
    def step(self, x, y, chess):
        self.matrix[0, 0, x, y] = chess
        self.reverse(x, y, chess)
        reward, done = self.getReward(x, y), 0
        if len(check(self.matrix, 1)) == 0 and len(check(self.matrix, -1)) == 0: # 双方均无棋可下
            done = 1
            l = list(self.matrix.numpy().reshape(64))
            if l.count(chess) > l.count(-chess): reward = 1000.0 + (l.count(chess) - l.count(-chess))*100 # 胜利
            elif l.count(chess) < l.count(-chess): reward = -1000.0 - (l.count(-chess) - l.count(chess))*100 # 失败
            else: reward = 0.0 # 平局
        return copy.deepcopy(self.matrix), reward, done
    
    def countchess(self): # 输出黑白棋子数量
        l = list(self.matrix.numpy().reshape(64))
        print('------------------------')
        print('Black chess: ', l.count(1))
        print('White chess: ', l.count(-1))
    
    def display(self): # 输出当前棋盘
        print('----------------------------------------------------------')
        for i in range(8):
            for j in range(8): print('{0: >4}'.format(self.matrix[0, 0, i, j]), end = ' ')
            print()
        print('----------------------------------------------------------')
        self.countchess()
        
        
