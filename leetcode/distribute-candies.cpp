// https://leetcode.com/problems/distribute-candies/

class Solution {
public:
    int distributeCandies(vector<int>& candies) {
        sort(begin(candies), end(candies));
        
        int k = 1;
        for (int i = 1; i < candies.size(); ++i) {
            if (candies[i - 1] != candies[i]) {
                k += 1;
            }
        }
        
        return min(k, (int)candies.size() / 2);
    }
};
