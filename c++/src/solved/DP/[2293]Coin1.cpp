#include <bits/stdc++.h>
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
using namespace std;

int n, k;
vector<int> coin;

int count_coin() {
    vector<int> dp(k + 1, 0);
    dp[0] = 1;

    for (int i = 0; i < n; i++) {
        for (int j = coin[i]; j <= k; j++) {
            dp[j] += dp[j - coin[i]];
        }
    }
    
    return dp[k];
}

int main() {
    FASTIO;

    cin >> n >> k;
    coin.assign(n, 0);
    for (int i = 0; i < n; i++) cin >> coin[i];
    sort(coin.begin(), coin.end());

    cout << count_coin() << '\n';
}