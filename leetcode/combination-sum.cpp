// https://leetcode.com/problems/combination-sum/

vector<int> concat(vector<int> xs, int x) {
    xs.push_back(x);
    return move(xs);
}

class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        
        vector<vector<int>> ans;
        work(ans, candidates, 0, target, {});
        return ans;
    }
    
    void work(vector<vector<int>>& ans, const vector<int>& ns, int i, int left, vector<int> pre) {
        if (left == 0) {
            ans.emplace_back(move(pre));
            return;
        }
        
        if (ns[i] > left) {
            return;
        }
        
        work(ans, ns, i, left - ns[i], concat(pre, ns[i]));
        
        if (i + 1 < ns.size()) {
            work(ans, ns, i+1, left, move(pre));
        }
    }
};
