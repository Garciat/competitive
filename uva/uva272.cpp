#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <bitset>
#include <array>
#include <map>
#include <set>
#include <cctype>
#include <cstdio>
using namespace std;

int main() {
    bool open = false;

    for (int c; (c = getchar()) != EOF; ) {
        if (c == '"') {
            cout << (open ? "''" : "``");
            open = !open;
        } else {
            putchar(c);
        }
    }

    return 0;
}
