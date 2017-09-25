# http://codeforces.com/problemset/problem/296/A

from collections import deque
from heapq import *

n = int(input())
xs = map(int, input().split(' '))

MAXSIZEOMGWTFOFFBYONE = 1100

counts = [0] * MAXSIZEOMGWTFOFFBYONE

for x in xs:
    counts[x] += 1

avail = []

for x in range(MAXSIZEOMGWTFOFFBYONE):
    c = counts[x]
    if c > 0:
        heappush(avail, (-c, x))

last = None

while len(avail) > 0:
    cur = heappop(avail)
    c, x = cur
    if x == last:
        if len(avail) == 0:
            print("NO")
            exit()
        c, x = heappop(avail)
        heappush(avail, cur)
    c += 1
    last = x
    if c < 0:
        heappush(avail, (c, x))

print("YES")
