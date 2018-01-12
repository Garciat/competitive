// http://codeforces.com/problemset/problem/913/C

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

struct Offer {
  long long cost;
  int volume;
};

vector<Offer> build_best_offers_vector(const vector<int>& c, const int L) {
  vector<Offer> offers;

  for (int i = 0; i < (int)c.size(); ++i) offers.push_back(Offer{c[i], 1 << i});

  for (int i = 1; i < (int)c.size(); ++i) {
    long long alt_cost = offers[i - 1].cost * 2;

    if (alt_cost < offers[i].cost) offers[i].cost = alt_cost;

    for (int j = i - 1; j >= 0 && offers[j].cost > offers[i].cost; --j)
      offers[j].cost = offers[i].cost;
  }

  while (offers.size() < 31 && offers.back().volume < L) {
    long long prev_cost = offers.back().cost;
    int prev_volume = offers.back().volume;
    offers.push_back(Offer{prev_cost * 2, prev_volume * 2});
  }

  return offers;
}

long long find_best_cost(int L, const vector<Offer>& offers, int offer_idx) {
  if (L <= 0)
    return 0;

  if (offer_idx == 0)
    return offers[offer_idx].cost;

  if (offers[offer_idx].volume <= L)
    return offers[offer_idx].cost + find_best_cost(L - offers[offer_idx].volume, offers, offer_idx - 1);

  return min(
    offers[offer_idx].cost,
    find_best_cost(L, offers, offer_idx - 1)
  );
}

long long solve(const int L, const vector<int>& c) {
  auto offers = build_best_offers_vector(c, L);
  return find_best_cost(L, offers, offers.size() - 1);
}

int main() {
  int n, L;
  while (cin >> n >> L) {
    vector<int> c(n);
    for (int i = 0; i < n; ++i) cin >> c[i];
    cout << solve(L, c) << endl;
  }
  return 0;
}
