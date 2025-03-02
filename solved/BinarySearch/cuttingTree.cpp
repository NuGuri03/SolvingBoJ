#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

long long search(vector<long long>& tree, long long n, long long m) {
    long long start = 1;
    long long end = tree[n - 1];
    long long result = 0;

    while (start <= end) {
        long long mid = (start + end) / 2;
        long long len = 0;

        for (int i = 0; i < n; i++) {
            if (tree[i] > mid) len += tree[i] - mid;
        }
        if (len >= m) {
            result = mid;
            start = mid + 1;
        }
        else {
            end = mid - 1;
        }
    }
    return result;
}

int main() {
    long long n, m;
    cin >> n >> m;

    vector<long long> tree(n, 0);
    for (auto& t : tree) cin >> t;

    sort(tree.begin(), tree.end());
    cout << search(tree, n, m) << endl;
}