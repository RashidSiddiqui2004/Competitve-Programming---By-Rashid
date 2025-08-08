#include <iostream>
#include <bitset>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using lld = long double;
using ull = unsigned long long;

// Constants
const ll INF = LONG_LONG_MAX;
const ll mod = 1e9 + 7;

// TypeDEf
typedef pair<ll, ll> pll;
typedef vector<ll> vll;
typedef vector<pll> vpll;
typedef vector<string> vs;
typedef unordered_map<ll, ll> umll;
typedef map<ll, ll> mll;
// Macros
#define ff first
#define ss second
#define pb push_back
#define pii pair<int, int>
#define fl(i, start, n) for (int i = start; i < n; i++)
#define loop(i, n) for (int i = 0; i < n; i++)
#define rl(i, m, n) for (int i = n; i >= m; i--)
#define py cout << "YES\n";
#define pm cout << "-1\n";
#define pn cout << "NO\n";
#define pimp cout << "IMPOSSIBLE\n";
#define vr(v) v.begin(), v.end()
#define rv(v) v.end(), v.begin()
#define len(s) (int)s.size()
#define forn(i, n) for (int i = 0; i < int(n); i++)
#define all(v) v.begin(), v.end()
#define one(x) memset(x, -1, sizeof(x))
#define zero(x) memset(x, 0, sizeof(x))

template <class T>
void print(const T &t)
{
    print_single(t);
}

template <class T, class... Args>
void print(const T &t, const Args &...args)
{
    print_single(t, 2);
    print(args...);
}

string readString()
{
    string s;
    cin >> s;
    return s;
}

void printarr(vector<int> &a)
{
    for (auto i : a)
    {
        cout << i << " ";
    }
    cout << endl;
}

// read unweighted undirected/directed graph
vector<vector<ll>>
readUnWeightedGraph(int n, int m, bool isDirected = true)
{
    vector<vector<ll>> g(n);
    fl(i, 0, m)
    {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        g[a].pb(b);
        if (isDirected == false)
            g[b].pb(a);
    }
    return g;
}
// read weighted undirected/directed graph
vector<vector<pll>> readWeightedGraph(int n, int m, bool isDirected = true)
{
    vector<vector<pll>> g(n);
    fl(i, 0, m)
    {
        ll a, b, w;
        cin >> a >> b >> w;
        a--;
        b--;
        g[a].pb({b, w});
        if (isDirected == false)
            g[b].pb({a, w});
    }
    return g;
}

#define khalaas return 0;
#define in1(t) \
    int t;     \
    cin >> t;
#define in2(a, b) \
    int a, b;     \
    cin >> a >> b
#define in3(a, b, c) \
    int a, b, c;     \
    cin >> a >> b >> c
#define in4(a, b, c, d) \
    int a, b, c, d;     \
    cin >> a >> b >> c >> d
#define in5(a, b, c, d, e) \
    ll a, b, c, d, e;      \
    cin >> a >> b >> c >> d >> e
#define in6(a, b, c, d, e, f) \
    ll a, b, c, d, e, f;      \
    cin >> a >> b >> c >> d >> e >> f

#define vecin(v, n) \
    vector<ll> v;   \
    loop(i, 0, n)   \
    {               \
        in1(x);     \
        v.pb(x);    \
    }

typedef priority_queue<int> pq;

typedef unordered_map<char, int> ump;

typedef unordered_set<ll> ust;

typedef priority_queue<int, vector<int>, greater<int>> minh;

typedef priority_queue<int> maxh;

#define TEST   \
    int t = 1; \
    cin >> t;  \
    while (t--)

#define QUERY \
    int q;    \
    cin >> q; \
    while (q--)

#define prec(n) fixed << setprecision(n)

int mod_add(int a, int b, int m)
{
    a %= m;
    b %= m;
    return ((a + b) % m);
}
int mod_sub(int a, int b, int m)
{
    a %= m;
    b %= m;
    return ((a - b) % m);
}
int mod_mul(int a, int b, int m)
{
    a %= m;
    b %= m;
    return ((a * b) % m);
}

