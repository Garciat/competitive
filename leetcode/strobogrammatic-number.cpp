// https://leetcode.com/problems/strobogrammatic-number/

class Solution {
public:
    bool isStrobogrammatic(string num) {
        string upside_down;
        
        for (char c : num) {
            switch (c) {
            case '0':
                upside_down += '0';
                break;
            case '1':
                upside_down += '1';
                break;
            case '6':
                upside_down += '9';
                break;
            case '8':
                upside_down += '8';
                break;
            case '9':
                upside_down += '6';
                break;
            default:
                return false;
            }
        }
        
        reverse(begin(upside_down), end(upside_down));
        
        return num == upside_down;
    }
};
