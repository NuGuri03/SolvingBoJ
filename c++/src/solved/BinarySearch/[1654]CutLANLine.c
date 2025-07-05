#include <stdio.h>
#include <stdlib.h>

int parametric_search(int *arr, int n, int k) {
    long long start = 1;
    long long end = arr[0];
    for (int i = 1; i < n; i++) {
        if (end < arr[i]) end = arr[i];
    }

    long long result = -1;
    while (start <= end) {
        long long mid = (start + end) / 2;
        long long cnt = 0;
        for (int i = 0; i < n; i++) {
            cnt += arr[i] / mid;
        }
        if (cnt >= k) {
            result = mid;
            start = mid + 1;
        }
        else end = mid - 1;
    }
    return result;
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    int *wires = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &wires[i]);
    }

    printf("%d\n", parametric_search(wires, n, k));
}