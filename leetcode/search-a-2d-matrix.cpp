// https://leetcode.com/problems/search-a-2d-matrix/

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if (matrix.empty() || matrix[0].empty()) {
            return false;
        }
        
        auto it = lower_bound(begin(matrix), end(matrix), target, [target](const vector<int>& row, int) {
            return row.front() < target && row.back() < target;
        });
        
        if (it == end(matrix)) {
            return false;
        }
        
        auto ot = lower_bound(begin(*it), end(*it), target);
        
        return ot != end(*it) && *ot == target;
    }
};
