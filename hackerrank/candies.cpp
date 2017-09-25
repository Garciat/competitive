// https://www.hackerrank.com/challenges/candies

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

#define int long long
  
int n;
int ratings[100001];

int answers[100001]{};

int candies(int i) {
  if (answers[i] != 0)
    return answers[i];
  int c;
  if (i == 0) {
    if (ratings[i] <= ratings[i+1]) {
      c = 1;
    } else {
      c = 1 + candies(i+1);
    }
  } else if (i == n-1) {
    if (ratings[i] <= ratings[i-1]) {
      c = 1;
    } else {
      c = 1 + candies(i-1);
    }
  } else {
    int LB = ratings[i] <= ratings[i-1];
    int RB = ratings[i] <= ratings[i+1];
    if (LB && RB) {
      c = 1;
    } else if (LB) {
      c = 1 + candies(i+1);
    } else if (RB) {
      c = 1 + candies(i-1);
    } else {
      c = 1 + max(candies(i-1), candies(i+1));
    }
  }
  return answers[i] = c;
}

int32_t main() {
  cin >> n;
  if (n == 1) {
    cout << "1\n";
    return 0;
  }
  for (int i = 0; i < n; ++i) {
    cin >> ratings[i];
  }
  int s = 0;
  for (int i = 0; i < n; ++i) {
    s += candies(i);
  }
  cout << s << endl;
  return 0;
}
