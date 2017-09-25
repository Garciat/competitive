// https://leetcode.com/problems/spiral-matrix/

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        if (matrix.empty()) return {};
        
        int a = 0;
        int b = 0;
        int r = matrix.size();
        int s = matrix[0].size();
        int d = 1;
        
        vector<int> ans;
        
        for (;;) {
            cout << a << ' ' << b << ' ' << r << ' ' << s << endl;
            if (d == 1) {
                for (int j = b; j < b+s; ++j) {
                    ans.push_back(matrix[a][j]);
                }
                for (int i = a+1; i < a+r; ++i) {
                    ans.push_back(matrix[i][b+s-1]);
                }
                
                a += 1;
            } else {
                for (int j = b+s-1; j >= b; --j) {
                    ans.push_back(matrix[a+r-1][j]);
                }
                for (int i = a+r-2; i >= a; --i) {
                    ans.push_back(matrix[i][b]);
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
        
        return ans;
    }
};
