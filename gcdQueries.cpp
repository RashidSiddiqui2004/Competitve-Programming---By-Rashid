#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

#define ll long long
#define int long long
#define endl '\n'
#define sp ' '
#define pb push_back
#define vi vector<int>
#define vll vector<ll>
#define vvi vector<vi>
#define all(c) c.begin(), c.end()
#define f first
#define s second
#define FORN(i, n) for (i = 0; i < n; i++)
#define OUT(a)                         \
    for (int l = 0; l < a.size(); l++) \
        cout << a[l] << sp;            \
    cout << endl;
#define OUT2(a)                        \
    for (int o = 0; o < a.size(); o++) \
    {                                  \
        OUT(a[o])                      \
    }
#define IN(a)                          \
    for (int l = 0; l < a.size(); l++) \
        cin >> a[l];
const int mod = 1e9 + 7;
ll i, j, k;

#define ordered_set tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>

const int maxn = 100005;
int spf[maxn];
map<int, ordered_set> idx;
int ans;

void inex(int v, int l, int r, int t)
{
    vector<int> di;
    while (v > 1)
    {
        int d = spf[v];
        while (v % d == 0)
            v /= d;
        di.pb(d);
    }

    int ds = di.size();

    // Generates all subsets of the divisors of v, using bitmasking.
    // p is the product of selected divisors, and countDiv is the number of selected divisors.

    for (int mask = 1; mask < (1 << ds); mask++)
    {
        int p = 1;
        int countDiv = 0;
        for (int i = 0; i < ds; i++)
        {
            if ((mask >> i) & 1)
            {
                p *= di[i];
                countDiv++;
            }
        }
        // insert index l into numbers which are divisors of v
        if (t == 0)
            idx[p].insert(l);
        else if (t == 1)
            idx[p].erase(l);
        else
        {
            if (countDiv & 1)
                ans += idx[p].order_of_key(r) - idx[p].order_of_key(l - 1);
            else
                ans -= idx[p].order_of_key(r) - idx[p].order_of_key(l - 1);
        }
    }
}

void solve()
{
    int n;
    cin >> n;
    vi a(n);
    IN(a);
    for (int k = 0; k < n; k++)
    {
        inex(a[k], k, 0, 0);
    }
    int q;
    cin >> q;
    while (q--)
    {
        int t;
        cin >> t;
        if (t == 1)
        {
            int x, y;
            cin >> x >> y;
            x--;
            inex(a[x], x, 0, 1);
            inex(y, x, 0, 0);
            a[x] = y;
        }
        else
        {
            int l, r, g;
            cin >> l >> r >> g;
            ans = 0;
            inex(g, l, r, 2);
            assert((r - l + 1) - ans >= 0);
            cout << r - l + 1 - ans << endl;
        }
    }
}

int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // spf => smallest prime factor
    // modified sieves for faster factorization
    for (ll i = 2; i < maxn; i++)
    {
        if (spf[i])
            continue;
        spf[i] = i;
        for (ll j = i * i; j < maxn; j += i)
        {
            if (!spf[j])
                spf[j] = i;
        }
    }
    int tt = 1;
    // 	cin>>tt; // No. of testcases
    while (tt--)
    {
        solve();
    }
    return 0;
}