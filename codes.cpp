
void s1()
{
    int n;
    cin >> n;
    unordered_map<ll, ll> mp;

    fl(i, n)
    {
        ll e;
        cin >> e;
        mp[e]++;
    }

    priority_queue<ll> pq;

    for (auto i : mp)
    {
        pq.push(i.second);
    }

    ll res = 0;

    while (pq.size() > 1)
    {
        int top = pq.top();
        pq.pop();

        int sectop = pq.top();
        pq.pop();

        top--;
        sectop--;

        res++;

        if (top > 0)
            pq.push(top);

        if (sectop > 0)
            pq.push(sectop);
    }

    if (!pq.empty())
    {
        res += pq.top();
    }

    cout << res << endl;
}

void s2()
{
    ll n, c;
    cin >> n >> c;

    vector<ll> v(n);
    input_vector(v);

    // choice-1
    ll ch1 = 0ll;

    for (int i = 1; i < n; i++)
    {
        ch1 += v[0] * 1ll * v[i];
    }

    if (ch1 <= c)
    {
        cout << 1 << endl;
        return;
    }

    priority_queue<pll, vector<pll>, greater<pll>> pq;

    for (int i = 1; i < n; i++)
    {
        ll currReq = 0;
        for (int j = 0; j < n; j++)
        {
            if (j != i)
                currReq += v[i] * 1ll * v[j];
        }
        pq.push({currReq, i});
    }

    int ans = n;

    while (!pq.empty())
    {
        // remove top city
        auto top = pq.top();
        pq.pop();

        ll node = top.second, price = top.first;

        if (price <= c)
        {
            c -= price;
            ans--;

            vector<pll> temp;

            while (!pq.empty())
            {
                temp.push_back(pq.top());
                pq.pop();
            }

            for (auto i : temp)
            {
                pq.push({i.first - (v[i.second] * v[node]), i.second});
            }
        }
        else
        {
            break;
        }
    }

    cout << ans << endl;
}

void s3()
{
    int n;
    cin >> n;

    vector<ll> v(n);
    input_vector(v);

    int q;
    cin >> q;

    while (q--)
    {
        int l, r, x, y;
        cin >> l >> r >> x >> y;
        --l, --r;

        ll res = 0;

        for (int i = l; i <= r; i++)
        {
            vector<int> factors;
            int num = v[i];

            while (num > 1)
            {
                int d = spf[num], exp = 0;

                while (num % d == 0)
                {
                    exp++;
                    num /= d;
                }

                if (d >= x and d <= y)
                    res += exp;
            }
        }

        cout << res << endl;
    }
}

void s4()
{
    ll n;
    cin >> n;

    vector<int> v(n);
    input_vector(v);

    ll total = ((n) * 1ll * (n + 1)) / 2;

    ll rem = 0;

    vector<pair<int, int>> vp(4, {-1, -1});

    for (int i = 0; i < n; i++)
    {
        if (vp[v[i]].first == -1)
        {
            vp[v[i]].first = i;
        }
        vp[v[i]].second = i;
    }

    vector<int> compatible = {-1, 2, 3, 1};

    for (int i = 1; i <= 3; i++)
    {
        int l = vp[i].first;
        int r = vp[i].second;

        bool valid = true;

        for (int j = l; j <= r; j++)
        {
            if (v[j] == i || v[j] == compatible[i])
            {
                continue;
            }
            else
            {
                valid = false;
                break;
            }
        }

        if (valid)
        {
            rem++;

            l--;

            int n1 = 0, n2 = 0;

            while (l >= 0)
            {
                if (v[l] == compatible[i])
                {
                    n1++;
                }
                else
                {
                    break;
                }
                l--;
            }

            r++;

            while (r < n)
            {
                if (v[r] == compatible[i])
                {
                    n2++;
                }
                else
                {
                    break;
                }
                r++;
            }

            rem += n1 + n2 + (n1 * 1ll * n2);
        }
    }

    ll res = total - rem;

    cout << res << endl;
}
