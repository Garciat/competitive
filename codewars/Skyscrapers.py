from functools import wraps
from itertools import (
    count,
    permutations,
)

def compose_with(f):
    def wrapper(g):
        @wraps(g)
        def composed(*args, **kwargs):
            return f(g(*args, **kwargs))
        return composed
    return wrapper

def groupby(xs, key):
    g = {}
    for x in xs:
        g.setdefault(key(x), []).append(x)
    return g

def div_mod(x, y):
    return x // y, x % y

def rev_eq(n, xs, ys):
    for i in range(n):
        if xs[i] != ys[n-i-1]:
            return False
    return True

@compose_with(list)
def concat(xss):
    for xs in xss:
        yield from xs

@compose_with(list)
def transpose(xss):
    return zip(*xss)

###

@compose_with(list)
def all_strips(n):
    for xs in permutations(range(1, n+1)):
        yield list(xs)

def strip_rank(strip):
    m, r = strip[0], 0
    for x in strip:
        if x >= m:
            r += 1
        m = max(m, x)
    return r

@compose_with(dict)
def ranked_strips(n):
    strips = all_strips(n)
    yield 0, strips
    yield from groupby(strips, key=strip_rank).items()

def solution(n, clues):
    strips = ranked_strips(n)
    initial = [strips[r] for r in clues]

    for sol in work(n, 0, initial):
        return sol

def work(n, i, options):
    if i == n * 4:
        yield [level[0] for level in options[:n]]
    else:
        for strip in options[i]:
            next_options = constrain(n, i, strip, options)
            if next_options is not None:
                yield from work(n, i+1, next_options)

def constrain(n, i, strip, options):
    a, c = div_mod(i, n)
    next_options = []
    for j, level in zip(count(), options):
        b, d = div_mod(j, n)
        next_level = []
        if i == j:
            next_level.append(strip)
        elif abs(a-b) == 2 and abs(c-d) == n-1:
            for s in level:
                if rev_eq(n, strip, s):
                    next_level.append(s)
                    break
        elif (a+1) % 4 == b:
            for s in level:
                if strip[d] == s[n-c-1]:
                    next_level.append(s)
        elif (a-1) % 4 == b:
            for s in level:
                if strip[n-d-1] == s[c]:
                    next_level.append(s)
        else:
            next_level = level
        if not next_level:
            return None
        next_options.append(next_level)
    return next_options

def solve_puzzle(clues):
    sol = solution(len(clues) // 4, clues)
    return transpose(sol)

def artificial(n):
    return solve_puzzle([0] * (4 * n))

if __name__ == '__main__':
    print(artificial(4))
    print()

    print(solve_puzzle(( 3, 2, 2, 3, 2, 1,
            1, 2, 3, 3, 2, 2,
            5, 1, 2, 2, 4, 3,
            3, 2, 1, 2, 2, 4)))
