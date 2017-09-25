#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> ps(n);
    for (int& p : ps)
        cin >> p;
    
    double ans = 0;

    for (int p : ps)
        ans += (double)p / ps.size();
    
    cout << fixed << setprecision(14) << ans << endl;

    return 0;
}
