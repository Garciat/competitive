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
    
    for (string s; getline(cin, s), s != "END"; ) {

        if (s == "1") {
            cout << "1" << endl;
            continue;
        }

        int i = 2;
        int n = s.size();

        for (;;) {
            int m = to_string(n).size();
            if (m == n) break;
            n = m;
            i += 1;
        }

        cout << i << endl;
    }

    return 0;
}
