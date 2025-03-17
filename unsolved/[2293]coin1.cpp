#include <bits/stdc++.h>
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
using namespace std;

int n, k;
vector<int> coin;

int countCoin() {
    // dp 정의
    vector<int> dp(k + 1, 0);
    for (int i = 0; i < n; i++) {
        for (int j = 1; j <= k; j++) {
            if (j % coin[i] == 0) dp[j]++;
        }
        for (int j = 1; j <= k; j++) cout << dp[j] << ' ';
        cout << '\n';
    }

    return dp[k];
}

int main() {
    FASTIO;

    cin >> n >> k;
    coin.assign(n, 0);
    for (int i = 0; i < n; i++) cin >> coin[i];
    sort(coin.begin(), coin.end());

    cout << countCoin() << '\n';
}