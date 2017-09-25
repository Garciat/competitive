// https://leetcode.com/problems/third-maximum-number/

class Solution {
public:
    int thirdMax(vector<int>& nums) {
        set<int, greater<int>> mx;
        
        for (int n : nums) {
            mx.insert(n);
            if (mx.size() > 3)
                mx.erase(++++++mx.begin());
        }
        
        if (mx.size() == 3)
            return *++++mx.begin();
        else
            return *mx.begin();
    }
};
