// https://leetcode.com/problems/4sum/

struct Quad {
    int a, b, c, d;
    
    Quad(array<int, 4> ns) {
        sort(begin(ns), end(ns));
        auto it = begin(ns);
        a = *it++;
        b = *it++;
        c = *it++;
        d = *it++;
    }
    
    bool operator==(const Quad &q) const {
        return a == q.a
            && b == q.b
            && c == q.c
            && d == q.d;
    }
    
    array<int, 4> vals() {
        return {a, b, c, d};
    }
};

namespace std {
    template<>
    struct hash<Quad> {
        std::size_t operator()(const Quad &q) const 
        {
            auto h1 = hash<int>{}(q.a);
            auto h2 = hash<int>{}(q.b);
            auto h3 = hash<int>{}(q.c);
            auto h4 = hash<int>{}(q.d);
            return h1 ^ (h2 << 1) ^ (h3 << 2) ^ (h4 << 3);
        }
    };
}

class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        unordered_map<int, vector<pair<int, int>>> m;
        
        for (int i = 0; i < nums.size(); ++i) {
            for (int j = i+1; j < nums.size(); ++j) {
                m[nums[i] + nums[j]].push_back(make_pair(i, j));
            }
        }
        
        unordered_set<Quad> qs;
        
        for (auto p : m) {
            auto q = m.find(target - p.first);
            if (q == m.end()) continue;
            for (auto r : p.second) {
                for (auto s : q->second) {
                    if (r.first == s.first || r.first == s.second
                     || r.second == s.first || r.second == s.second)
                        continue;
                    qs.insert(Quad{{
                        nums[r.first],
                        nums[r.second],
                        nums[s.first],
                        nums[s.second]
                    }});
                }
            }
        }
        
        vector<vector<int>> ans;
        
        for (auto q : qs) {
            vector<int> xs;
            for (auto i : q.vals())
                xs.push_back(i);
            sort(begin(xs), end(xs));
            ans.push_back(xs);
        }
        
        return ans;
    }
};
