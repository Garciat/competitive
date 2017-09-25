#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <bitset>
#include <array>
#include <map>
#include <set>
using namespace std;

int main() {
    int n;
    cin >> n;

    int i = 1;
    int c = 1;
    int s = 1;
    for (;;) {
        s += i + 1;
        c += s;
        if (c > n)
            break;
        i += 1;
    }

    cout << i << endl;

    return 0;
}