// it returns the logarithm of n to the base k
// @param(long long n) the value
// @param(long long k) the base for the logarithm
int lognk(ll n, ll k)
{
    int ans = 0;
    if (k == 1)
    {
        // Logarithm base 1 is undefined, return special value
        return n - 1; // Subtracting one repeatedly in this case
    }

    int currnum = 1;
    while ((currnum * k) <= n)
    {
        if (currnum > n / k) // Prevent multiplication overflow
            break;
        currnum *= k;
        ans++;
    }
    return ans;
}

const ll M = mod;

unsigned long long powerOptimum(unsigned long long x,
                                int y, int p = M)
{
    unsigned long long res = 1;

    x = x % p; // Update x if it is more than or
    // equal to p

    while (y > 0)
    {

        // If y is odd, multiply x with result
        if (y & 1)
            res = (res * x) % p;

        // y must be even now
        y = y >> 1; // y = y/2
        x = (x * x) % p;
    }
    return res;
}

ll modInverse(ll A)
{
    return (powerOptimum(A, M - 2));
}

unsigned long long factdp[1000000 + 1];

ll nCr(ll n, ll r)
{
    ll x = factdp[n - r];
    x = modInverse(x);

    n = factdp[n];
    r = factdp[r];
    r = modInverse(r);

    ll ans = (n * r) % M;
    ans *= x;
    ans %= M;

    return ans;
}

void factorialCalculation()
{
    memset(factdp, -1, sizeof(factdp));
    factdp[0] = 1;
    for (int i = 1; i <= 1000000; i++)
        factdp[i] = (factdp[i - 1] * i) % mod;
}

void solve1()
{
    int a, b;
    cin >> a >> b;
    if (a >= b)
    {
        cout << a << endl;
        return;
    }

    int x = b - a;
    if (x > a)
    {
        cout << 0 << endl;
    }
    else
    {
        a = a - x;
        cout << a << endl;
    }
}

void solve2()
{
    int n;
    cin >> n;
    string s;
    cin >> s;

    int ans = 0;
    int as = 0, bs = 0;
    for (auto i : s)
    {
        if (i == 'a')
            as++;
        else
        {
            bs++;
        }
    }

    ans = max(as, bs);

    // int curr = 0;
    // int len = 0;
    // for (int i = 0; i < n; i++)
    // {
    //     if (s[i] == 'a' and curr == 0)
    //     {
    //         len++;
    //         curr = !curr;
    //     }
    //     else if (s[i] == 'b' and curr == 1)
    //     {
    //         len++;
    //         curr = !curr;
    //     }
    // }

    int p1 = 0, p2 = n - 1;

    while (p1 < n and s[p1] != 'a')
    {
        p1++;
    }
    while (p2 >= 0 and s[p2] != 'a')
    {
        p2--;
    }

    if (p1 <= p2)
    {
        ans = max(ans, p2 - p1 + 1);
    }
    p1 = 0, p2 = n - 1;

    while (p1 < n and s[p1] != 'b')
    {
        p1++;
    }
    while (p2 >= 0 and s[p2] != 'b')
    {
        p2--;
    }

    if (p1 <= p2)
    {
        ans = max(ans, p2 - p1 + 1);
    }

    cout << ans << endl;
}

