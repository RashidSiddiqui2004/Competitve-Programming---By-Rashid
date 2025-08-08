
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

vector<ll> pow2;

void mod_pow2_memo()
{
    pow2.resize(1e5 + 1);

    ll curr = 1ll;
    for (int i = 0; i <= 1e5; i++)
    {
        pow2[i] = curr;
        curr = (curr * 2) % MOD;
    }
}

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
    cout << "YES\n";

#define no \
    cout << "NO\n";

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

void solve1()
{
    string s;
    cin >> s;

    unordered_map<char, vector<int>> pos;

    string t = "CHEF";
    int n = s.size();

    fl(i, n)
    {
        if (t.find(s[i]) != string::npos)
        {
            pos[s[i]].push_back(i);
        }
    }

    for (auto ch : t)
    {
        if (!pos.count(ch))
        {
            cout << 0 << endl;
            return;
        }
    }

    int ans = 0;

    auto C = pos['C'], H = pos['H'], E = pos['E'], F = pos['F'];

    for (auto i : C)
    {
        auto lbh = lower_bound(H.begin(), H.end(), i);

        if (lbh == H.end())
        {
            break;
        }

        auto lbe = lower_bound(E.begin(), E.end(), *lbh);

        if (lbe == E.end())
        {
            continue;
        }

        auto lbf = lower_bound(F.begin(), F.end(), *lbe);

        if (lbf == F.end())
        {
            continue;
        }

        ans++;
    }

    cout << ans << endl;
}

// https://www.codechef.com/START185B

void s1()
{
    int n, k;
    cin >> n >> k;

    if ((n - 1) > k)
    {
        cout << -1 << endl;
        return;
    }

    int x = k - (n - 2);

    vector<ll> a = {x, 2 * x};

    for (int p : primes)
    {
        if (a.size() == n)
            break;
        if ((2 * x) % p != 0)
        {
            a.push_back(p);
        }
    }

    for (int i = 2 * 1e6 + 1; a.size() < n && i <= 1e9; ++i)
    {
        bool check = true;
        for (int d = 2; d * d <= i; ++d)
        {
            if (i % d == 0)
            {
                check = false;
                break;
            }
        }
        if (check && (2 * x) % i != 0)
        {
            a.push_back(i);
        }
    }

    if (a.size() != n)
    {
        cout << -1 << endl;
        return;
    }

    print_vector(a);
    return;
}

void s2()
{
    int n, h;
    cin >> n >> h;

    vector<int> s(n), d(n);

    fl(i, n)
    {
        cin >> s[i] >> d[i];
    }

    int j = 0;

    for (int i = 1; i < n; i++)
    {
        if (d[i] * s[j] > d[j] * s[i])
        {
            j = i;
        }
    }

    ll df = d[j], sj = s[j];

    ll full = (h + df - 1) / df;

    ll res = full * sj;

    fl(i, n)
    {
        ll l = d[i], si = s[i];

        ll rem = h - l;

        if (rem < 0)
            rem = 0;

        ll remj = (rem + df - 1) / df;

        ll time2 = remj * 1ll * sj + si;

        res = min(res, time2);
    }

    cout << res << "\n";
}

struct SegmentTree
{
    int n;
    vector<ll> t;

    SegmentTree(const vector<ll> &v)
    {
        n = v.size();
        t.assign(2 * n, LLONG_MIN);

        for (int i = 0; i < n; i++)
            t[n + i] = v[i];

        for (int i = n - 1; i > 0; --i)
            t[i] = max(t[i << 1], t[i << 1 | 1]);
    }

    void update(int pos, ll val)
    {
        pos += n;
        t[pos] = val;
        for (pos >>= 1; pos; pos >>= 1)
            t[pos] = max(t[pos << 1], t[pos << 1 | 1]);
    }

    ll query(int l, int r)
    {
        ll res = LLONG_MIN;
        for (l += n, r += n; l <= r; l >>= 1, r >>= 1)
        {
            if (l & 1)
                res = max(res, t[l++]);
            if (!(r & 1))
                res = max(res, t[r--]);
        }
        return res;
    }
};

void s3()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    int m = 2 * n;
    vector<ll> a(m);

    read_vector(a);

    vector<ll> dp(n + 1, LLONG_MIN);
    dp[0] = 0;

    SegmentTree seg(dp);

    for (int i = 0; i < 2 * n; ++i)
    {
        int maxK = min(n, (i + 1) / 2);
        if (maxK >= 1)
        {
            ll bestPrev = seg.query(maxK - 1, maxK - 1);
            ll cand = bestPrev + a[i];
            if (cand > dp[maxK])
            {
                dp[maxK] = cand;
                seg.update(maxK, cand);
            }
        }
    }

    cout << dp[n] << "\n";
}

int32_t main()
{
    fast_io;

    int t = 1;
    cin >> t;

    // sieve(2 * 1e6);

    while (t--)
        s3();

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