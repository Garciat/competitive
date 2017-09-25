def product(xo, dx, mx):
    p = 1
    x = xo
    while x <= mx:
        p *= x
        x += dx
    return p

def catalan(n):
    c = n // 2
    d = n % 2
    m = n - c
    
    g = 0
    x = m
    while True:
        x //= 2
        if x <= 0:
            break
        g += x
    
    k = 1 << (c - g)
    top = k * product(n - d + 3, 2, n * 2)
    
    bot = 1
    x = m
    while x > 0:
        bot *= product(1, 2, x)
        x //= 2
    
    return top // bot

if __name__ == '__main__':
    n = int(input())
    c = catalan(n + 1)
    print(c)
