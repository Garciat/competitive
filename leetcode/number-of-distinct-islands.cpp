// https://leetcode.com/problems/number-of-distinct-islands/

struct MyPoint { int x, y; };

bool operator<(MyPoint p, MyPoint q) {
    return p.x < q.x || (p.x == q.x && p.y < q.y);
}

class Solution {
public:
    int numDistinctIslands(vector<vector<int>>& grid) {
        vector<MyPoint> points;
        unordered_set<string> islands;
        for (int i = 0; i < grid.size(); ++i) {
            for (int j = 0; j < grid[i].size(); ++j) {
                points.clear();
                
                expand(grid, i, j, points);
                
                if (points.size() == 0) continue;
                
                int minx = INT_MAX;
                int miny = INT_MAX;
                
                for (auto p : points) {
                    minx = min(minx, p.x);
                    miny = min(miny, p.y);
                }
                
                sort(begin(points), end(points));
                
                ostringstream oss;
                
                for (auto p : points) {
                    oss << "(" << (p.x-minx) << "," << (p.y-miny) << ")";
                }
                
                islands.insert(oss.str());
            }
        }
        return islands.size();
    }
    
    void expand(vector<vector<int>>& grid, int i, int j, vector<MyPoint> &points) {
        if (i < 0 || i >= grid.size()) return;
        if (j < 0 || j >= grid[i].size()) return;
        if (grid[i][j] != 1) return;
        grid[i][j] = -1;
        points.push_back(MyPoint{i, j});
        expand(grid, i+1, j, points);
        expand(grid, i-1, j, points);
        expand(grid, i, j+1, points);
        expand(grid, i, j-1, points);
    }
};
