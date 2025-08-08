
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using lld = long double;
using ull = unsigned long long;
using pll = pair<ll, ll>;

// @param(p,q,r)
// finf p^(q!) % r
void func()
{
    int p, q, r;
    cin >> p >> q >> r;
}

int main()
{
    ll n, m;
    cin >> n >> m;
    vector<pll> x(m);

    for (int i = 0; i < m; i++)
    {
        cin >> x[i].first;
    }
    ll sum = 0;
    for (int i = 0; i < m; i++)
    {
        cin >> x[i].second;
        sum += x[i].second;
    }

    if (sum != n)
    {
        cout << -1 << endl;
    }
    else
    {
        sort(x.begin(), x.end());
        ll last = n;
        ll oper = 0;
        for (int i = m - 1; i >= 0; i--)
        {
            ll curr = x[i].first, extras = x[i].second;

            ll firstterm = last - curr;
            ll t = min(firstterm, extras);

            ll sum = 1ll * (t * 1ll * ((2 * 1ll * firstterm) + 1 - t)) / 2;
            oper += sum;

            last = max(1ll * (last - t), 1ll * x[i].first);
            if (extras > firstterm)
            {
                last--;
            }
        }
        if (last == 0)
            cout << oper << endl;
        else
        {
            cout << -1 << endl;
        }
    }
    return 0;
}