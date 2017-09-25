#include <iostream>

using namespace std;

template <typename T>
T ceilDiv(T x, T y) {
    return (x + y - 1) / y;
}

int main() {
    long long n, m, a;
    cin >> n >> m >> a;

    cout << ceilDiv(n, a) * ceilDiv(m, a) << endl;

    return 0;
}
