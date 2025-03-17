#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int LIS(vector<int>& v, int n) {
    vector<int> memo(n, 1);
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (v[j] < v[i]) {
                memo[i] = max(memo[i], memo[j] + 1);
            }
        }
    }

    return *max_element(memo.begin(), memo.end());
}

int main() {
    int n;
    cin >> n;

    vector<int> v(n, 0);
    for (int i = 0; i < n; i++) cin >> v[i];

    cout << LIS(v, n) << endl;
}