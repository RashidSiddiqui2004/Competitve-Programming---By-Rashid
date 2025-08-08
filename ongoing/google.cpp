
#include <bits/stdc++.h>
using namespace std;

// Macros
#define fast_io                  \
    ios::sync_with_stdio(false); \
    cin.tie(nullptr);            \
    cout.tie(nullptr);
#define pb push_back
#define mp make_pair
#define all(v) (v).begin(), (v).end()
#define rall(v) (v).rbegin(), (v).rend()
#define fi first
#define se second
#define sz(x) (int)((x).size())
#define endl '\n'
#define fl(i, n) for (int i = 0; i < n; i++)
#define fr(i, n) for (int i = n - 1; i >= 0; i--)

// Typedefs

#define int long long

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pll> vpll;

#define vvi vector<vector<int>>
// Constants
const int MOD = 1e9 + 7;
const ll InF = 1e18;
const double EPS = 1e-9;
const ll nEG = -1e18;

// Debugging
#ifndef OnLInE_JUDGE
#define debug(x) cerr << #x << " = " << (x) << endl;
#else
#define debug(x)
#endif

// Utility Functions
inline ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
inline ll lcm(ll a, ll b) { return a / gcd(a, b) * b; }

inline ll mod_add(ll a, ll b, ll m = MOD)
{
    return (a + b) % m;
}

inline ll mod_sub(ll a, ll b, ll m = MOD)
{
    return (a - b + m) % m;
}

inline ll mod_mul(ll a, ll b, ll m = MOD)
{
    return (a * b) % m;
}

ll mod_pow(ll a, ll b, ll m = MOD)
{
    ll res = 1;
    while (b > 0)
    {
        if (b & 1)
            res = mod_mul(res, a, m);
        a = mod_mul(a, a, m);
        b >>= 1;
    }
    return res;
}

ll exp_fast(ll a, ll b)
{
    ll res = 1;
    while (b > 0)
    {
        if (b & 1)
            res = res * 1ll * a;
        a = 1 * 1ll * a;
        b >>= 1;
    }
    return res;
}

// vector<ll> pow2;

// void mod_pow2_memo()
// {
//     pow2.resize(1e5 + 1);

//     ll curr = 1ll;
//     for (int i = 0; i <= 1e5; i++)
//     {
//         pow2[i] = curr;
//         curr = (curr * 2) % MOD;
//     }
// }

ll mod_inv(ll a, ll m = MOD)
{
    // Modular inverse using Fermat's Little Theorem: a^(m-2) % m
    return mod_pow(a, m - 2, m);
}

vector<ll> factorial, inv_factorial;

void precompute_factorials(int maxn, ll m = MOD)
{
    factorial.resize(maxn + 1);
    inv_factorial.resize(maxn + 1);

    factorial[0] = 1;
    for (int i = 1; i <= maxn; ++i)
    {
        factorial[i] = mod_mul(factorial[i - 1], i, m);
    }

    inv_factorial[maxn] = mod_inv(factorial[maxn], m);

    // (n)^-1 = ((n+1)^-1) * (n+1)
    for (int i = maxn - 1; i >= 0; --i)
    {
        inv_factorial[i] = mod_mul(inv_factorial[i + 1], i + 1, m);
    }
}

ll ncr(ll n, ll r, ll m = MOD)
{
    if (r > n || r < 0)
        return 0;
    return mod_mul(factorial[n], mod_mul(inv_factorial[r], inv_factorial[n - r], m), m);
}

bool is_prime(int n)
{
    if (n < 2)
        return false;
    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
            return false;
    }
    return true;
}

vector<int> primes;
vector<bool> isPrime;

vector<int> sieve(int n)
{
    primes.clear();
    isPrime.assign(n + 1, true);

    for (int i = 2; i <= n; i++)
    {
        if (isPrime[i])
        {
            primes.pb(i);
            for (int j = i * 2; j <= n; j += i)
            {
                isPrime[j] = false;
            }
        }
    }
    return primes;
}

const int maxn = 1e6 + 1;
vector<int> spf;

// Input/Output
template <typename T>
void read_vector(vector<T> &v)
{
    for (auto &x : v)
        cin >> x;
}

template <typename T>
void print_vector(const vector<T> &v)
{
    for (const auto &x : v)
        cout << x << " ";
    cout << endl;
}

#define yes          \
    cout << "Yes\n"; \
    return;

#define no          \
    cout << "No\n"; \
    return;

#define impossible  \
    cout << "-1\n"; \
    return;

