// https://leetcode.com/problems/fraction-to-recurring-decimal/

class Solution {
public:
    string fractionToDecimal(int numerator, int denominator) {
        if (numerator == 0) return "0";
        return work(numerator, denominator);
    }
    
    string work(long long a, long long b) {
        ostringstream oss;
        
        auto sign = ((a < 0) ^ (b < 0)) ? -1 : 1;
        
        auto w = a / b;
        
        if (w == 0 && sign == -1) {
            oss << '-';
        }
        
        oss << w;
        
        auto c = abs(a % b) * 10;
        b = abs(b);
        
        string z;
        unordered_map<int, int> forms;
        int rec = -1;
        
        if (c != 0) {
            oss << '.';
        }
        
        for (int i = 0; c != 0; ++i) {

            if (has_key(forms, c)) {
				rec = forms[c];
                break;
            } else {
                forms[c] = i;
            }

            z += '0' + (c / b);
            c %= b;
            c *= 10;
        }
        
        if (rec != -1) {
            for (int i = 0; i < rec; ++i) {
                oss << z[i];
            }
            oss << '(';
            for (int i = rec; i < z.size(); ++i) {
                oss << z[i];
            }
            oss << ')';
        } else {
            oss << z;
        }
        
        return oss.str();
    }
    
    template <typename T, typename U>
    static bool has_key(T &&x, U &&u) {
        return x.find(u) != x.end();
    }
};