void solve3()
{
    int n;
    cin >> n;

    vector<ll> a(n), b(n);

    fl(i, 0, n)
    {
        cin >> a[i];
    }
    fl(i, 0, n)
    {
        cin >> b[i];
    }

    vector<int> vis(n, false);
    vector<pll> morecost, lesscost;

    fl(i, 0, n)
    {
        if (b[i] >= a[i])
        {
            morecost.push_back({b[i] - a[i], i});
        }
        else
        {
            lesscost.push_back({a[i] - b[i], i});
        }
    }

    int morecostsz = morecost.size(), lesscostsz = lesscost.size();
    ll mini = 0;

    if (lesscostsz == 0 and n == 1)
    {
        mini = b[0];
        cout << mini << endl;
        return;
    }

    if ((morecostsz >= 2) || (morecostsz == 0))
    {
        for (int i = 0; i < n; i++)
        {
            mini += min(a[i], b[i]);
        }
        cout << mini << endl;
        return;
    }
    else
    {
        if (morecostsz)
            sort(all(morecost), greater<>());
        if (lesscostsz)
            sort(all(lesscost));
        ll mini = 0;

        ll loss = b[morecost[0].second] - a[morecost[0].second];
        ll gain = a[lesscost[0].second] - b[lesscost[0].second];

        if (gain >= loss)
        {
            // cout << "0" << endl;
            vis[morecost[0].second] = 1;
            mini += b[morecost[0].second];
            for (int i = 0; i < n; i++)
            {
                if (vis[i] == 0)
                    mini += min(a[i], b[i]);
            }
            cout << mini << endl;
            return;
        }
        else
        {
            // cout << "1" << endl;
            vis[morecost[0].second] = 1;
            vis[lesscost[0].second] = 1;
            mini += a[morecost[0].second];
            mini += a[lesscost[0].second];
            for (int i = 0; i < n; i++)
            {
                if (vis[i] == 0)
                    mini += min(a[i], b[i]);
            }
            cout << mini << endl;
            return;
        }
    }

    //   for (auto i : morecost)
    // {
    //     if (vis[i.second] == 1)
    //     {
    //         morep1++;
    //         continue;
    //     }
    //     vis[i.second] = 1;
    //     mini += a[i.second];
    //     if (morep1 < morecost.size())
    //     {
    //         while (morep1 < (morecost.size()) and vis[morecost[morep1].second] == 1)
    //         {
    //             morep1++;
    //         }

    //         vis[morecost[morep1].second] = 1;
    //         mini += a[morecost[morep1].second];
    //         morep1++;
    //     }
    //     else
    //     {
    //         while (lessp1 < (lesscost.size()) and vis[lesscost[lessp1].second] == 1)
    //         {
    //             lessp1++;
    //             // cout << "hi" << " ";
    //         }

    //         vis[lesscost[lessp1].second] = 1;
    //         mini += a[lesscost[lessp1].second];
    //         lessp1++;
    //     }
    // }

    // for (int i = 0; i < n; i++)
    // {
    //     if (vis[i] == 0)
    //     {
    //         mini += b[i];
    //     }
    // }

    // cout << mini << endl;
}

void solve5()
{
    int n;
    cin >> n;
    unordered_map<ll, ll> mp;

    fl(i, 0, n)
    {
        ll e;
        cin >> e;
        if (mp.count(e))
        {
            ll elem = e;
            mp[elem]++;
            while (mp[elem] >= 2)
            {
                mp.erase(elem);
                mp[2 * 1ll * elem]++;
                elem = elem * 1ll * 2;
            }
        }
        else
        {
            mp[e]++;
        }
        int sz = mp.size();
        cout << sz << " ";
    }

    cout << endl;
}

void solve6()
{
    int n;
    cin >> n;

    vector<unordered_set<ll>> adj(n);

    fl(i, 0, n - 1)
    {
        ll u, v;
        cin >> u >> v;
        adj[u - 1].insert(v - 1);
    }

    int ans = 0;

    vector<vector<ll>> vt;

    fl(i, 0, n - 1)
    {
        unordered_set<int> skip;
        unordered_map<int, int> mp;
        bool chk = false;

        for (int j = 0; j < n; j++)
        {
            if (skip.count(j))
            {
                continue;
            }

            if (adj[j].size() >= 1)
            {
                int cantake = -1;
                for (auto t : adj[j])
                {
                    if (!skip.count(t))
                    {
                        cantake = t;
                        break;
                    }
                }
                if (cantake == -1)
                {
                    continue;
                }
                else
                {
                    chk = true;
                    mp[j] = cantake;
                    skip.insert(j);
                    skip.insert(cantake);
                    adj[j].erase(cantake);
                }
            }
        }

        if (!chk)
        {
            break;
        }
        vector<ll> vec(n);
        iota(vec.begin(), vec.end(), 1);
        for (auto k : mp)
        {
            int first = k.first, sec = k.second;
            int val = vec[first];
            vec[sec] = val;
        }
        skip.clear();
        mp.clear();
        vt.push_back(vec);
    }

    ans = vt.size();

    cout << ans << endl;

    for (auto vec : vt)
    {
        for (auto i : vec)
        {
            cout << i << " ";
        }
        cout << endl;
    }
}

