// https://leetcode.com/problems/reverse-vowels-of-a-string/


bool is_vowel(char c) {
    c = tolower(c);
    return c == 'a'
        || c == 'e'
        || c == 'i'
        || c == 'o'
        || c == 'u';
}

class Solution {
public:
    string reverseVowels(string s) {
        int i = 0;
        int j = s.size() - 1;
        
        while (i < j) {
            if (is_vowel(s[i]) && is_vowel(s[j])) {
                swap(s[i], s[j]);
                i += 1;
                j -= 1;
            } else if (is_vowel(s[i])) {
                j -= 1;
            } else if (is_vowel(s[j])) {
                i += 1;
            } else {
                i += 1;
                j -= 1;
            }
        }
        
        return s;
        
    }
};

