
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
const ll INF = 1e18;
const double EPS = 1e-9;
const ll NEG = -1e18;

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

void sol1()
{
    int n, k;
    cin >> n >> k;

    int d = k - 1;

    int ans = 0;

    if (n % 2 == 0)
    {
        ans = (n + d - 1) / d;
    }
    else
    {
        ans = 1 + ((n - k) + d - 1) / d;
    }

    cout << ans << endl;
}

void sol3()
{
    int n, m;
    cin >> n >> m;

    vector<int> freq(n + 1, 0);
    for (int i = 0; i < m; i++)
    {
        int a;
        cin >> a;
        if (a <= n)
            freq[a]++;
    }

    vector<int> count_ge(n + 2, 0);

    for (int i = n; i >= 1; i--)
    {
        count_ge[i] = freq[i] + count_ge[i + 1];
    }

    int ans = 0;

    for (int p = 1; p < n; p++)
    {
        int left = p;
        int right = n - p;

        int lc = count_ge[left];
        int rc = count_ge[right];
        int both = max(p, n - p);

        int bothcnt = count_ge[both];

        ans += (lc * 1ll * rc) - bothcnt;
    }

    cout << ans << "\n";
}

void solve()
{
    int x, y;
    cin >> x >> y;

    if (x == y)
    {
        cout << 0 << endl;
        return;
    }

    const int mx = 55;
    const int mxshift = 55;

    vvi dpprev(mxshift + 1, vector<ll>(mxshift + 1, INF));
    vvi dpcurr(mxshift + 1, vector<ll>(mxshift + 1, INF));

    dpprev[0][0] = 0;

    for (int i = 1; i <= mx; i++)
    {
        ll cost = 1LL << i;
        dpcurr = dpprev;

        fl(a, mxshift + 1)
        {
            fl(b, mxshift + 1)
            {
                if (dpprev[a][b] == INF)
                    continue;

                if (a + i <= mxshift)
                    dpcurr[a + i][b] = min(dpcurr[a + i][b], dpprev[a][b] + cost);

                if (b + i <= mxshift)
                    dpcurr[a][b + i] = min(dpcurr[a][b + i], dpprev[a][b] + cost);
            }
        }
        swap(dpprev, dpcurr);
    }

    ll ans = INF;

    fl(i, mxshift + 1)
    {
        fl(j, mxshift + 1)
        {
            if ((x >> i) == (y >> j))
            {
                ans = min(ans, dpprev[i][j]);
            }
        }
    }

    cout << (ans == INF ? -1 : ans) << "\n";
}

void sol4()
{
    string s;
    cin >> s;
    string s1 = "", s2 = "";

    int n = s.size();

    for (int i = 1; i < n; i++)
    {
        // [0...i-1] [i...n-1]
        int prevrating = 0, newrating = 0;
        if (s[i] == '0')
        {
            continue;
        }
        for (int j = 0; j < i; j++)
        {
            prevrating *= 10;
            prevrating += (s[j] - '0');
        }
        for (int j = i; j < n; j++)
        {
            newrating *= 10;
            newrating += (s[j] - '0');
        }
        if (newrating > prevrating)
        {
            cout << prevrating << " " << newrating << endl;
            return;
        }
    }

    impossible;
}

void sol5()
{
    string s;
    cin >> s;
    int n = s.size();

    int zeros = count(all(s), '0');
    int ones = n - zeros;
    string t = "";
    for (int i = 0; i < n; i++)
    {
        if (s[i] == '0')
        {
            if (ones > 0)
            {
                t += '1';
                ones--;
            }
            else
            {
                break;
            }
        }
        else
        {
            if (zeros > 0)
            {
                t += '0';
                zeros--;
            }
            else
            {
                break;
            }
        }
    }

    cout << n - (int)t.size() << endl;
}

void sol6()
{
    int m;
    cin >> m;
    vector<long long> freq(32, 0);

    for (int i = 0; i < m; i++)
    {
        int type;
        long long x;
        cin >> type >> x;
        if (type == 1)
        {
            freq[x]++;
        }
        else
        {
            long long w = x;
            for (int j = 31; j >= 0; j--)
            {
                long long coin = (1LL << j);
                long long use = min(freq[j], w / coin);
                w -= use * coin;
            }
            cout << (w == 0 ? "YES" : "NO") << "\n";
        }
    }
}

void sol7()
{
    int n;
    cin >> n;

    int alice = 0, bob = 0;
    fl(i, n)
    {
        int e;
        cin >> e;
        if (e == 0)
            alice++;
        else
            bob++;
    }

    if (alice > bob)
    {
        cout << "ALICE\n";
    }
    else if (alice < bob)
    {
        cout << "BOB\n";
    }
    else
    {
        cout << "TIE\n";
    }
}

vector<int> primes;

void sol8()
{
    int n;
    cin >> n;

    int it = *lower_bound(all(primes), n);

    cout << it << endl;
}

void sol9()
{
    int n;
    cin >> n;

    vector<int> v(n);
    read_vector(v);

    int ans = 0;
    if ((n % 2) == 0)
    {
        fl(i, n)
        {
            ans |= v[i];
        }
    }

    else
    {
        vector<int> bits(32, 0);

        fl(i, n)
        {
            fl(j, 32)
            {
                if (((1 << j) & v[i]) != 0)
                {
                    bits[j]++;
                }
            }
        }

        int total = 0;

        fl(j, 32)
        {
            if (bits[j] != 0)
            {
                total |= (1 << j);
            }
        }

        fl(i, n)
        {
            int curr = 0;
            fl(j, 32)
            {
                if (((1 << j) & v[i]) != 0 and bits[j] == 1)
                {
                    curr |= (1 << j);
                }
            }
            ans = max(ans, total ^ curr);
        }
    }

    cout << ans;
}

void sol10()
{
    int n, A, B;
    cin >> n >> A >> B;
    vector<int> v(n);
    read_vector(v);

    vector<int> fA(n + 1, 0), fB(n + 1, 0);

    for (int i = 0; i < n; i++)
    {
        fA[i + 1] = fA[i] + (v[i] < A ? 1 : (v[i] > A ? -1 : 0));
        fB[i + 1] = fB[i] + (v[i] < B ? 1 : (v[i] > B ? -1 : 0));
    }

    int ex1 = (A < B ? 1 : (A > B ? -1 : 0));
    int ex2 = (B < A ? 1 : (B > A ? -1 : 0));

    long long ans = 0;

    for (int p = 0; p <= n; p++)
    {
        for (int q = p + 1; q <= n + 1; q++)
        {
            if (fA[p] > fB[q - 1] + ex1)
            {
                ans++;
            }
        }
    }

    for (int p = 0; p <= n; p++)
    {
        for (int q = p + 1; q <= n + 1; q++)
        {
            if (fA[q - 1] + ex2 > fB[p])
            {
                ans++;
            }
        }
    }

    cout << ans << "\n";
}

void sol11()
{
}

int32_t main()
{
    fast_io;
    // primes = sieve(1e6);

    bool isMulti = false;

    int t = 1;

    if (isMulti)
        cin >> t;

    while (t--)
        sol10();

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