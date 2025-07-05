#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;

ll maxArea(vector<ll>& h, int left, int right) {
    if (left == right) return h[right];

    int mid = (left + right) / 2;
    ll leftMax = maxArea(h, left, mid);
    ll rightMax = maxArea(h, mid + 1, right);

    int l = mid, r = mid + 1;
    ll height = min(h[l], h[r]);
    ll midMax = height *  2;
    while (l > left || r < right) {
        if (r < right && (l == left || h[r + 1] >= h[l - 1])) {
            r++;
            height = min(height, h[r]);
        }
        else {
            l--;
            height = min(height, h[l]);
        }
        midMax = max(midMax, height * (r - l + 1));
    }
    return max({midMax, leftMax, rightMax});
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    vector<ll> result;
    while (1) {
        int n;
        cin >> n;
        if (n == 0) break;

        vector<ll> height(n, 0);
        for (int i = 0; i < n; i++) {
            cin >> height[i];
        }
        result.push_back(maxArea(height, 0, n - 1));
    }
    for (auto& ele : result) cout << ele << '\n';
}