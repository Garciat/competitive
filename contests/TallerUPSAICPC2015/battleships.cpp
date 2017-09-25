// https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=3104

#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <utility>
#include <sstream>

using namespace std;

int read_int() {
  string s;
  getline(cin, s);
  istringstream iss{s};
  int n;
  iss >> n;
  return n;
}

enum state { EMPTY, ALIVE, HIT };

state grid[100][100];
int checked[100][100];

void expand(int i, int j, int n) {
  if (i < 0 || j < 0 || i >= n || j >= n) return;
  if (checked[i][j]) return;
  if (grid[i][j] == EMPTY) return;
  checked[i][j] = 1;
  expand(i-1, j, n);
  expand(i+1, j, n);
  expand(i, j-1, n);
  expand(i, j+1, n);
}

int main() {
  int ttt = read_int();
  for (int t = 0; t < ttt; ++t) {
    memset(grid, 0, sizeof(grid));
    memset(checked, 0, sizeof(checked));
    
    int n = read_int();
    string ln;
    
    vector<pair<int,int>> check;
    
    for (int i = 0; i < n; ++i) {
      getline(cin, ln);
      for (int j = 0; j < n; ++j) {
        switch (ln[j]) {
        case 'x':
          grid[i][j] = ALIVE;
          check.push_back(make_pair(i, j));
          break;
        case '@':
          grid[i][j] = HIT;
          break;
        }
      }
    }
    
    int alives = 0;
    
    for (auto&& cc : check) {
      if (checked[cc.first][cc.second]) continue;
      expand(cc.first, cc.second, n);
      alives += 1;
    }
    
    cout << "Case " << (t+1) << ": " << alives << '\n';
  }
}