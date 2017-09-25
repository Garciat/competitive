// https://leetcode.com/problems/bitwise-and-of-numbers-range/

class Solution {
public:
    int rangeBitwiseAnd(int m, int n) {
        assert(0 <= m && m <= n && n <= INT_MAX);
        int d = n - m;
        int k = 0;
        while (k < d) {
            k <<= 1;
            k |= 1;
        }
        int x = (m & n) & ~k;
        return x;
    }
};
