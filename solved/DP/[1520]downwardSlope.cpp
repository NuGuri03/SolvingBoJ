#include <bits/stdc++.h>
using namespace std;

int m, n;
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
vector<vector<int>> dp;

void print_dp() {
    for (auto& row : dp) {
        for (auto& ele : row) cout << setw(3) << ele << ' ';
        cout << '\n';
    }
    cout << '\n';
}

int dfs(vector<vector<int>>& matrix, int i, int j) {
    if (i == m - 1 && j == n - 1) return 1;
    if (dp[i][j] != -1) return dp[i][j];

    dp[i][j] = 0;
    for (int k = 0; k < 4; k++) {
        int di = i + dx[k];
        int dj = j + dy[k];

        bool isInside = (0 <= di && di < m) && (0 <= dj && dj < n);
        if (!isInside) continue;

        if (matrix[di][dj] < matrix[i][j]) {
            dp[i][j] += dfs(matrix, di, dj);
        }
        cout << '(' << i << ", " << j << ")\n";
        print_dp();
    }
    return dp[i][j];
}

int count_H(vector<vector<int>>& matrix) {
    dp.assign(m, vector<int>(n, -1));
    return dfs(matrix, 0, 0);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    cin >> m >> n;
   
    vector<vector<int>> matrix(m, vector<int>(n, 0));
   
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) cin >> matrix[i][j];
    }
    cout << count_H(matrix) << '\n';
}