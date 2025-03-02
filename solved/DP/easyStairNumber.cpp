#include <iostream>
using namespace std;

const long long mod = 1000000000;

int main() {
    int n;
    cin >> n;

    long long **memo;
    memo = new long long*[10];
    for (int i = 0; i < 10; i++) {
        memo[i] = new long long[n + 1];
        for (int j = 0; j <= n; j++) {
            if (i == 0) memo[i][j] = 0;
            else if (j == 0) memo[i][j] = 1;
            else memo[i][j] = 0;
        }
    }
    for (int y = 1; y <= n; y++) {
        for (int x = 0; x < 10; x++) {
            if (x == 0) {
                memo[x][y] = memo[x + 1][y - 1] % mod;
            }
            else if (x == 9) {
                memo[x][y] = memo[x - 1][y - 1] % mod;
            }
            else {
                memo[x][y] = (memo[x - 1][y - 1] + memo[x + 1][y - 1]) % mod;
            }
        }
    }

    long long result = 0;
    for (int i = 0; i < 10; i++) {
        result = (result + memo[i][n - 1]) % mod;
    }
    cout << result << endl;
}