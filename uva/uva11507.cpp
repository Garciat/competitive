#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <bitset>
#include <array>
#include <map>
#include <set>
#include <cctype>
using namespace std;

int main() {
    
    for (;;) {
        int n;
        cin >> n;

        if (n == 0) break;

        int x = 1;
        int y = 0;
        int z = 0;

        for (int i = 0; i < n - 1; ++i) {
            string r;
            cin >> r;

            if (r == "No") continue;

            int k = r[0] == '+' ? 1 : -1;

            int x_, y_, z_;

            switch (r[1]) {
            case 'y':
                x_ = y * -k;
                y_ = x * k;
                z_ = z;
                break;
            case 'z':
                x_ = z * -k;
                y_ = y;
                z_ = x * k;
                break;
            }

            x = x_;
            y = y_;
            z = z_;
        }

        string ans;
        if (x != 0)
            ans = x == 1 ? "+x" : "-x";
        if (y != 0)
            ans = y == 1 ? "+y" : "-y";
        if (z != 0)
            ans = z == 1 ? "+z" : "-z";
        
        cout << ans << endl;
    }

    return 0;
}
