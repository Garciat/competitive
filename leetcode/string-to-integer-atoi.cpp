// https://leetcode.com/problems/string-to-integer-atoi/

class Solution {
public:
    int myAtoi(string str) {
        const char *p = str.c_str();
        
        while (isspace(*p))
            ++p;
        
        int sign = 1;
        
        if (*p == '-') {
            sign = -1;
            ++p;
        } else if (*p == '+') {
            ++p;
        }
        
        int digits = 0;
        long long value = 0;
        
        while (isdigit(*p) && -value > INT_MIN) {
            value *= 10;
            value += *p - '0';
            digits += 1;
            ++p;
        }
        
        if (!digits) {
            return 0;
        }
        
        if (-value > INT_MIN) {
            return sign == 1 ? (int)value : (int)(-value);
        } else {
            return sign == 1 ? INT_MAX : INT_MIN;
        }
    }
};
