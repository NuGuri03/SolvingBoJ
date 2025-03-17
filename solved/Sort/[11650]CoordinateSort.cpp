#include <iostream>
#include <algorithm>

typedef struct {
    int x, y;
}coordinate;

//bool 함수!!
bool compare(coordinate a, coordinate b) {
    if (a.x != b.x) return  a.x < b.x;
    else return a.y < b.y; 
}

int main() {
    int n;
    std::cin >> n;

    coordinate *points = new coordinate[n];
    for (int i = 0; i < n; i++) 
        std::cin >> (points + i) -> x >> (points + i) -> y;

    std::sort(points, points + n, compare);

    for (int i = 0; i < n; i++) {
        std::cout << points[i].x << ' ' << points[i].y << '\n';
    }
    return 0;
}