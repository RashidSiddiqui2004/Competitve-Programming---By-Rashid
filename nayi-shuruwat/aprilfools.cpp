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
int mod_mul(ll a, ll b, ll m = mod)
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
    ll ans = log2(n) / log2(k);
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

unsigned long long power(unsigned long long x,
                         int y)
{
    unsigned long long res = 1;

    while (y > 0)
    {
        if (y & 1)
            res = (res * x);

        y = y >> 1;
        x = (x * x);
    }
    return res;
}

ll modInverse(ll A)
{
    return (powerOptimum(A, M - 2));
}

unsigned long long factdp[200000 + 1];

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
    for (int i = 1; i <= 200000; i++)
        factdp[i] = (factdp[i - 1] * i) % mod;
}

// @usage => ./. see div3_2l.cpp for usage

class DSU
{
private:
    std::vector<int> parent, rank;

public:
    DSU(int n)
    {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++)
        {
            parent[i] = i; // Each node is its own parent initially
        }
    }

    // Path compression optimization for the find operation
    int find(int x)
    {
        if (parent[x] != x)
        {
            parent[x] = find(parent[x]); // Path compression
        }
        return parent[x];
    }

    // Union by rank optimization for the union operation
    void unionSets(int x, int y)
    {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX != rootY)
        {
            // Union by rank
            if (rank[rootX] < rank[rootY])
            {
                parent[rootX] = rootY;
            }
            else if (rank[rootX] > rank[rootY])
            {
                parent[rootY] = rootX;
            }
            else
            {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }
};

void solve1()
{
    int n;
    cin >> n;
    vector<ll> v(n);

    loop(i, n)
    {
        cin >> v[i];
    }

    bool chk = true;
    for (int i = 1; i < n; i++)
    {
        if ((abs(v[i] - v[i - 1]) == 5) || (abs(v[i] - v[i - 1]) == 7))
        {
            continue;
        }
        else
        {
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
}

void sol2()
{
    int n, k;
    cin >> n >> k;

    unordered_map<ll, ll> cost;
    loop(i, k)
    {
        ll b, c;
        cin >> b >> c;
        cost[b] += c;
    }

    vector<ll> t;
    for (auto i : cost)
    {
        t.push_back(i.second);
    }
    sort(all(t), greater<>());
    n = min(n, (int)t.size());
    ll ans = accumulate(t.begin(), t.begin() + n, 0);

    cout << ans << endl;
}

void sol3()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> grid(n, vector<int>(m));

    loop(i, n)
    {
        string s;
        cin >> s;
        loop(j, m)
        {
            grid[i][j] = (s[j] - '0');
        }
    }

    ll ans = 0;
    int top = 0, bottom = n - 1, left = 0, right = m - 1;

    while (top <= bottom && left <= right)
    {
        vector<int> layer;

        for (int j = left; j <= right; ++j)
        {
            layer.push_back(grid[top][j]);
        }
        ++top;

        for (int i = top; i <= bottom; ++i)
        {
            layer.push_back(grid[i][right]);
        }
        --right;

        if (top <= bottom)
        {
            for (int j = right; j >= left; --j)
            {
                layer.push_back(grid[bottom][j]);
            }
            --bottom;
        }

        if (left <= right)
        {
            for (int i = bottom; i >= top; --i)
            {
                layer.push_back(grid[i][left]);
            }
            ++left;
        }
        int lz = layer.size();
        for (int i = 0; i < 3; i++)
        {
            layer.push_back(layer[i]);
        }

        for (int i = 0; i < lz; i++)
        {
            string s = "";
            for (int j = 0; j <= 3; j++)
                s += ('0' + layer[i + j]);
            // cout << s << " ";
            if (s == "1543")
            {
                ans++;
            }
        }
    }
    cout << ans << endl;
}

void sol5()
{
    string s;
    cin >> s;

    if (s.find("it") != string::npos)
    {
        cout << "YES\n";
    }
    else
    {
        cout << "NO\n";
    }
}

void sol6()
{
    ll n;
    cin >> n;

    int fr[101] = {0};

    loop(i, n)
    {
        ll e;
        cin >> e;
        fr[e]++;
    }

    ll maxifreq = *max_element(fr, fr + 101);

    ll ans = n - maxifreq;

    cout << ans << endl;
}

void solv7()
{
    ll n;
    cin >> n;

    vector<ll> ans(n);

    if (n % 2 == 0)
    {
        cout << -1 << endl;
        return;
    }
    else
    {
        int num = 1;
        ans[0] = n;
        for (int i = 1; i < n; i += 2)
        {
            ans[i] = num;
            num++;
        }

        for (int i = n - 1; i > 0; i -= 2)
        {
            ans[i] = num;
            num++;
        }
    }

    for (auto i : ans)
    {
        cout << i << " ";
    }
    cout << endl;
}

int query(int u, int v)
{
    cout << "? " << u + 1 << ' ' << v + 1 << '\n';
    int x;
    cin >> x;
    return x - 1;
}

void sol8()
{
    int n;
    cin >> n;

    vector<array<int, 2>> e;
    vector<int> c(n);
    iota(c.begin(), c.end(), 0);

    auto addEdge = [&](int u, int v)
    {
        e.push_back({u, v});
        vector<int> cand;
        for (int i = 0; i < n; i++)
            if (c[i] == c[v])
                cand.emplace_back(i);
        for (int i : cand)
            c[i] = c[u];
    };

    for (int i = 0; i < n - 1; i++)
    {
        int u = 0, v = 0;
        while (c[v] == c[u])
            v++;
        int x;
        while ((x = query(u, v)) != u)
        {
            if (c[u] == c[x])
                u = x;
            else
                v = x;
        }
        addEdge(u, v);
    }

    cout << "!";
    for (auto edge : e)
        cout << ' ' << edge[0] + 1 << ' ' << edge[1] + 1;
    cout << '\n';
}

signed main()
{
    factorialCalculation();
    ll t;
    cin >> t;

    while (t--)
    {
        sol8();
    }

    khalaas
}