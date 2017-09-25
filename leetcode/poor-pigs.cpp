// https://leetcode.com/problems/poor-pigs/

class Solution {
public:
    int poorPigs(int buckets, int minutesToDie, int minutesToTest) {
        if (minutesToDie > minutesToTest) {
            exit(1);
        }
        
        return ceil(log(buckets)/log(1 + minutesToTest / minutesToDie));
    }
};
