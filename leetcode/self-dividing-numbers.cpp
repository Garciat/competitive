// https://leetcode.com/problems/self-dividing-numbers/

class Solution {
public:
    vector<int> selfDividingNumbers(int left, int right) {
        vector<int> ans;
        for (int i = left; i <= right; ++i) {
            if (isSelfDividing(i))
                ans.push_back(i);
        }
        return ans;
    }
    
    bool isSelfDividing(int n) {
        if (n == 0) return false;
        int t = n;
        for (;;) {
            if (t == 0) break;
            int d = t % 10;
            if (d == 0) return false;
            if (n % d != 0) return false;
            t /= 10;
        }
        return true;
    }
};
