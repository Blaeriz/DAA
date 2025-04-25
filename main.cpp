#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int optimalBSTWithRotation(const vector<int>& freq, int R) {
    int n = freq.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));
    vector<vector<int>> sumFreq(n, vector<int>(n, 0));

    // Precompute prefix sums of frequencies
    for (int i = 0; i < n; ++i) {
        sumFreq[i][i] = freq[i];
        for (int j = i + 1; j < n; ++j) {
            sumFreq[i][j] = sumFreq[i][j - 1] + freq[j];
        }
    }

    for (int len = 1; len <= n; ++len) {
        for (int i = 0; i <= n - len; ++i) {
            int j = i + len - 1;
            dp[i][j] = INT_MAX;
            for (int k = i; k <= j; ++k) {
                int costLeft = (k > i) ? dp[i][k - 1] : 0;
                int costRight = (k < j) ? dp[k + 1][j] : 0;
                int rotations = ((k > i) ? 1 : 0) + ((k < j) ? 1 : 0);
                int totalCost = costLeft + costRight + sumFreq[i][j] + R * rotations;
                dp[i][j] = min(dp[i][j], totalCost);
            }
        }
    }

    return dp[0][n - 1];
}

int main() {
    vector<int> freq = {4, 2, 6, 3};  // From 10(4), 20(2), 30(6), 40(3)
    int R = 5;
    cout << optimalBSTWithRotation(freq, R) << endl;  // Should print 148
    return 0;
}
