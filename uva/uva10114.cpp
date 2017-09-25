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
        int duration;
        double down, amount;
        int n;

        cin >> duration >> down >> amount >> n;

        if (duration < 0) break;

        vector<pair<int, double>> rates(n);
        for (auto& r : rates)
            cin >> r.first >> r.second;
        
        // sentinel rate
        rates.push_back(rates.back());
        rates.back().first = duration + 1;

        pair<int, double> rate = rates[0];
        int rate_i = 1;
        
        double billed = amount / duration;
        double owes = amount + billed;
        double value = down + amount;

        int ans = -1;

        for (int i = 0; i <= duration; ++i) {
            if (i == rates[rate_i].first) {
                rate = rates[rate_i++];
            }

            // cout << i << ' ' << value << "->" << value*(1.0 - rate.second)
            //      << ' ' << owes << "->" << (owes - billed) << ' ' << rate.second << endl;
            value *= 1.0 - rate.second;
            owes -= billed;

            if (value > owes) {
                ans = i;
                break;
            }
        }

        if (ans == 1)
            cout << "1 month" << endl;
        else
            cout << ans << " months" << endl;
    }
    
    return 0;
}
