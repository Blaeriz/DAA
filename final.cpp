// C++ program for implementation of
// optimal binary search tree using memoization
#include <bits/stdc++.h>
using namespace std;

// A utility function to get sum of
// array elements freq[i] to freq[j]
int sum(vector<int> &freq, int i, int j) {

    int s = 0;
    for (int k = i; k <= j; k++)
        s += freq[k];
    return s;
}

// A recursive function to calculate
// cost of optimal binary search tree
int optCost(vector<int> &freq, int i, int j, vector<vector<int>> &memo) {

    // Base cases
    if (j < i)
        return 0;
    if (j == i)
        return freq[i];

    if (memo[i][j] != -1)
        return memo[i][j];

    // Get sum of freq[i], freq[i+1], ... freq[j]
    int fsum = sum(freq, i, j);

    // Initialize minimum value
    int min = INT_MAX;

    // One by one consider all elements
    // as root and recursively find cost
    // of the BST, compare the cost with
    // min and update min if needed
    for (int r = i; r <= j; ++r) {
        int cost = optCost(freq, i, r - 1, memo) + optCost(freq, r + 1, j, memo);
        if (cost < min)
            min = cost;
    }

    // Return minimum value
    return memo[i][j] = min + fsum;
}

// The main function that calculates
// minimum cost of a Binary Search Tree.
// It mainly uses optCost() to find
// the optimal cost.
int optimalSearchTree(vector<int> &keys, vector<int> &freq) {
    int n = keys.size();
    vector<vector<int>> memo(n, vector<int>(n, -1));
    return optCost(freq, 0, n - 1, memo);
}

int main() {

    vector<int> keys = {10, 20, 30, 40};
    vector<int> freq = {4, 2, 6, 3};
    cout << optimalSearchTree(keys, freq) << endl;
    return 0;
}
