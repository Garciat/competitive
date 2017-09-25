// https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=945
#include <iostream>
#include <cstring>
#include <stack>
#include <utility>

using namespace std;

int graph[200][200];
int colors[200];

#define COL1 1
#define COl2 2

int swapper[] = { 0, 2, 1 };

int main() {
  int n, l;
  
  while (cin >> n >> l && n) {
    memset(graph, 0, sizeof(graph));
    memset(colors, 0, sizeof(colors));
    
    for (int i = 0; i < l; ++i) {
      int a, b;
      cin >> a >> b;
      graph[a][b] = graph[b][a] = 1;
    }
    
    stack<pair<int, int> > todo;
    todo.push(make_pair(0, COL1));
    
    while (!todo.empty()) {
      pair<int, int> cur = todo.top();
      todo.pop();
      
      int i = cur.first;
      int me = cur.second;
      
      colors[i] = me;
      
      for (int j = 0; j < n; ++j) {
        if (graph[i][j]) {
          int other = colors[j];
          
          if (other == 0) {
            todo.push(make_pair(j, swapper[me]));
          } else {
            if (me == other) {
              goto ABORT_MISSION;
            }
          }
        }
      }
    }
    
    cout << "BICOLORABLE.\n";
    continue;
  ABORT_MISSION:
    cout << "NOT BICOLORABLE.\n";
  }
}