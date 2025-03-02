#include <iostream>
#include <vector>

void BackTracking(std::vector<int>& vec, int arr[],bool visited[], int Cnt, int n, int m) {
    if (Cnt == m) {
        for (int i = 0; i < vec.size(); i++) {
            std::cout << vec[i] << ' '; 
        }
        std::cout << '\n';
        return;
    }
    for (int i = 0; i < n; i++) {
        if (visited[i] == true) continue;
        visited[i] = true;
        vec.push_back(arr[i]);
        BackTracking(vec, arr, visited, Cnt + 1, n, m);
        vec.pop_back();
        visited[i] = false;
    }
}

int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<int> vec;
    bool *selected = new bool[n];
    std::fill(selected, selected + n, false);
    int* arr = new int[n];
    for (int i = 1; i <= n; i++) arr[i - 1] = i;

    BackTracking(vec, arr, selected, 0, n, m);
}