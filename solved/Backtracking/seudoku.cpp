    #include <iostream>

    int rect[9][9];

    bool check(int n, int m, int x) {
        int a = (n / 3) * 3;
        int b = (m / 3) * 3;
        for (int i = 0; i < 9; i++) {
            if (i != m) {
                if (rect[n][i] == x) {
                    return false;
                }
            }
            if (i != n) {
                if (rect[i][m] == x) {
                    return false;
                }
            }
            if (n != i / 3 + a && m != i % 3 + b) {
                if (rect[i / 3 + a][i % 3 + b] == x) {
                    return false;
                }
            }
        } 
        return true;
    }

    bool seudoku() {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (rect[i][j] != 0) continue;

                for (int x = 1; x <= 9; x++) {
                    if (check(i, j, x)) {
                        rect[i][j] = x;
                        if (seudoku()) {
                            return true;
                        }
                        rect[i][j] = 0;
                    }
                }
                return false;
            }
        }
        return true;
    }

    int main() {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                std::cin >> rect[i][j];
            }
        }

        seudoku();
        std::cout << '\n';
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                std::cout << rect[i][j] << ' ';
            }
            std::cout << '\n';
            
        }
    }