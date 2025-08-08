void s14()
{
    int n, points;
    cin >> n >> points;

    vector<int> rows(n), cols(n);

    fl(i, n)
    {
        cin >> rows[i] >> cols[i];
    }

    vector<vector<ll>> cost(n + 1, vector<ll>(points + 1, 1e9));

    for (int i = 0; i <= n; i++)
    {
        cost[i][0] = 0;
    }

    fl(i, n)
    {
        fl(j, rows[i] + 1)
        {
            fl(k, cols[i] + 1)
            {
                int total = j + k;
                if (total <= points)
                {
                    ll val = (rows[i] * (k)) + (cols[i] * (j)) - (j * k);

                    cost[i][total] = min(cost[i][total], val);
                }
            }
        }
    }

    // for (auto i : cost)
    // {
    //     for (auto j : i)
    //     {
    //         cout << j << " ";
    //     }
    //     cout << endl;
    // }

    vector<vector<ll>> dp(n + 1, vector<ll>(points + 1, 1e9));

    for (int i = 0; i <= n; i++)
    {
        dp[i][0] = 0;
    }

    for (int i = 1; i <= n; i++)
    {
        int r = rows[i - 1], c = cols[i - 1];
        int total = r + c;
        for (int j = 0; j <= min(total, points); j++)
        {
            for (int t = 0; (j + t) <= points; t++)
            {
                dp[i][j + t] = min(dp[i][j + t], dp[i - 1][t] + cost[i - 1][j]);
            }
        }
    }

    ll ans = (dp[n][points] >= 1e9) ? -1 : dp[n][points];

    cout << ans << endl;
}
