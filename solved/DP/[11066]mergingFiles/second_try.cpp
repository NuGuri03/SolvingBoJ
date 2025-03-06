#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
using namespace std;

int merge(vector<int> &v, int n) {
    vector<vector<int>> dp(n, vector<int>(n, 0)) ;
    vector<int> prefix_sum(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        prefix_sum[i] = prefix_sum[i - 1] + v[i - 1];
    }

    for (int i = n - 1; i >= 0; i--) {
        
        for (int j = i + 1; j < n; j++) {
            int sum = prefix_sum[j + 1] - prefix_sum[i];

            dp[i][j] = INT_MAX;
            for (int k = i; k < j; k++) {
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j] + sum);
            }

        }
    }
    
    return dp[0][n - 1];
}

int main() {
    fastio;
    int t;
    cin >> t;

    while (t--) {
        int k;
        cin >> k;

        vector<int> files(k, 0);
        for (int i = 0; i < k; i++) cin >> files[i];
        
        cout << merge(files, k) << '\n';
    }
}