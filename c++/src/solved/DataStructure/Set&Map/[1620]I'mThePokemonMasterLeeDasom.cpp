#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cctype>

bool isNum(const std::string& str) {
    for (char c : str) {
        if (!std::isdigit(c)) {
            return false;
        }
    }
    return true;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);
    
    int n, m;
    std::cin >> n >> m;
    std::map<std::string, int> pokemon_name;
    std::map<int, std::string> pokemon_num;
    for (int i = 1; i <= n; i++) {
        std::string name;
        std::cin >> name;
        pokemon_name.insert({name, i});
        pokemon_num.insert({i, name});
    }

    for (int i = 0; i < m; i++) {
        std::string input;
        std::cin >> input;

        if (isNum(input)) { 
            int id = std::stoi(input);
            std::cout << pokemon_num[id] << '\n';
        }
        else {
            std::cout << pokemon_name[input] << '\n';
            
        }

    }
}
