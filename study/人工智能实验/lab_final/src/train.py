import torch, tqdm, time
import Agent, Env, Memory

# auto: "cuda" if torch.cuda.is_available() else "cpu"; GPU: "cuda"; CPU: "cpu"
device = torch.device("cuda:1" if torch.cuda.is_available() else "cpu")

env = Env.Env() # 环境
state, chess = env.reset()
agent1 = Agent.Agent(device, chess) # 黑棋AI
agent2 = Agent.Agent(device, -chess) # 白棋AI
memory1 = Memory.Memory(5000, device) # 经验池
memory2 = Memory.Memory(5000, device) # 经验池

progressive = tqdm.tqdm(range(12000), total = 12000, ncols = 80, leave = False, unit="b") # 可视化进度条
for step in progressive: # 前 12000 次 agent 进行瞎玩，不学习、不训练网络，仅用于填满初始经验池
    if chess == 1:
        action = agent1.run(state.float().to(device))
        if action != -1:
            Next, reward, done = env.step(action//8, action%8, chess)
            memory1.push(state, action, Next, reward) # 储存（s,a,r）到经验池中
            state = Next
        chess = -chess
    else:
        action = agent2.run(state.float().to(device))
        if action != -1:
            Next, reward, done = env.step(action//8, action%8, chess)
            memory2.push(state, action, Next, reward) # 储存（s,a,r）到经验池中
            state = Next
        chess = -chess
    if done: state, chess = env.reset()
        
state, chess = env.reset()
progressive = tqdm.tqdm(range(1000000), total = 1000000, ncols = 80, leave = False, unit="b") # 可视化进度条
for step in progressive: # 后 1000000 次 agent 在玩的过程中训练网络
    if chess == 1:
        action = agent1.run(state.float().to(device))
        if action != -1:
            Next, reward, done = env.step(action//8, action%8, chess)
            memory1.push(state, action, Next, reward) # 储存（s,a,r）到经验池中
            state = Next
        chess = -chess
    else:
        action = agent2.run(state.float().to(device))
        if action != -1:
            Next, reward, done = env.step(action//8, action%8, chess)
            memory2.push(state, action, Next, reward) # 储存（s,a,r）到经验池中
            state = Next
        chess = -chess
    if done: state, chess = env.reset()
        
    loss1 = agent1.learn(memory1, 64, agent2) # 训练
    loss2 = agent2.learn(memory2, 64, agent1) # 训练
    if step % 500 == 0: 
        agent1.sync() # 将策略网络中的权重同步到目标网络
        agent2.sync() # 将策略网络中的权重同步到目标网络   
    if step % 50000 == 0: 
        agent1.save('Models/model_first_' + str(step//50000+1) + '.pkl')
        agent2.save('Models/model_second_' + str(step//50000+1) + '.pkl')
