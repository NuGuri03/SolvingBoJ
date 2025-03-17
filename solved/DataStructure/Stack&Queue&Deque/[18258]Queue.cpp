#include <iostream>
#include <queue>

void function(std::queue<int>& q, int n, int k) {
    std::cout << '<';

    while (!q.empty()) {
        for (int j = 0; j < k - 1; j++) {
            int temp = q.front();
            q.pop();
            q.push(temp);
        }
        std::cout << q.front();
        q.pop();

        if (!q.empty()) {
            std::cout << ", ";
        }
    }
    std::cout << ">\n";
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n, k;
    std::cin >> n >> k;

    std::queue<int> q;
    for (int i = 1; i <= n; i++) {
        q.push(i);
    }

    function(q, n , k);
}