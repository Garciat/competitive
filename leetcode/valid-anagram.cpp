// https://leetcode.com/problems/valid-anagram/

class Solution {
public:
    bool isAnagram(string s, string t) {
        if (s.size() != t.size()) return false;
        
        return char_freq(s) == char_freq(t);
    }
    
    static unordered_map<char, int> char_freq(const string &s) {
        unordered_map<char, int> m;
        for (char c : s) {
            m[c] += 1;
        }
        return m;
    }
};
