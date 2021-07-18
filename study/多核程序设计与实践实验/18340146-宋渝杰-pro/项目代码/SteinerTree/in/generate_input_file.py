import random

n, m, k = 800, 1600, 300
f = open('in6.txt', 'w')
f.write(str(n) + ' ' + str(m) + ' ' + str(k) + '\n')
for i in range(n-1):
    x = random.randint(i+1, n-1)
    f.write(str(i) + ' ' + str(x) + '\n')
for i in range(m-n+1):
    x, y = random.randint(0, n-1), random.randint(0, n-1)
    while x == y: x, y = random.randint(0, n-1), random.randint(0, n-1)
    f.write(str(x) + ' ' + str(y) + '\n')
    
l = [i for i in range(n)]
random.shuffle(l)

for i in range(k):
    f.write(str(l[i]) + ' ')

f.write('\n')