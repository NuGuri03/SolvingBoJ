#include <iostream>
#include <vector>

int main() {
    unsigned int n;
    std::cin >> n;
    
    // vector < > 괄호 안에는 short가 아닌 int가 들어가야함; 값은 개수를 의미함으로...
    std::vector<unsigned int> counting_arr(10001, 0);
    
    // vector.resize 는 오류를 불러일으킬 수 있음;
    for (int i = 0; i < n; i++) {
        unsigned short num;
        std::cin >> num;
        counting_arr[num]++;
    }

    // while(0)은 실행되지 않지만, 가독성을 위해 while (num > 0) 으로 하자;
    for (int i = 1; i <= 10000; i++) {
        while (counting_arr[i]-- > 0) {
            std::cout << i << '\n';
        }
    }
    return 0;
}