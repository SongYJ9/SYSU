import random

num = 1000
f = open('in5.txt', 'w')
f.write(str(num) + '\n')
for i in range(num):
    x, y = random.randint(1, 100), random.randint(1, 100)
    f.write(str(x) + ' ' + str(y) + '\n')