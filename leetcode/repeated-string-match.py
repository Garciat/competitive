# https://leetcode.com/problems/repeated-string-match/

class Solution:
    def repeatedStringMatch(self, A, B):
        x = ''
        for i in range(10000):
            x += A
            if B in x:
                return i + 1
            if len(x) / len(B) > 3:
                return -1
        return -1
