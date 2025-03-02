#include <iostream>
#include <string>
using namespace std;

string a, b;

int LCS(int i, int j) {
    if (a[i] == '\0' || b[j] == '\0') return 0;
    else if (a[i] == b[j]) return 1 + LCS(i + 1, j + 1);
    else return max(LCS(i + 1, j), LCS(i, j + 1));
}

int main() {
    cin >> a >> b;
    cout << LCS(0, 0) << endl;
}