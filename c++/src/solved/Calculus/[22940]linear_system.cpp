#include <bits/stdc++.h>
using namespace std;

void make_pivot_1(vector<double>& row, int i, int n) {
    if (row[i] == 0 || row[i] == 1) return;

    double div = row[i];
    for (int j = i; j <= n; j++) row[j] /= div;
}

void make_echelon_form(vector<vector<double>>& m, int n) {
    for (int i = 0; i < n; i++) {
        if (m[i][i] == 0) {
            for (int j = i + 1; j < n; j++) {
                if (m[j][i] != 0) {
                    swap(m[i], m[j]);
                    break;
                }
            }
        }
        
        make_pivot_1(m[i], i, n);
        
        for (int j = i + 1; j < n; j++) {
            double mult = m[j][i] / m[i][i];
            for (int k = i; k <= n; k++) {
                m[j][k] = m[j][k] - m[i][k] * mult;
            }
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        if (m[i][i] == 0) continue;
        
        make_pivot_1(m[i], i, n);

        for (int j = i - 1; j >= 0; j--) {
            double mult = m[j][i] / m[i][i];
            for (int k = i; k <= n; k++) {
                m[j][k] -= m[i][k] * mult;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n;
    cin >> n;

    vector<vector<double>> augumented_matrix(n, vector<double>(n + 1, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n + 1; j++) cin >> augumented_matrix[i][j];
    }

    make_echelon_form(augumented_matrix, n);

    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j <= n; j++) cout << augumented_matrix[i][j] << ' ';
    //     cout << '\n';
    // }

    vector<double> solution(n);
    for (int i = 0; i < n; i++) solution[i] = augumented_matrix[i][n];

    for (double& s : solution) cout << s << ' ';
    cout << '\n';
}