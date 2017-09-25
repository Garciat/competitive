// https://leetcode.com/problems/two-sum/

/*

fails:
    
    sorted but forgot reordered indices
    
    use lower_bound on unsorted stuff
    
    implement movement wrongly
    
    reuse numbers...

*/

class Solution {
public:
    vector<int> twoSum(vector<int> &nums, int target) {
        vector<int> cpy = nums;
        
        sort(begin(nums), end(nums));
        
        int iL = 0;
        int iR = nums.size() - 1;
        
        while (iL < iR) {
            int s = nums[iL] + nums[iR];
            if (s == target) {
                int kL = find(begin(cpy), end(cpy), nums[iL]) - begin(cpy);
                int kR = find(begin(cpy), end(cpy), nums[iR]) - begin(cpy);
                if (kL == kR) {
                    kR = find(begin(cpy)+kR+1, end(cpy), nums[iR]) - begin(cpy);
                }
                return {kL, kR};
            }
            if (s < target) {
                iL += 1;
            } else {
                iR -= 1;
            }
        }
    }
};
