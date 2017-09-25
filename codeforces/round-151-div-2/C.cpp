// http://codeforces.com/problemset/problem/246/C

#include <iostream>
#include <algorithm>

using namespace std;

int soldiers[50];

int main() {
    int N, K;
    cin >> N >> K;
    
    for (int i = 0; i < N; ++i) {
        cin >> soldiers[i];
    }
    
    sort(soldiers, soldiers + N);
    
    int count = 0;
    
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N - i; ++j) {
            cout << i + 1 << ' ';
            cout << soldiers[j] << ' ';
            
            for (int k = 0; k < i; ++k) {
                cout << soldiers[N - i + k] << ' ';
            }
            
            cout << '\n';
            
            if (++count == K) {
                return 0;
            }
        }
    }
}
