#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
using namespace std;

void print(vector<vector<int>>& v) {
    for (auto& row : v) {
        for (auto& ele : row) cout << ele << ' ';
        cout << '\n';
    }
}

int sol(vector<int>& v, int n) {
    vector<vector<int>> dp(n + 2, vector<int>(n + 1, 0));
    for (int i = n; i >= 1; i--) {
        for (int j = i; j <= n; j++) {
            dp[i][j] = dp[i+1][j] + v[i];
        }
    }
    // for (int i = n; i >= 1; i--) {
    //     for (int j = i + 2; j <= n; j++) {
    //         int value = INT_MAX;
    //         for (int k = i + 1; k <= j; k++) {
    //             value = min(value, dp[k][j] + dp[i][k-1]);
    //         }
    //         dp[i][j] += value;
    //     }
    // }
    print(dp);
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
        vector<int> vec(k + 1, 0);
        for (int i = 1; i <= k; i++) cin >> vec[i];
        result.push_back(sol(vec, k));
    }
    for (int& v : result) cout << v << '\n';
}