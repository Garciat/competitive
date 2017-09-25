// https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=41
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct building { int l, h, r; };

int main() {
  vector<building> bs;
  bs.reserve(5000);
  
  int ml = 100000;
  int mr = 0;
  building b;
  while (cin >> b.l >> b.h >> b.r) {
    b.l *= 2;
    b.r *= 2;
    bs.push_back(b);
    ml = min(ml, b.l);
    mr = max(mr, b.r);
  }
  
  int ch = 0;
  for (int i = ml; i < mr; ++i) {
    int mh = 0;
    for (auto&& b : bs) {
      if (i >= b.l && i <= b.r) {
        if (b.h > mh) {
          mh = b.h;
        }
      }
    }
    if (mh != ch) {
      if (mh > ch) {
        cout << i/2;
      } else {
        cout << (i - 1)/2;
      }
      cout << ' ' << mh << ' ';
    }
    ch = mh;
  }
  cout << (mr/2) << " 0\n";
}