// https://codeforces.com/contest/2000/problem/E

#include <vector>
using namespace std;

vector<vector<ll>> calculateFrequency(int n, int m, int k)
{
    vector<vector<ll>> grid(n + 1, vector<ll>(m + 1, 0));

    // Step 1: Apply the difference array updates
    for (int i = 0; i <= n - k; i++)
    {
        for (int j = 0; j <= m - k; j++)
        {
            grid[i][j]++;
            grid[i + k][j + k]++;
            grid[i][j + k]--;
            grid[i + k][j]--;
        }
    }

    // Step 2: Perform row-wise prefix sums
    for (int i = 0; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            grid[i][j] += grid[i][j - 1];
        }
    }

    // Step 3: Perform column-wise prefix sums
    for (int j = 0; j <= m; j++)
    {
        for (int i = 1; i <= n; i++)
        {
            grid[i][j] += grid[i - 1][j];
        }
    }

    // Step 4: Trim the grid to size n x m
    vector<vector<ll>> result(n, vector<ll>(m, 0));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            result[i][j] = grid[i][j];
        }
    }

    return result;
}

void s13()
{
    int n, m;
    cin >> n >> m;
    int k;
    cin >> k;
    int w;
    cin >> w;

    vector<ll> gor(w);
    fl(i, w)
    {
        cin >> gor[i];
    }
    sort(all(gor), greater<>());

    vector<vector<ll>> grid = calculateFrequency(n, m, k);

    map<ll, ll> freq;

    for (auto i : grid)
    {
        for (auto j : i)
        {
            freq[j]++;
        }
    }

    auto it = freq.rbegin();

    ll ans = 0;
    int pos = 0;

    while (it != freq.rend())
    {
        auto f = it->second, val = it->first;
        // f kya hai ? kitne cells hai iss freq ke

        for (int i = 0; i < f and pos < w; i++)
        {
            ans += gor[pos++] * 1ll * val;
        }

        ++it;
    }

    cout << ans << endl;
}
