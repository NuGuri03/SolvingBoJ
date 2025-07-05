#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

#define MAX 200001

int parent[MAX];
int network[MAX];

int find(int x) {
    if (parent[x] != x) 
        parent[x] = find(parent[x]);
    return parent[x];
}

int union_set(int x, int y) {
    int a = find(x);
    int b = find(y);

    if (a != b) {
        parent[b] = a;
        network[a] += network[b];
    }
    return network[a];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;
    while (T--) {
        int F;
        cin >> F;

        unordered_map<string, int> name_to_idx;
        int idx = 0;

        for (int i = 0; i < 2 * F; ++i) {
            parent[i] = i;
            network[i] = 1;
        }

        for (int i = 0; i < F; ++i) {
            string a, b;
            cin >> a >> b;

            if (name_to_idx.find(a) == name_to_idx.end())
                name_to_idx[a] = idx++;
            if (name_to_idx.find(b) == name_to_idx.end())
                name_to_idx[b] = idx++;

            int ans = union_set(name_to_idx[a], name_to_idx[b]);
            cout << ans << '\n';
        }
    }
    return 0;
}
