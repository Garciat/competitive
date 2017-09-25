// https://leetcode.com/problems/complex-number-multiplication/

struct icomplex {
    int re, im;
    
    string str() {
        ostringstream oss;
        oss << re;
        oss << '+';
        oss << im;
        oss << 'i';
        return oss.str();
    }
};

icomplex operator*(icomplex x, icomplex y) {
    return icomplex { x.re * y.re - x.im * y.im, x.re * y.im + x.im * y.re };
}

class Solution {
public:
    string complexNumberMultiply(string a, string b) {
        auto x = parse_complex(a);
        auto y = parse_complex(b);
        
        auto z = x * y;
        
        return z.str();
    }
    
    static icomplex parse_complex(const string &s) {
        int i = 0;
        int re = parse_int(s, i, '+');
        i += 1;
        int im = parse_int(s, i, 'i');
        return icomplex { re, im };
    }
    
    static int parse_int(const string &s, int &i, char until) {
        int sign = 1;
        
        if (s[i] == '-') {
            sign = -1;
            i += 1;
        }
        
        int x = 0;
        while (s[i] != until) {
            x *= 10;
            x += s[i] - '0';
            i += 1;
        }
        
        return sign * x;
    }
};
