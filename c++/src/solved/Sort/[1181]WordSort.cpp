#include <iostream>
#include <algorithm> //std::sort, std::unique
#include <vector>    //vector 배열 선언
#include <string>    //string 활용

//const : 읽기 전용 선언
// & : 참조(call by value 가 아닌 주소를 활용해 메모리 사용 감소)
//str1 < str2 로 사전적 순서를 할 수 있다
bool compare(const std::string& str1, const std::string& str2) {
    if (str1.length() != str2.length())
        return str1.length() < str2.length();
    
    else return str1 < str2;
}

int main() {
    int n;
    std::cin >> n;

    //std::vector<<배열 내 데이터 타입> 이름(배열 개수)
    std::vector<std::string> strings(n);
    for (int i = 0; i < n; i++) {
        std::cin >> strings[i];
    }

    std::sort(strings.begin(), strings.end(), compare);

    //std::unique : 중복되는 단어 혹은 숫자를 뒤로 보내고, 중복되지 않는 배열의 마지막 요소의 다음 주소를 반환한다.
    //auto : 컴퓨터가 데이터 타입을 추론한다. 
    auto last = std::unique(strings.begin(),strings.end());
    
    //배열.erase(주소 시작, 주소 끝)
    strings.erase(last,strings.end());


    for (const auto& str : strings) {
        std::cout << str << '\n';
    }

    return 0;
}