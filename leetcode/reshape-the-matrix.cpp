// https://leetcode.com/problems/reshape-the-matrix/

class Solution {
public:
    vector<vector<int>> matrixReshape(vector<vector<int>>& nums, int r, int c) {
        if (nums.size() == 0) {
            return nums;
        }
        if (nums.size() * nums[0].size() != r * c) {
            return nums;
        }
        
        vector<vector<int>> m(r, vector<int>(c, 0));
        
        int a = 0;
        int b = 0;
        
        for (int i = 0; i < nums.size(); ++i) {
            for (int j = 0; j < nums[0].size(); ++j) {
                m[a][b++] = nums[i][j];
                
                if (b == c) {
                    a += 1;
                    b = 0;
                }
            }
        }
        
        return m;
    }
};
