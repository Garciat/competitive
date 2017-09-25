// https://leetcode.com/problems/reverse-integer/

/*
simple algo:
  put digits in a vector
  reverse the vector
  create number from vector


*/

class Solution {
public:
    int reverse(int x) {
        if (x == 0) {
            return 0;
        }
        
        bool is_neg = x < 0;
        x = is_neg ? -x : x;
        
        long long r = 0;
        
        while (x > 0) {
            r *= 10;
            r += x % 10;
            x /= 10;
        }
        
        if (is_neg && -r < INT_MIN) {
            return 0;
        } else if (r > INT_MAX) {
            return 0;
        }
        
        return (int)(is_neg ? -r : r);
    }
};

