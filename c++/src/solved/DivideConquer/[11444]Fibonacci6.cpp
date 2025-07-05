#include <iostream>
#include <vector>
#define mod 1000000007
using namespace std;

vector<vector<long long>> crossProduct(const vector<vector<long long>> m1, const vector<vector<long long>> m2) {
    long long a = m1.size();
    long long b = m2[0].size();
    
    vector<vector<long long>> result(a, vector<long long>(b, 0));
    for (int i = 0; i < result.size(); i++) {
        for (int j = 0; j < result[i].size(); j++) {
            int temp = 0;
            for (int k = 0; k < m2.size(); k++) {
                temp = (temp + (m1[i][k] * m2[k][j]) % mod) % mod;
            }
            result[i][j] = temp;
        }
    }
    return result;
}

vector<vector<long long>> powerMatrix(vector<vector<long long>> m, long long b) {
    if (b == 0) {
        long long size = m.size();
        vector<vector<long long>> unit(size, vector<long long>(size, 0));
        for (int i = 0; i < m.size(); i++) unit[i][i] = 1;
        return unit;
    }
    
    vector<vector<long long>> half = powerMatrix(m, b / 2);
    half = crossProduct(half, half);

    if (b % 2 == 1) half = crossProduct(half, m);

    return half;
} 

int main() {
    long long n;
    cin >> n;

    vector<vector<long long>> A = {{1, 1}, {1, 0}};
    vector<vector<long long>> B = {{1}, {0}};
    vector<vector<long long>> C = crossProduct(powerMatrix(A, n), B);

    cout << C[1][0] << '\n';
}