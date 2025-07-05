#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int *parent;
int *size;
int *visited;

typedef struct {
    int x, y;
} Point;

typedef struct {
    int p1_idx;
    int p2_idx;
    double w;
} Edge;

double get_distance(Point p1, Point p2) {
    double dx = pow(p2.x - p1.x, 2);
    double dy = pow(p2.y - p1.y, 2);
    return sqrt(dx + dy);
}

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void union_sets(int x, int y) {
    int rx = find(x);
    int ry = find(y);

    if (rx == ry) {
        return;
    }

    if (size[rx] < size[ry]) {
        parent[rx] = ry;
        size[ry] += size[rx];
    } else {
        parent[ry] = rx;
        size[rx] += size[ry];
    }
}

int partition(Edge *edge, int start, int end) {
    int pivot_pos = start;
    int l = start + 1;
    int r = end;

    while (l <= r) {
        while (l <= end && edge[l].w < edge[pivot_pos].w) l++;
        while (r >= start + 1 && edge[r].w >= edge[pivot_pos].w) r--;

        if (l < r) {
            Edge temp = edge[l];
            edge[l] = edge[r];
            edge[r] = temp;
        }
    }

    Edge temp = edge[pivot_pos];
    edge[pivot_pos] = edge[r];
    edge[r] = temp;

    return r;
}

void quick_sort(Edge *edge, int start, int end) {
    if (start < end) {
        int pivot = partition(edge, start, end);

        quick_sort(edge, start, pivot - 1);
        quick_sort(edge, pivot + 1, end);
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    Point *point = (Point*)malloc(n * sizeof(Point));
    int edge_count = 0;
    for (int i = 0; i < n; i++) {
        edge_count += i;
        scanf("%d %d", &point[i].x, &point[i].y);
    }

    Edge *edge = (Edge*)malloc(edge_count * sizeof(Edge));
    int idx = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            edge[idx].p1_idx = i;
            edge[idx].p2_idx = j;
            edge[idx++].w = get_distance(point[i], point[j]);
        }
    }

    for (int i = 0; i < m; i++) {
        int l, r;
        scanf("%d %d", &l, &r);

        l -= 1;
        r -= 1;
        for (int j = 0; j < edge_count; j++) {
            if ((edge[j].p1_idx == l && edge[j].p2_idx == r) ||
                (edge[j].p1_idx == r && edge[j].p2_idx == l)) {
                edge[j].w = 0.0;
                break;
            }
        }
    }

    quick_sort(edge, 0, edge_count - 1);
    
    parent = (int*)calloc(n, sizeof(int));
    size = (int*)calloc(n, sizeof(int));
    visited = (int*)calloc(n, sizeof(int));

    for (int i = 0; i < n; i++) {
        parent[i] = i;
        size[i] = 1;
    }

    double total_w = 0.0;
    int selected = 0;
    for (int i = 0; i < edge_count && selected < n - 1; i++) {
        Edge e = edge[i];
        if (find(e.p1_idx) != find(e.p2_idx)) {
            union_sets(e.p1_idx, e.p2_idx);
            total_w += e.w;
            selected++;
        }
    }

    printf("%.2lf\n", total_w);

    return 0;
}