void getFactorization(ll n, unordered_map<ll, ll> &mp)
{
    while (n > 0)
    {
        if (spf[n] == n)
        {
            mp[n]++;
            break;
        }
        mp[spf[n]]++;
        n /= spf[n];
    }
    return;
}

const int mod_CC = 998244353;

int ceil_log2(int x)
{
    if (x <= 1)
        return 0;
    return 64 - __builtin_clzll(x - 1);
}

struct BIT
{
    int n;
    vector<int> f;
    BIT(int _n) : n(_n), f(n + 1, 0) {}
    void add(int index, int value)
    {
        while (index <= n)
        {
            f[index] += value;
            index += index & -index;
        }
    }

    int sum(int index)
    {
        int result = 0;
        while (index > 0)
        {
            result += f[index];
            index -= index & -index;
        }
        return result;
    }

    int sum(int l, int r)
    {
        if (l > r)
            return 0;
        return sum(r) - sum(l - 1);
    }
};

struct Node
{
    int key, type, pos, l, idx;
};

ll get_val(int c, int d, const vector<ll> &ps, int n)
{
    if (c < d)
        return ps[d - 1] - ps[c];
    return (ps[2 * n] - ps[c]) + ps[d - 1];
}

class DSU
{
    vector<int> parent, size;

public:
    DSU(int n)
    {
        parent.resize(n);
        size.resize(n, 1);
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int find(int x)
    {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    void unionSets(int x, int y)
    {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX != rootY)
        {
            if (size[rootX] < size[rootY])
                swap(rootX, rootY);
            parent[rootY] = rootX;
            size[rootX] += size[rootY];
        }
    }
};

void usecase()
{
    yes;
    no;
    impossible;
}

void sol1()
{
    int n;
    cin >> n;
    string s1, s2;
    cin >> s1 >> s2;

    int red = 0, blue = 0;

    fl(i, n)
    {
        int a = s1[i] - '0';
        int b = s2[i] - '0';
        if (a > b)
        {
            red++;
        }
        else if (a < b)
        {
            blue++;
        }
    }

    if (red == blue)
    {
        cout << "EQUAL\n";
    }
    else if (red > blue)
    {
        cout << "RED\n";
    }
    else
    {
        cout << "BLUE\n";
    }
}

vector<int> dx = {0, 0, 1, -1};
vector<int> dy = {1, -1, 0, 0};

void sol2()
{
    int n;
    cin >> n;

    set<pair<int, int>> points;

    unordered_map<char, vector<char>> mp;

    mp['E'] = {'N', 'S'};
    mp['w'] = {'N', 'S'};
    mp['N'] = {'E', 'W'};
    mp['S'] = {'E', 'W'};

    unordered_map<char, int> mp2;

    queue<array<int, 4>> q;
}

void sol3()
{
    int n;
    cin >> n;

    vector<int> v(n);
    read_vector(v);

    // 1100.. or 0011... or 11 or 00

    int ones = 0, zeros = 0;

    fl(i, n)
    {
        if (v[i] == 1)
        {
            ones++;
        }
        else
        {
            zeros++;
        }
    }

    int ans = 0;

    vector<int> ret;

    if (zeros >= (n / 2))
    {
        ret = vector<int>(n / 2, 0);
        cout << (int)ret.size() << endl;
        print_vector(ret);
        return;
    }
    vector<int> v1, v2;

    string s1 = "1100", s2 = "0011";
    int i = 0, ptr = 0;

    while (i < n)
    {
        if (v[i] == (s1[ptr] - '0'))
        {
            ptr = (ptr + 1) % 4;
            v1.push_back(v[i]);
        }
        i++;
    }

    ptr = 0;
    while (i < n)
    {
        if (v[i] == (s1[ptr] - '0'))
        {
            ptr = (ptr + 1) % 4;
            v2.push_back(v[i]);
        }
        i++;
    }

    if (v1.size() > v2.size())
    {
        cout << (int)v1.size() << endl;
        print_vector(v1);
    }
    else
    {
        cout << (int)v2.size() << endl;
        print_vector(v2);
    }
}

void sol4()
{
    int n, x;
    cin >> n >> x;

    vector<int> v(n);
    read_vector(v);

    int totalclosed = 0;

    for (auto i : v)
    {
        totalclosed += i;
    }

    int currClosed = 0;

    for (int i = 0; i < min(x, n); i++)
    {
        if (v[i])
        {
            currClosed++;
        }
    }

    if (currClosed == totalclosed)
    {
        cout << "YES\n";
        return;
    }

    for (int i = x; i < n; i++)
    {
        if (v[i - x])
        {
            currClosed--;
        }
        if (v[i])
        {
            currClosed++;
        }
        if (currClosed == totalclosed)
        {
            cout << "YES\n";
            return;
        }
    }
    cout << "NO\n";
}

void sol5()
{
    int n;
    cin >> n;
    cout << 1 << " ";
    for (int i = 3; i <= n; i++)
    {
        cout << i << " ";
    }
    cout << 2 << endl;
}

void sol6()
{
    int n;
    cin >> n;

    vector<int> v(n);
    read_vector(v);

    vector<bool> ispres(n + 1, false);
    vector<bool> temp(n + 1, false);

    ispres[v[0]] = true;
    int uniq = 1, uniqtemp = 0;

    int ans = 1;

    for (int i = 1; i < n; i++)
    {
        if (!temp[v[i]])
        {
            temp[v[i]] = true;
            uniqtemp++;
        }

        if (ispres[v[i]])
        {
            ispres[v[i]] = false;
            uniq--;
        }

        if (uniq == 0)
        {
            ans++;
            uniq = uniqtemp;
            uniqtemp = 0;
            ispres = temp;
            temp = vector<bool>(n + 1, false);
        }
    }

    cout << ans << endl;
}

void sol7()
{
    int n;
    cin >> n;
    vector<long long> v(n);
    for (auto &it : v)
        cin >> it;

    long long diff = v[1] - v[0];
    bool bad = 0;

    for (int i = 2; i < n; i++)
        if (diff != (v[i] - v[i - 1]))
            bad = 1;

    if (bad)
    {
        cout << "NO" << endl;
        return;
    }

    for (int i = 0; i < n; i++)
        v[i] = v[i] + (diff < 0 ? diff * (n - i) : -diff * (i + 1));

    cout << (v[0] >= 0 && v[0] % (n + 1) == 0 ? "YES" : "NO") << endl;
}

void fridgeLockers()
{
    int n, m;
    cin >> n >> m;
    vector<int> v(n);
    read_vector(v);

    if (n == 2 || (m < n))
    {
        cout << -1 << endl;
        return;
    }

    int sum = accumulate(all(v), 0);
    sum = sum * 2ll;

    cout << sum << endl;

    for (int i = 0; i < n; i++)
    {
        if (i == (n - 1))
        {
            cout << i + 1 << " " << 1 << endl;
        }
        else
        {
            cout << i + 1 << " " << i + 2 << endl;
        }
    }
}

bool dfs(int node, int par, vector<vector<int>> &adj, vector<int> &vis)
{
    vis[node] = 1;

    bool ans = false;

    for (auto i : adj[node])
    {
        if (i == par)
        {
            continue;
        }
        if (vis[i])
        {
            return true;
        }
        ans |= dfs(i, node, adj, vis);
    }

    return ans;
}

void easyz()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);

    fl(i, m)
    {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].pb(v);
        adj[v].pb(u);
    }

    if (m != (n - 1))
    {
        cout << "no\n";
        return;
    }

    vector<int> vis(n, 0);

    int ans = dfs(0, -1, adj, vis);

    if (ans)
    {
        cout << "no\n";
        return;
    }

    fl(i, n)
    {
        if (!vis[i])
        {
            cout << "no\n";
            return;
        }
    }

    cout << "yes\n";
}

