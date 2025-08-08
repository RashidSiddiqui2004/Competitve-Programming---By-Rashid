
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

vector<int> sieve(int n)
{
    vector<int> primes;
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
    cout << "nO\n";

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

void sol1()
{
    int x, y;
    cin >> x >> y;

    int t = min(x, y);
    int r = max(x - t, y - t);

    string s = "";

    fl(i, t)
    {
        if (x > y)
            s += "0110";
        else
        {
            s += "1001";
        }
    }

    fl(i, r)
    {
        if (x > y)
            s += "01";
        else if (x < y)
        {
            s += "10";
        }
    }

    // cout << s << endl;

    int ans = 0;

    int n = s.size();
    fl(i, n - 1)
    {
        if (s[i] != s[i + 1])
            ans++;
    }

    cout << ans << endl;
}

void sol3()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<int> v(26, 0);
    int ans = 0;

    for (auto i : s)
    {
        if (!v[i - 'A'])
        {
            ans += 2;
            v[i - 'A'] = 1;
        }
        else
        {
            ans++;
        }
    }

    cout << ans << endl;
}

void sol4()
{
    int n;
    cin >> n;
    vector<int> v(n);
    read_vector(v);

    fl(i, n)
    {
        int sz;
        cin >> sz;
        string s;
        cin >> s;

        for (auto k : s)
        {
            if (k == 'D')
            {
                v[i] = v[i] + 1;
            }
            else
            {
                v[i] = v[i] - 1;
            }
            if (v[i] == 10)
            {
                v[i] = 0;
            }
            if (v[i] == -1)
            {
                v[i] = 9;
            }
        }
    }

    print_vector(v);
}

void sol5()
{
    unordered_set<string> st;
    int n;
    cin >> n;
    vector<string> v(n);

    fl(i, n)
    {
        cin >> v[i];
        st.insert(v[i]);
    }

    fl(i, n)
    {
        bool check = false;
        string curr = v[i];
        int m = curr.size();
        string f = "", s = "";

        fl(j, m)
        {
            f += curr[j];
            s = curr.substr(j + 1);

            if (st.count(f) and st.count(s))
            {
                check = true;
                break;
            }
        }
        if (check)
        {
            cout << 1;
        }
        else
        {
            cout << 0;
        }
    }
    cout << endl;
}

void sol6()
{
    int n;
    cin >> n;
    vector<string> grid(n);

    fl(i, n)
    {
        cin >> grid[i];
    }

    int ans = 0;

    fl(i, ((n + 1) / 2))
    {
        fl(j, ((n) / 2))
        {
            set<pll> st;
            st.insert({i, j});
            st.insert({j, n - i - 1});
            st.insert({n - j - 1, i});
            st.insert({n - i - 1, n - j - 1});

            int ones = 0, zeros = 0;

            for (auto vp : st)
            {
                if (grid[vp.first][vp.second] == '1')
                {
                    ones++;
                }
                else
                {
                    zeros++;
                }
            }

            ans += min(ones, zeros);
        }
    }

    cout << ans << endl;
}

int32_t main()
{
    fast_io;
    // primes = sieve(1e6);

    bool isMulti = true;

    int t = 1;

    if (isMulti)
        cin >> t;

    while (t--)
        sol6();

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