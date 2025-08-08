
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
#define fl(i, n) for (int i = 0; i < n; i++)
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
    fl(i, m)
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
    fl(i, m)
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

// oh hello!

enum DPType
{
    arraydp1d,
    arraydp2d,
    arraydp3d,
    mapdp1d,
    mapdp2d,
    mapdp3d
};

template <typename T>
T createDp(DPType type)
{
    switch (type)
    {
    case arraydp1d:
        return std::vector<int>(); // 1D array DP
    case arraydp2d:
        return std::vector<std::vector<int>>(); // 2D array DP
    case arraydp3d:
        return std::vector<std::vector<std::vector<int>>>(); // 3D array DP
    case mapdp1d:
        return std::unordered_map<int, int>(); // 1D map DP
    case mapdp2d:
        return std::unordered_map<pair<int, int>, int>(); // 2D map DP
    case mapdp3d:
        return std::unordered_map<pair<int, pair<int, int>>, int>(); // 1D map of 3D
    default:
        throw std::invalid_argument("Invalid DPType");
    }
}

void solve1()
{
    int n;
    cin >> n;

    vector<int> v(n);
    fl(i, n)
    {
        cin >> v[i];
    }

    int last = n - 1, jumps = 0;
    for (int i = n - 2; i >= 0; i--)
    {
        int currjump = v[i];
        if (currjump >= (last - i))
        {
            last = i;
            jumps++;
        }
    }

    if (last == 0)
    {
        cout << jumps << "\n";
    }
    else
    {
        cout << -1 << "\n";
    }
}

void solve2()
{
    ll n;
    cin >> n;
    ll sum;
    ll terms = n - 2;
    if (n == 1)
    {
        cout << 1 << "\n";
    }
    else if (n == 2)
    {
        cout << 1 << "\n";
    }
    else
    {
        sum = 1;
        sum += (n - 1) * 1ll * (n - 2);
        cout << sum << "\n";
    }
}

void solve3()
{
    int n;
    cin >> n;

    vector<int> v(n);

    fl(i, n)
    {
        cin >> v[i];
    }

    sort(all(v));

    for (int i = 0; i <= n; i++)
    {
        int lim = i;
        bool isposssible = true;

        for (auto j : v)
        {
            if (j > i)
            {
                if (lim > 0)
                {
                    --lim;
                }
                else
                {
                    isposssible = false;
                    break;
                }
            }
        }
        if (isposssible and lim == 0)
        {
            cout << i << endl;
            return;
        }
    }

    cout << -1 << endl;
}

void solve4()
{
    int n;
    cin >> n;
    vector<ll> v(n);

    fl(i, n)
    {
        cin >> v[i];
    }

    bool same = true;

    for (int i = 1; i < n; i++)
    {
        if (v[i] != v[0])
        {
            same = false;
            break;
        }
    }

    if (same)
    {
        cout << 0 << endl;
        return;
    }

    int p1 = 0, p2 = n - 1;
    unordered_set<ll> diffs;

    while (p1 < p2)
    {
        diffs.insert(abs(v[p2] - v[p1]));
        p1++;
        p2--;
    }

    ll gcd = 0;
    for (auto i : diffs)
    {
        gcd = __gcd(gcd, i);
    }

    cout << gcd << endl;
}

void solve5()
{
    ll n, m;
    cin >> n >> m;
    if (n % m == 0)
    {
        cout << "NO\n";
    }
    else
    {
        cout << "YES\n";
    }
}

void solve6()
{
    int n;
    cin >> n;

    vector<ll> v(n);

    fl(i, n)
    {
        cin >> v[i];
    }

    vector<ll> pref(n);
    vector<ll> suff(n);

    pref[0] = v[0];
    for (int i = 1; i < n; i++)
    {
        pref[i] = max(pref[i - 1], v[i] + i);
    }

    suff[n - 1] = v[n - 1] - (n - 1);
    for (int i = n - 2; i >= 0; i--)
    {
        suff[i] = max(suff[i + 1], v[i] - i);
    }

    ll ans = -1;
    for (int i = 1; i < n - 1; i++)
    {
        ans = max(ans, v[i] + pref[i - 1] + suff[i + 1]);
    }

    cout << ans << endl;
}

