#include <iostream>
#include <vector>
//시간 초과
void function(std::vector<std::pair<int, int>>& v, std::vector<std::vector<bool>>& nodes, int cnt, int n, int row, int col, int* count) {
    if (v.size() == n) {
        (*count)++;
        return;
    }
    for (int i = row; i < n; i++) {
        for (int j = (i == row ? col : 0); j < n; j++) {
            bool attack = false;
            for (int k = 0; k < n; k++) {
                if (k == i || k == j) {
                    attack = true;
                    break;
                }
                if (i + k < n && j + k < n && nodes[i + k][j + k]) {
                    attack = true;
                    break;
                }
                if (i - k >= 0 && j - k >= 0 && nodes[i - k][j - k]) {
                    attack = true;
                    break;
                }
                if (i + k < n && j - k >= 0 && nodes[i + k][j - k]) {
                    attack = true;
                    break;
                }
                if (i - k >= 0 && j + k < n && nodes[i - k][j + k]) {
                    attack = true;
                    break;
                }
            }
            if (attack) continue;
            nodes[i][j] = true;
            v.push_back(std::pair(i , j));
            
            std::cout << std::endl;
            int next_i, next_j;
            if (j + 1 < n) {
                next_i = i;
                next_j = j + 1;
            }
            else {
                next_i = i + 1;
                next_j = 0;
            }
            function(v, nodes, cnt + 1, n, next_i, next_j,count);
            v.pop_back();
            nodes[i][j] = false;
        }
    }
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n;
    std::cin >> n;

    std::vector<std::vector<bool>> nodes(n, std::vector<bool>(n, false));
    std::vector<std::pair<int,int>> vec;
    
    int count = 0;
    function(vec, nodes, 0, n, 0, 0, &count);
    std::cout << count << '\n';
}