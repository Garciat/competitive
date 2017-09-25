// https://leetcode.com/problems/combination-sum-ii/

vector<int> concat(vector<int> xs, int x) {
    xs.push_back(x);
    return xs;
}

class Solution {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        
        vector<vector<int>> ans;
        work(ans, candidates, 0, target, {});
        return ans;
    }
    
    void work(vector<vector<int>>& ans, const vector<int>& ns, int i, int left, vector<int> pre) {
        if (left == 0) {
            ans.emplace_back(pre);
            return;
        }
        
        if (ns[i] > left) {
            return;
        }
        
        // case 1: use this number
        work(ans, ns, i + 1, left - ns[i], concat(pre, ns[i]));
        
        // case 2: don't use this number (and all its duplicates)
        {
            int j = i + 1;
        
            while (j < ns.size() && ns[i] == ns[j]) {
                j += 1;
            }

            if (j < ns.size()) {
                work(ans, ns, j, left, pre);
            }
        }
    }
};
