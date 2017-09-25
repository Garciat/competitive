// http://codeforces.com/problemset/problem/405/A

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

    vector<int> as(n);
    for (int& a : as)
        cin >> a;
    
    sort(begin(as), end(as));

    for (int a : as)
        cout << a << ' ';
    cout << endl;

    return 0;
}
