#include <iostream>
#include <vector>

void merge(std::vector<int>& arr, int start, int mid, int end) {
    std::vector<int> sorted(end - start + 1);
    int i = start;
    int j = mid + 1;
    int k = 0;

    while (i <= mid && j <= end) {
        if (arr[i] <= arr[j]) sorted[k++] = arr[i++];
        else sorted[k++] = arr[j++];
    }

    if (i > mid) {
        while (j <= end) sorted[k++] = arr[j++];
    }
    else {
        while (i <= mid) sorted[k++] = arr[i++];
    }

    for (int x = start, y = 0; x <= end; x++, y++) arr[x] = sorted[y];
}

void merge_sort(std::vector<int>& arr, int start, int end) {
    if (start < end) {
        int mid = (start + end) / 2;
        merge_sort(arr, start, mid);
        merge_sort(arr, mid + 1, end);
        merge(arr, start, mid, end);
    }
}

int main() {
    std::vector<int> arr = {21, 10, 12, 20, 25, 13, 15, 22};

    merge_sort(arr, 0, arr.size() - 1);
    for (auto& ele : arr) {
        std::cout << ele << ' ';
    }
}