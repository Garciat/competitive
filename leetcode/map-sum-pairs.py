# https://leetcode.com/problems/map-sum-pairs/

class MapSum(object):
    def __init__(self):
        self.data = {}

    def insert(self, key, val):
        self.data[key] = val

    def sum(self, prefix):
        total = 0
        for key, val in self.data.items():
            if key.startswith(prefix):
                total += val
        return total
        


# Your MapSum object will be instantiated and called as such:
# obj = MapSum()
# obj.insert(key,val)
# param_2 = obj.sum(prefix)