void solve7()
{
    int n, m;
    cin >> n >> m;

    vector<ll> a(n), b(m);

    fl(i, 0, n)
    {
        cin >> a[i];
    }

    fl(i, 0, m)
    {
        cin >> b[i];
    }

    if ((n < 4) || (m < 4) || (n + m < 11))
    {
        cout << -1 << endl;
    }
    else
    {
        sort(all(a), greater<>());
        sort(all(b), greater<>());
        ll maxi = 0;
        vector<ll> rem(a.begin() + 4, a.end());

        for (int i = 4; i < m; i++)
        {
            rem.push_back(b[i]);
        }

        for (int i = 0; i < 4; i++)
        {
            maxi += (a[i] + b[i]);
        }

        sort(all(rem), greater<>());

        for (int i = 0; i < 3; i++)
        {
            maxi += rem[i];
        }
        cout << maxi << endl;
    }
}

void solve8()
{
    int n, k;
    cin >> n >> k;

    vector<string> v(n);
    fl(i, 0, n)
    {
        cin >> v[i];
    }

    vector<bool> bitsset(k, 0);
    fl(i, 0, n)
    {
        bool hasfound = false, chk = true;
        int pos = -1;
        for (int j = 0; j < k; j++)
        {
            if (v[i][j] == '1')
            {
                if (!hasfound)
                {
                    hasfound = true;
                    pos = j;
                }
                else
                {
                    chk = false;
                    break;
                }
            }
        }
        if (chk and hasfound)
        {
            bitsset[pos] = 1;
        }
    }

    bool chk = true;
    for (int i = 0; i < k; i++)
    {
        if (bitsset[i] == 0)
        {
            chk = false;
            break;
        }
    }

    if (chk)
    {
        cout << "YES\n";
    }
    else
    {
        cout << "NO\n";
    }
}

void solve9()
{
    int n;
    cin >> n;

    vector<ll> v(n);

    fl(i, 0, n)
    {
        cin >> v[i];
    }

    int i = 0;
    vector<ll> countodds;

    while (i < n)
    {
        while (i < n and (v[i] % 2) == 0)
        {
            i++;
        }
        ll len = 0;
        while (i < n and (v[i] % 2) != 0)
        {
            i++;
            len++;
        }
        countodds.push_back(len);
    }

    ll ans = (n * 1ll * (n + 1)) / 2;

    sort(countodds.begin(), countodds.end());

    ll maxi = countodds[countodds.size() - 1];
    countodds.pop_back();

    if ((maxi % 2) == 0)
    {
        countodds.push_back(maxi / 2);
        countodds.push_back((maxi / 2) - 1);
    }
    else
    {
        countodds.push_back(maxi / 2);
        countodds.push_back(maxi / 2);
    }

    for (auto i : countodds)
    {
        ans -= (i * (i + 1)) / 2;
    }
    cout << ans << endl;
}

void solve10()
{
    ll n;
    cin >> n;
    vector<ll> a(n + 1), ones(n, 0ll), twos(n, 0ll);

    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        ones[i] = (i != 0 ? ones[i - 1] : 0) + (a[i] == 1 ? 1 : 0);
        twos[i] = (i != 0 ? twos[i - 1] : 0) + (a[i] == 2 ? 1 : 0);
    }

    int q;
    cin >> q;

    while (q--)
    {
        ll l, r, k;
        cin >> l >> r >> k;
        --l, --r;
        ll currones = ones[r] - (l == 0 ? 0 : ones[l - 1]);
        ll currtwos = twos[r] - (l == 0 ? 0 : twos[l - 1]);
        if (currones > currtwos)
        {
            swap(currones, currtwos);
        }

        // sirf subarray ka btana hai bhai => simple :)

        ll rem = (r - l + 1) - currones - currtwos;
        ll tosubt = min({rem, k, currtwos - currones});
        currones += tosubt;
        k -= tosubt;
        rem -= tosubt;

        if (currones == currtwos)
        {
            k = min(k, rem);
            currones += (k / 2);
            currtwos += (k + 1) / 2;
        }
        else
        {
            ll diff = (currtwos - currones);
            k = min(k, diff / 2);
            currones += k;
            currtwos -= k;
        }
        ll currans = currones * 1ll * currtwos;
        cout << currans << endl;
    }
}

void solve11()
{
    ll ans = 0, maxi = -1;

    for (int i = 0; i < 22; i++)
    {
        ll a, b;
        cin >> a >> b;
        ll curr = a + (20 * 1ll * b);
        if (curr > maxi)
        {
            maxi = curr;
            ans = i + 1;
        }
    }
    cout << ans << endl;
}

