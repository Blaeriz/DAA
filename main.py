import sys

def optimal_bst_cost(keys, freq):
    """
    Calculates the minimum cost of an Optimal Binary Search Tree using dynamic programming.
    Minimizes the standard expected search cost: Sum(freq[i] * (depth[i] + 1)).

    Args:
        keys: A sorted list of keys.
        freq: A list of frequencies corresponding to each key in keys.

    Returns:
        The minimum total search cost for the OBST.
    """
    n = len(freq)
    if n == 0:
        return 0

    cost = [[0.0] * (n + 1) for _ in range(n + 1)]

    prefix_sum = [0] * (n + 1)
    for i in range(n):
        prefix_sum[i + 1] = prefix_sum[i] + freq[i]

    def get_sum(i, j):
        if i > j:
            return 0
        start_idx = max(0, i)
        end_idx = min(n, j + 1)
        return prefix_sum[end_idx] - prefix_sum[start_idx]

    for i in range(n):
        cost[i][i] = freq[i]

    for L in range(2, n + 1):
        for i in range(n - L + 1):
            j = i + L - 1
            if i > j: continue

            current_freq_sum = get_sum(i, j)
            cost[i][j] = sys.float_info.max

            for k in range(i, j + 1):
                left_cost = cost[i][k - 1] if k > i else 0
                right_cost = cost[k + 1][j] if k < j else 0
                current_k_cost = left_cost + right_cost + current_freq_sum
                cost[i][j] = min(cost[i][j], current_k_cost)

    return cost[0][n - 1]

# --- Example Usage ---
keys = [10, 20, 30, 40]
frequencies = [4, 2, 6, 3]
min_cost = optimal_bst_cost(keys, frequencies)
print(f"Minimum OBST Search Cost: {min_cost}") # Output: 26.0
