// https://leetcode.com/problems/number-complement/

class Solution {
public:
    int findComplement(int num) {
        int k = 0;
        for (int x = num; x != 0; x >>= 1) {
            k += 1;
        }
        return ~(0xFFFFFFFF << k) & ~num;
    }
};
