from random import uniform

def init():
    w = [1 for i in range(40)]
    b = 1
    return w,b

def data(n,w,b):
    f = open('test.csv',mode='w')
    for i in range(n):
        s = ''
        ans = 0
        for j in range(40):
            x = round(uniform(-10,10),2)
            ans += w[j]*x
            s += str(x)+','
        s += '1\n' if ans+b > 0 else '-1\n'
        f.write(s)

if __name__ == '__main__':
    n = 10000
    w,b = init()
    data(n,w,b)
