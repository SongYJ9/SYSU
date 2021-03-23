import torch, random, time
import torch.nn.functional as F
import Memory, DQN, Env

class Agent(object):

    def __init__(self, device, chess, model = ''):
        self.gamma = 0.99
        self.eps = 1
        self.chess = chess
        if model == '': self.policy = DQN.DQN().to(device) # 策略DQN
        else: 
            print(model)
            # GPU: torch.load(model, map_location=lambda storage, loc: storage.cuda(0))
            # CPU: torch.load(model, map_location=lambda storage, loc: storage)
            self.policy = torch.load(model, map_location=lambda storage, loc: storage)
            self.eps = 0.0
        self.target = DQN.DQN().to(device) # 目标DQN，减少目标计算与当前值的相关性
        self.target.load_state_dict(self.policy.state_dict()) # 将策略网络中的权重同步到目标网络
        self.optimizer = torch.optim.SGD(self.policy.parameters(), lr = 0.001, momentum = 0.9, weight_decay = 5e-4) # torch.optim.Adam(self.policy.parameters(), lr = 0.001, eps = 1.5e-4) # 优化器
        self.target.eval() # 验证模式
        
    def run(self, matrix):
        l = Env.check(matrix, self.chess) # 找出可选位置
        if len(l) == 0: return -1
        if random.random() > self.eps: # 1-eps概率取最大值
            with torch.no_grad(): # 暂时关闭梯度计算，起且仅起到加速作用
                out = self.policy(matrix).to('cpu')
                choice = [out[0, i] for i in l] # 筛选出可选位置的预估收益
                return l[choice.index(max(choice))] # 选择预估收益最大的动作
        return random.choice(l) # eps概率随机

    def learn(self, memory, batch_size, anotherAgent):
        self.eps = max(self.eps-1e-5, 0.1)
        states, actions, nexts, rewards = memory.sample(batch_size) # 在经验池中选取一组样本(批处理)
        values = self.policy(states.squeeze(1)).gather(1, actions) # Q(S,A)
        values_next = anotherAgent.target(nexts.squeeze(1)).max(1).values.detach() # max_a(Q(S',a))
        expected = rewards - (self.gamma * values_next.unsqueeze(1)) # R-gamma*max_a(Q(S',a))
        loss = F.smooth_l1_loss(values, expected) # 计算误差 
        self.optimizer.zero_grad() # 更新网络参数三部曲
        loss.backward()
        for param in self.policy.parameters(): param.grad.data.clamp_(-1, 1)
        self.optimizer.step()
        return loss.item() # 返回误差

    def sync(self): # 将策略网络中的权重同步到目标网络
        self.target.load_state_dict(self.policy.state_dict())

    def save(self, path): # 保存模型
        torch.save(self.policy, path)
