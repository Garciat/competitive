// https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/

class Solution {
public:
    vector<int> twoSum(vector<int>& ns, int target) {
        int iL = 0;
        int iR = ns.size() - 1;
        
        while (iL < iR) {
            if (ns[iL] + ns[iR] == target) {
                return {iL + 1, iR + 1};
            }
            if (ns[iL] + ns[iR] < target) {
                iL += 1;
            }
            if (ns[iL] + ns[iR] > target) {
                iR -= 1;
            }
        }
    }
};
