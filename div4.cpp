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
#define ha           \
    cout << "YES\n"; \
    return;
#define na          \
    cout << "NO\n"; \
    return;

// Typedefs
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pii> vpii;
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
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
ll lcm(ll a, ll b) { return a / gcd(a, b) * b; }

ll mod_add(ll a, ll b, ll m = MOD)
{
    return (a + b) % m;
}

ll mod_sub(ll a, ll b, ll m = MOD)
{
    return (a - b + m) % m;
}

ll mod_mul(ll a, ll b, ll m = MOD)
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

template <typename T>
void input_vector(vector<T> &v)
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

void rash1()
{
    ll x, y, ans = -1;
    cin >> x >> y;

    if ((y % x) == 0)
    {
        y /= x;
        for (int k = 1; k < 60; k++)
        {
            ll val = y + k;
            if (val % 2)
                continue;
            int cnt = __builtin_popcountll(val);
            if (cnt == k)
            {
                int tmp = 0;
                for (int i = 1; i <= 60; i++)
                {
                    if (val & (1LL << i))
                        tmp += i;
                }
                tmp += k - 1;
                ans = tmp;
                break;
            }
        }
    }

    cout << ans << endl;
}

void rash2()
{
    int n;
    cin >> n;

    vector<ll> v(n);
    input_vector(v);

    ll maxVal = 0;

    for (int shift = 0; shift < n; shift++)
    {
        ll x = 0;
        unordered_set<ll> uniq;

        // Compute XOR sequence with a new start index
        for (int i = 0; i < n; i++)
        {
            x ^= v[(shift + i) % n]; // Simulate the rotation without modifying the array
            uniq.insert(x);
        }

        maxVal = max(maxVal, (ll)uniq.size());
    }

    cout << maxVal << endl;
}

int main()
{
    fast_io;

    int t = 1;
    cin >> t;

    while (t--)
    {
        rash2();
    }

    return 0;
}
