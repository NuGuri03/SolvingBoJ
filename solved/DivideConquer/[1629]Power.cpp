#include <iostream>
#include <vector>
using namespace std;

long long power(int a, int b, int c) {
    if (b == 0) return 1;

    long long half = power(a, b / 2, c);
    half = half * half % c;

    if (b % 2 != 0) half = (half * a % c) % c;

    return half;
}

int main() {
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int a, b, c;
    cin >> a >> b >> c;

    cout << power(a, b, c) << '\n';
}