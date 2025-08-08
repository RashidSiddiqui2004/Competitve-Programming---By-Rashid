
// https://www.codechef.com/problems/SUBSEQINV
// good question
void h3()
{
    int n;
    cin >> n;

    vector<ll> v(n);

    fl(i, n)
    {
        cin >> v[i];
    }

    int cnt = 0;
    vector<int> less(n), greater(n);

    ll mini = INT_MAX;

    for (int i = n - 1; i >= 0; i--)
    {
        less[i] = mini;
        mini = min(mini, v[i]);
    }
    ll maxi = 0;
    fl(i, n)
    {
        greater[i] = maxi;
        maxi = max(maxi, v[i]);
    }

    for (int i = n - 1; i >= 0; i--)
    {
        if (v[i] < less[i] and v[i] > greater[i])
        {
            cnt++;
        }
    }

    ll mod2 = 998244353;
    ll res = power(2, cnt, mod2);

    if (cnt == n)
    {
        res--;
    }

    cout << res << endl;
}
