// https://www.codechef.com/problems/GRDXOR
void r4()
{
    int n, m;
    cin >> n >> m;

    vector<vector<ll>> grid(n, vector<ll>(m, 0));

    fl(i, n)
    {
        fl(j, m)
        {
            cin >> grid[i][j];
        }
    }

    vector<vector<int>> rows(31, vector<int>(n, 0)), cols(31, vector<int>(m, 0));

    vector<int> bitsloc(31, 0);

    fl(i, 31)
    {
        int cnt = 0;
        fl(j, n)
        {
            fl(k, m)
            {
                if (((1 << i) & grid[j][k]) != 0)
                {
                    cnt++;
                }
            }
        }
        bitsloc[i] = cnt;
    }

    // rowwise set bits
    for (int k = 0; k < 31; k++)
    {
        for (int i = 0; i < n; i++)
        {
            int cnt = 0;
            for (int j = 0; j < m; j++)
            {
                if (((1 << k) & grid[i][j]) != 0)
                {
                    cnt++;
                }
            }
            rows[k][i] = cnt;
        }
    }

    // colwise set bits
    for (int k = 0; k < 31; k++)
    {
        for (int i = 0; i < m; i++)
        {
            int cnt = 0;
            for (int j = 0; j < n; j++)
            {
                if (((1 << k) & grid[j][i]) != 0)
                {
                    cnt++;
                }
            }
            cols[k][i] = cnt;
        }
    }

    ll res = 0;

    fl(i, n)
    {
        fl(j, m)
        {
            ll sum = 0;

            for (int bitpos = 0; bitpos < 30; bitpos++)
            {
                if (((1 << bitpos) & grid[i][j]) == 0)
                {
                    ll total = bitsloc[bitpos];

                    total = total - (rows[bitpos][i] + cols[bitpos][j]);

                    sum += (1 << bitpos) * total;
                }
                else
                {
                    ll total = (n * m) - bitsloc[bitpos];

                    total = total - ((m - rows[bitpos][i]) + (n - cols[bitpos][j]));

                    sum += (1 << bitpos) * total;
                }
            }

            res = max(res, sum);
        }
    }

    cout << res << endl;
}
