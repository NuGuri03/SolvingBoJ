#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;

    int *memo = new int[n + 1];
    for (int i = 0; i <= n; i++) memo[i] = 0;

    int count;
    count = 1;
    for (int i = 2; i <= n; i *= 2) memo[i] = count++;
    count = 1;
    for (int i = 3; i <= n; i *= 3) memo[i] = count++;
    count = 2;
    for (int i = 6; i <= n; i *= 2) memo[i] = count++;
    count = 2;
    for (int i = 6; i <= n; i *= 3) memo[i] = count++;
    count = 2;
    for (int i = 6; i <= n; i *= 6) {
        memo[i] = count;
        count += 2;
    }

    for (int i = 4; i <= n; i++) {
        if (memo[i] == 0) {
            int num = memo[i - 1] + 1;
            if (i % 2 == 0) {
                num = memo[i / 2] + 1 < num ? memo[i / 2] + 1 : num;
            }
            if (i % 3 == 0) {
                num = memo[i / 3] + 1 < num ? memo[i / 3] + 1 : num;
            }
            memo[i] = num;
        }
    }
    cout << memo[n] << '\n';
}