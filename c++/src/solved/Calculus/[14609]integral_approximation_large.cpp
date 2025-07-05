#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
using namespace std;
const double error = pow(10, -4);

double RiemannSum(function<double(double)> f, int a, int b, int N, double e) {
    double dx = (b - a) / (double)N;
    double sum = 0;

    for (int i = 0; i < N; i++) {
        double x = a + i*dx + e;
        sum += f(x) * dx;
    }
    return sum;
}
double integrate(function<double(double)> F, int a, int b) {
    return F(b) - F(a);
}

int main() {
    fastio;
    int K;
    cin >> K;
    vector<int> c(K + 1, 0);
    for (int i = K; i >= 0; i--) cin >> c[i];
    int a, b, N;
    cin >> a >> b >> N;

    auto f = [K, c](double x) {
        double result = 0;
        for (int i = K; i >= 0; i--) {
            result += pow(x, i) * c[i]; 
        } 
        return result;
    };
    auto F = [K, c](double x) {
        double result = 0;
        for (int i = K; i >= 0; i--) {
            result += pow(x, i + 1) * c[i] / (double)(i+1);
        }
        return result;
    };
    cout << fixed << setprecision(6);

    double realValue = integrate(F, a, b);
    // cout << "real value is: " << realValue << '\n';

    double epsilon = (double)(b - a) / N;
    double appValue = RiemannSum(f, a, b, N, epsilon);
    // cout << "approximate value is: " << appValue << '\n';

    while (abs(appValue - realValue) > error &&
       abs(appValue - realValue) / abs(realValue) > error) {
        if (epsilon < 0) break;

        epsilon -= 1e-6;
        appValue = RiemannSum(f, a, b, N, epsilon);
    };

    cout << epsilon << '\n';
}