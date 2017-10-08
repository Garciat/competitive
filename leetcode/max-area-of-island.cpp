// https://leetcode.com/problems/max-area-of-island/

class Solution {
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int ans = 0;
        for (int i = 0; i < grid.size(); ++i) {
            for (int j = 0; j < grid[i].size(); ++j) {
                ans = max(ans, expand(grid, i, j));
            }
        }
        return ans;
    }
    
    int expand(vector<vector<int>>& grid, int i, int j) {
        if (i < 0 || i >= grid.size()) return 0;
        if (j < 0 || j >= grid[i].size()) return 0;
        if (grid[i][j] != 1) return 0;
        grid[i][j] = -1;
        return 1 + expand(grid, i+1, j)
             + expand(grid, i-1, j)
             + expand(grid, i, j+1)
             + expand(grid, i, j-1);
    }
};
