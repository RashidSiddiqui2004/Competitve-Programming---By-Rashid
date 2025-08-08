

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

    string s;
    cin >> s;

    vector<int> freq(26, 0);

    for (auto i : s)
    {
        freq[i - 'a']++;
    }

    for (int i = 1; i < n - 1; i++)
    {
        if (freq[s[i] - 'a'] > 1)
        {
            cout << "Yes\n";
            return;
        }
    }

    cout << "No\n";
}

void sol4()
{
    int n, m;
    cin >> n >> m;

    vector<vector<int>> grid(n, vector<int>(m));

    fl(i, n)
    {
        read_vector(grid[i]);
    }

    int highest = 0;

    fl(i, n)
    {
        fl(j, m)
        {
            highest = max(highest, grid[i][j]);
        }
    }

    // check if all occurences of highest are forming plus sign

    vector<int> x(n, 0), y(m, 0);
    int total = 0;

    fl(i, n)
    {
        fl(j, m)
        {
            if (grid[i][j] == highest)
            {
                x[i]++;
                y[j]++;
                total++;
            }
        }
    }

    fl(i, n)
    {
        fl(j, m)
        {
            bool extra = grid[i][j] == highest;

            if ((x[i] + y[j]) == (extra + total))
            {
                cout << highest - 1 << endl;
                return;
            }
        }
    }

    cout << highest << endl;
}

void sol5()
{
    int n;
    cin >> n;
    vector<int> a(n), b(n);

    read_vector(a);
    read_vector(b);

    vector<pair<int, int>> ops;

    for (int pass = 0; pass < n; pass++)
    {
        for (int j = 0; j + 1 < n; j++)
        {
            if (a[j] > a[j + 1])
            {
                swap(a[j], a[j + 1]);
                ops.emplace_back(1, j + 1);
            }
        }
    }
    for (int pass = 0; pass < n; pass++)
    {
        for (int j = 0; j + 1 < n; j++)
        {
            if (b[j] > b[j + 1])
            {
                swap(b[j], b[j + 1]);
                ops.emplace_back(2, j + 1);
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        if (a[i] > b[i])
        {
            swap(a[i], b[i]);
            ops.emplace_back(3, i + 1);
        }
    }

    cout << ops.size() << "\n";
    for (auto x : ops)
    {
        cout << x.first << " " << x.second << "\n";
    }
}

void sol6()
{
    int n, q;
    cin >> n >> q;

    string colors(n, 'W');
    int grps = 0;

    fl(i, q)
    {
        int t;
        cin >> t;
        if (t == 1)
        {
            if (colors[t] == 'B')
            {
                colors[t] = 'W';
                if (!(colors[t + 1] == 'B'))
                {
                    grps--;
                }
            }
            else
            {
                colors[t] = 'B';
                if (!(colors[t + 1] == 'B'))
                {
                    grps++;
                }
            }
        }
        else if (t == n)
        {
            if (colors[t] == 'B')
            {
                colors[t] = 'W';
                if (!(colors[t - 1] == 'B'))
                {
                    grps--;
                }
            }
            else
            {
                colors[t] = 'B';
                if (!(colors[t - 1] == 'B'))
                {
                    grps++;
                }
            }
        }
        else
        {
            if (colors[t] == 'B')
            {
                colors[t] = 'W';
                if ((colors[t - 1] == 'B' and colors[t + 1] == 'B'))
                {
                    grps++;
                }
                else if (!(colors[t - 1] == 'B' || colors[t + 1] == 'B'))
                {
                    grps--;
                }
            }
            else
            {
                colors[t] = 'B';
                if ((colors[t - 1] == 'B' and colors[t + 1] == 'B'))
                {
                    grps--;
                }
                else if (!(colors[t - 1] == 'B' || colors[t + 1] == 'B'))
                {
                    grps++;
                }
            }
        }

        cout << grps << endl;
    }
}

void sol7()
{
    int n, q;
    cin >> n >> q;

    string server = "";
    unordered_map<int, string> mp1;

    fl(i, q)
    {
        int type, p;
        cin >> type;
        cin >> p;

        if (type == 1)
        {
            if (server != "")
            {
                mp1[p] = server;
            }
        }
        else if (type == 2)
        {
            string s;
            cin >> s;

            if (mp1.count(p))
            {
                mp1[p] += s;
            }
            else
            {
                mp1[p] = s;
            }
        }
        else
        {
            if (mp1.count(p))
                server = mp1[p];
            else
            {
                server = "";
            }
        }
    }

    cout << server << endl;
}

void sol8()
{
    int a, x, y;
    cin >> a >> x >> y;

    if (x > y)
    {
        swap(x, y);
    }
    if (a == x || a == y)
    {
        cout << "NO\n";
    }
    else if ((a < x) || (y < a))
    {
        cout << "YES\n";
    }
    else
    {
        cout << "NO\n";
    }
}

void sol9()
{
    int n;
    cin >> n;
    int maxn = 1e4;

    vector<int> v(n);
    read_vector(v);

    fl(i, n - 1)
    {
        if (abs(v[i] - v[i + 1]) <= 1)
        {
            cout << 0 << endl;
            return;
        }
    }

    int ans = maxn;

    fl(i, n)
    {
        int curr = v[i];
        for (int j = i - 1; j >= 0; j--)
        {
            if (abs(curr - v[j]) <= 1)
            {
                ans = min(ans, i - j);
                break;
            }
        }
        for (int j = i + 1; j < n; j++)
        {
            if (abs(curr - v[j]) <= 1)
            {
                ans = min(ans, j - i);
                break;
            }
        }
        if (ans == 1)
        {
            break;
        }
    }

    if (ans == maxn)
    {
        ans = -1;
    }
    else
    {
        ans--;
    }
    cout << ans << endl;
}

int32_t main()
{
    fast_io;

    // precompute_factorials(maxn);
    // sieve(2e5 + 2);

    int t = 1;
    cin >> t;

    while (t--)
    {
        sol9();
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