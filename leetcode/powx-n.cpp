// https://leetcode.com/problems/powx-n/

class Solution {
public:
    double myPow(double x, long long n) {
        if (n < 0) return myPow(1.0/x, -n);
        if (n == 0) return 1;
        auto y = myPow(x * x, n/2);
        if (n % 2 == 1)
            y *= x;
        return y;
    }
};
