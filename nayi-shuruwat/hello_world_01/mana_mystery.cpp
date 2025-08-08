class Solution
{
public:
    using ll = long long;

    // DP table with dimensions [n][max_reduce_factor]
    vector<vector<ll>> dp;

    ll solve(vector<int> &arr, int k, int i, int reduceFactor)
    {
        int n = arr.size();

        // Base case: no items left
        if (i == n)
            return 0;

        // Limit reduceFactor to avoid redundant states
        if (reduceFactor > 30)
            return 0; // Beyond 2^30 is negligible for int inputs

        // Memoization check
        if (dp[i][reduceFactor] != -1)
            return dp[i][reduceFactor];

        // Choices:
        // 1. Do not apply additional reduction
        ll use1 = (arr[i] / (1LL << reduceFactor)) - k + solve(arr, k, i + 1, reduceFactor);

        // 2. Apply additional reduction
        ll use2 = (arr[i] / (1LL << (reduceFactor + 1))) + solve(arr, k, i + 1, reduceFactor + 1);

        // Store and return the maximum result
        return dp[i][reduceFactor] = max(use1, use2);
    }

    ll collectMana(vector<int> &arr, int k)
    {
        int n = arr.size();

        // Initialize DP table dynamically
        dp.assign(n, vector<ll>(31, -1)); // 31 covers all reasonable reduceFactors for int inputs

        return solve(arr, k, 0, 0);
    }
};