pair<int, int> bfs(int start, vector<vector<int>> &adj)
{
    int n = adj.size();
    vector<int> dist(n, -1);
    queue<int> q;

    q.push(start);
    dist[start] = 0;

    int farthestNode = start;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (int v : adj[u])
        {
            if (dist[v] == -1)
            {
                dist[v] = dist[u] + 1;
                q.push(v);
                if (dist[v] > dist[farthestNode])
                {
                    farthestNode = v;
                }
            }
        }
    }

    return {farthestNode, dist[farthestNode]};
}

void medium()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);

    fl(i, m)
    {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].pb(v);
        adj[v].pb(u);
    }

    auto t = bfs(0, adj);
    auto node1 = t.first;     // Farthest from node 0
    auto b = bfs(node1, adj); // Farthest from node1

    cout << b.second << "\n";
}

const int MAXN = 200005;
const int LOG = 20;

vector<int> tree[MAXN];
int up[MAXN][LOG]; // up[v][j] is the 2^j-th ancestor of v
int depth[MAXN];

void dfs(int v, int p)
{
    up[v][0] = p;
    for (int j = 1; j < LOG; ++j)
    {
        up[v][j] = up[up[v][j - 1]][j - 1];
    }
    for (int u : tree[v])
    {
        if (u != p)
        {
            depth[u] = depth[v] + 1;
            dfs(u, v);
        }
    }
}

