def solve(n, k):
    freqs = [1] + [0] * n

    for i in range(k):
        step(freqs)
    
    total_value = 0
    for value, freq in enumerate(freqs):
        total_value += value * freq
    
    return 0.5 ** k * total_value


def step(f):
    last = 0
    for i in range(len(f) - 2):
        last, f[i] = f[i], last + f[i]
    f[-2], f[-1] = last + f[-2] + f[-1], f[-2] + f[-1]


if __name__ == '__main__':
    n, k = map(int, input().split(' '))
    print(solve(n, k))
