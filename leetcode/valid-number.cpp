// https://leetcode.com/problems/valid-number/

template <char... Cs>
struct chars_impl {
    constexpr bool operator()(char c) const {
        return ((c==Cs) || ... || false);
    }
};

template <char... Cs>
constexpr chars_impl<Cs...> chars = {};

struct NumberParser {
    
    const string &s;
    int i;
    
    NumberParser(const string &s) : s{s}, i{0} { }
    
    bool isNumber() {
        try {
            skipMany(chars<' '>);
            skipOpt(chars<'+', '-'>);
            if (skipOpt(chars<'.'>)) {
                integerUntil(chars<'e', ' '>);
            } else {
                integerUntil(chars<'.', 'e', ' '>);
                if (skipOpt(chars<'.'>)) {
                    integerOptUntil(chars<'e', ' '>);
                }
            }
            if (skipOpt(chars<'e'>)) {
                skipOpt(chars<'+', '-'>);
                integerUntil(chars<' '>);
            }
            skipMany(chars<' '>);
            return i == s.size();
        } catch (runtime_error &e) {
            cout << e.what() << endl;
            return false;
        }
    }
    
    template <typename Pred>
    void skipMany(Pred pred) {
        while (pred(s[i])) ++i;
    }
    
    template <typename Pred>
    bool skipOpt(Pred pred) {
        if (pred(s[i])) {
            i += 1;
            return true;
        } else {
            return false;
        }
    }
    
    template <typename Pred>
    void integerUntil(Pred pred) {
        if (integerOptUntil(pred) == 0) {
            throw runtime_error{"no read"};
        }
    }
    
    template <typename Pred>
    int integerOptUntil(Pred pred) {
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
