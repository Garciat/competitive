// https://leetcode.com/problems/island-perimeter/

class Solution {
public:
    int islandPerimeter(vector<vector<int>>& grid) {
        int ans = 0;
        for (int i = 0; i < grid.size(); ++i) {
            for (int j = 0; j < grid[0].size(); ++j) {
                if (grid[i][j] == 1) {
                    work(grid, i, j, ans);
                    goto done;
                }
            }
        }
    done:
        return ans;
    }
    
    void work(vector<vector<int>>& grid, int i, int j, int &ans) {
        grid[i][j] = 2;
        
        if (i > 0) {
            if (grid[i-1][j] == 1)
                work(grid, i-1, j, ans);
            
            ans += grid[i-1][j] == 0;
        } else {
            ans += 1;
        }
        if (j > 0) {
            if (grid[i][j-1] == 1)
                work(grid, i, j-1, ans);
            
            ans += grid[i][j-1] == 0;
        } else {
            ans += 1;
        }
        
        if (i + 1 < grid.size()) {
            if (grid[i+1][j] == 1)
                work(grid, i+1, j, ans);
            
            ans += grid[i+1][j] == 0;
        } else {
            ans += 1;
        }
        if (j + 1 < grid[0].size()) {
            if (grid[i][j+1] == 1)
                work(grid, i, j+1, ans);
            
            ans += grid[i][j+1] == 0;
        } else {
            ans += 1;
        }
    }
};
