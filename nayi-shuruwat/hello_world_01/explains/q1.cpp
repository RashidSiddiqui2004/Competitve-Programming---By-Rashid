
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define inputvector(v) \
    for (auto &x : v)  \
    {                  \
        cin >> x;      \
    }
#define fl(i, n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define pii pair<int, int>

vector<pii> helper2(const vector<ll> &array)
{
    unordered_map<int, int> mp;
    mp[0] = 0;

    ll prefixXor = 0;
    vector<pii> result;

    for (int j = 0; j < array.size(); ++j)
    {
        prefixXor ^= array[j];

        auto it = mp.find(prefixXor);
        if (it != mp.end())
        {
            result.push_back({it->second, j + 1});
        }

        mp[prefixXor] = j + 1;
    }

    return result;
}

void solve()
{
    int n;
    cin >> n;

    vector<ll> v(n);

    fl(i, n)
    {
        cin >> v[i];
    }

    ll ans = 0;
    vector<ll> score(n, -1);

    auto temp = helper2(v);

    unordered_map<int, int> mp;

    for (auto i : temp)
    {
        // cout << i.first << " " << i.second << endl;
        if (mp.count(i.first))
            mp[i.first] = min(mp[i.first], i.second - 1);
        else
            mp[i.first] = i.second - 1;
    }

    for (int i = n - 1; i >= 0; i--)
    {
        ll curr = v[i], currxor = v[i];

        if (mp.count(i))
        {
            curr += score[mp[i]];
            ans = max(ans, curr);
            score[i] = curr;
        }
        else
        {
            ans = max(ans, curr);
            score[i] = curr;
        }
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