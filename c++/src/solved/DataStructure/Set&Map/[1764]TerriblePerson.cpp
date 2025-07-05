#include <iostream>
#include <string>
#include <set>

int main() {
    int n, m;
    std::cin >> n >> m;

    //std::set<자료형> 이름; set는 들어갈때 부터 정렬되어 들어감, 중복 제거됨.
    std::set<std::string> S;
    for (int i = 0; i < n; i++) {
        std::string input;
        std::cin >> input;
        S.insert(input);
    }

    int count = 0;
    for (int i = 0; i < m; i++) {
        std::string str;
        std::cin >> str;
        //(set 이름).find(x) , x 가 있으면 iterator 반환 아니면 (set 이름).end() 반환;
        if (S.find(str) != S.end()) count++;
    }

    std::cout << count << std::endl;
}