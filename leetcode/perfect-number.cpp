// https://leetcode.com/problems/perfect-number/

/*

fails:
    
    assume 1 is ok

*/
class Solution {
public:
    bool checkPerfectNumber(int num) {
        if (num == 1) {
            return false;
        }
        int a = 1;
        
        for (int i = 2; i <= sqrt(num); ++i) {
            if (num % i == 0) {
                a += i;
                a += num / i;
            }
        }
        
        return a == num;
    }
};
