#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
using namespace std;

int merge(vector<int>& v, int n) {
    vector<vector<int>> dp(n + 2, vector<int>(n + 1, 0));
    
    //init dp()
    for (int i = n; i >= 1; i--) {
        for (int j = i; j <= n; j++) {
            dp[i][j] = dp[i+1][j] + v[i - 1];
        }
    }
    // //dp
    for (int i = n; i >= 1; i--) {
        for (int j = i + 2; j <= n; j++) {
            int value = min(dp[i][j - 1], dp[i+1][j]);
            for (int k = j - 2; k >=  i; k--) {
                value = min(value, dp[i][k] + dp[k + 1][j]);
            }
            dp[i][j] += value;
        }
    }
    return dp[1][n];
}

int main() {
    fastio;
    int t;
    cin >> t;

    vector<int> result;
    while (t--) {
        int k;
        cin >> k;
        vector<int> vec(k, 0);
        for (int i = 0; i < k; i++) cin >> vec[i];
        result.push_back(merge(vec, k));
    }
    for (int& v : result) cout << v << '\n';
}