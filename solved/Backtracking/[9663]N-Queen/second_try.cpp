#include <iostream>
#include <cmath>

int sol_count = 0;
int col[16];
int n;

bool check(int x) {
    for (int j = 0; j < x; j++) {
        if (col[j] == col[x] || abs(col[x] - col[j]) == x - j) {
            return false;
        }
    }
    return true;
}

void n_queen(int x) {
    if (x == n) {
        sol_count++;
        return;
    }
    for (int i = 0; i < n; i++) {
        col[x] = i;
        if (check(x)) n_queen(x + 1);
    }
}


int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::cin >> n;
    n_queen(0);
    std::cout << sol_count << '\n';
}