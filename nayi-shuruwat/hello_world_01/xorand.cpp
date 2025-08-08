
// https://www.codechef.com/problems/XORGAND?tab=statement
void magicnumbers()
{
    int n;
    cin >> n;

    vector<ll> v(n);
    inputvector(v);

    int q;
    cin >> q;
    vector<vector<ll>> queries(q);

    fl(i, q)
    {
        ll l, r, x;
        cin >> l >> r >> x;
        queries[i] = {l - 1, r - 1, x};
    }

    vector<vector<int>> countBits(32, vector<int>(n, 0));

    // countBits[i][j] tells count of numbers in range v[0] to v[j] having ith bit as first set bit

    fl(j, n)
    {
        for (int i = 31; i >= 0; i--)
        {
            if (((1 << i) & v[j]) != 0)
            {
                countBits[i][j]++;
                break;
            }
        }
    }

    fl(i, 32)
    {
        for (int j = 1; j < n; j++)
        {
            countBits[i][j] += countBits[i][j - 1];
        }
    }

    vector<int> ans(q, 0);

    fl(j, q)
    {
        ll l = queries[j][0], r = queries[j][1], x = queries[j][2];
        ll currsum = 0;
        for (int i = 31; i >= 0; i--)
        {
            bool isxset = ((1 << i) & x) != 0;

            if (isxset)
            {
                ll count = countBits[i][r] - (l != 0 ? countBits[i][l - 1] : 0);
                ll total = r - l + 1;

                currsum += total - (count + currsum);
                break;
            }
            else
            {
                ll count = countBits[i][r] - (l != 0 ? countBits[i][l - 1] : 0);
                currsum += count;
            }
        }
        ans[j] = currsum;
    }

    for (auto i : ans)
    {
        cout << i << endl;
    }
}