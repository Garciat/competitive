# http://codeforces.com/problemset/problem/302/B

import __builtin__

def lower_bound(haystack, needle, lo = 0, hi = None, cmp = None, key = None):
    if cmp is None: cmp = __builtin__.cmp
    if key is None: key = lambda x: x
    if lo < 0: raise ValueError( 'lo cannot be negative' )
    if hi is None: hi = len(haystack)
	
    val = None
    while lo < hi:
        mid = (lo + hi) // 2
        val = cmp(key(haystack[mid]), needle)
        if val < 0:
            lo = mid + 1
        else:
            hi = mid
    return lo

N, M = map(int, raw_input().split(' '))
R = []
T = 0

for i in xrange(N):
	c, t = map(long, raw_input().split())
	R.append(T)
	T += c * t

M = map(long, raw_input().split(' '))

for m in M:
	print lower_bound(R, m)
