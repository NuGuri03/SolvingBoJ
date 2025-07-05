#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double x, y;
} Point;

typedef struct {
    int i, j;
    double w;
} Edge;

double get_distance(Point a, Point b) {
    double dx = (b.x - a.x) * (b.x - a.x);
    double dy = (b.y - a.y) * (b.y - a.y);

    return sqrt(dx + dy);
}

void swap(Edge *a, Edge *b) {
    Edge temp = *b;
    *b = *a;
    *a = temp;
}

int partition(Edge *edges, int left, int right) {
    int pivot = left;
    int low = left + 1;
    int high = right;

    do {
        while (edges[low].w <= edges[pivot].w && low <= high) {
            low += 1;
        }

        while (edges[high].w > edges[pivot].w && low <= high) {
            high -= 1;
        }

        if (low > high) {
            break;
        }

        swap(&edges[low], &edges[high]);
    } while (low <= high);

    swap(&edges[high], &edges[pivot]);

    return high;
}

void quick_sort(Edge *edges, int left, int right) {
    if (left >= right) return;

    int pivot_position = partition(edges, left, right);

    quick_sort(edges, left, pivot_position - 1);
    quick_sort(edges, pivot_position + 1, right);
}

int find(int* parent, int n) {
    if (parent[n] != n) {
        parent[n] = find(parent, parent[n]);
    }
    return parent[n];
}

void union_sets(int *parent, int a, int b) {
    int x = find(parent, a);
    int y = find(parent, b);

    if (x != y) {
        parent[y] = x;
    }
}

int main() {
    int n;
    scanf("%d", &n);

    Point *points = (Point*)malloc(n * sizeof(Point));
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf", &points[i].x, &points[i].y);
    }

    int e = (n-1)*n/2;
    Edge *edges = (Edge*)calloc(e, sizeof(Edge));

    int idx = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double distance = get_distance(points[i], points[j]);
            Edge edge = {i, j, distance};

            edges[idx++] = edge;
        }
    }
    quick_sort(edges, 0, e-1);

    int* parent = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) parent[i] = i;
    
    double total = 0;
    int selected = 0;
    for (int i = 0; i < e && selected < n - 1; i++) {
        Edge edge = edges[i];

        int a = edge.i;
        int b = edge.j;

        if (find(parent, a) != find(parent, b)) {
            union_sets(parent, a, b);
            total += edge.w;

            selected++;
        }
    }

    printf("%.2lf\n", total);
}