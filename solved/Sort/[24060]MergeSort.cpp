#include <iostream>

int sol_count = 0;
int result = -1;

void merge(int* arr, int start, int mid, int end, int u) {
    int *sorted = new int[end - start + 1];
    int i = start;
    int j = mid + 1;
    int k = 0;
    
    while (i <= mid && j <= end) {
        if (arr[i] <= arr[j]) {
            sorted[k++] = arr[i++];
        }
        else {
            sorted[k++] = arr[j++];
        }
    }

    while (j <= end) {
        sorted[k++] = arr[j++];
    }
    while (i <= mid) {
        sorted[k++] = arr[i++];
    }

    
    for (int i = 0; i < end - start + 1; i++) {
        sol_count++;
        arr[start + i] = sorted[i];
        if (sol_count == u) result = sorted[i];
    }

    delete[] sorted;
}

void merge_sort(int *arr, int start, int end, int u) {
    if (start < end) {
        int mid = (start + end) / 2;
        merge_sort(arr,start, mid, u);
        merge_sort(arr,mid + 1, end, u);
        merge(arr, start, mid, end, u);
    }
}

int main() {
    int n, k;
    std::cin >> n >> k;

    int* arr = new int[n];
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }

    merge_sort(arr, 0, n - 1, k);
    std::cout << result << '\n';
}