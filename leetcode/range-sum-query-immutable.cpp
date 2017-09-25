// https://leetcode.com/problems/range-sum-query-immutable/

class NumArray {
    vector<int> z;
public:
    NumArray(vector<int> nums) : z(nums.size()) {
        int s = 0;
        for (int i = 0; i < nums.size(); ++i) {
            s += nums[i];
            z[i] = s;
            cout << s << endl;
        }
    }
    
    int sumRange(int i, int j) {
        int a = z[j];
        if (i > 0) a -= z[i-1];
        return a;
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray obj = new NumArray(nums);
 * int param_1 = obj.sumRange(i,j);
 */
