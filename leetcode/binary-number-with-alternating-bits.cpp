// https://leetcode.com/problems/binary-number-with-alternating-bits/

class Solution {
public:
    bool hasAlternatingBits(int n) {
        if (n == 0) return false;
        bool cur = n & 1;
        while (n) {
            if ((n & 1) != int(cur)) return false;
            cur = !cur;
            n >>= 1;
        }
        return true;
    }
};
