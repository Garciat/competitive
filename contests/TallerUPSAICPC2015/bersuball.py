"""
http://codeforces.com/problemset/problem/489/B
"""

def read_input():
    n = int(input())
    xs = map(int, input().split(' '))
    return n, list(xs)

n, boys  = read_input()
m, girls = read_input()

boys.sort()
girls.sort()

pairs = 0
i, j = 0, 0

while i < n and j < m:
    d = boys[i] - girls[j]
    if abs(d) <= 1:
        pairs += 1
        i += 1
        j += 1
    else:
        if d < 0:
            i += 1
        else:
            j += 1

print(pairs)