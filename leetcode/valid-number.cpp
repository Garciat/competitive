// https://leetcode.com/problems/valid-number/

template <char... Cs>
struct chars {
    bool operator()(char c) {
        return ((c==Cs) || ... || false);
    }
};

struct NumberParser {
    const string &s;
    int i;
    
    NumberParser(const string &s) : s{s}, i{0} { }
    
    bool isNumber() {
        try {
            skipMany(s, ' ');
            if (s[i] == '+' || s[i] == '-') {
                i += 1;
            }
            if (s[i] == '.') {
                i += 1;
                integerUntil(s, chars<'e', ' '>());
            } else {
                integerUntil(s, chars<'.', 'e', ' '>());
                if (s[i] == '.') {
                    i += 1;
                    integerOptUntil(s, chars<'e', ' '>());
                }
            }
            if (s[i] == 'e') {
                i += 1;
                if (s[i] == '+' || s[i] == '-') {
                    i += 1;
                }
                integerUntil(s, chars<' '>());
            }
            skipMany(s, ' ');
            return i == s.size();
        } catch (runtime_error &e) {
            cout << e.what() << endl;
            return false;
        }
    }
    
    void skipMany(const string &s, char c) {
        while (s[i] == c) ++i;
    }
    
    template <typename Pred>
    void integerUntil(const string &s, Pred pred) {
        if (integerOptUntil(s, pred) == 0) {
            throw runtime_error{"no read"};
        }
    }
    
    template <typename Pred>
    int integerOptUntil(const string &s, Pred pred) {
        int k = 0;
        for (; s[i]; ++i, ++k) {
            if (isdigit(s[i])) {
                continue;
            }
            if (pred(s[i])) {
                break;
            }
            throw runtime_error{"bad char"};
        }
        return k;
    }
};

class Solution {
public:
    bool isNumber(string s) {
        return NumberParser{s}.isNumber();
    }
};
