import torch, time, pygame
import Agent, Env, Memory

# auto: "cuda" if torch.cuda.is_available() else "cpu"; GPU: "cuda"; CPU: "cpu"
device = torch.device("cuda:1" if torch.cuda.is_available() else "cpu")

# First = 1 代表人先手；First = -1 代表我方AI先手
First = -1
agent = Agent.Agent(device, -First, 'model/first.pkl') if First == -1 else Agent.Agent(device, -First, 'model/second.pkl')

env = Env.Env() # 环境
state, chess = env.reset()

background = pygame.image.load('hello.png')
screen = pygame.display.set_mode((500, 500))
pygame.display.set_caption('Do you wanna dance~')

def show(matrix, valid=[], pos=(-1, -1)):
    screen.blit(background, (0, 0))
    # 画线
    for line in [((50, 50), (50, 450)), ((50, 50), (450, 50)), ((50, 450), (450, 450)), ((450, 50), (450, 450))]:
        pygame.draw.line(screen, (0, 0, 0), line[0], line[1], 4) # 画外框粗线
    for i in range(2, 9):
        pygame.draw.line(screen, (0, 0, 0), (50 * i, 50), (50 * i, 450)) # 画内框细线
        pygame.draw.line(screen, (0, 0, 0), (50, 50 * i), (450, 50 * i))
    # 画黑白棋子
    for i in range(8):
        for j in range(8):
            if matrix[i, j] == 1:
                pygame.draw.circle(screen, (0, 0, 0), (int((j + 1.5) * 50), int((i + 1.5) * 50)), 16)
            elif matrix[i, j] == -1:
                pygame.draw.circle(screen, (255, 255, 255), (int((j + 1.5) * 50), int((i + 1.5) * 50)), 16)
    # 画可选位置
    for point in valid:
        pygame.draw.circle(screen, (0, 255, 0), (int((point % 8 + 1.5) * 50), int((point // 8 + 1.5) * 50)), 16)
    # 画上一步
    if pos != (-1, -1):
        pygame.draw.circle(screen, (255, 0, 0), (int((pos[1] + 1.5) * 50), int((pos[0] + 1.5) * 50)), 6)
    pygame.display.flip()

judge, running, point = 0, 1, (-1, -1)
show(state[0, 0])
while running:
    if First == 1:
        if chess == 1:  
            l = Env.check(state, chess)
            if len(l) == 0: chess = -chess
            else:
                show(state[0, 0], l, (point[0], point[1]))
                for event in pygame.event.get():
                    if event.type == pygame.QUIT:
                        running = False
                    elif event.type == pygame.MOUSEBUTTONDOWN:
                        choosePoint = (int(event.pos[1] / 50.0 - 1), int(event.pos[0] / 50.0 - 1))
                        if choosePoint[0] >= 0 and choosePoint[0] < 8 and choosePoint[1] >= 0 and \
                           choosePoint[1] < 8 and choosePoint[0]*8+choosePoint[1] in l:
                            point = choosePoint
                            Next, reward, done = env.step(point[0], point[1], chess)
                            state = Next
                            chess = -chess
                            show(state[0, 0], [], (point[0], point[1]))
                            env.countchess()
                            if done: break
        else:
            time.sleep(0.5)
            action = agent.run(state.float().to(device))
            if action != -1:
                point = (action//8, action%8)
                Next, reward, done = env.step(action//8, action%8, chess)
                state = Next
                show(state[0, 0], Env.check(state, -chess), point)
                env.countchess()
            chess = -chess
            if done: break
    else:
        if chess == 1:  
            time.sleep(0.5)
            action = agent.run(state.float().to(device))
            if action != -1:
                point = (action//8, action%8)
                Next, reward, done = env.step(action//8, action%8, chess)
                state = Next
                show(state[0, 0], Env.check(state, -chess), point)
                env.countchess()
            chess = -chess
            if done: break
        else:
            l = Env.check(state, chess)
            if len(l) == 0: chess = -chess
            else:
                show(state[0, 0], l, (point[0], point[1]))
                for event in pygame.event.get():
                    if event.type == pygame.QUIT:
                        running = False
                    elif event.type == pygame.MOUSEBUTTONDOWN:
                        choosePoint = (int(event.pos[1] / 50.0 - 1), int(event.pos[0] / 50.0 - 1))
                        if choosePoint[0] >= 0 and choosePoint[0] < 8 and choosePoint[1] >= 0 and \
                           choosePoint[1] < 8 and choosePoint[0]*8+choosePoint[1] in l:
                            point = choosePoint
                            Next, reward, done = env.step(point[0], point[1], chess)
                            state = Next
                            chess = -chess
                            show(state[0, 0], [], (point[0], point[1]))
                            env.countchess()
                            if done: break

env.display()
time.sleep(1000)
