// https://leetcode.com/problems/number-of-boomerangs/

using pii = pair<int, int>;

ostream& operator<<(ostream& os, pii p) {
    return os << p.first << ',' << p.second;
}

class Solution {
public:
    int numberOfBoomerangs(vector<pii>& points) {
        int ans = 0;
        
        unordered_map<int, int> m;
        
        for (int i = 0; i < points.size(); ++i) {
            auto p = points[i];
            for (int j = 0; j < points.size(); ++j) {
                if (i == j)
                    continue;
                
                auto q = points[j];
                
                auto dx = p.first - q.first;
                auto dy = p.second - q.second;
                auto d = dx * dx + dy * dy;
                
                m[d] += 1;
            }
            
            for (auto t : m) {
                ans += t.second * (t.second - 1);
            }
            
            m.clear();
        }
        
        return ans;
    }
};
