// https://leetcode.com/problems/sum-of-two-integers/

class Solution {
public:
    int getSum(int a, int b) {
        int s = a ^ b;
        int r = a & b;
        while (r) {
            r <<= 1;
            int s_ = s ^ r;
            int r_ = s & r;
            s = s_;
            r = r_;
        }
        return s;
    }
};
