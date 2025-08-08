
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
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
// typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pll> vpll;

// Constants
const int MOD = 1e9 + 7;
const ll INF = 1e18;
const double EPS = 1e-9;

// Debugging
#ifndef ONLINE_JUDGE
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

void precompute_factorials(int maxN, ll m = MOD)
{
    factorial.resize(maxN + 1);
    inv_factorial.resize(maxN + 1);

    factorial[0] = 1;
    for (int i = 1; i <= maxN; ++i)
    {
        factorial[i] = mod_mul(factorial[i - 1], i, m);
    }

    inv_factorial[maxN] = mod_inv(factorial[maxN], m);

    // (n)^-1 = ((n+1)^-1) * (n+1)
    for (int i = maxN - 1; i >= 0; --i)
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

#define yes cout << "YES\n";
#define no cout << "NO\n";

void sol1()
{
    int n;
    cin >> n;
    // 01.03.2025.

    vector<int> req(10, 0);
    req[0] = 3;
    req[1] = 1;
    req[2] = 2;
    req[3] = 1;
    req[5] = 1;

    vector<int> v(n);
    read_vector(v);

    vector<int> curr(10, 0);

    fl(i, n)
    {
        curr[v[i]]++;
        bool ch = false;
        fl(j, 10)
        {
            if (req[j] > curr[j])
            {
                ch = true;
            }
        }
        if (ch == false)
        {
            cout << i + 1 << endl;
            return;
        }
    }

    cout << 0 << endl;
}

void sol2()
{
    int n, x;
    cin >> n >> x;
    vector<int> a(n);

    read_vector(a);

    sort(all(a));

    int left = 1, rt = n, ans = 0;

    while (left <= rt)
    {
        int mid = (left + rt) / 2;
        int cnt = 0, mbrs = 0;

        for (int i = n - 1; i >= 0; --i)
        {
            mbrs++;
            if (mbrs * a[i] >= x)
            {
                cnt++;
                mbrs = 0;
            }
        }

        if (cnt >= mid)
        {
            ans = mid;
            left = mid + 1;
        }
        else
        {
            rt = mid - 1;
        }
    }

    cout << ans << "\n";
}

void sol3()
{
    int n;
    cin >> n;

    if (n % 2 == 0)
    {
        cout << -1 << endl;
    }
    else
    {
        for (int i = 1; i <= n; i++)
        {
            int t = (2 * i - 1) % n;
            if (t == 0)
                t = n;
            cout << t << " ";
        }
        cout << "\n";
    }
}

vector<int> generate_primes(int max_val)
{
    vector<bool> is_prime(max_val + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= max_val; i++)
    {
        if (is_prime[i])
        {
            for (int j = i * i; j <= max_val; j += i)
            {
                is_prime[j] = false;
            }
        }
    }
    vector<int> primes;
    for (int i = 2; i <= max_val; i++)
    {
        if (is_prime[i])
            primes.push_back(i);
    }
    return primes;
}

const int MAXN = 1e7 + 1;

vector<bool> is_prime(MAXN, 1);
vector<int> prime_count(MAXN, 0);

void precompute()
{
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i < MAXN; i++)
    {
        if (is_prime[i])
        {
            for (int j = i * i; j < MAXN; j += i)
            {
                is_prime[j] = false;
            }
        }
    }

    for (int i = 1; i < MAXN; i++)
    {
        prime_count[i] = prime_count[i - 1] + (is_prime[i] ? 1 : 0);
    }
}

void sol4()
{
    int n;
    cin >> n;

    ll ans = 0;
    for (int i = 1; i <= n; i++)
    {
        int t = n / i;
        ans += prime_count[t];
    }

    cout << ans << endl;
}

const int MOD2 = 998244353;

bool vert(int c, int x, int d)
{
    int dsq = 1 + (c - x) * (c - x);
    return dsq <= d * d;
}

bool hor(int x, int y, int d)
{
    return abs(x - y) <= d;
}

void sol5()
{
    int n, m, d;
    cin >> n >> m >> d;

    vector<string> grid(n);

    fl(i, n)
    {
        cin >> grid[i];
    }

    vector<vector<int>> holds(n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (grid[i][j] == 'X')
                holds[i].push_back(j);
        }
    }

    if (holds[0].empty() || holds[n - 1].empty())
    {
        cout << 0 << "\n";
        return;
    }

    vector<vector<int>> dp(n);

    for (int r = 0; r < n; r++)
    {
        dp[r].resize(holds[r].size(), 0);
    }

    for (int i = 0; i < holds[n - 1].size(); i++)
    {
        dp[n - 1][i] = 1;
    }

    for (int i = 0; i < holds[n - 1].size(); i++)
    {
        for (int j = 0; j < holds[n - 1].size(); j++)
        {
            if (i == j)
                continue;

            if (hor(holds[n - 1][i], holds[n - 1][j], d))
            {
                dp[n - 1][j] = (dp[n - 1][j] + 1) % MOD2;
            }
        }
    }

    for (int row = n - 1; row >= 1; row--)
    {
        vector<int> dp2(holds[row - 1].size(), 0);

        for (int i = 0; i < holds[row].size(); i++)
        {
            int c = holds[row][i];
            int ways = dp[row][i];

            if (!ways)
                continue;

            for (int j = 0; j < holds[row - 1].size(); j++)
            {
                int x = holds[row - 1][j];
                if (vert(c, x, d))
                {
                    dp2[j] = (dp2[j] + ways) % MOD2;
                }
            }

            for (int j = 0; j < holds[row - 1].size(); j++)
            {
                int x = holds[row - 1][j];
                if (!vert(c, x, d))
                    continue;

                for (int k = 0; k < holds[row - 1].size(); k++)
                {
                    if (j == k)
                        continue;

                    int y = holds[row - 1][k];

                    if (hor(x, y, d))
                    {
                        dp2[k] = (dp2[k] + ways) % MOD2;
                    }
                }
            }
        }

        dp[row - 1] = dp2;
    }

    int ans = 0;
    
    for (int count : dp[0])
        ans = (ans + count) % MOD2;

    cout << ans % MOD2 << "\n";
}

int32_t main()
{
    fast_io;

    bool isMulti = true;

    int t = 1;

    if (isMulti)
        cin >> t;

    while (t--)
        sol5();

    return 0;
}

// long long use krna hai
// binary search thoroughly test krna hai
// multi test cases check krna hai
// yes/no me case check krna hai
// early returns me be careful for edge cases
// unordered_map / map me dhyan dena hai
// when to use map
// when to use unordered_map

// precompute_factorials(maxn);
// spf => smallest prime factor
// modified sieves for faster factorization

// precompute();
// for (int i = 1; i < 20; i++)
// {
//     for (int j = i + 1; j < 20; j++)
//     {
//         int _gcd = gcd(i, j);
//         int t = ((i) * (j)) / (_gcd * _gcd);

//         if (spf[t] == t)
//         {
//             cout << i << " " << j << endl;
//         }
//     }
// }
