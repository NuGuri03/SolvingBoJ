#include <iostream>
#include <cmath>
#include <string>
using namespace std;

int main() {
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int L;
    string str;
    cin >> L >> str;

    long long Hash_value = 0;
    long long r = 1;
    const int MOD = 1234567891;
    const int BASE = 31;
    for (int i = 0; i < L; i++) {
        Hash_value = (Hash_value + (str[i] - 'a' + 1) * r % MOD) % MOD;
        r = (r * 31) % MOD;
    }

    std::cout << Hash_value << '\n';
}