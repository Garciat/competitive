# https://leetcode.com/problems/diagonal-traverse/

class Solution(object):
    def findDiagonalOrder(self, matrix):
        """
        :type matrix: List[List[int]]
        :rtype: List[int]
        """
        if not matrix:
            return []
        
        ans = []
        
        M = len(matrix)
        N = len(matrix[0])
        D = M + N - 1
        
        for d in xrange(D):
            if d % 2 == 1:
                j = min(d, N - 1)
                i = d - j
                s = +1
            else:
                i = min(d, M - 1)
                j = d - i
                s = -1
                
            while 0 <= i < M and 0 <= j < N:
                ans.append(matrix[i][j])
                i += s
                j -= s
        
        return ans
