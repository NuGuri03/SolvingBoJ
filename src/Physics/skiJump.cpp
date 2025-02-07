#include <iostream>
#include <cmath>
#include <vector>
#include <limits>
#include <iomanip>
using namespace std;
const double g = 9.81;
const double PI = acos(-1);

double quad_eq(double a, double b, double c, double left, double right) {
    double D = b*b - 4*a*c;
    if (D < 0) return -1;
    else if (D == 0) {
        return -b/(2*a);
    }
    else {
        double x = (-b + sqrt(D)) / (2*a);
        double y = (-b - sqrt(D)) / (2*a);
        
        if (x >= left && x <= right) return x;
        else if (y >= left && y <= right) return y;
        else return -1;
    }
}
double ConservationOfMechanicalEnergy(double h, double u) {
    return sqrt(2*g*h + u * u);
}
double getPosition(double v0, double L, double H, double p) {
    double l1 = quad_eq(g/(2*v0*v0) - 2*H/(L*L), 0, -p, 0, L/2);
    double l2 = quad_eq(2*H/(L*L) + g/(2*v0*v0), -4*H/L, H - p, L/2, L);
    double l3 = quad_eq(-g/(2*v0*v0), 0, p + H, L, numeric_limits<double>::max());
    if (l1 != -1) return l1;
    else if (l2 != -1) return l2;
    else if (l3 != -1) return l3;
    else return -1;
}

double getVelocity(double l, double v0, double H, double p) {
    double y = (-g/2)*pow(l/v0,2) + H + p;
    return ConservationOfMechanicalEnergy(H+p-y, v0);
}

double getAngle(double l, double L, double H, double v0, double v) {
    double df, dh;
    df = -g*l/(v0*v0);
    if (l < L / 2) dh = H*(-4*l/(L*L));
    else if (l <= L) dh = 4*H/L*(l/L-1);
    else dh = 0;

    double temp = abs((dh - df)/(1 + dh*df));
    return atan(temp) * 180.0 / PI;
}

int main() {
    int t;
    cin >> t;

    vector<vector<double>> result;
    while (t-- > 0) {
        double j, p, H, L;
        cin >> j >> p >> H >> L;
        
        double v0 = ConservationOfMechanicalEnergy(j, 0);
        double l = getPosition(v0, L, H, p);
        double v = getVelocity(l, v0, H, p);
        double theta = getAngle(l, L, H, v0, v);
        vector<double> arr = {l, v, theta};
        result.push_back(arr);
    }

    for (auto& vec : result) {
        for (auto& ele : vec) cout << fixed << setprecision(8) << ele << ' ';
        cout << '\n';
    }
}