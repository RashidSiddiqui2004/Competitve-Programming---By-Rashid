// https://codeforces.com/contest/1324/problem/F

vector<ll> a;
vector<ll> dp;
vector<ll> ans;
// returns {black, white}

void dfs(int node, vector<vector<ll>> &adj, int par)
{
    dp[node] = a[node];
    for (auto to : adj[node])
    {
        if (to == par)
            continue;
        dfs(to, adj, node);
        dp[node] += max(dp[to], 0ll);
    }
}

void dfs2(int v, vector<vector<ll>> &adj, int p = -1)
{
    ans[v] = dp[v];
    for (auto to : adj[v])
    {
        if (to == p)
            continue;

        dp[v] -= max(0ll, dp[to]);
        dp[to] += max(0ll, dp[v]);
        dfs2(to, adj, v);
        dp[to] -= max(0ll, dp[v]);
        dp[v] += max(0ll, dp[to]);
    }
}

void r4()
{
    int n;
    cin >> n;
    a = dp = ans = vector<ll>(n);
    fl(i, n)
    {
        cin >> a[i];
        if (a[i] == 0)
            a[i] = -1;
    }

    vector<vector<ll>> adj(n);

    fl(i, n - 1)
    {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(0, adj, -1);
    dfs2(0, adj, -1);

    for (int i = 0; i < n; i++)
    {
        cout << ans[i] << " ";
    }
}
