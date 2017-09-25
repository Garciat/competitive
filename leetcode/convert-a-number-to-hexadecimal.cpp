// https://leetcode.com/problems/convert-a-number-to-hexadecimal/

class Solution {
public:
    string toHex(int num) {
        if (num == 0) return "0";
        
        unsigned x = static_cast<unsigned>(num);
        string s;
        for (int i = 1; i <= 8; ++i) {
            int p = (x >> (32 - i*4)) & 0xF;
            assert(0 <= p && p < 16);
            if (s.empty() && p == 0)
                continue;
            if (p < 10)
                s += '0' + p;
            else
                s += 'a' + p % 10;
        }
        return s;
    }
};
