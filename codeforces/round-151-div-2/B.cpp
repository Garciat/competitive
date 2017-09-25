// http://codeforces.com/problemset/problem/246/B

#include <cstdio>
#include <iostream>

using namespace std;

int main() {
	int N;

	scanf("%d", &N);

	if (N == 1) {
		puts("1");
		return 0;
	}

	int s = 0;

	for (int i = 0; i < N; ++i) {
		int t;
		scanf("%d", &t);
		s += t;
	}

	printf("%d\n", s % N == 0 ? N : N - 1);
}
