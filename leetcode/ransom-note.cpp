// https://leetcode.com/problems/ransom-note/

class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        auto freq_note = letterFreq(ransomNote);
        auto freq_mag = letterFreq(magazine);
        for (int i = 0; i < 26; ++i) {
            if (freq_note[i] > freq_mag[i]) {
                return false;
            }
        }
        return true;
    }
    
    array<int, 26> letterFreq(const string& s) {
        array<int, 26> freq {};
        for (char c : s) {
            freq[c - 'a'] += 1;
        }
        return freq;
    }
};
