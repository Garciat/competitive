// https://leetcode.com/problems/remove-duplicates-from-sorted-array/

/*

simple algo:
    
    while value {i+1} is equal to the value {i}, keep count
    when that no longer holds, if the count is greater than 1,
        erase elements from lowest index to highest - 1
    
    time: O(n^2) because of erase shifting
    space: O(1)

simple algo v2:

    same thing, but instead of earsing, save the ranges
    finally, iterate through the array, copying values into place, skipping those ranges
    then, erase the tail of the array
    
    time: O(n)
    space: O(n)

*/

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.size() == 0) return 0;
        
        int len = 1;
        
        for (int i = 1; i < nums.size(); ++i) {
            if (nums[i] != nums[len-1]) {
                nums[len++] = nums[i];
            }
        }
        
        return len;
    }
};
