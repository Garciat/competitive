n  = int(input())
hs = map(int, input().split())
t  = int(input())

print(min(hs, key=lambda h: t % h))