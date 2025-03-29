#include <bits/stdc++.h>
using namespace std;

int find_maximum_rectangle(int n, vector<int>& h) {
    stack<int> s;

    int l, m, r;
    int area = 0;
    // for (int i = 0; i < n; i++) {
    //     m = i; l = i; r = i;
    //     s.push(h[m]);
    //     while (0 <= l-- && r++ < n) {
    //         return 0;
    //     }
    // }
    return 1;
}

int main() {
    int N;
    cin >> N;

    vector<int> heights(N, 0);
    for (int i = 0; i < N; i++) cin >> heights[i];

    find_maximum_rectangle(N, heights);
}
