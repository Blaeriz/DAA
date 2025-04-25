#include <iostream>
#include <vector>
#include <climits>
using namespace std;

// Function to calculate the sum of frequencies between indices i and j
int sum(const vector<int>& freq, int i, int j) {
    int result = 0;
    for (int k = i; k <= j; ++k) {
        result += freq[k];
    }
    return result;
}

// Function to compute the minimum search cost and construct the tree
int optimalBST(const vector<int>& keys, const vector<int>& freq, vector<vector<int>>& dp, vector<vector<int>>& root) {
    int n = keys.size();

    // Initialize DP and root tables
    for (int i = 0; i < n; ++i) {
        dp[i][i] = freq[i];  // Base case: cost for a single node
        root[i][i] = i;       // Root of the single-node tree is the node itself
    }

    // Fill the DP table for subarrays of length 2 to n
    for (int length = 2; length <= n; ++length) {
        for (int i = 0; i <= n - length; ++i) {
            int j = i + length - 1;
            dp[i][j] = INT_MAX;
            int totalFreq = sum(freq, i, j);  // Total frequency sum for the range [i, j]

            // Try each key as the root and calculate the cost
            for (int k = i; k <= j; ++k) {
                int cost = (k > i ? dp[i][k - 1] : 0) + (k < j ? dp[k + 1][j] : 0) + totalFreq;
                if (cost < dp[i][j]) {
                    dp[i][j] = cost;
                    root[i][j] = k;  // Set the root of the subtree to be key k
                }
            }
        }
    }

    // Return the minimum cost to construct the optimal BST
    return dp[0][n - 1];
}

// Function to print the optimal tree structure recursively
void printTree(const vector<int>& keys, const vector<vector<int>>& root, int i, int j) {
    if (i > j)
        return;

    // Find the root node of the current subtree
    int r = root[i][j];
    cout << "Root of subtree [" << i << ", " << j << "] is key: " << keys[r] << endl;

    // Recursively print the left and right subtrees
    printTree(keys, root, i, r - 1);
    printTree(keys, root, r + 1, j);
}

// Function to calculate the total search cost with depth adjustment
int calculateTotalCost(const vector<int>& keys, const vector<int>& freq, const vector<vector<int>>& root) {
    int n = keys.size();
    vector<vector<int>> depth(n, vector<int>(n, 0));

    // Calculate depth for each node
    for (int length = 1; length <= n; ++length) {
        for (int i = 0; i <= n - length; ++i) {
            int j = i + length - 1;
            // Root of the subtree is stored in root[i][j]
            int r = root[i][j];
            // Depth of the root node of the subtree
            int nodeDepth = length;  // Subtree depth is calculated based on the length of the range

            // Assign depth to all nodes in the subtree
            depth[i][j] = nodeDepth;
        }
    }

    // Calculate the total search cost using the formula: value * frequency * depth
    int totalCost = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int r = root[i][j];
            totalCost += keys[r] * freq[r] * depth[i][j];
        }
    }

    return totalCost;
}

int main() {
    vector<int> keys = {10, 20, 30, 40};  // Keys
    vector<int> freq = {4, 2, 6, 3};      // Frequencies

    int n = keys.size();
    
    // DP table to store the minimum cost for subarrays
    vector<vector<int>> dp(n, vector<int>(n, 0));

    // Table to store the root index for each subarray
    vector<vector<int>> root(n, vector<int>(n, 0));

    // Compute the optimal BST search cost
    int minCost = optimalBST(keys, freq, dp, root);
    cout << "Minimum total search cost: " << minCost << endl;

    // Print the optimal tree structure
    cout << "Optimal tree structure:" << endl;
    printTree(keys, root, 0, n - 1);

    // Calculate the total search cost including depth adjustment
    int totalSearchCost = calculateTotalCost(keys, freq, root);
    cout << "Total search cost (including depth): " << totalSearchCost << endl;

    return 0;
}