// no mistakes again
void solve12()
{
    ll n, m, x, y, l;
    cin >> n >> m >> x >> y >> l;

    ll t1 = (m - y) / l;
    if ((y + (t1 * l)) > m)
    {
        t1--;
    }
    ll t2 = (n - x) / l;
    if ((x + (t2 * l)) > n)
    {
        t2--;
    }
    ll t3 = y / l;
    if ((y - t3 * l) <= 0)
    {
        t3--;
    }
    ll t4 = x / l;
    if ((x - t4 * l) <= 0)
    {
        t4--;
    }
    ll r = t3 + t1 + 1;
    ll t = t4 + t2 + 1;

    ll ans = r * 1ll * t;
    cout << ans << endl;
}

void solve13()
{
    ll n;
    cin >> n;

    // get the lowest bit
    ll ans = 0;
    bool condition = true;

    while (condition)
    {
        int pos = -1;
        bitset<sizeof(ll) * 32> bits(n);
        for (int i = 0; i < 32; i++)
        {
            if (bits[i] == 1)
            {
                pos = i;
                break;
            }
        }
        if (pos == -1)
        {
            break;
        }
        // check if required
        bool chk = false;
        bool found0 = false;
        for (int i = pos + 1; i < 32; i++)
        {
            if (bits[i] == 0)
            {
                found0 = true;
            }
            if (bits[i] == 1 and found0)
            {
                chk = true;
                break;
            }
        }
        if (!chk)
        {
            break;
        }
        n += (1 << pos);
        ans += (1 << pos);
    }

    cout << ans << endl;
}

void solve16()
{
    int n;
    cin >> n;
    for (int i = n; i >= 1; i--)
    {
        cout << i << " ";
    }
    cout << endl;
}

