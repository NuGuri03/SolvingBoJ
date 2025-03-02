#include <iostream>
#include <vector>
#include <stack>
#include <string>

std::string check(std::string str) {
    std::stack<char> st;
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == '(') st.push('(');
        else if (str[i] == ')') {
            if (!st.empty()) st.pop();
            else return "NO";
        }
    }

    if (st.empty()) return "YES";
    else return "NO";
}

int main() {
    int n;
    std::cin >> n;

    std::vector<std::string> result(n);
    for (int i = 0; i < n; i++) {
        std::string str;
        std::cin >> str;

        result[i] = check(str);
    }

    for (auto& ele : result) {
        std::cout << ele << '\n';
    }
}