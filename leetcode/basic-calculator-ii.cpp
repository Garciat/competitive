// https://leetcode.com/problems/basic-calculator-ii/

#define int int64_t

struct Token {
    enum { EMPTY, INT, PLUS, MINUS, STAR, DIV } tag;
    int value;
    
    static Token empty() {
        return { EMPTY };
    }
    
    static Token plus() {
        return { PLUS };
    }
    
    static Token minus() {
        return { MINUS };
    }
    
    static Token star() {
        return { STAR };
    }
    
    static Token div() {
        return { DIV };
    }
    
    static Token intval(int val) {
        return { INT, val };
    }
};

struct Prog {
    string s;
    int i;
    
    Prog(string s) : s{s}, i{0} { }
    
    int parse() {
        int summand = 0;
        int factor = 1;
        int sign = 1;
        
        for (;;) {
            auto t = next_token();
            
            if (t.tag == Token::EMPTY) break;
            
            switch (t.tag) {
            case Token::INT:
                factor *= t.value;
                break;
            case Token::STAR:
                break;
            case Token::DIV:
                factor /= next_token().value;
                break;
            case Token::PLUS:
                summand += sign * factor;
                factor = 1;
                sign = 1;
                break;
            case Token::MINUS:
                summand += sign * factor;
                factor = 1;
                sign = -1;
                break;
            }
        }
        
        summand += sign * factor;
        
        return summand;
    }
    
    Token next_token() {
        while (i < s.size() && s[i] == ' ')
            i += 1;
        
        if (i == s.size())
            return Token::empty();
        
        switch (s[i]) {
        case '+':
            return i += 1, Token::plus();
        case '-':
            return i += 1, Token::minus();
        case '*':
            return i += 1, Token::star();
        case '/':
            return i += 1, Token::div();
        }
        
        assert(isdigit(s[i]));
        
        int val = 0;
        while (i < s.size() && isdigit(s[i])) {
            val *= 10;
            val += s[i] - '0';
            i += 1;
        }
        
        return Token::intval(val);
    }
};

class Solution {
public:
    int calculate(string s) {
        Prog prog(s);
        return prog.parse();
    }
};
