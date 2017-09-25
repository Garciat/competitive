// https://leetcode.com/problems/valid-number/

template <char...>
struct chars;

template <char C, char... Cs>
struct chars<C, Cs...> {
	bool operator()(char c) {
    	return c==C || chars<Cs...>()(c);
  	}
};

template <>
struct chars<> {
    bool operator()(char c) {
        return false;
    }
};

class Solution {
public:
    bool isNumber(string s) {
        try {
            int i = 0;
            skipMany(s, ' ', i);
            if (s[i] == '+' || s[i] == '-') {
                i += 1;
            }
            if (s[i] == '.') {
                i += 1;
                integerUntil(s, chars<'e', ' '>(), i);
            } else {
                integerUntil(s, chars<'.', 'e', ' '>(), i);
                if (s[i] == '.') {
                    i += 1;
                    integerOptUntil(s, chars<'e', ' '>(), i);
                }
            }
            if (s[i] == 'e') {
                i += 1;
                if (s[i] == '+' || s[i] == '-') {
                    i += 1;
                }
                integerUntil(s, chars<' '>(), i);
            }
            skipMany(s, ' ', i);
            return i == s.size();
        } catch (runtime_error &e) {
            cout << e.what() << endl;
            return false;
        }
    }
    
    void skipMany(const string &s, char c, int &i) {
        while (s[i] == c) ++i;
    }
    
    template <typename Pred>
    void integerUntil(const string &s, Pred pred, int &i) {
        if (integerOptUntil(s, pred, i) == 0) {
            throw runtime_error{"no read"};
        }
    }
    
    template <typename Pred>
    int integerOptUntil(const string &s, Pred pred, int &i) {
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
