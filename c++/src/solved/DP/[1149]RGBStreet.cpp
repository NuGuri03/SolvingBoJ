#include <iostream>
#include <algorithm>


int RGB_street(int cost[][3], int n) {
    for (int i = 1; i < n; i++) {
        cost[i][0] = std::min(cost[i][0] + cost[i - 1][1], cost[i][0] + cost[i - 1][2]);
        
        cost[i][1] = std::min(cost[i][1] + cost[i - 1][0], cost[i][1] + cost[i - 1][2]);
        
        cost[i][2] = std::min(cost[i][2] + cost[i - 1][0], cost[i][2] + cost[i - 1][1]);
    }
    int min = std::min({cost[n - 1][0], cost[n - 1][1], cost[n - 1][2]});
    return min;
}

int main() {
    int n;
    std::cin >> n;
    int cost[1000][3];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 3; j++) std::cin >> cost[i][j];
    }
    std::cout << RGB_street(cost, n) << '\n';
}