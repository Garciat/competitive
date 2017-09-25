// https://leetcode.com/problems/construct-the-rectangle/

class Solution {
public:
    vector<int> constructRectangle(int area) {
        int k = (int)sqrt(area);
        while (k*(area/k) != area) --k;
        return {area/k, k};
    }
};
