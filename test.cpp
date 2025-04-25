#include <bits/stdc++.h>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    Node(int k) : key(k), left(nullptr), right(nullptr) {}
};

Node* insertBST(Node* root, int key) {
    if (!root) return new Node(key);
    if (key < root->key)
        root->left = insertBST(root->left, key);
    else
        root->right = insertBST(root->right, key);
    return root;
}

// Build OBST using root[i][j]
Node* buildOBST(vector<int>& keys, vector<vector<int>>& root, int i, int j) {
    if (i > j) return nullptr;
    int r = root[i][j];
    Node* node = new Node(keys[r]);
    node->left = buildOBST(keys, root, i, r - 1);
    node->right = buildOBST(keys, root, r + 1, j);
    return node;
}

// Compare two trees and count structural differences (approximating rotations)
int countRotations(Node* t1, Node* t2) {
    if (!t1 && !t2) return 0;
    if (!t1 || !t2 || t1->key != t2->key) return 1;
    return countRotations(t1->left, t2->left) + countRotations(t1->right, t2->right);
}

int sum(vector<int>& freq, int i, int j) {
    int s = 0;
    for (int k = i; k <= j; k++)
        s += freq[k];
    return s;
}

int optCost(vector<int>& freq, int i, int j, vector<vector<int>>& memo, vector<vector<int>>& root) {
    if (j < i) return 0;
    if (j == i) {
        root[i][j] = i;
        return freq[i];
    }
    if (memo[i][j] != -1) return memo[i][j];

    int fsum = sum(freq, i, j);
    int minCost = INT_MAX;
    for (int r = i; r <= j; ++r) {
        int cost = optCost(freq, i, r - 1, memo, root) + optCost(freq, r + 1, j, memo, root);
        if (cost < minCost) {
            minCost = cost;
            root[i][j] = r;
        }
    }
    return memo[i][j] = minCost + fsum;
}

int optimalSearchTree(vector<int>& keys, vector<int>& freq, int& rotationCount) {
    int n = keys.size();
    vector<vector<int>> memo(n, vector<int>(n, -1));
    vector<vector<int>> root(n, vector<int>(n, -1));
    int cost = optCost(freq, 0, n - 1, memo, root);

    // Simulate naive BST
    Node* naiveBST = nullptr;
    for (int key : keys) {
        naiveBST = insertBST(naiveBST, key);
    }

    // Build OBST from root table
    Node* obst = buildOBST(keys, root, 0, n - 1);

    // Estimate rotations
    rotationCount = countRotations(naiveBST, obst);
    return (cost + (rotationCount*5));
}

void printTree(Node* root, string indent = "", bool last = true) {
    if (!root) return;
    cout << indent;
    if (last) {
        cout << "└──";
        indent += "   ";
    } else {
        cout << "├──";
        indent += "│  ";
    }
    cout << root->key << endl;
    printTree(root->left, indent, false);
    printTree(root->right, indent, true);
}

int main() {
    vector<int> keys = {10, 20, 30, 40};
    vector<int> freq = {4, 2, 6, 3};
    int rotationCount = 0;
    int cost = optimalSearchTree(keys, freq, rotationCount);
    cout << "Optimal Search Tree Cost: " << cost << endl;
    cout << "Estimated Number of Rotations (structural changes): " << rotationCount << endl;
    return 0;
}
