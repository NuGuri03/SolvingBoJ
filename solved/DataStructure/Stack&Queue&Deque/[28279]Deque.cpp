#include <iostream>
#include <deque>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::deque<int> d;
    int n;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        int op;
        std::cin >> op;
        if (op == 1) {
            int x;
            std::cin >> x;
            d.push_front(x);
        }
        if (op == 2) {
            int x;
            std::cin >> x;
            d.push_back(x);
        }
        if (op == 3) {
            if (!d.empty()) {
                int x = d.front();
                d.pop_front();
                std::cout << x << '\n';
            }
            else {
                std::cout << -1 << '\n';
            }
        }
        if (op == 4) {
            if (!d.empty()) {
                int x = d.back();
                d.pop_back();
                std::cout << x << '\n';
            }
            else {
                std::cout << -1 << '\n';
            }
        }
        if (op == 5) {
            std::cout << d.size() << '\n';
        }
        if (op == 6) {
            std::cout << ((d.empty()) ? 1 : 0) << '\n';
        }
        if (op == 7) {
            if (!d.empty()) {
                int x = d.front();
                std::cout << x << '\n';
            }
            else {
                std::cout << -1 << '\n';
            }
        }
        if (op == 8) {
            if (!d.empty()) {
                int x = d.back();
                std::cout << x << '\n';
            }
            else {
                std::cout << -1 << '\n';
            }
        }
    }
    return 0;
}