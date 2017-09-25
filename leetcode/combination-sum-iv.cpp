// https://leetcode.com/problems/combination-sum-iv/

vector<int> concat(vector<int> xs, int x) {
    xs.push_back(x);
    return move(xs);
}

class Solution {
    
    unordered_map<int, int> memo;
    
public:
    int combinationSum4(vector<int>& candidates, int target) {
        return work(candidates, target);
    }
    
    int work(const vector<int>& ns, int left) {
        
        auto it = memo.find(left);
        
        if (it != memo.end()) return it->second;
        
        if (left == 0) return 1;
        if (left <  0) return 0;
        
        int a = 0;
        for (auto x : ns) {
            a += work(ns, left - x);
        }
        return memo[left] = a;
    }
};
