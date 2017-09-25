// https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1625
#include <iostream>
#include <algorithm>

using namespace std;

int bets[10000];

int main() {
  int n;
  while (cin >> n && n) {
    for (int i = 0; i < n; ++i) {
      cin >> bets[i];
    }
    
    int mh, mm;
    mh = mm = bets[0];
    
    for (int i = 1; i < n ; ++i) {
      int x = bets[i];
      mh = max(x, mh + x);
      mm = max(mm, mh);
    }
    
    if (mm <= 0) {
      cout << "Losing streak.\n";
    } else {
      cout << "The maximum winning streak is " << mm << ".\n";
    }
  }
}