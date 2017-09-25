// https://leetcode.com/problems/find-all-anagrams-in-a-string/


class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        vector<int> sv(26, 0);
        vector<int> pv(26, 0);
        vector<int> ans;
        
        for (int i = 0; i < p.size(); ++i) {
            pv[p[i]-'a'] += 1;
            sv[s[i]-'a'] += 1;
        }
        
        if (pv == sv)
            ans.push_back(0);
        
        for (int i = p.size(); i < s.size(); ++i) {
            sv[s[i]-'a'] += 1;
            sv[s[i-p.size()]-'a'] -= 1;
            
            if (pv == sv)
                ans.push_back(i - p.size() + 1);
        }
        
        return ans;
    }
};
