#include <bits/stdc++.h>
using namespace std;

class stuff {
public: 
    int w;
    int v;
};

int n, k;
vector<stuff> stuffs;

int getMaximumValue() {
    // dp[i][j] = i개의 물체를 고르고, 가치가 k 일 때 최대의 가치
    vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= k; j++) {
            if (j < stuffs[i - 1].w) {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            } 
            else {
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - stuffs[i - 1].w] + stuffs[i - 1].v);
            }
        }
    }
    return dp[n][k];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    cin >> n >> k;
    stuffs.assign(n, {0, 0});
    for (int i = 0; i < n; i++) cin >> stuffs[i].w >> stuffs[i].v;

    cout << getMaximumValue() << '\n';
}