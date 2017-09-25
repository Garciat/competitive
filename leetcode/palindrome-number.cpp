// https://leetcode.com/problems/palindrome-number/

/*

simple algo:
    
    cut numbers from left and right at same time:
    left: decreasing (div by 100) powers of 10 (starting at one <= n)
    right: just 10, truncating number

fail:
    INT_MIN

*/

class Solution {
public:
    bool isPalindrome(int inp) {
        if (inp == 0) {
            return true;
        }
        
        long long x = inp;
        
        if (x < 0) {
            x *= -1;
            return false;
        }
        
        int decP10 = 1000000000; // 1e9
        
        while (decP10 > x) {
            decP10 /= 10;
        }
        
        while (decP10 != 0 && x != 0) {
            int digitL = x / decP10;
            int digitR = x % 10;
            
            if (digitL != digitR) {
                return false;
            }
            
            x = (x % decP10) / 10;
            
            decP10 /= 100;
        }
        
        return true;
    }
};
