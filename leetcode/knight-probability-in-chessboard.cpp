// https://leetcode.com/problems/knight-probability-in-chessboard/

class Solution {
public:
    double knightProbability(int N, int K, int r, int c) {
        double *map1 = new double[N * N]{};
        double *map2 = new double[N * N]{};
        
        auto at = [N] (double *m, int i, int j) -> double& {
            return m[i*N + j];
        };
        
        auto get = [N] (double *m, int i, int j) -> double {
            if (i < 0 || i >= N || j < 0 || j >= N)
                return 0.0;
            else
                return m[i*N + j];
        };
        
        at(map1, r, c) = 1.0;
        
        for (int k = 0; k < K; ++k) {
            fill(map2, map2+N*N, 0.0);
            
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    at(map2, i, j) =
                        get(map1, i-1, j-2) / 8.0
                      + get(map1, i-2, j-1) / 8.0
                      + get(map1, i+1, j-2) / 8.0
                      + get(map1, i+2, j-1) / 8.0
                      + get(map1, i-1, j+2) / 8.0
                      + get(map1, i-2, j+1) / 8.0
                      + get(map1, i+1, j+2) / 8.0
                      + get(map1, i+2, j+1) / 8.0;
                }
            }
            
            swap(map1, map2);
        }
        
        double ans = 0.0;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                ans += at(map1, i, j);
            }
        }
        
        return ans;
    }
};
