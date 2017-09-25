// https://leetcode.com/problems/integer-to-english-words/

class Solution {
    static constexpr int BILLION  = 1000000000;
    static constexpr int MILLION  = 1000000;
    static constexpr int THOUSAND = 1000;
    static constexpr int HUNDRED  = 100;
    static constexpr int TEN      = 10;
public:
    string numberToWords(int num) {
        if (num == 0) return "Zero";
        
        vector<string> parts;
        
        segment(parts, num, BILLION,  "Billion");
        segment(parts, num, MILLION,  "Million");
        segment(parts, num, THOUSAND, "Thousand");
        do_part(parts, num);
        
        return concat1(parts);
    }
    
    void segment(vector<string> &parts, int &num, int level, string name) {
        if (num >= level) {
            do_part(parts, num / level);
            parts.push_back(name);
            num %= level;
        }
    }
    
    string concat1(const vector<string> &parts) {
        string ans = parts[0];
        for (int i = 1; i < parts.size(); ++i) {
            ans += ' ';
            ans += parts[i];
        }
        return ans;
    }
    
    void do_part(vector<string> &parts, int num) {
        if (num >= HUNDRED) {
            parts.push_back(digit(num / HUNDRED));
            parts.push_back("Hundred");
            num %= HUNDRED;
        }
        
        if (isTeen(num)) {
            parts.push_back(teen(num));
            return;
        }
        
        if (num >= TEN) {
            parts.push_back(tens(num / TEN));
            num %= TEN;
        }
        
        if (num > 0) {
            parts.push_back(digit(num));
        }
    }
    
    string tens(int n) {
        switch (n) {
            case 1: return "Ten";
            case 2: return "Twenty";
            case 3: return "Thirty";
            case 4: return "Forty";  // check
            case 5: return "Fifty";
            case 6: return "Sixty";
            case 7: return "Seventy";
            case 8: return "Eighty";
            case 9: return "Ninety";
            default: throw runtime_error{"tens " + to_string(n)};
        }
    }
    
    string teen(int n) {
        switch (n) {
            case 11: return "Eleven";
            case 12: return "Twelve";
            case 13: return "Thirteen";
            case 14: return "Fourteen";
            case 15: return "Fifteen";
            case 16: return "Sixteen";
            case 17: return "Seventeen";
            case 18: return "Eighteen";
            case 19: return "Nineteen";
            default: throw runtime_error{"teen " + to_string(n)};
        }
    }
    
    string digit(int n) {
        switch (n) {
            case 1: return "One";
            case 2: return "Two";
            case 3: return "Three";
            case 4: return "Four";
            case 5: return "Five";
            case 6: return "Six";
            case 7: return "Seven";
            case 8: return "Eight";
            case 9: return "Nine";
            default: throw runtime_error{"digit " + to_string(n)};
        }
    }
    
    bool isTeen(int n) {
        return n >= 11 && n <= 19;
    }
};
