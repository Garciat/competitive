// https://leetcode.com/problems/letter-combinations-of-a-phone-number/

array<char, 4> digit_letters(char d) {
    switch (d) {
        case '2':
            return {'a', 'b', 'c', 0};
        case '3':
            return {'d', 'e', 'f', 0};
        case '4':
            return {'g', 'h', 'i', 0};
        case '5':
            return {'j', 'k', 'l', 0};
        case '6':
            return {'m', 'n', 'o', 0};
        case '7':
            return {'p', 'q', 'r', 's'};
        case '8':
            return {'t', 'u', 'v', 0};
        case '9':
            return {'w', 'x', 'y', 'z'};
    }
}

class Solution {
public:
    vector<string> letterCombinations(string digits) {
        if (digits.empty()) {
            return {};
        }
        if (digits.find('1') != string::npos || digits.find('0') != string::npos) {
            return {};
        }
        vector<string> ans;
        work(ans, digits, 0, "");
        return ans;
    }
    
    void work(vector<string>& ans, const string& ds, int i, string pre) {
        
        if (i == ds.size()) {
            ans.emplace_back(move(pre));
        } else {
            
            for (char c : digit_letters(ds[i])) {
                if (c == 0) continue;
                work(ans, ds, i+1, pre + c);
            }
            
        }
    }
};
