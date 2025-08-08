#include <bits/stdc++.h>
#define ll long long
#define MAXN 100010
using namespace std;
ll n, s, a[MAXN], b[MAXN];
struct seg_tree
{
    vector<pair<ll, ll>> st;

    pair<ll, ll> Merge(pair<ll, ll> x, pair<ll, ll> y)
    {
        return {min(x.first, y.first), max(x.second, y.second)};
    }

    void Init()
    {
        st.clear();
        s = 1;
        while (s < n)
            s <<= 1;
        st.resize(2 * s + 2, {LLONG_MAX, LLONG_MIN});
    }

    void Build()
    {
        for (ll i = s; i < s + n; i++)
            st[i] = {a[i - s + 1], b[i - s + 1]};
        for (ll i = s - 1; i > 0; i--)
            st[i] = Merge(st[2 * i], st[2 * i + 1]);
    }

    pair<ll, ll> Calc(ll l, ll r, ll x, ll lx, ll rx)
    {
        if (lx > r || rx < l)
            return {LLONG_MAX, LLONG_MIN};
        if (lx >= l && rx <= r)
            return st[x];
        ll mid = (lx + rx) / 2;
        return Merge(Calc(l, r, 2 * x, lx, mid), Calc(l, r, 2 * x + 1, mid + 1, rx));
    }
};

seg_tree S;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    ll t;
    cin >> t;
    while (t--)
    {
        cin >> n;
        for (ll i = 1; i <= n; i++)
            cin >> a[i];

        bool yes = true;

        map<ll, vector<ll>> pos;

        for (ll i = 1; i <= n; i++)
        {
            cin >> b[i];
            if (b[i] < a[i])
                pos[b[i]].push_back(i);

            if (b[i] > a[i])
            {
                yes = false;
                break;
            }
        }

        S.Init();
        S.Build();
        if (!yes)
        {
            cout << -1 << "\n";
            continue;
        }

        ll ans = 0;
        for (auto it : pos)
        {
            vector<ll> cur = it.second;
            ll h = it.first, lastt = cur[0];

            ans++;

            for (ll i = 1; i < cur.size(); i++)
            {
                auto p = S.Calc(lastt, cur[i], 1, 1, s);
                if (p.first < h || p.second > h)
                {
                    ans++;
                    lastt = cur[i];
                }
            }
        }
        cout << ans << "\n";
    }
    return 0;
}