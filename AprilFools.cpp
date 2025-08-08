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
const ll MOD_UNCONVENTIONAL = 998244353;

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

struct myComp
{
    bool operator()(const pair<int, pii> &a, const pair<int, pii> &b)
    {
        // Sort by first value in descending order
        if (a.first != b.first)
            return a.first < b.first;
        // If first values are equal, sort by first value of second element in ascending order priority_queue<pair<int, pii>, vector<pair<int, pii>>, myComp> pq;
        return a.second.first > b.second.first;
    }
};

void sol1()
{
    int n;
    cin >> n;
    int ans = 2 * n;
    cout << ans << endl;
}

void sol2()
{
    ll n, k, x;
    cin >> n >> k >> x;

    vector<int> v(n);
    read_vector(v);

    ll sum = accumulate(all(v), 0ll);
    ll req = x / sum;

    ll ans = 0;

    if (req > k)
    {
        cout << ans << endl;
        return;
    }
    else
    {
        x -= (sum * 1ll * req);

        ans = (k - req) * n;
        if (x == 0)
        {
            ans++;
        }

        for (int i = n - 1; i >= 0; i--)
        {
            x -= v[i];
            if (x <= 0)
            {
                break;
            }
            ans--;
        }

        ans = max(0ll, ans);

        cout << ans << endl;
    }
}

void sol3()
{
    int n;
    cin >> n;

    vector<int> v(n + 1);

    fl(i, n)
    {
        cin >> v[i + 1];
    }

    vector<bool> mark(n + 1, 0);
    int ans = 0;

    fl(i, n)
    {
        int e;
        cin >> e;

        int curr = e;
        while (true)
        {
            if (mark[curr])
            {
                break;
            }
            mark[curr] = true;
            curr = v[curr];
            ans++;
        }

        cout << ans << " ";
    }

    cout << endl;
}

void sol4()
{
    int k;
    cin >> k;

    // {a1, a2, a3, a4, ..... ak} -> palindromic

    // if k is odd => always true
    // else =>
    //

    if (k % 2 != 0)
    {
        yes
    }
    else
    {
        no
    }
}

ll modexp(ll base, ll exp, ll mod)
{
    ll result = 1;
    base %= mod;
    while (exp > 0)
    {
        if (exp & 1)
            result = (result * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

void sol5()
{
    ll N;
    cin >> N;

    ll ans;
    if (N % 2 == 1)
    {  
        ans = modexp(2, N - 1, MOD_UNCONVENTIONAL);
    }
    else
    { 
        ans = (3 * modexp(2, N - 2, MOD_UNCONVENTIONAL)) % MOD_UNCONVENTIONAL;
    }

    cout << ans << "\n";
}

int main()
{
    fast_io;

    int t = 1;
    cin >> t;

    while (t--)
    {
        sol5();
    }

    return 0;
}
