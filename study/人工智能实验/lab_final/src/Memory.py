import torch

class Memory(object):

    def __init__(self, size, device):
        self.size = size
        self.index = 0
        self.device = device
        self.states = torch.zeros((size, 1, 1, 8, 8), dtype=torch.int8) # 状态
        self.actions = torch.zeros((size, 1), dtype=torch.long) # 动作
        self.Nexts = torch.zeros((size, 1, 1, 8, 8), dtype=torch.int8) # 下一个状态
        self.rewards = torch.zeros((size, 1), dtype=torch.float) # 收益

    def push(self, state, action, Next, reward):
        self.states[self.index] = state
        self.actions[self.index] = action
        self.Nexts[self.index] = Next
        self.rewards[self.index] = reward
        self.index = (self.index + 1) % self.size

    def sample(self, batch_size):
        index = torch.randint(0, high = self.size, size = (batch_size, ))
        states = self.states[index].float().to(self.device)
        actions = self.actions[index].to(self.device)
        Nexts = self.Nexts[index].float().to(self.device)
        rewards = self.rewards[index].to(self.device)
        return states, actions, Nexts, rewards