// https://leetcode.com/problems/add-strings/

class Solution {
public:
    string addStrings(string num1, string num2) {
        string ans;
        int carry = 0;
        
        int i = num1.size() - 1;
        int j = num2.size() - 1;
        
        while (i >= 0 || j >= 0) {
            int x = carry;
            
            if (i >= 0)
                x += num1[i--] - '0';
            if (j >= 0)
                x += num2[j--] - '0';
            
            carry = x / 10;
            ans += (x % 10) + '0';
        }
        
        if (carry)
            ans += carry + '0';
        
        reverse(ans.begin(), ans.end());
        
        return ans;
    }
};
