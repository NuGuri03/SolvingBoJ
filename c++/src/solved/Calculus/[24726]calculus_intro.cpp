#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
using namespace std;

const double pi = acos(-1);
const double delta = 1e-4;

double integrate_dx(pair<double, double> a, pair<double, double> b) {
    if (a.first == b.first) return 0;

    double m = (b.second - a.second) / (b.first - a.first);
    double c = a.second - m * a.first;

    auto f = [m, c](double x) {
        return pow(m * x + c, 2);
    };

    double sum = 0;
    for (double i = a.first; i < b.first; i += delta) {
        double next_x = min(b.first, i + delta);
        sum += (f(i) + f(next_x)) / 2 * (next_x - i);
    }
    return sum * pi;
}

double integrate_dy(pair<double, double> a, pair<double, double> b) {
    if (a.second == b.second) return 0;

    double m = (b.first - a.first) / (b.second - a.second);
    double c = a.first - m * a.second;

    auto f = [m, c](double y) {
        return pow(m * y + c, 2);
    };

    double sum = 0;
    for (double i = a.second; i < b.second; i += delta) {
        double next_y = min(b.second, i + delta);
        sum += (f(i) + f(next_y)) / 2 * (next_y - i);
    }
    return sum * pi;
}

double revolvedByX(vector<pair<double, double>> p) {
    sort(p.begin(), p.end(), [](const pair<double, double> &a, const pair<double, double> &b) {
        return a.first < b.first;
    });

    double A = integrate_dx(p[0], p[2]);
    double B = integrate_dx(p[0], p[1]);
    double C = integrate_dx(p[1], p[2]);

    return abs(A - B - C);
}

double revolvedByY(vector<pair<double, double>> p) {
    sort(p.begin(), p.end(), [](const pair<double, double> &a, const pair<double, double> &b) {
        return a.second < b.second;
    });

    double A = integrate_dy(p[0], p[2]); 
    double B = integrate_dy(p[0], p[1]); 
    double C = integrate_dy(p[1], p[2]); 

    return abs(A - B - C);
}

int main() {
    fastio;
    vector<pair<double, double>> points(3);
    for (int i = 0; i < 3; i++) {
        cin >> points[i].first >> points[i].second;
    }

    cout << fixed << setprecision(9) << revolvedByX(points) << ' ' << revolvedByY(points) << '\n';
}
