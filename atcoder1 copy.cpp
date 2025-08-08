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
const int MOD = 1e9;
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
    int s;
    cin >> s;
    if (s >= 200 and s <= 299)
    {
        cout << "Success";
    }
    else
    {
        cout << "Failure";
    }
}

void sol2()
{
    int n;
    cin >> n;
    string s;
    int ans = 0;
    bool login = false;
    while (n--)
    {
        cin >> s;
        if (s == "login")
        {
            login = true;
        }
        else if (s == "logout")
        {
            login = false;
        }
        else if (s == "public")
        {
        }
        else
        {
            if (!login)
            {
                ans++;
            }
        }
    }

    cout << ans << endl;
}

void sol3()
{
    int n, k;
    cin >> n >> k;

    if (n < k)
    {
        cout << 1 << endl;
        return;
    }
    else if (n == k)
    {
        cout << n << endl;
        return;
    }

    vector<ll> A(n + 1, 0);

    for (int i = 0; i < min(n + 1, k); i++)
    {
        A[i] = 1;
    }

    ll prevsum = 0ll;

    for (int i = 0; i < k; i++)
    {
        prevsum = (prevsum + A[i]) % MOD;
    }

    for (int i = k; i <= n; i++)
    {
        A[i] = prevsum % MOD;
        prevsum = (prevsum + A[i] - A[i - k] + MOD) % MOD;
    }

    cout << A[n] << "\n";
}

ll n1, n2;

void dfs(int node, int par, vector<vector<int>> &adj, vector<ll> &dist)
{
    for (int n : adj[node])
    {
        if (n == par)
            continue;
        dist[n] = dist[node] + 1ll;
        dfs(n, node, adj, dist);
    }
}

vector<ll> solver(vector<vector<int>> &adj, int n)
{
    vector<ll> d1(n, 0);
    dfs(0, -1, adj, d1);

    int fth = max_element(all(d1)) - d1.begin();

    vector<ll> d2(n, 0);
    dfs(fth, -1, adj, d2);

    int other = max_element(all(d2)) - d2.begin();

    vector<ll> d3(n, 0);
    dfs(other, -1, adj, d3);

    vector<ll> depth(n);
    for (int i = 0; i < n; ++i)
    {
        depth[i] = max(d2[i], d3[i]);
    }

    return depth;
}

void sol5()
{
    cin >> n1;
    vector<vector<int>> adj1(n1);

    fl(i, n1 - 1)
    {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj1[u].push_back(v);
        adj1[v].push_back(u);
    }

    cin >> n2;
    vector<vector<int>> adj2(n2);

    fl(i, n2 - 1)
    {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj2[u].push_back(v);
        adj2[v].push_back(u);
    }

    vector<ll> depth1 = solver(adj1, n1);
    vector<ll> depth2 = solver(adj2, n2);

    sort(all(depth2));

    ll d1 = *max_element(all(depth1));
    ll d2 = *max_element(all(depth2));

    ll ans = 0ll;
    ll prec = accumulate(all(depth2), 0LL);

    if (d2 < d1)
    {
        swap(d1, d2);
    }

    fl(i, n1)
    {
        ll temp = depth1[i] + 1;

        // First partition for depth2: nodes in depth2 < temp
        ll p1 = upper_bound(all(depth2), temp - 1) - depth2.begin();

        // First partition for depth1: nodes in depth1 < temp
        ll p3 = upper_bound(all(depth1), temp - 1) - depth1.begin();

        // Second partition for depth2: nodes in depth2 >= temp
        ll p2 = n2;

        // Second partition for depth1: nodes in depth1 >= temp
        ll p4 = n1;

        // Now apply the logic
        ans += (p1 * d1);        // For nodes in depth2 < temp
        ans += ((p2 - p1) * d2); // For nodes in depth2 >= temp
        ans += 1LL * (n2 - p2) * (depth1[i] + 1) + prec;

        ans += (p3 * d1);        // For nodes in depth1 < temp (same logic applied to depth1)
        ans += ((p4 - p3) * d2); // For nodes in depth1 >= temp (same logic applied to depth1)
    }

    cout << ans << endl;
}

int main()
{
    fast_io;
    int t = 1;

    while (t--)
    {
        sol5();
    }

    return 0;
}