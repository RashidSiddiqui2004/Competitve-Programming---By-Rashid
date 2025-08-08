
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
    vector<int> v(n);
    inputvector(v);

    unordered_map<int, int> distinct_elements;
    for (auto i : v)
    {
        distinct_elements[i]++;
    }

    vector<int> t;
    for (auto i : distinct_elements)
    {
        t.push_back(i.second);
    }

    sort(all(t), greater<>());

    int p = distinct_elements.size();
    int ans = 0;

    for (int i = p; i >= 1; i--)
    {
        ans = max(ans, (n / i) * i);
        n -= t[i - 1];
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