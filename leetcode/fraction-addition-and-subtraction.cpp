// https://leetcode.com/problems/fraction-addition-and-subtraction/

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a%b);
}

struct Fraction {
    bool positive;
    int num, den;
    
    Fraction()
        : positive{true}
        , num{0}
        , den{1}
    { }
    
    int sign() const {
        return positive ? 1 : -1;
    }
    
    Fraction& normalize() {
        int g = gcd(num, den);
        num /= g;
        den /= g;
        return *this;
    }
    
    string str() const {
        string s;
        if (!positive)
            s += '-';
        s += to_string(num);
        s += '/';
        s += to_string(den);
        return s;
    }
};

Fraction operator+(const Fraction &a, const Fraction &b) {
    Fraction c;
    c.positive = true;
    c.den = a.den * b.den;
    c.num = a.sign() * a.num * b.den + b.sign() * b.num * a.den;
    if (c.num < 0) {
        c.positive = false;
        c.num = -c.num;
    }
    c.normalize();
    return c;
}

istream& operator>>(istream& is, Fraction &frac) {
    int c = is.peek();
    if (!is || c == EOF) return is;
    if (c == '+' || c == '-')
        is.get(); // consume sign
    frac.positive = c != '-';
    is >> frac.num;
    assert(is.get() == '/');
    is >> frac.den;
    frac.normalize();
    return is;
}

class Solution {
public:
    string fractionAddition(string expression) {
        istringstream iss{expression};
        Fraction ans, f;
        while (iss >> f) {
            ans = ans + f;
        }
        return ans.str();
    }
};
