// https://leetcode.com/problems/roman-to-integer/

class Solution {
public:
    int romanToInt(string s) {
        map<char, int> rank;
        rank['M'] = 1000;
        rank['D'] = 500;
        rank['C'] = 100;
        rank['L'] = 50;
        rank['X'] = 10;
        rank['V'] = 5;
        rank['I'] = 1;
        
        int ans = 0;
        int cum = 0;
        
        for (char c : s) {
            int r = rank[c];
            if (r > cum) {
                ans -= cum;
            } else {
                ans += cum;
            }
            cum = r;
        }
        
        ans += cum;
        
        return ans;
    }
};
