#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int sol(vector<pair<int, int>>& m, int n) {
    vector<vector<int>> dp(n, vector<int>(n, 0));
    for (int i = n - 2; i >= 0; i--) {
        for (int j = i + 1; j < n; j++) {
            int temp = INT_MAX;
            for (int k = i; k < j; k++) {
                temp = min(temp, dp[i][k] + dp[k + 1][j] + m[i].first * m[k].second * m[j].second);
            }
            dp[i][j] = temp;
        }
    }
    return dp[0][n - 1];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n;
    cin >> n;
    vector<pair<int, int>> matrix(n, {0, 0});
    for (int i = 0; i < n; i++) {
        int r, c;
        cin >> r >> c;
        matrix[i] = {r, c};
    }

    cout << sol(matrix, n) << '\n';
}