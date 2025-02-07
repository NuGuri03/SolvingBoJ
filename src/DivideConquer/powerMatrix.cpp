#include <iostream>
#include <vector>
#define p 1000
using namespace std;

vector<vector<int>> unit;

vector<vector<int>> power(vector<vector<int>> &matrix, int n, long long b) {
    if (b == 0) return unit;

    vector<vector<int>> halfM(n, vector<int>(n, 0));
    halfM = power(matrix, n, b / 2);

    vector<vector<int>> tempM = halfM;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            long long temp = 0;
            for (int k = 0; k < n; k++) {
                temp = (temp % p + (tempM[i][k] * tempM[k][j]) % p) % p;
            }
            halfM[i][j] = temp;
        }
    }

    tempM = halfM;
    if (b % 2 == 1) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                long long temp = 0;
                for (int k = 0; k < n; k++) {
                    temp += (tempM[i][k] * matrix[k][j]) % p;
                    temp %= p;
                }
                halfM[i][j] = temp;
            }
        }
    }
    return halfM;
}

int main() {
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int n;
    long long b;
    cin >> n >> b;

    unit.resize(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) unit[i][i] = 1;
    
    vector<vector<int>> matrix(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) cin >> matrix[i][j];
    }

    matrix = power(matrix, n, b);
    for (auto& row : matrix) {
        for (auto& ele : row) cout << ele << ' ';
        cout << '\n';
    }
}
