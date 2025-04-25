#include <iostream>
#include <climits>
#include <unordered_map>
using namespace std;

// Find optimal cost to construct a binary search tree from keys i to j
// where each key k occurs freq[k] number of times
int findOptimalCost(int freq[], int i, int j, int level, int rotationCost, auto &lookup)
{
	// base case
	if (j < i) {
		return 0;
	}

	// construct a unique map key from dynamic elements of the input
	string key = to_string(i) + "|" + to_string(j) + "|" + to_string(level);

	// if the subproblem is seen for the first time, solve it and
	// store its result in a map
	if (lookup.find(key) == lookup.end())
	{
		lookup[key] = INT_MAX;

		int leftOptimalCost, rightOptimalCost;

		// consider each key as root and recursively find an optimal solution
		for (int k = i; k <= j; k++)
		{
			// recursively find the optimal cost of the left subtree
			leftOptimalCost = findOptimalCost(freq, i, k - 1, level + 1, rotationCost, lookup);

			// recursively find the optimal cost of the right subtree
			rightOptimalCost = findOptimalCost(freq, k + 1, j, level + 1, rotationCost, lookup);

			// current node's cost is freq[k]×level
			// Add the rotation cost for each rotation
			int cost = freq[k] * level + leftOptimalCost + rightOptimalCost + rotationCost;

			// update the optimal cost
			lookup[key] = min(lookup[key], cost);
		}
	}

	// return the subproblem solution from the map
	return lookup[key];
}

int main()
{
	int freq[] = { 4, 2, 6, 3 };
	int n = sizeof(freq) / sizeof(freq[0]);
	int rotationCost = 5; // Fixed rotation cost for every operation

	// create a map to store solutions to subproblems
	unordered_map<string, int> lookup;

	cout << "The optimal cost of constructing BST with rotation cost is "
		 << findOptimalCost(freq, 0, n - 1, 1, rotationCost, lookup);

	return 0;
}
