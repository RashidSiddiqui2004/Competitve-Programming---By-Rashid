
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define inputvector(v) \
    for (auto &x : v)  \
    {                  \
        cin >> x;      \
    }

#define all(v) v.begin(), v.end()

void solve()
{
    int n;
    cin >> n;
    vector<ll> v(n);
    inputvector(v);

    ll my = v[0];
    vector<ll> sm, lg;

    for (int i = 1; i < n; i++)
    {
        if (v[i] < my)
        {
            sm.push_back(v[i]);
        }
        else
        {
            lg.push_back(v[i]);
        }
    }

    ll ans = 1;
    if (sm.size() == 0)
    {
        ans += my - 1;
    }
    else
    {
        ll t = *max_element(all(sm));
        ll gap = abs(t - my);
        ans += gap / 2;
    }

    if (lg.size() == 0)
    {
        ans += (1e6 - my);
    }
    else
    {
        ll t = *min_element(all(lg));
        ll gap = abs(t - my);
        ans += gap / 2;
    }

    if (lg.size() == 0 and sm.size() == 0)
    {
        ans--;
    }

    cout << ans << endl;
}
int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    ll t;
    cin >> t;

    while (t--)
        solve();

    return 0;
}