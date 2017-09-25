// https://leetcode.com/problems/detect-capital/

class Solution {
public:
    bool detectCapitalUse(string word) {
        if (word.size() == 0) {
            return true;
        }
        if (isupper(word[0])) {
            return all_lower(word, 1) || all_upper(word, 1);
        } else {
            return all_lower(word, 1);
        }
    }
    
    bool all_lower(string &w, int i) {
        return all_of(begin(w) + i, end(w), ::islower);
    }
    bool all_upper(string &w, int i) {
        return all_of(begin(w) + i, end(w), ::isupper);
    }
};
