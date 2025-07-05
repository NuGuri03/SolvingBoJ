#include <iostream>
#include <vector>

int max;
int *continous_sum;

void func(std::vector<int> v, int n) {
    for (int i = n - 2; i >= 0; i--) {
        if (continous_sum[i + 1] > 0)
            continous_sum[i] += continous_sum[i + 1];
        max = max < continous_sum[i] ? max = continous_sum[i] : max;  
    }
}

int main() {
    int n;
    std::cin >> n;

    std::vector<int> inputs(n, 0);
    continous_sum = new int[n];

    for (int i = 0; i < n; i++) {
        std::cin >> inputs[i];
        if (i == 0) max = inputs[i];
        max = max < inputs[i] ? max = inputs[i] : max;
        continous_sum[i] = inputs[i];
    }
    
    func(inputs, n);
    std::cout << max << '\n';
}