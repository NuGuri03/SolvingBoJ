#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void sol(vector<int> v, int n) {
    int *memo = new int[n];

    //점화식 구하기
    memo[0] = v[0];
    memo[1] = v[0] + v[1];
    memo[2] = max(v[0] + v[2], v[1] + v[2]);

    for (int i = 3; i < n; i++) {
        memo[i] = max(memo[i - 2] + v[i], memo[i - 3] + v[i - 1] + v[i]);
    }
    
    cout << memo[n - 1] << endl;
}

int main() {
    int n;
    cin >> n;

    vector<int> v(n);
    for (int i = 0; i < n; i++) cin >> v[i];
    sol(v,n);
}