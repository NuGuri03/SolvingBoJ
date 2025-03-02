#include <iostream>
#include <algorithm>
#include <string>

typedef struct {
    int age;
    std::string name;
}person;

bool compare(const person& a, const person& b) {
    return a.age < b.age;
}

int main() {
    int n;
    std::cin >> n;

    person* members = new person[n];
    for (int i = 0; i < n; i++) {
        std::cin >> members[i].age >> members[i].name;
    }

    std::stable_sort(members, members + n, compare);
    for (int i = 0; i < n; i++) {
        std::cout << members[i].age << ' ' << members[i].name << '\n';
    }
}