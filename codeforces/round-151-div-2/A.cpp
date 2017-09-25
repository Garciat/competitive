// http://codeforces.com/problemset/problem/246/A

#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
	int N;

	scanf("%d", &N);

	if (N <= 2) {
		puts("-1");
		return 0;
	}

	for (int i = N; i >= 1; --i) {
		if (i < N) putchar(' ');
		printf("%d", i);
	}

	putchar('\n');
}
