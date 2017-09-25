# http://codeforces.com/problemset/problem/302/A

N, M = map(int, raw_input().split(' '))

A, B = 0, 0

for a in raw_input().split(' '):
	if a[0] == '-':
		A += 1
	else:
		B += 1

for i in xrange(M):
	i, j = map(int, raw_input().split(' '))
	
	n = j - i + 1
	
	if n % 2 == 1:
		print '0'
	elif A >= n // 2 and B >= n // 2:
		print '1'
	else:
		print '0'
