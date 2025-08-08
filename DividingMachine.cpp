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

const int maxn = 1e6 + 5;

// https://www.codechef.com/problems/DIVMAC

vector<ll> v, spf;
vector<struct Node> segTree;

struct Node
{
    ll leastPrime;
    Node() : leastPrime(LLONG_MAX) {}
};

void sieve(int n)
{
    spf.resize(n + 1);
    iota(spf.begin(), spf.end(), 0);

    for (ll i = 2; i * i <= n; i++)
    {
        if (spf[i] == i)
        {
            for (ll j = i * i; j <= n; j += i)
            {
                if (spf[j] == j)
                {
                    spf[j] = i;
                }
            }
        }
    }
}

// Build the segment tree
void build(int idx, int low, int high)
{
    if (low == high)
    {
        segTree[idx].leastPrime = spf[v[low]];
        return;
    }

    int mid = (low + high) / 2;
    build(2 * idx + 1, low, mid);
    build(2 * idx + 2, mid + 1, high);

    segTree[idx].leastPrime = max(segTree[2 * idx + 1].leastPrime, segTree[2 * idx + 2].leastPrime);
}

// Point update
void update(int idx, int low, int high, int l, int r)
{
    if (low > r || high < l)
        return;

    if (low == high)
    {
        v[low] /= spf[v[low]];
        segTree[idx].leastPrime = spf[v[low]];
        return;
    }

    // simple mtlb yhi hai ki maximum agr 1 hi hai -> to ab aage
    // change nhi kr skta no matter what we do

    if (segTree[idx].leastPrime == 1)
        return;

    int mid = (low + high) / 2;
    update(2 * idx + 1, low, mid, l, r);
    update(2 * idx + 2, mid + 1, high, l, r);

    segTree[idx].leastPrime = max(segTree[2 * idx + 1].leastPrime, segTree[2 * idx + 2].leastPrime);
}

// Query function
ll query(int idx, int low, int high, int l, int r)
{
    if (low > r || high < l)
        return 1;

    if (low >= l && high <= r)
        return segTree[idx].leastPrime;

    int mid = (low + high) / 2;

    ll t1 = query((2 * idx) + 1, low, mid, l, r);
    ll t2 = query((2 * idx) + 2, mid + 1, high, l, r);

    return max(t1, t2);
}

int main()
{
    fast_io;

    sieve(maxn);

    int t = 1;
    cin >> t;

    while (t--)
    {
        int n, q;
        cin >> n >> q;

        v.resize(n);

        segTree.resize(4 * n);

        fl(i, n)
        {
            cin >> v[i];
        }

        build(0, 0, n - 1);

        while (q--)
        {
            int type, l, r;
            cin >> type >> l >> r;
            --l, --r;

            if (type == 0)
            {
                update(0, 0, n - 1, l, r);
            }
            else
            {
                cout << query(0, 0, n - 1, l, r) << " ";
            }
        }

        cout << endl;
    }

    return 0;
}
