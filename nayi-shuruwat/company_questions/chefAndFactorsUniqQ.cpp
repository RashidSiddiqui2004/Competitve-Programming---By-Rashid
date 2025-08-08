
void h8()
{
    int n;
    cin >> n;
    vector<int> a(n);
    map<int, vector<int>> factors;
    unordered_map<int, int> dp;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        int x = a[i];
        if (factors.find(x) == factors.end())
        {
            for (int d = 1; d * d <= x; d++)
            {
                if (x % d == 0)
                {
                    factors[x].push_back(d);
                    if ((x / d) != d)
                    {
                        factors[x].push_back(x / d);
                    }
                }
            }
            sort(factors[x].begin(), factors[x].end());
        }
    }
    ll ans = 0;
    sort(a.rbegin(), a.rend());

    for (int i = 0; i < n; i++)
    {
        vector<int> f = factors[a[i]];
        for (auto &d : f)
        {
            dp[d] = max(dp[d], 1 + dp[a[i]]);
        }
    }

    for (int i = 0; i < n; i++)
    {
        ans = max(ans, 1LL * dp[a[i]] * a[i]);
    }

    cout << ans << endl;
}