void solve7()
{
    int n;
    cin >> n;
    string s;
    cin >> s;

    int qeuryCount = 0;
    for (auto i : s)
    {
        if (i == 'Q')
        {
            qeuryCount++;
        }
        else
        {
            if (qeuryCount > 0)
            {
                qeuryCount--;
            }
        }
    }

    if (qeuryCount == 0)
    {
        cout << "Yes\n";
    }
    else
    {
        cout << "No\n";
    }
}

int helper(int n, int m, vector<vector<int>> &tree_pref, int r)
{
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            int k;
            for (k = 0; (k + i) < n and (k + j) < m; k++)
            {
                int from_row = i + 1, to_row = k + i + 1;
                int from_col = j + 1, to_col = k + j + 1;
                int sum = tree_pref[to_row][to_col] - tree_pref[from_row - 1][to_col] -
                          tree_pref[to_row][from_col - 1] +
                          tree_pref[from_row - 1][from_col - 1];

                if (sum > r)
                {
                    break;
                }
            }

            ans += k * k;
            int col = j + k;
            if (col < m)
            {
                for (int row = i; row < n; row++)
                {
                    int from_row = i + 1, to_row = row + 1;
                    int from_col = j + 1, to_col = col + 1;
                    int sum = tree_pref[to_row][to_col] - tree_pref[from_row - 1][to_col] -
                              tree_pref[to_row][from_col - 1] +
                              tree_pref[from_row - 1][from_col - 1];

                    if (sum <= r)
                    {
                        ans++;
                    }
                    else
                    {
                        break;
                    }
                }
            }

            int row = i + k;
            if (row < n)
            {
                for (col = i; col < m; col++)
                {
                    int from_row = i + 1, to_row = row + 1;
                    int from_col = j + 1, to_col = col + 1;
                    int sum = tree_pref[to_row][to_col] - tree_pref[from_row - 1][to_col] -
                              tree_pref[to_row][from_col - 1] +
                              tree_pref[from_row - 1][from_col - 1];

                    if (sum <= r)
                    {
                        ans++;
                    }
                    else
                    {
                        break;
                    }
                }
            }
        }
    }

    return ans;
}

int cntGood(int n, int m, vector<vector<int>> &grid, int l, int r)
{

    int ans = 0;

    vector<vector<int>> tree_pref(n + 1, vector<int>(m + 1, 0));

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            tree_pref[i][j] = grid[i - 1][j - 1] + tree_pref[i - 1][j] +
                              tree_pref[i][j - 1] - tree_pref[i - 1][j - 1];
        }
    }

    ans = helper(n, m, tree_pref, r) - helper(n, m, tree_pref, l - 1);

    return ans;
}

void solve9()
{
    int n, k;
    cin >> n >> k;
    vector<int> v(n);

    fl(i, n)
    {
        cin >> v[i];
    }

    fl(i, n)
    {
        bool chk = true;
        fl(j, n)
        {
            if (i == j)
                continue;
            if (abs(v[i] - v[j]) % k == 0)
            {
                chk = false;
                break;
            }
        }
        if (chk)
        {
            cout << "YES\n";
            cout << i + 1 << " \n";
            return;
        }
    }
    cout << "NO\n";
}

void solve10()
{
    int n;
    cin >> n;
    vector<ll> v(n);
    unordered_set<ll> st;
    fl(i, n)
    {
        cin >> v[i];
        st.insert(v[i]);
    }

    sort(all(v));
    reverse(all(v));

    ll count = 0;
    for (auto i : v)
    {
        if (i > 0)
            count++;
        else
            count--;
        cout << count << " ";
    }

    cout << endl;

    count = 0;

    vector<int> v1, v2;
    for (auto i : v)
    {
        if (i < 0)
            break;
        if (st.count(-i))
        {
            v1.push_back(i);
        }
        else
        {
            v2.push_back(i);
        }
    }

    for (auto i : v1)
    {
        count++;
        cout << count << " ";
        count--;
        cout << count << " ";
    }
    for (auto i : v2)
    {
        count++;
        cout << count << " ";
    }

    cout << endl;
}

