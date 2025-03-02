#include <iostream>
#include <vector>
#include <algorithm>

//BinarySearch = 중간을 기준으로..
int binarySearch(const std::vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) return 1;
        else if (arr[mid] > target) right = mid - 1;
        else left = mid + 1; 
    }
    return 0;
}

int main() {
    std::cin.tie(nullptr);
    //flush 연산 수행 안하기로 선언
    //cin과 cout는 묶여있음 즉, cin을 사용할 떄 마다 flush 연산 발생
    //flush 연산 = 출력 버퍼에 보관하고 있던 내용을 모두 출력하고 출력 버퍼를 비우는 연산
    std::ios_base::sync_with_stdio(false);
    //C의 입출력과 비동기화

    int n;
    std::cin >> n;
    std::vector<int> S(n);
    for (int i = 0; i < n; i++) std::cin >> S[i];
    sort(S.begin(), S.end());

    int m;
    std::cin >> m;
    int x;
    for (int i = 0; i < m; i++) {
        std::cin >> x;
        std::cout << binarySearch(S, x) << ' ';
    }
}