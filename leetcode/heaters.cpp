// https://leetcode.com/problems/heaters/

class Solution {
public:
    int findRadius(vector<int>& houses, vector<int>& heaters) {
        if (heaters.empty()) return -1;
        
        sort(begin(houses), end(houses));
        sort(begin(heaters), end(heaters));
        
        int a = -1;
        int b = -1;
        
        auto hs = begin(heaters);
        
        int ans = -1;
        
        for (int x : houses) {
            // cout << "HOUSE " << x << endl;
            
            while (hs != end(heaters) && x > b) {
                // cout << "MOVE " << *hs << endl;
                a = b;
                b = *hs;
                ++hs;
                // cout << a << ' ' << b << endl;
            }
            if (hs == end(heaters) && x > b && b != -1) {
                a = b;
                b = -1;
            }
            
            // cout << "a=" << a << " b=" << b << endl;
            
            if (a != -1 && b != -1)
                ans = max(ans, min(abs(x - a), abs(x - b)));
            else if (a != -1)
                ans = max(ans, abs(x - a));
            else if (b != -1)
                ans = max(ans, abs(x - b));
        }
        
        return ans;
    }
};
