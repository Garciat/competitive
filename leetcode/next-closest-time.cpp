// https://leetcode.com/problems/next-closest-time/

int digit(char c) {
    return c - '0';
}

int tens(const string& s, int i) {
    return 10 * digit(s[i]) + digit(s[i+1]);
}

struct Time {
    int val;
    
    Time() : val{0} { }
    
    Time(const string &s) {
        val = 60 * tens(s, 0) + tens(s, 3);
    }
    
    Time(const Time &t) : val{t.val} { }
    
    void advance() {
        val += 1;
        if (val == 60 * 24)
            val = 0;
    }
    
    string str() {
        char s[5] = {0};
        sprintf(s, "%02d:%02d", val/60, val%60);
        return s;
    }
    
    bool operator==(Time t) {
        return val == t.val;
    }
};

bool compatible(Time r, Time t) {
    auto a = r.str();
    auto b = t.str();
    for (char c : b) {
        if (a.find(c) == string::npos) {
            return false;
        }
    }
    return true;
}

class Solution {
public:
    string nextClosestTime(string time) {
        Time r {time};
        Time t = r;
        for (;;) {
            t.advance();
            if (t == r) break;
            if (compatible(r, t)) break;
        }
        return t.str();
    }
};
