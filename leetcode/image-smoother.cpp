// https://leetcode.com/problems/image-smoother/

class Solution {
public:
    vector<vector<int>> imageSmoother(vector<vector<int>>& M) {
        auto N = M;
        
        for (int i = 0; i < M.size(); ++i) {
            for (int j = 0; j < M[i].size(); ++j) {
                int x = 0;
                int n = 0;
                for (int di = -1; di <= 1; ++di) {
                    for (int dj = -1; dj <= 1; ++dj) {
                        x += at(N, i + di, j + dj, n);
                    }
                }
                M[i][j] = x / n;
            }
        }
        
        return M;
    }
    
    static int at(vector<vector<int>> &M, int i, int j, int &n) {
        if (!(0 <= i && i < M.size())) return 0;
        if (!(0 <= j && j < M[i].size())) return 0;
        return n += 1, M[i][j];
    }
};
