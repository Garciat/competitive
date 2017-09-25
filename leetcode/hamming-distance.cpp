// https://leetcode.com/problems/hamming-distance/

class Solution {
public:
    int hammingDistance(int x, int y) {
        int z = x ^ y;
        
        int i = 0;
        while (z != 0) {
            i += z & 1;
            z >>= 1;
        }
        
        return i;
    }
};
