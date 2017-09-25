// https://leetcode.com/problems/valid-parentheses/

class Solution {
public:
    bool isValid(string s) {
        stack<char> bs;
        for (char c : s) {
            switch (c) {
            case '(':
            case '{':
            case '[':
                bs.push(c);
                break;
            case ')':
            case '}':
            case ']':
                if (bs.empty() || bs.top() != opening(c)) {
                    return false;
                } else {
                    bs.pop();
                }
                break;
            }
        }
        return bs.empty();
    }
    
    char opening(char b) {
        switch (b) {
        case ')':
            return '(';
        case '}':
            return '{';
        case ']':
            return '[';
        }
    }
};
