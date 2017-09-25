// https://leetcode.com/problems/base-7/

class Solution {
public:
    string convertToBase7(int num) {
        if (num == 0) {
            return "0";
        }
        bool is_neg = false;
        string ans;
        if (num < 0) {
            num *= -1;
            is_neg = true;
        }
        while (num > 0) {
            ans += '0' + num % 7;
            num /= 7;
        }
        if (is_neg) {
            ans += '-';
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};
