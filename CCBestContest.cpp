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

// https://codeforces.com/contest/1611

void solve()
{
    int n;
    cin >> n;

    vector<int> v(n);

    priority_queue<pair<int, pii>, vector<pair<int, pii>>, myComp> pq;

    pq.push({n, {0, n - 1}});

    int step = 1;

    while (step <= n)
    {
        auto top = pq.top();
        pq.pop();

        int l = top.second.first, r = top.second.second;

        int sz = top.first;

        if ((sz % 2) == 0)
        {
            int gap = (l + r - 1) / 2;
            // cout<<gap<<" ";
            v[gap] = step;

            if (l <= (gap - 1))
                pq.push({gap - l, {l, gap - 1}});

            if (r >= (gap + 1))
                pq.push({r - gap, {gap + 1, r}});
        }
        else
        {
            int gap = (l + r) / 2;
            v[gap] = step;
            // cout<<gap<<" ";

            if (l <= (gap - 1))
                pq.push({gap - l, {l, gap - 1}});

            if (r >= (gap + 1))
                pq.push({r - gap, {gap + 1, r}});
        }

        step++;
    }

    print_vector(v);
}

void solve2()
{
    int n;
    cin >> n;
    vector<int> v(n);
    read_vector(v);
    vector<int> ans = v;

    reverse(all(v));

    if (v[0] != n and v[n - 1] != n)
    {
        cout << -1 << endl;
        return;
    }

    print_vector(ans);
}

void sol3()
{
    int n;
    cin >> n;
    vector<int> b(n + 1), p(n + 1);

    fl(i, n)
    {
        cin >> b[i + 1];
    }

    fl(i, n)
    {
        cin >> p[i + 1];
    }

    int root = -1;

    for (int i = 1; i <= n; i++)
    {
        if (b[i] == i)
        {
            root = i;
            break;
        }
    }

    if (p[1] != root)
    {
        cout << -1 << endl;
        return;
    }

    vector<bool> nodes(n + 1, 0);

    nodes[root] = 1;

    vector<ll> ans(n + 1);

    ll currPrice = 0;
    ans[root] = currPrice++;

    vector<ll> costs(n + 1);
    costs[root] = ans[root];

    ll latestVal = 0;

    for (int i = 2; i <= n; i++)
    {
        int par = b[p[i]];

        if (!nodes[par])
        {
            cout << -1 << endl;
            return;
        }
        else
        {
            nodes[p[i]] = 1;

            ll req = latestVal + 1;

            ans[p[i]] = req - costs[par];

            costs[p[i]] = costs[par] + ans[p[i]];

            latestVal = costs[p[i]];
        }
    }

    fl(i, n)
    {
        cout << ans[i + 1] << " ";
    }

    cout << endl;
}

void sol4()
{
    ll l, r;
    cin >> l >> r;

    int ans = 0;

    if (l % 2 == 0)
    {
        l++;
    }

    int i = l;

    while (i <= r)
    {
        if ((i % 2) != 0 and (i + 2) <= r)
        {
            ans++;
            i += 4;
        }
        else
        {
            break;
        }
    }

    cout << ans << endl;
}

// trick q
// https://codeforces.com/contest/2007/problem/B
void sol5()
{
    ll n, m;
    cin >> n >> m;

    vector<ll> v(n);
    for (auto &x : v)
        cin >> x;

    ll maxi = *max_element(all(v));

    for (ll i = 0; i < m; i++)
    {
        char c;
        ll l, r;
        cin >> c >> l >> r;

        if (maxi >= l and maxi <= r)
        {
            if (c == '+')
                maxi++;
            else
                maxi--;
        }

        cout << maxi << " ";
    }

    cout << endl;
}

void dora()
{
    ll n, a, b;
    cin >> n >> a >> b;

    vector<ll> v(n);
    read_vector(v);

    ll maxi = *max_element(all(v));
    ll mini = LLONG_MAX;

    for (auto &i : v)
    {
        // choice 1 => a then b

        ll diff = maxi - i;

        ll m = -1;
        {
            ll t = diff / a;
            ll newelem = i + (t * 1ll * a);

            t = (maxi - newelem) / b;

            newelem += (t * 1ll * b);
            m = max(m, newelem);
        }

        // choice 2 => b then a

        {
            ll t = diff / b;
            ll newelem = i + (t * 1ll * b);

            t = (maxi - newelem) / a;
            newelem += (t * 1ll * a);
            m = max(m, newelem);
        }

        // cout<<m<<" ";

        mini = min(mini, m);
    }

    ll range = abs(maxi - mini);

    cout << range << endl;
}

void sol6()
{ 
}

int main()
{
    fast_io;

    int maxN = 1e6;

    int t = 1;
    cin >> t;
    while (t--)
    {
        dora();
    }
    return 0;
}
