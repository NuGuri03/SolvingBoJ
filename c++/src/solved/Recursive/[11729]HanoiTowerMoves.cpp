#include <iostream>
#include <vector>

void tower_of_Hanoi(int n, int from, int to, int aux,std::vector<std::pair<int,int>>& store ,int *count) {
    if (n == 1) {
        store.push_back(std::make_pair(from, to));
        (*count)++;
    }
    else {
        tower_of_Hanoi(n - 1, from, aux ,to, store ,count);
        store.push_back(std::make_pair(from, to));
        (*count)++;
        tower_of_Hanoi(n - 1, aux, to , from, store, count);
    }
}

int main() {
    int n;
    std::cin >> n;

    int count = 0;
    std::vector<std::pair<int,int>> store;
    tower_of_Hanoi(n, 1, 3, 2, store,&count);
    std::cout << count << '\n';
    for (auto& ele : store) {
        std::cout << ele.first << ' ' << ele.second << '\n';
    }
}