int lca(int u, int v)
{
    if (depth[u] < depth[v])
        swap(u, v);
    for (int j = LOG - 1; j >= 0; --j)
    {
        if (depth[u] - (1 << j) >= depth[v])
            u = up[u][j];
    }
    if (u == v)
        return u;
    for (int j = LOG - 1; j >= 0; --j)
    {
        if (up[u][j] != up[v][j])
        {
            u = up[u][j];
            v = up[v][j];
        }
    }
    return up[u][0];
}

int get_dist(int u, int v)
{
    int anc = lca(u, v);
    return depth[u] + depth[v] - 2 * depth[anc];
}

void hard()
{
    int n;
    cin >> n;
    vector<int> parent(n + 1);

    for (int i = 2; i <= n; ++i)
    {
        cin >> parent[i];
        tree[parent[i]].push_back(i);
    }

    // Initialize LCA structure
    depth[1] = 0;
    dfs(1, 1);

    // Maintain diameter endpoints
    int u = 1, v = 1, diameter = 0;

    for (int i = 2; i <= n; ++i)
    {
        int d1 = get_dist(u, v);
        int d2 = get_dist(u, i);
        int d3 = get_dist(v, i);

        // Update diameter and endpoints
        if (d2 > diameter)
        {
            diameter = d2;
            v = i;
        }
        if (d3 > diameter)
        {
            diameter = d3;
            u = i;
        }

        cout << diameter << " ";
    }
}

int dfsElections(int node, int par, vector<vector<int>> &adj, vector<bool> &damage)
{
    int maxVal = damage[node];
    for (auto i : adj[node])
    {
        if (i == par)
            continue;

        damage[i] = 0;
        maxVal += dfsElections(i, node, adj, damage);
    }
    return maxVal;
}

void elections()
{
    int n;
    cin >> n;

    vector<vector<int>> adj(n);
    vector<bool> damage(n, 0);

    fl(i, n - 1)
    {
        int u, v, t;
        cin >> u >> v >> t;
        --u, --v;
        adj[u].pb(v);
        adj[v].pb(u);
        if (t == 2)
        {
            damage[u] = 1;
            damage[v] = 1;
        }
    }

    cout << dfsElections(0, -1, adj, damage) << endl;
}

void at1()
{
    int n, q;
    cin >> n >> q;
    vector<int> v(n);
    iota(all(v), 1);
    int t = 0;

    fl(i, q)
    {
        int type;
        cin >> type;

        if (type == 1)
        {
            int p, x;
            cin >> p >> x;
            p--;
            v[(p + t) % n] = x;
        }
        else if (type == 2)
        {
            int p;
            cin >> p;
            p--;
            cout << v[(p + t) % n] << endl;
        }
        else
        {
            int k;
            cin >> k;
            t = (t + k) % n;
        }
    }
}

void at2()
{
    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, int>>> adj(n);

    fl(i, m)
    {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        adj[u].pb({v, w}); 
    }

    vector<vector<bool>> vis(n, vector<bool>(1025, 0));

    queue<pair<int, int>> q;
    q.push({0, 0});

    vis[0][0] = 1;

    while (!q.empty())
    {
        auto fr = q.front();
        auto x = fr.first, s = fr.second;
        q.pop();

        for (auto i : adj[x])
        {
            auto newnode = i.first, w = i.second;
            if (vis[newnode][s ^ w])
            {
                continue;
            }
            vis[newnode][s ^ w] = 1;
            q.push({newnode, s ^ w});
        }
    }

    for (int i = 0; i < 1025; i++)
    {
        if (vis[n - 1][i])
        {
            cout << i << endl;
            return;
        }
    }

    cout << -1;
}

void at3()
{

    int n, m;
    cin >> n >> m;
}

int32_t main()
{
    fast_io;

    // precompute_factorials(maxn);
    // sieve(2e5 + 2);

    int t = 1;
    // cin >> t;

    while (t--)
    {
        at2();
    }

    return 0;
}

// mod_pow2_memo();

// spf.resize(maxn + 1, 0ll);

// spf[1] = 1;

// for (ll i = 2; i < maxn; i++)
// {
//     if (spf[i])
//         continue;
//     spf[i] = i;
//     for (ll j = i * i; j < maxn; j += i)
//     {
//         if (!spf[j])
//             spf[j] = i;
//     }
// }

// long long use krna hai
// binary search thoroughly test krna hai
// multi test cases check krna hai
// yes/no me case check krna hai
// early returns me be careful for edge cases
// unordered_map / map me dhyan dena hai