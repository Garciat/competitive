// https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=2315
#include <iostream>
#include <sstream>
#include <cstring>
#include <string>

using namespace std;

int weights[1000];

int read_int() {
  string s;
  getline(cin, s);
  istringstream iss{s};
  int n;
  iss >> n;
  return n;
}

void read_weight() {
  char c = cin.get();
  cin >> weights[c];
  cin.ignore(100, '\n');
}

int main() {
  int n = read_int();
  
  for (int t = 0; t < n; ++t) {
    int k = read_int();
    
    memset(weights, 0, sizeof(weights));
    
    for (int i = 0; i < k; ++i) {
      read_weight();
    }
    
    int m = read_int();
    int value = 0;
    int lines = 0;
    
    for (;;) {
      char c = cin.get();
      value += weights[c];
      if (c == '\n') lines += 1;
      if (lines == m) break;
    }
    
    cout << (value/100) << '.';
    int ptm = value % 100;
    if (ptm < 10) cout << '0';
    cout << ptm << "$\n";
  }
}