void solve11()
{
    int n;
    cin >> n;

    int known = 0, unknown = 0;
    int need = 0;

    for (int i = 0; i < n; i++)
    {
        int e;
        cin >> e;
        if (e == 1)
        {
            unknown++;
        }
        else
        {
            known += unknown;
            unknown = 0;
        }
        need = max(need, unknown + ((known > 0) ? (known / 2) + 1 : 0));
    }

    cout << need << endl;
}

void solve12()
{
    int n, m;
    cin >> n >> m;

    vector<vector<ll>> grid(n, vector<ll>(m));

    int elem = 1;
    fl(i, n)
    {
        fl(j, m)
        {
            grid[i][j] = elem++;
        }
    }

    fl(i, n)
    {
        fl(j, m)
        {
            // check the 4*4 submatrix
            int lastcol = j + 3, lastrow = i + 3;
            if (lastcol < m and lastrow < n)
            {
                int x1 = 0, x2 = 0, x3 = 0, x4 = 0;
                for (int p = 0; p < 2; p++)
                {
                    for (int k = 0; k < 2; k++)
                    {
                        x1 ^= grid[i + p][j + k];
                    }
                }
                for (int p = 2; p < 4; p++)
                {
                    for (int k = 2; k < 4; k++)
                    {
                        x2 ^= grid[i + p][j + k];
                    }
                }
                for (int p = 0; p < 2; p++)
                {
                    for (int k = 2; k < 4; k++)
                    {
                        x3 ^= grid[i + p][j + k];
                    }
                }
                for (int p = 2; p < 4; p++)
                {
                    for (int k = 0; k < 2; k++)
                    {
                        x4 ^= grid[i + p][j + k];
                    }
                }
                if (x1 != x2)
                {
                    x2 ^= grid[i + 3][j + 3];
                    grid[i + 3][j + 3] = x1 ^ x2;
                }
                if (x3 != x4)
                {
                    x3 ^= grid[i + 1][j + 3];
                    grid[i + 1][j + 3] = x3 ^ x4;
                }
            }
            else
            {
                break;
            }
        }
    }

    fl(i, n)
    {
        fl(j, m)
        {
            // check the 4*4 submatrix
            int lastcol = j + 3, lastrow = i + 3;
            if (lastcol < m and lastrow < n)
            {
                int x1 = 0, x2 = 0, x3 = 0, x4 = 0;
                for (int p = 0; p < 2; p++)
                {
                    for (int k = 0; k < 2; k++)
                    {
                        x1 ^= grid[i + p][j + k];
                    }
                }
                for (int p = 2; p < 4; p++)
                {
                    for (int k = 2; k < 4; k++)
                    {
                        x2 ^= grid[i + p][j + k];
                    }
                }
                for (int p = 0; p < 2; p++)
                {
                    for (int k = 2; k < 4; k++)
                    {
                        x3 ^= grid[i + p][j + k];
                    }
                }
                for (int p = 2; p < 4; p++)
                {
                    for (int k = 0; k < 2; k++)
                    {
                        x4 ^= grid[i + p][j + k];
                    }
                }
                cout << x1 << " " << x2 << " " << x3 << " " << x4 << endl;
            }
        }
    }

    int ans = n * m;
    cout << ans << endl;

    // for (auto i : grid)
    // {
    //     for (auto j : i)
    //     {
    //         cout << j << " ";
    //     }
    //     cout << endl;
    // }
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    ll t;
    cin >> t;

    // int x1 = 1 ^ 2 ^ 6 ^ 7;
    // int x2 = 13 ^ 14 ^ 18 ^ 19;
    // cout << x1 << " " << x2 << endl;

    while (t--)
    {
        solve12();
    }
    // Example usage
    // DPType type = arraydp2d;

    // // Create 2D array DP
    // auto dp = createDp<std::vector<std::vector<int>>>(type);

    // // Add data
    // dp.resize(3, std::vector<int>(3, 0)); // Resize and initialize to 0
    // dp[0][0] = 1;
    // dp[1][1] = 2;

    // // Display
    // for (const auto &row : dp)
    // {
    //     for (int val : row)
    //     {
    //         std::cout << val << " ";
    //     }
    //     std::cout << "\n";
    // }
    khalaas
}