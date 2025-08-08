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

unordered_map<int, int> dp;

void solve1()
{
    int n;
    cin >> n;
    int step = 1, num = 0, dir = 0;

    int move = 0;
    while (abs(num) <= n)
    {
        if (dir == 1)
            num += (2 * step - 1);
        else
        {
            num -= (2 * step - 1);
        }
        step++;
        dir = !dir;
    }
    if (!dir)
    {
        cout << "kosuke\n";
    }
    else
    {
        cout << "Sakurako\n";
    }
}

void solve2()
{
    int n;
    cin >> n;

    vector<vector<ll>> v(n, vector<ll>(n));
    loop(i, n)
    {
        loop(j, n)
        {
            cin >> v[i][j];
        }
    }

    ll ans = 0;

    for (int i = 0; i < n; i++)
    {
        bool chk = false;
        int row = 0;
        ll mini = 0;
        for (int j = 0; j < n - i; j++)
        {
            if (v[row + j][i + j] <= 0)
            {
                chk = true;
                mini = min(mini, v[row + j][i + j]);
            }
        }
        if (chk)
        {
            ans += abs(mini);
        }
    }
    for (int i = 1; i < n; i++)
    {
        bool chk = false;
        int col = 0;
        ll mini = 0;
        for (int j = 0; j < n - i; j++)
        {
            if (v[i + j][col + j] <= 0)
            {
                chk = true;
                mini = min(mini, v[i + j][col + j]);
            }
        }
        if (chk)
        {
            ans += abs(mini);
        }
    }
    // for (int i = 0; i < n; i++)
    // {
    //     bool chk = false;
    //     int ptr = 0;
    //     for (int j = 0; j < elems; j++)
    //     {
    //         if (v[ptr + j][ptr + i + j] <= 0)
    //         {
    //             chk = true;
    //             break;
    //         }
    //         ptr++;
    //     }
    //     elems--;
    //     if (chk)
    //     {
    //         ans++;
    //     }
    // }

    cout << ans << endl;
}

void solve3()
{
    int n;
    cin >> n;

    vector<ll> v(n);

    fl(i, 0, n)
    {
        cin >> v[i];
    }

    for (int i = 0; i < n; i++)
    {
        int t = n - i - 1;
        if (i == t)
        {
            continue;
        }
        int curr = 0;
        if (i != n - 1)
        {
            curr += (v[i] == v[i + 1]);
        }
        if (i != 0)
        {
            curr += (v[i] == v[i - 1]);
        }

        int next = 0;
        if (t != n - 1)
        {
            if (i != (t + 1))
                next += (v[i] == v[t + 1]);
            if (i != n - 1 and (i + 1) != t)
            {
                next += (v[t] == v[i + 1]);
            }
        }
        if (t != 0)
        {
            if (i != (t - 1))
                next += (v[i] == v[t - 1]);
            if (i != 0 and (i - 1) != t)
            {
                next += (v[t] == v[i - 1]);
            }
        }
        if (curr > next)
        {
            ll temp = v[i];
            v[i] = v[t];
            v[t] = temp;
        }
    }

    int ans = 0;

    // for (auto i : v)
    // {
    //     cout << i << " ";
    // }
    // cout << endl;

    for (int i = 0; i < n - 1; i++)
    {
        if (v[i] == v[i + 1])
        {
            ans++;
        }
    }
    cout << ans << endl;
}

void solve5()
{
    int n;
    cin >> n;
    vector<int> v(n);
    fl(i, 0, n)
    {
        cin >> v[i];
    }

    int last = 0;
    ll sum = 0;
    map<ll, ll> mp;
    mp[0] = -1;

    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        sum += v[i];
        if (mp.count(sum))
        {
            sum = 0;
            ans++;
            mp.clear();
            mp[0] = -1;
        }
        mp[sum] = i;
    }
    cout << ans << endl;
}

void solve6()
{
    int n;
    cin >> n;
    vector<int> v(n);
    fl(i, 0, n)
    {
        cin >> v[i];
        v[i]--;
    }
    int ans = 0;
    vector<int> rev(n);
    fl(i, 0, n)
    {
        rev[v[i]] = i;
    }
    fl(i, 0, n)
    {
        if ((i == v[i]) || (v[v[i]] == i))
        {
            continue;
        }
        else
        {
            int loc = rev[i];
            int where = v[i];
            int temp = v[loc];
            v[loc] = v[where];
            v[where] = temp;
            rev[v[loc]] = loc;
            rev[v[where]] = where;
            ans++;
        }
    }
    cout << ans << endl;
}

const long long MOD = 1e9 + 7;

vector<long long> get_factors(long long num)
{
    vector<long long> factors;
    for (long long i = 1; i * i <= num; ++i)
    {
        if (num % i == 0)
        {
            factors.push_back(i);
            if (i != num / i)
                factors.push_back(num / i);
        }
    }
    return factors;
}

void solve7()
{
    ll n, k;
    cin >> n >> k;
    n %= mod, k %= mod;

    ll a = 1 % k, b = 1 % k;
    ll t = 1;

    while (a)
    {
        t++;
        ll temp = a;
        a = b;
        b = (b + temp) % k;
    }

    ll ans = (t * n) % mod;
    cout << ans << endl;
}

signed main()
{
    // int N = 1e5 + 1;
    // vector<long long> fib(10000);
    // vector<ll> ind(N + 1, -1);

    // fib[1] = 1;
    // fib[2] = 1;

    // for (int i = 3; i < 10000; ++i)
    // {
    //     fib[i] = (fib[i - 1] + fib[i - 2]) % MOD;
    // }

    // for (int i = 0; i < 10000; ++i)
    // {
    //     long long fibNum = fib[i];
    //     vector<long long> factors = get_factors(fibNum);

    //     for (long long factor : factors)
    //     {
    //         if (factor <= N and ind[factor] == -1)
    //         {
    //             ind[factor] = (i);
    //         }
    //     }
    // }

    // for (int i = 1; i <= 50; ++i)
    // {
    //     cout << "ind[" << i << "]: ";
    //     cout << ind[i] << " ";
    //     cout << endl;
    // }

    ll t;
    cin >> t;
    while (t--)
    {
        // samapt
    }

    khalaas
}