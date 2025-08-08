#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 50;
ll dp[MAXN][MAXN];
ll v[MAXN];

ll solve(int l, int r)
{
    if (l == r)
        return v[l]; // Base case: single slime remains

    if (dp[l][r] != -1)
        return dp[l][r]; // Memoization

    ll best = 0;
    // Try merging adjacent slimes
    for (int k = l; k < r; k++)
    {
        ll leftOutcome = solve(l, k);
        ll rightOutcome = solve(k + 1, r);

        // Two ways to merge adjacent segments
        best = max(best, max(0LL, leftOutcome - rightOutcome));
        best = max(best, max(0LL, rightOutcome - leftOutcome));
    }

    return dp[l][r] = best;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++)
            cin >> v[i];

        memset(dp, -1, sizeof(dp));

        cout << solve(0, n - 1) << "\n";
    }
    return 0;
}
