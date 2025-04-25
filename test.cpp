#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// Function to compute the sum of frequencies from i to j
int sumFreq(const vector<int>& freq, int i, int j) {
    int total = 0;
    for (int k = i; k <= j; ++k) {
        total += freq[k];
    }
    return total;
}

// Function to compute the optimal BST with rotations, also tracks the number of rotations
int optimalBSTWithRotations(const vector<int>& freq, const vector<int>& values, int rotationCost, int& numRotations, vector<vector<int>>& root, vector<vector<int>>& dp) {
    int n = freq.size();
    
    // Base case: single keys
    for (int i = 0; i < n; ++i) {
        dp[i][i] = freq[i] * values[i];  // Cost is frequency * value for single keys
        root[i][i] = i;                  // Root is itself for a single element
    }

    // Build up the table
    for (int len = 2; len <= n; ++len) {
        for (int i = 0; i <= n - len; ++i) {
            int j = i + len - 1;
            dp[i][j] = INT_MAX;
            root[i][j] = -1;

            int totalFreq = sumFreq(freq, i, j);

            for (int r = i; r <= j; ++r) {
                int left = (r > i) ? dp[i][r - 1] : 0;
                int right = (r < j) ? dp[r + 1][j] : 0;
                int cost = left + right + totalFreq * values[r]; // Add node value cost

                // Add rotation cost only when the subarray has more than one element
                if (i != j) cost += rotationCost;

                if (cost < dp[i][j]) {
                    dp[i][j] = cost;
                    root[i][j] = r;
                }
            }
        }
    }

    // Now, track the number of rotations (each non-singleton subtree split counts as one rotation)
    numRotations = 0;
    // Traverse the tree to count rotations (split for each internal node)
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (root[i][j] != -1) {
                numRotations++;
            }
        }
    }

    return dp[0][n - 1];
}

// Function to print the tree structure
void printTreeStructure(const vector<vector<int>>& root, int i, int j, const vector<int>& freq, const vector<int>& values) {
    if (i > j) return;

    int r = root[i][j];
    if (r == -1) return;

    cout << "Root of subtree [" << i << ", " << j << "] is key: " << values[r] << endl;

    // Print the left and right subtrees recursively
    printTreeStructure(root, i, r - 1, freq, values);
    printTreeStructure(root, r + 1, j, freq, values);
}

int main() {
    // Input: frequencies of sorted keys [10, 20, 30, 40] => [4, 2, 6, 3]
    vector<int> freq = {4, 2, 6, 3};
    vector<int> values = {10, 20, 30, 40};  // Node values
    int rotationCost = 5;
    int numRotations = 0;

    int n = freq.size();
    vector<vector<int>> dp(n, vector<int>(n, 0)); // DP matrix for storing optimal cost
    vector<vector<int>> root(n, vector<int>(n, -1)); // Root matrix to track tree structure

    int minCost = optimalBSTWithRotations(freq, values, rotationCost, numRotations, root, dp);
    cout << "Minimum total cost including rotations: " << minCost << endl;
    cout << "Total number of rotations: " << numRotations << endl;

    // Print the tree structure
    cout << "\nOptimal tree structure:" << endl;
    printTreeStructure(root, 0, freq.size() - 1, freq, values);

    return 0;
}
