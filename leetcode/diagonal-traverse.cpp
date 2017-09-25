// https://leetcode.com/problems/diagonal-traverse/

class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& matrix) {
        vector<int> list;
        int rows = matrix.size();
        if (rows == 0)
            return {};
        int cols = matrix[0].size();
        
        int limit = rows + cols;
        
        int sign = -1;
        for (int col_index = 0; col_index < limit; ++col_index) {
            if (sign > 0) {
                for (int row_index = 0; row_index < col_index + 1; ++row_index) {
                    int col = col_index - row_index;
                    int row = col_index - col;
                    if (row < rows && col < cols) {
                        list.push_back(matrix[row][col]);
                    }
                }
            } else {
                for (int row_index = col_index; row_index >= 0; --row_index) {
                    int col = col_index - row_index;
                    int row = col_index - col;
                    if (row < rows && col < cols) {
                        list.push_back(matrix[row][col]);
                    }
                }
            }
            sign *= -1;
        }
        
        return list;
    }
};
