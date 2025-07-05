#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
using namespace std;

typedef struct {
    int r, c;
}matrixSize;

//simplify solution
int minimum_count_number_of_operation(vector<matrixSize>& v, int n) {
    //definiton of dp[i][j] = minimum_cnt_of_operation of i - j matrices 
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
    
    for (int i = n; i >= 1; i--) {

        for (int j = i + 1; j <= n; j++) {
            
            dp[i][j] = INT_MAX;

            for (int k = i; k < j; k++) {
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j] + v[i].r * v[k].c * v[j].c);  
            }

        }
    }

    return dp[1][n];
}

int main() {
    fastio;
    
    int N;
    cin >> N;
    
    vector<matrixSize> matrix_arr(N + 1, {0, 0});
    
    for (int i = 1; i <= N; i++) cin >> matrix_arr[i].r >> matrix_arr[i].c;   

    int minimum_cnt = minimum_count_number_of_operation(matrix_arr, N);
    cout << minimum_cnt << '\n';
}