// https://www.codechef.com/problems/SUMARRAY

void h7()
{
    ll n, k;
    cin >> n >> k;

    vector<ll> v(n, 1);
    for (int i = 0; i < n; i += 2)
    {
        v[i] = 2;
    }

    ll sum = accumulate(all(v), 0ll);
    ll rem = k - sum;

    for (int i = 0; i < n and rem > 0; i++)
    {
        if ((v[i] + rem) <= 1e5)
        {
            ll inc = rem;
            if ((v[i] % 2) != ((v[i] + rem) % 2))
            {
                inc--;
            }
            v[i] += inc;
            rem -= inc;
        }
        else
        {
            if (i % 2 == 0)
            {
                ll inc = 1e5 - v[i];
                v[i] = 1e5;
                rem -= inc;
            }
            else
            {
                ll inc = (1e5 - 1) - v[i];
                v[i] = (1e5 - 1);
                rem -= inc;
            }
        }
    }

    if (rem == 0)
    {
        for (auto i : v)
        {
            cout << i << " ";
        }
        cout << "\n";
    }
    else
    {
        cout << -1 << "\n";
    }
}