void solve17()
{
    int n;
    cin >> n;
    string s;
    cin >> s;

    bool c1 = true, c2 = true;

    for (int i = 0; i < n; i++)
    {
        if (s[i] == '0')
        {
            if (i + 1 == n)
            {
                c1 = false;
                break;
            }
            if (s[i + 1] == '1')
            {
                c1 = false;
                break;
            }
            else
            {
                i++;
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (s[i] == '1')
        {
            if (i + 1 == n)
            {
                c2 = false;
                break;
            }
            if (s[i + 1] == '0')
            {
                c2 = false;
                break;
            }
            else
            {
                i++;
            }
        }
    }

    if (c1 || c2)
    {
        cout << "Yes\n";
    }
    else
    {
        cout << "No\n";
    }
}

void solve18()
{
    int n;
    cin >> n;

    vector<ll> v(n);
    loop(i, n)
    {
        cin >> v[i];
    }

    ll curr = v[0];
    for (int i = 1; i < n; i++)
    {
        curr = curr + v[i];
    }

    cout << curr << endl;
}

void solve19()
{
    ll n;
    cin >> n;

    ll cnt = 0;
    loop(i, 2 * n)
    {
        int e;
        cin >> e;
        if (e)
        {
            cnt++;
        }
    }
    int a1 = cnt % 2;
    int a2 = -1;
    if (cnt < n)
    {
        a2 = min(n, cnt);
    }
    else
    {
        int off = cnt - n;
        a2 = n - off;
    }
    cout << a1 << " " << a2 << endl;
}

void solve20()
{
    ll n, m;
    cin >> n >> m;

    ll mid = (n + 1) / 2;
    if (mid == m)
    {
        cout << 1 << endl
             << 1 << endl;
    }
    else
    {
        ll right = n - m;
        ll left = m - 1;
        if ((right % 2 != 0) and (left % 2 != 0))
        {
            cout << 3 << endl;
            cout << 1 << " " << m << " " << m + 1 << endl;
        }
        else
        {
            cout << -1 << endl;
        }
    }
}

void solve21()
{
    int n;
    cin >> n;

    unordered_map<ll, ll> mp;

    loop(i, n)
    {
        int e;
        cin >> e;

        if (!mp.count(e))
        {
            cout << -1 << " ";
            mp[e] = i + 1;
        }
        else
        {
            cout << mp[e] << " ";
            mp[e] = i + 1;
        }
    }
}

void solve22()
{
    int n;
    cin >> n;
    string s;
    cin >> s;

    if (n % 2 == 0)
    {
        cout << "No";
        return;
    }
    int mid = n / 2;
    int i = 0;
    for (; i < mid; i++)
    {
        if (s[i] != '1')
        {
            cout << "No";
            return;
        }
    }
    if (s[i] != '/')
    {
        cout << "No";
        return;
    }
    i++;
    for (; i < n; i++)
    {
        if (s[i] != '2')
        {
            cout << "No";
            return;
        }
    }

    cout << "Yes";
}

void solve23()
{
    string s;
    cin >> s;
    int n = s.size();
    if (n % 2 != 0)
    {
        cout << "No";
        return;
    }
    int mid = n / 2;
    int i = 0;
    unordered_map<char, int> mp;
    for (; i < mid; i++)
    {
        mp[s[i]]++;
        char ch1 = s[2 * i - 2], ch2 = s[2 * i - 1];
        if (ch1 != ch2)
        {
            cout << "No";
            return;
        }
    }
    for (; i < n; i++)
    {
        mp[s[i]]++;
    }
    for (auto i : mp)
    {
        if (i.second != 2)
        {
            cout << "No";
            return;
        }
    }
    cout << "Yes";
}

void solve24()
{
    int n;
    cin >> n;
    string s;
    cin >> s;

    vector<int> pref(n, 0), suff(n, 0);

    int ones = 0;
    for (int i = 0; i < n; i++)
    {
        if (s[i] != '1')
        {
            ones = 0;
            if (s[i] == '/')
            {
                pref[i] = ones;
            }
        }
        else
        {
            ones++;
        }
    }

    int zeros = 0;
    for (int i = n - 1; i >= 0; i--)
    {
        if (s[i] != '2')
        {
            zeros = 0;
            if (s[i] == '/')
            {
                suff[i] = zeros;
            }
        }
        else
        {
            zeros++;
        }
    }
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        if (s[i] == '/')
        {
            ans = max(ans, pref[i] + suff[i]);
        }
    }

    cout << ans << endl;
}

void solve50()
{
    int n, d;
    cin >> n >> d;
    string s;
    cin >> s;
    int tot = 0;
    for (auto i : s)
    {
        if (i == '@')
        {
            tot++;
        }
    }
    int ans = tot - d;
    ans = n - ans;
    cout << ans << endl;
}

void solve51()
{
    int n, d;
    cin >> n >> d;
    string s;
    cin >> s;
    int tot = 0;
    for (int i = n - 1; i >= 0 and d > 0; i--)
    {
        if (s[i] == '@')
        {
            s[i] = '.';
            d--;
        }
    }

    cout << s << endl;
}

void solve42()
{
    int n, m;
    cin >> n >> m;
    vector<ll> a(n);
    vector<pll> b(m);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    for (int i = 0; i < m; i++)
    {
        cin >> b[i].first;
        b[i].second = i;
    }

    sort(all(b), [](pll &p1, pll &p2)
         {
             if (p1.first != p2.first)
             {
                 return p1.first > p2.first;
             }
             return p1.second < p2.second; // Tie-breaking by index
         });

    vector<ll> ans(m, -1);
    int k = 0;

    for (int i = 0; i < m and k < n; i++)
    {

        while (k < n && a[k] > b[i].first)
        {
            k++;
        }

        if (k < n)
            ans[b[i].second] = k + 1;
    }

    for (auto i : ans)
    {
        cout << i << endl;
    }
}

void solve42c()
{
    int n, m;
    cin >> n >> m;
    vector<ll> a(n);
    vector<pll> b(m);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    for (int i = 0; i < m; i++)
    {
        cin >> b[i].first;
        b[i].second = i;
    }

    // Sort `b` based on `first` descending, and tie-break with `second`
    sort(all(b), [](pll &p1, pll &p2)
         {
             if (p1.first != p2.first)
             {
                 return p1.first > p2.first;
             }
             return p1.second < p2.second; // Ensure stable sorting
         });

    vector<ll> ans(m, -1);
    int k = 0;

    for (int i = 0; i < m && k < n; i++)
    {
        while (k < n && a[k] > b[i].first)
        {
            k++;
        }
        if (k < n)
        {
            ans[b[i].second] = k + 1; // Store 1-based index
        }
    }

    for (auto i : ans)
    {
        cout << i << endl;
    }
}

signed main()
{
    // factorialCalculation();

    // ll t;
    // cin >> t;
    // while (t--)
    solve42c();
    khalaas
}