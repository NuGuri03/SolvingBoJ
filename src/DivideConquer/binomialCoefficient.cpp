#include <iostream>
using namespace std;

const long long p = 1000000007;

long long factorial(long long x) {
    long long result = 1;
    for (int i = 1; i <= x; i++) result = (result * i) % p;
    return result;
}

long long power(long long x, long long y) {
    if (y == 0) return 1;

    long long half = power(x, y / 2);
    half = half * half % p;

    if (y % 2 == 1) half = (half * x % p) % p;
    return half;
}

int main() {
    int n, k;
    cin >> n >> k;

    long long fact_n = factorial(n);
    long long fact_k = factorial(k);
    long long fact_n_k = factorial(n - k);

    long long temp1 = power(fact_k, p - 2);
    long long temp2 = power(fact_n_k, p - 2);

    long long temp = temp1 * temp2 % p;
    cout << temp * fact_n % p << '\n';
}