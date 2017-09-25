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
    string s;
    cin >> s;

    string t;
    for (int i = 0; i < s.size(); ++i) {
        if (isupper(s[i])) {
            t += tolower(s[i]);
        } else {
            if (i > 0) break;
            t += toupper(s[i]);
        }
    }

    if (s.size() == t.size()) {
        cout << t << endl;
    } else {
        cout << s << endl;
    }

    return 0;
}
