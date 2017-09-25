// https://leetcode.com/problems/redundant-connection/


class Solution {
    
    using AdjMap = unordered_map<int, vector<int>>;
    
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        for (int i = edges.size() - 1; i >= 0; --i) {
            auto g = buildGraphWithout(edges, i);
            if (isTree(g, edges.size())) {
                return edges[i];
            }
        }
        return {0, 0};
    }
    
    AdjMap buildGraphWithout(vector<vector<int>>& edges, int k) {
        AdjMap g;
        for (int i = 0; i < edges.size(); ++i) {
            if (i == k) continue;
            g[edges[i][0]].push_back(edges[i][1]);
            g[edges[i][1]].push_back(edges[i][0]);
        }
        return g;
    }
    
    bool isTree(AdjMap& g, int n) {
        unordered_set<int> seen;
        dfs(g, g.begin()->first, seen);
        return seen.size() == n;
    }

    void dfs(AdjMap& g, int k, unordered_set<int>& seen) {
        seen.insert(k);
        for (int v : g[k]) {
            if (seen.count(v) != 0) continue;
            dfs(g, v, seen);
        }
    }
};
