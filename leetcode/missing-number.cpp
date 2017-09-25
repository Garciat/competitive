// https://leetcode.com/problems/missing-number/

class Solution {
public:
    int missingNumber(vector<int>& nums) {
        bool zero = false;
        uint64_t p = 0;
        uint64_t q = 0;
        
        uint64_t i = 1;
        for (int x : nums) {
            q += i++;
            if (!zero && x == 0) {
                zero = true;
            } else if (x > 0) {
                p += x;
            }
        }
        
        return zero ? (q - p) : 0;
    }
};
