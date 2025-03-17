#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

using namespace std;
const double g = 9.81;
const double PI = acos(-1);

int main() {
    fastio;
    int t;
    cin >> t;

    vector<vector<double>> result;
    while (t-- > 0) {
        int j, p, H, L;
        cin >> j >> p >> H >> L;
        
        auto h = [&](double l) -> double {
            if (l < 0) return (double)H;
            else if (l < L/2) return pow(1 - 2*pow(l/L,2),2) * H;
            else if (l < L) return 2*H * pow(l/L - 1, 2);
            else return 0;
        };
        auto f = [&](double l, double v0) -> double {
            return H+p-g/2*pow(l/v0,2);
        };


    }

    for (auto& vec : result) {
        for (auto& ele : vec) cout << fixed << setprecision(8) << ele << ' ';
        cout << '\n';
    }
}