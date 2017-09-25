// http://codeforces.com/problemset/problem/779/A

#include <stdio.h>

#define MAX_N 101

typedef struct {
    int values[6];
} perf_count;

int abs(int x) {
    return x < 0 ? -x : x;
}

// assumption: academic performance is in [1..5]
perf_count read_academic_perf_fast(int n) {
    char line[MAX_N * 2 + 1];
    // n times: read ac.perf. (one char) + one space / final '\n'
    fread(line, sizeof(char), n * 2, stdin);
    // "parse" & count:
    perf_count result = {.values = {0}};
    for (int i = 0; i < n; ++i) {
        int perf = line[i*2] - '0';
        result.values[perf] += 1;
    }
    return result;
}

int solve(perf_count a_count, perf_count b_count) {
    int sum = 0;
    for (int i = 1; i <= 5; ++i) {
        int d = abs(a_count.values[i] - b_count.values[i]);
        if (d % 2 == 1) {
            return -1;
        }
        sum += d;
    }
    return sum / 4;
}

int main(int argc, char *argv[]) {
    int n;
    scanf("%d\n", &n);

    perf_count a_count = read_academic_perf_fast(n);
    perf_count b_count = read_academic_perf_fast(n);

    int ans = solve(a_count, b_count);

    printf("%d\n", ans);

    return 0;
}
