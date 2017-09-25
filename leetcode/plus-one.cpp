// https://leetcode.com/problems/plus-one/

class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        reverse(digits.begin(), digits.end());
        
        digits[0] += 1;
        
        int carry = 0;
        for (int i = 0; i < digits.size(); ++i) {
            int s = digits[i] + carry;
            carry = s / 10;
            digits[i] = s % 10;
        }
        
        if (carry) {
            digits.push_back(carry);
        }
        
        reverse(digits.begin(), digits.end());
        return digits;
    }
};
