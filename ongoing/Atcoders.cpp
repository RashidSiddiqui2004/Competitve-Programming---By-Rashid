
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

vector<int> sieve(int n)
{
    primes.clear();

    vector<bool> is_prime(n + 1, true);
    for (int i = 2; i <= n; i++)
    {
        if (is_prime[i])
        {
            primes.pb(i);
            for (int j = i * 2; j <= n; j += i)
            {
                is_prime[j] = false;
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

#define yes \
    cout << "Yes\n";

#define no \
    cout << "No\n";

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

void sol1()
{
    int r, x;
    cin >> r >> x;

    if (x == 1)
    {
        if (r >= 1600 and r <= 2999)
        {
            cout << "Yes";
            return;
        }
        else
        {
            cout << "No";
        }
    }
    else
    {
        if (r >= 1200 and r <= 2399)
        {
            cout << "Yes";
            return;
        }
        else
        {
            cout << "No";
        }
    }
}

void sol3()
{
    int n;
    cin >> n;

    vector<int> v(n);
    read_vector(v);

    int total = 0;
    int sq = 0;

    for (int i : v)
    {
        total += i;
        sq += 1LL * i * i;
    }

    int ans = (total * total - sq) / 2;

    cout << ans;
}

vector<int> dx = {0, 0, 1, -1};
vector<int> dy = {1, -1, 0, 0};
vector<char> arrs = {'>', '<', 'v', '^'};

void sol4()
{
    int n, m;
    cin >> n >> m;

    vector<string> grid(n);

    fl(i, n)
    {
        cin >> grid[i];
    }

    map<pair<int, int>, int> mp;
    queue<pair<int, pair<int, int>>> q;
    int id = 0;

    vector<vector<int>> mintime(n, vector<int>(m, INT_MAX));

    fl(i, n)
    {
        fl(j, m)
        {
            if (grid[i][j] == 'E')
            {
                q.push({i, {j, 0}});
                mp[{i, j}] = id++;
                mintime[i][j] = 0;
            }
        }
    }

    while (!q.empty())
    {
        auto front = q.front();
        q.pop();
        int x = front.first;
        int y = front.second.first;
        int ctime = front.second.second;

        for (int k = 0; k < 4; k++)
        {
            int newx = x + dx[k], newy = y + dy[k];
            if (newx >= 0 && newx < n &&
                newy >= 0 && newy < m &&
                grid[newx][newy] == '.' &&
                mintime[newx][newy] > ctime + 1)
            {
                q.push({newx, {newy, ctime + 1}});
                mintime[newx][newy] = ctime + 1;
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (grid[i][j] == '.')
            {
                for (int k = 0; k < 4; k++)
                {
                    int ni = i + dx[k], nj = j + dy[k];
                    if (ni >= 0 && ni < n &&
                        nj >= 0 && nj < m &&
                        mintime[ni][nj] == mintime[i][j] - 1)
                    {
                        grid[i][j] = arrs[k];
                        break;
                    }
                }
            }
        }
    }

    for (int i = 0; i < n; i++)
        cout << grid[i] << "\n";
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

void sol5()
{
    int n, m, q;
    cin >> n >> m;

    vector<pair<int, int>> seg(m);
    vector<int> mark(2 * n + 1, 0);

    for (int i = 0; i < m; ++i)
    {
        int a, b;
        cin >> a >> b;
        if (a > b)
            swap(a, b);
        seg[i] = {a, b};
        mark[a] = mark[b] = 1;
    }

    vector<ll> ps(2 * n + 1, 0);
    for (int i = 1; i <= 2 * n; ++i)
        ps[i] = ps[i - 1] + mark[i];

    cin >> q;
    vector<int> c(q), d(q);
    vector<Node> ev;
    for (int i = 0; i < m; ++i)
    {

        auto a = seg[i].first, b = seg[i].second;
        ev.push_back({b, 0, a, 0, 0});
    }

    for (int i = 0; i < q; ++i)
    {
        cin >> c[i] >> d[i];
        if (c[i] < d[i])
        {
            int l = c[i], r = d[i];
            if (l + 1 <= r - 1)
                ev.push_back({r - 1, 1, 0, l, i});
        }
        else
        {
            if (c[i] + 1 <= 2 * n)
                ev.push_back({2 * n, 1, 0, c[i], i});
            if (1 <= d[i] - 1)
                ev.push_back({d[i] - 1, 1, 0, 0, i});
        }
    }

    sort(ev.begin(), ev.end(), [](const Node &a, const Node &b)
         { return a.key == b.key ? a.type < b.type : a.key < b.key; });

    BIT bit(2 * n);
    vector<ll> bcnt(q, 0);

    for (auto &e : ev)
    {
        if (e.type == 0)
        {
            bit.add(e.pos, 1);
        }
        else
        {
            int cnt = bit.sum(e.l + 1, e.key);
            bcnt[e.idx] += cnt;
        }
    }

    for (int i = 0; i < q; ++i)
    {
        ll e = get_val(c[i], d[i], ps, n);
        cout << e - 2LL * bcnt[i] << endl;
    }
}

void sol6()
{
    int n;
    cin >> n;

    vector<vector<int>> grid(n);

    int curr = 1;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            grid[i][j] = curr++;
        }

        for (int j = i + 1; j >= 0; j--)
        {

            grid[i][j] = curr++;
        }
    }

    fl(i, n)
    {
        fl(j, n)
                cout
            << grid[i][j] << "\n";
    }
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

void sol7()
{
    int n;
    cin >> n;
    vector<int> a(n);
    read_vector(a);

    vector<int> l(n + 1), r(n + 1);
    l[0] = 0;
    r[n - 1] = 0;

    for (int i = 1; i < n; i++)
    {
        int prev = INT_MAX, next = INT_MAX;
        if (i != 0)
        {
            prev = a[i] - a[i - 1];
        }
        if (i != (n - 1))
        {
            next = a[i + 1] - a[i];
        }
        if (prev < next)
        {
            l[i] = l[i - 1] + abs(a[i] - a[i - 1]);
        }
        else if (prev > next)
        {
            l[i] = l[i - 1] + 1;
        }
    }

    for (int i = n - 2; i >= 0; i--)
    {
        int prev = INT_MAX, next = INT_MAX;
        if (i != 0)
        {
            prev = a[i] - a[i - 1];
        }
        if (i != (n - 1))
        {
            next = a[i + 1] - a[i];
        }
        if (prev < next)
        {
            r[i] = r[i + 1] + abs(a[i] - a[i + 1]);
        }
        else if (prev > next)
        {
            r[i] = r[i + 1] + 1;
        }
    }

    int m;
    cin >> m;

    fl(i, m)
    {
        int u, v;
        cin >> u >> v;
        --u, --v;

        int cost;

        if (u < v)
        {
            cost = l[v] - (u == 0 ? 0 : l[u - 1]);
        }
        else
        {
            cost = r[u] - (v == (n - 1) ? 0 : r[v + 1]);
        }

        cout << cost << endl;
    }
}

void sol8()
{
    int n;
    cin >> n;

    vector<int> v(n + 1, 0), prefsum(n + 1, 0);

    fl(i, n)
    {
        cin >> v[i + 1];
    }

    for (int i = 1; i <= n; i++)
    {
        prefsum[i] = prefsum[i - 1] + v[i];
    }

    int l = 1, r = n, mid, ans;

    while (l <= r)
    {
        mid = (l + r) / 2;

        int queriedWt;

        int len = (r - mid + 1);
        cout << "? " << len << " ";

        for (int i = mid; i <= r; i++)
        {
            cout << i << " ";
        }

        cout << endl
             << flush;

        cin >> queriedWt;

        int calcWt = prefsum[r] - prefsum[mid - 1];

        if (calcWt == queriedWt)
        {
            r = mid - 1;
        }
        else
        {
            ans = mid;
            l = mid + 1;
        }
    }

    cout << "! " << ans << endl
         << flush;
}

struct MyNode
{
    int x, y;
    int currStep;
    vector<vector<bool>> vis;

    MyNode(int _x, int _y, int _currStep) : x(_x), y(_y), currStep(_currStep)
    {
        vis.assign(11, vector<bool>(11, false));
    }
};

void sol9()
{
    int n, m, k;
    cin >> n >> m >> k;

    vector<string> grid(n);

    fl(i, n)
    {
        cin >> grid[i];
    }

    queue<MyNode> q;

    fl(i, n)
    {
        fl(j, m)
        {
            if (grid[i][j] == '.')
            {
                MyNode mynode = MyNode(i, j, 0);
                mynode.vis[i][j] = 1;
                q.emplace(mynode);
            }
        }
    }

    int ans = 0ll;

    while (!q.empty())
    {
        auto fr = q.front();
        q.pop();

        int t = fr.currStep, x = fr.x, y = fr.y;

        if (t == k)
        {
            ans++;
        }
        else
        {
            fl(i, 4)
            {
                int newx = x + dx[i], newy = y + dy[i];
                if (newx >= 0 and newx < n and newy >= 0 and newy < m and grid[newx][newy] == '.')
                {
                    if (!fr.vis[newx][newy])
                    {
                        MyNode next(newx, newy, t + 1);
                        next.vis = fr.vis;
                        next.vis[newx][newy] = 1;
                        q.emplace(next);
                    }
                }
            }
        }
    }

    cout << ans << endl;
}

void sol10()
{
    int n;
    cin >> n;

    vector<int> degree(n, 0);
    vector<vector<int>> adj(n);

    fl(i, n - 1)
    {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        degree[u]++;
        degree[v]++;
    }

    vector<vector<int>> components;
    vector<int> vis(n, 0);
    queue<int> q;

    fl(i, n)
    {
        if (!vis[i] and degree[i] == 3)
        {

            int start = i, ending = i;
            q.push(i);
            vector<int> comp;

            while (!q.empty())
            {
                int fr = q.front();
                q.pop();
                comp.push_back(fr);
                vis[fr] = 1;
                for (auto i : adj[fr])
                {
                    if (degree[i] == 3)
                    {
                        vis[i] = 1;
                        q.push(i);
                    }
                }
            }
            components.push_back(comp);
        }
    }

    int ans = 0;

    for (auto &v : components)
    {
        int d2 = 0;
        for (auto i : v)
        {
            for (auto t : adj[i])
            {
                if (degree[t] == 2)
                {
                    d2++;
                }
            }
        }

        ans += (d2 * 1ll * (d2 - 1)) / 2;
    }

    cout << ans << endl;
}

void usecase()
{
    yes;
    no;
    impossible;
}

void r1()
{
    int a, b, c, d;
    cin >> a >> b >> c >> d;

    if (c < a || (c == a && d < b))
    {
        yes
    }
    else
    {
        no
    }
}

void r4()
{
    int h, w, n;
    cin >> h >> w >> n;

    vvi rowt(h + 1), colt(w + 1);
    vector<int> rowcnt(h + 1, 0), colcnt(w + 1, 0);
    vector<char> rowrmv(h + 1, 0), colrmv(w + 1, 0);

    int x, y;

    fl(i, n)
    {
        cin >> x >> y;
        rowt[x].push_back(y);
        colt[y].push_back(x);
    }

    for (int x = 1; x <= h; x++)
        rowcnt[x] = rowt[x].size();
    for (int y = 1; y <= w; y++)
        colcnt[y] = colt[y].size();

    int q;
    cin >> q;

    fl(i, q)
    {
        int type;
        cin >> type;
        if (type == 1)
        {
            int x;
            cin >> x;
            if (rowrmv[x])
            {
                cout << 0 << endl;
            }
            else
            {
                int ans = rowcnt[x];
                cout << ans << endl;
                rowrmv[x] = 1;
                for (int y : rowt[x])
                {
                    if (!colrmv[y])
                    {
                        colcnt[y]--;
                    }
                }
                rowcnt[x] = 0;
            }
        }
        else
        {
            int y;
            cin >> y;
            if (colrmv[y])
            {
                cout << 0 << endl;
            }
            else
            {
                int ans = colcnt[y];
                cout << ans << endl;
                colrmv[y] = 1;
                for (int x : colt[y])
                {
                    if (!rowrmv[x])
                    {
                        rowcnt[x]--;
                    }
                }
                colcnt[y] = 0;
            }
        }
    }
}

static const int MAXB = 60;
static const int M = 998244353;
long long C[MAXB + 1][MAXB + 1], sumOne[MAXB + 1][MAXB + 1], pow2[MAXB + 1];

// precompute
void init()
{
    pow2[0] = 1;
    for (int i = 1; i <= MAXB; i++)
        pow2[i] = pow2[i - 1] * 2 % M;
    for (int n = 0; n <= MAXB; n++)
    {
        C[n][0] = C[n][n] = 1;
        for (int k = 1; k < n; k++)
            C[n][k] = (C[n - 1][k - 1] + C[n - 1][k]) % M;
    }
    // sumOne[0][0]=0 by default
    for (int n = 1; n <= MAXB; n++)
    {
        for (int k = 0; k <= n; k++)
        {
            long long a = sumOne[n - 1][k]; // MSB=0
            long long b = (k > 0
                               ? (sumOne[n - 1][k - 1] + C[n - 1][k - 1] * pow2[n - 1]) % M
                               : 0); // MSB=1
            sumOne[n][k] = (a + b) % M;
        }
    }
}

void r5()
{
    ull N, K;
    cin >> N >> K;
    vector<int> bits;
    for (int i = 0; i < MAXB; i++)
    {
        bits.push_back((N >> i) & 1);
    }
    int L = MAXB;
    while (L > 0 && bits[L - 1] == 0)
        L--;
    long long ans = 0, ones = 0;
    for (int i = L - 1; i >= 0; i--)
    {
        if (bits[i] == 1)
        {
            int rem = K - ones;
            if (0 <= rem && rem <= i)
            {
                ans = (ans + sumOne[i][rem]) % M;
            }
            ones++;
            if (ones > K)
                break;
        }
    }
    if (ones == K)
    {
        ans = (ans + (N % M)) % M;
    }
    cout << ans << endl;
}

int32_t main()
{
    fast_io;

    int t = 1;
    cin >> t;

    init();

    while (t--)
    {
        r5();
    }

    return 0;
}

// precompute_factorials(maxn);

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
// when to use map
// when to use unordered_map