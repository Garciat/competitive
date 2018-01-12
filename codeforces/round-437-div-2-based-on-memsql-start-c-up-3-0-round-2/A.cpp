// http://codeforces.com/problemset/problem/867/A

#include <iostream>
using namespace std;

int main() {
    int n; cin >> n;
    getchar(); // '\n'

    int sf = 0;
    int fs = 0;

    int prev = getchar();

    for (int i = 1; i <= n; ++i) {
        int next = getchar();

        if (prev == 'S' && next == 'F') {
            sf += 1;
        }
        if (prev == 'F' && next == 'S') {
            fs += 1;
        }

        prev = next;
    }

    cout << (sf > fs ? "YES" : "NO") << endl;

    return 0;
}
