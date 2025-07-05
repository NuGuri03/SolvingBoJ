#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int LBS(vector<int> v, int n) {
    vector<int> left_len(n, 1);
    vector<int> right_len(n, 1);
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (v[j] < v[i]) left_len[i] = max(left_len[i], left_len[j] + 1);
        }
    }
    for (int i = n - 2; i >= 0; i--) {
        for (int j = n - 1; j > i && i < n - 1; j--) {
            if (v[j] < v[i]) right_len[i] = max(right_len[i], right_len[j] + 1);
        }
    }
    
    // for (auto& ele : left_len) cout << ele << ' ';
    // cout << endl;

    // for (auto& ele : right_len) cout << ele << ' ';
    // cout << endl;
    
    vector<int> length(n);
    for (int i = 0; i < n; i++) {
        length[i] = left_len[i] + right_len[i] - 1;
        //cout << length[i] << ' ';
    }
    //cout << '\n';
    return *max_element(length.begin(), length.end());
}

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;

    vector<int> series(n, 0);
    for (auto& ele : series) {
        cin >> ele;
    }

    cout << LBS(series, n) << endl;
}
