#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void sort(vector<int>& a, vector<int>& b, int n) {
    for (int i = n - 1; i >= 0; i--) {
        for (int j = 0; j + 1 < i; j++) {
            if (a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
                swap(b[j], b[j + 1]);
            }
        }
    }
}

int sol(vector<int> a, vector<int> b, int n) {
    vector<int> memo(n, 1);
    for (int i = n - 2; i >= 0; i--) {
        for (int j = i + 1; j < n; j++) {
            if (b[i] < b[j]) {
                memo[i] = max(memo[i], memo[j] + 1);
            }
        }
    }
    return n - *max_element(memo.begin(), memo.end());
}

int main() {
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;

    vector<int> A(n);
    vector<int> B(n);

    for (int i = 0; i < n; i++) {
        cin >> A[i] >> B[i];
    }
    sort(A, B, n);
    cout << sol(A, B, n) << '\n';
}