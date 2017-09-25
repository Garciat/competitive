// https://leetcode.com/problems/palindrome-permutation/

class Solution {
public:
    bool canPermutePalindrome(string s) {
        unordered_map<char, int> m;
        for (char c : s)
            m[c] += 1;
        int n_odd = 0;
        for (auto& p : m)
            if (p.second % 2 == 1)
                n_odd += 1;
        return s.size() % 2 == 0 ? (n_odd == 0) : (n_odd == 1);
    }
};

