from itertools import cycle, islice

class Settlement:
    def __init__(self, h, r, t):
        self.h, self.r, self.t = h, r, t

    def is_night(self, x):
        if self.r < self.t:
            return x <= self.r or x >= self.t
        else:
            return x <= self.r and x >= self.t

    @property
    def night_hours(self):
        return cycle(map(self.is_night, range(self.h)))

def hours_until_darkness(settlements):
    longest_solar_day = max(s.h for s in settlements)
    president_term = 1825 * longest_solar_day
    hours_by_settlement_until_term = (islice(s.night_hours, president_term) for s in settlements)
    hours_by_day_until_term = transpose(hours_by_settlement_until_term)
    return find_index(all, hours_by_day_until_term)

def transpose(iterables):
    return zip(*iterables)

def find_index(pred, iterable):
    for i, item in enumerate(iterable):
        if pred(item):
            return i
    return -1

def read_settlement():
    return Settlement(*map(int, input().split(' ')))

if __name__ == '__main__':
    n = int(input())
    settlements = [read_settlement() for _ in range(n)]
    ans = hours_until_darkness(settlements)
    print("impossible" if ans == -1 else ans)
