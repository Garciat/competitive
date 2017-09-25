// https://leetcode.com/problems/spiral-matrix-ii/

class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        if (!n) return {};
        
        vector<vector<int>> matrix(n, vector<int>(n, 0));
        
        int a = 0;
        int b = 0;
        int r = matrix.size();
        int s = matrix[0].size();
        int d = 1;
        int x = 1;
        
        auto elem = [&x]() { return x++; };
        
        for (;;) {
            cout << a << ' ' << b << ' ' << r << ' ' << s << endl;
            if (d == 1) {
                for (int j = b; j < b+s; ++j) {
                    matrix[a][j] = elem();
                }
                for (int i = a+1; i < a+r; ++i) {
                    matrix[i][b+s-1] = elem();
                }
                
                a += 1;
            } else {
                for (int j = b+s-1; j >= b; --j) {
                    matrix[a+r-1][j] = elem();
                }
                for (int i = a+r-2; i >= a; --i) {
                    matrix[i][b] = elem();
                }
                
                b += 1;
            }
            
            r -= 1;
            s -= 1;
            d *= -1;
            
            if (!r || !s) {
                break;
            }
        }
        
        return matrix;
    }
};
