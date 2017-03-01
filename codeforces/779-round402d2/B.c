#include <stdio.h>

int solve(int n, int k) {
    if (n == 0) {
        return 0;
    }

    int digits = 0;
    int zerosLeft = k;
    int cuts = 0;

    while (n != 0) {
        if (zerosLeft == 0) {
            return cuts;
        }
        if (n % 10 == 0) {
            zerosLeft -= 1;
        } else {
            cuts += 1;
        }
        digits += 1;
        n /= 10;
    }

    return digits - 1;
}

int main(int argc, char *argv[]) {
    int n, k;
    scanf("%d %d", &n, &k);

    int ans = solve(n, k);
    printf("%d\n", ans);

    return 0;
}
