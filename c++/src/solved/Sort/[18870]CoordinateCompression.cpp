#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
//map 헤더파일;

int main() {
    int n;
    std::cin >> n;

    std::vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }

    std::vector<int> sorted_arr = arr;
    
    std::sort(sorted_arr.begin(), sorted_arr.end());
    auto last = std::unique(sorted_arr.begin(), sorted_arr.end());
    sorted_arr.erase(last, sorted_arr.end());

    std::map<int, int> mapping;
    for (int i = 0; i < sorted_arr.size(); i++) {
        mapping[sorted_arr[i]] = i;
    }

    for (int i = 0; i < n; i++) {
        std::cout << mapping[arr[i]] << ' ';
    }

    return 0;
}