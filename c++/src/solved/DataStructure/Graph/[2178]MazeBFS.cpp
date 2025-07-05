#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<vector<bool>> visited;
vector<vector<int>> matrix;
int n, m;

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

int BFS(int startX, int startY) {
    queue<pair<int, int>> q;
    q.push({startX, startY});
    visited[startX][startY] = true;

    vector<vector<int>> distance(n, vector<int>(m, 0));
    distance[startX][startY] = 1;

    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        if (x == n - 1 && y == m - 1) {
            return distance[x][y];
        }

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx >= 0 && nx < n && ny >= 0 && ny < m &&
                matrix[nx][ny] == 1 && !visited[nx][ny]) {
                visited[nx][ny] = true;
                distance[nx][ny] = distance[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }

    return -1;
}

int main() {
    cin >> n >> m;
    cin.ignore();

    visited.assign(n, vector<bool>(m, false));
    matrix.assign(n, vector<int>(m));

    for (int i = 0; i < n; i++) {
        string row;
        cin >> row;
        for (int j = 0; j < m; j++) {
            matrix[i][j] = row[j] - '0';
        }
    }

    cout << BFS(0, 0) << '\n';
    return 0;
}
