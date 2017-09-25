// https://leetcode.com/problems/counting-bits/

class Solution {
    
    array<int, 256> bit_counts;
    
public:
    Solution() {
        for (int i = 0; i < bit_counts.size(); ++i) {
            bit_counts[i] = count_set_bits(i);
        }
    }
    
    vector<int> countBits(int num) {
        vector<int> ans;
        
        for (int i = 0; i <= num; ++i) {
            int b0 = (i >> 0) & 0xFF;
            int b1 = (i >> 8) & 0xFF;
            int b2 = (i >> 16) & 0xFF;
            int b3 = (i >> 24) & 0xFF;
            
            int bc = bit_counts[b0]
                   + bit_counts[b1]
                   + bit_counts[b2]
                   + bit_counts[b3];
            
            ans.push_back(bc);
        }
        
        return ans;
    }
    
    static int count_set_bits(int x) {
        int b = 0;
        while (x != 0) {
            b += x & 1;
            x >>= 1;
        }
        return b;
    }
};
