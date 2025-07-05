#include <iostream>
#include <vector>
#include <climits>

int n;
int **arr;
int min = INT_MAX;


void sum_value(bool node2[], std::vector<int> v, std::vector<int> vec, int& sum, int cnt, int next_num) {
    if (cnt == 2) {
        sum += arr[vec[0]][vec[1]] + arr[vec[1]][vec[0]];
        return;
    }
    for (int i = next_num; i < n / 2; i++) {
        if (node2[i]) continue;
        node2[i] = true;
        vec.push_back(v[i]);
        sum_value(node2, v, vec, sum, cnt + 1, i + 1);
        vec.pop_back();
        node2[i] = false;
    }
}

void divide_team(bool node1[], std::vector<int>& v1, std::vector<int>& vec1, std::vector<int>& v2, std::vector<int>& vec2, int cnt, int next_num) {
    if (cnt == n / 2) {
        for (int i = 0; i < n; i++) {
            if (node1[i] == false) {
                v2.push_back(i);
            }
        }
        bool node2[n / 2] = {false};
        int start, link;
        start = link = 0;
        sum_value(node2, v1, vec1, start, 0, 0);
        sum_value(node2, v2, vec2, link, 0, 0);
        v2.clear();
        int num = (start > link) ? start - link : link - start;
        if (min > num) min = num;
        return;
    }

    for (int i = next_num; i < n; i++) {
        if (node1[i]) continue;
        node1[i] = true;
        v1.push_back(i);
        divide_team(node1, v1, vec1, v2, vec2, cnt + 1, i + 1);
        v1.pop_back();
        node1[i] = false;
    }
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::cin >> n;
    arr = new int*[n];
    for (int i = 0; i < n; i++) {
        arr[i] = new int[n];
        for (int j = 0; j < n; j++) std::cin >> arr[i][j];
    }

    bool node[n] = {false};
    std::vector<int> v1,vec1, v2,vec2;

    divide_team(node, v1, vec1, v2, vec2, 0, 0);
    std::cout << min << '\n';
}