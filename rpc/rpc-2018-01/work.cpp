#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct modulo_of {
    int x;
    modulo_of(int x) : x(x) { }
    bool operator()(int m, int n) {
        return x % m < x % n;
    }
};

int main() {
    int n, t;
    cin >> n;
    vector<int> hs(n);
    for (int i = 0; i < n; ++i)
        cin >> hs[i];
    cin >> t;

    cout << *min_element(hs.begin(), hs.end(), modulo_of(t)) << endl;

    return 0;
}
