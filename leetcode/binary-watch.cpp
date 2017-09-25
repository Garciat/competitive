// https://leetcode.com/problems/binary-watch/

class Solution {
public:
    vector<string> readBinaryWatch(int num) {
        vector<string> ans;
        
        for (int h = 0; h < 12; ++h) {
            for (int m = 0; m < 60; ++m) {
                if (count_bits(h) + count_bits(m) == num) {
                    string t;
                    t += to_string(h);
                    t += ':';
                    if (m < 10) {
                        t += '0';
                    }
                    t += to_string(m);
                    ans.emplace_back(move(t));
                }
            }
        }
        
        return ans;
    }
    
    static int count_bits(int x) {
        int b = 0;
        while (x != 0) {
            b += x & 1;
            x >>= 1;
        }
        return b;
    }
};
