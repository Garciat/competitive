// https://leetcode.com/problems/nth-digit/

#define int long long

class Solution {
public:
    int findNthDigit(int n) {
        int s = 1;
        int d = 1;
        int p = 0;
        
        for (;;) {
            int pp = p + 9 * s * d;
            if (pp >= n) {
                break;
            }
            p = pp;
            s *= 10;
            d += 1;
        }
        
        int k = n - p - 1;
        int x = s + k / d;
        int r = k % d;
        
        int y = x;
        int w = s;
        for (int i = 0; i < r; ++i) {
            y %= w;
            w /= 10;
        }
        
        cout << "s=" << s << endl;
        cout << "d=" << d << endl;
        cout << "p=" << p << endl;
        cout << "k=" << k << endl;
        cout << "x=" << x << endl;
        cout << "r=" << r << endl;
        cout << "y=" << y << endl;
        cout << "w=" << w << endl;
        
        return y / w;
    }
};
