#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int LCS(string a, string b) {
    int a_len = a.length();
    int b_len = b.length();
    vector<vector<int>> memo(a_len + 1, vector<int>(b_len + 1, 0));
    
    for (int i = a_len - 1; i >= 0; i--) {
        for (int j = b_len - 1; j >= 0; j--) {
            if (a[i] == b[j]) memo[i][j] = memo[i + 1][j + 1] + 1;
            else memo[i][j] = max(memo[i][j + 1], memo[i + 1][j]);
        }
    }
    return memo[0][0];
}

int main() {
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    string a, b;
    cin >> a >> b;
    if (a.length() < b.length()) swap(a, b);
    cout << LCS(a, b) << '\n';
}