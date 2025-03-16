#include <bits/stdc++.h>
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
using namespace std;

int weightCount;
vector<int> weight;
vector<vector<bool>> dp;

void createDp() {
    int sumWeight = 0;
    for (int i = 0; i < weightCount; i++) sumWeight += weight[i];
    dp.assign(weightCount + 1, vector<bool>(sumWeight + 1, false));
    dp[0][0] = true;

    for (int i = 1; i <= weightCount; i++) {
        for (int j = 0; j <= sumWeight; j++) {
            dp[i][j] = dp[i - 1][j];
            if (j < weight[i-1] && (dp[i-1][weight[i-1] - j] || dp[i-1][weight[i-1] + j])) dp[i][j] = true;
            else if (j >= weight[i-1] && (dp[i-1][j - weight[i-1]] || (j + weight[i-1] <= sumWeight && dp[i-1][j + weight[i-1]]))) dp[i][j] = true;
        }
    }

    // 디버깅을 위한 배열 출력
    // for (const auto row : dp) {
    //     for (bool ele : row) cout << ele << ' ';
    //     cout << '\n';
    // }
}

bool canMeasureWeight(int bead) {
    if (dp[0].size() <= bead) return false;
    else return dp[weightCount][bead]; 
}

int main() {
    FASTIO;
    
    // 추 세기
    cin >> weightCount;
    weight.assign(weightCount, 0);
    for (int i = 0; i < weightCount; i++) cin >> weight[i];
    
    createDp();

    // 구슬 세기
    int beadCount, bead;
    cin >> beadCount;
    vector<char> results(beadCount);
    for (int i = 0; i < beadCount; i++) {
        cin >> bead;
        // 양팔 저울과 추를 통해 구슬의 무게를 확인 할 수 있는지 확인하기
        if (canMeasureWeight(bead)) results[i] = 'Y';
        else results[i] = 'N';
    }

    // 결과 출력
    for (char& result : results) cout << result << ' ';
    cout << '\n';
}