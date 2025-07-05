#include <stdio.h>
#include <stdlib.h>

int *parent;

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

int union_sets(int x, int y) {
    x = find(x);
    y = find(y);

    if (x != y) {
        parent[y] = x;
        return x;
    } else {
        return -1;
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    parent = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) parent[i] = i;

    int ans = 0;
    for (int i = 0; i < m; i++) {
        int p1, p2;
        scanf("%d %d", &p1, &p2);

        if (union_sets(p1, p2) == -1 && ans == 0) {
            ans = i + 1;
        }
    }

    printf("%d\n", ans);
}