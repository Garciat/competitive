// https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=2296
#include <iostream>
#include <algorithm>

using namespace std;

int nums[10000];

int main() {
  int n, m;
  while (cin >> n >> m && n && m) {
    for (int i = 0; i < n; ++i) {
      cin >> nums[i];
    }
    
    sort(nums, nums+n, [m] (int a, int b) {
      int am = a % m;
      int bm = b % m;
      
      if (am == bm) {
        int ao = a & 1;
        int bo = b & 1;
        
        if (ao && bo) {
          return b < a;
        }
        
        if (ao && !bo) {
          return true;
        }
        
        if (!ao && bo) {
          return false;
        }
        
        return a < b;
        
      } else {
        return am < bm;
      }
    });
    
    cout << n << ' ' << m << '\n';
    for (int i = 0; i < n; ++i) {
      cout << nums[i] << '\n';
    }
  }
  cout << "0 0\n";
}