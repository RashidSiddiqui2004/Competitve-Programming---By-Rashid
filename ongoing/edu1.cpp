
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
const int MOD2 = 998244353;
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
        curr = (curr * 1ll * 2) % MOD;
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

    int a, b, c;
    cin >> a >> b >> c;

    ll sum = a + b + c;

    ll t = sum / 3;

    if (sum % 3 != 0)
    {
        cout << "NO\n";
    }
    else if (a > t || b > t)
    {
        cout << "NO\n";
    }
    else
    {
        cout << "YES\n";
    }
}

void sol2()
{
    int n;
    cin >> n;

    vector<ll> v(n);
    read_vector(v);

    vector<ll> maxLeft(n, 0);
    ll currMax = LLONG_MIN;

    for (int i = 0; i < n; i++)
    {
        currMax = max(currMax, v[i]);
        maxLeft[i] = currMax;
    }

    vector<ll> suffSum(n, 0ll);
    ll currSum = 0;

    for (int i = n - 1; i >= 0; i--)
    {
        currSum += v[i];
        suffSum[i] = currSum;
    }

    for (int i = n - 1; i >= 0; i--)
    {
        ll sum = suffSum[i];
        sum += maxLeft[i] - v[i];
        cout << sum << " ";
    }

    cout << endl;
}

void sol3()
{
    int n;
    cin >> n;
    string s;
    cin >> s;

    vector<int> alice, bob;

    for (int i = 0; i < n; i++)
    {
        if (s[i] == 'A')
        {
            alice.push_back(i + 1);
        }
        else
        {
            bob.push_back(i + 1);
        }
    }

    // if ownership[i] = 1 => Alice

    for (auto i : alice)
    {
        bool isValid = true;

        if (i == 1)
        {
            for (auto j : bob)
            {
                if (j == n)
                {
                }
                else if (i < j)
                {
                    isValid = false;
                }
            }
        }
        else
        {
            for (auto j : bob)
            {
                if (i < j || (j == 1 and i == n))
                {
                    isValid = false;
                }
            }
        }

        if (isValid)
        {
            cout << "Alice\n";
            return;
        }
    }

    cout << "Bob\n";
}

void sol4()
{
    int n;
    cin >> n;
    string s, t;
    cin >> s >> t;
    int cnt = 0;

    fl(i, n)
    {
        if (s[i] == '0' and t[i] == '1')
        {
            cout << "No\n";
            return;
        }
        else if (s[i] == '1' and t[i] == '0')
        {
            cnt++;
        }
    }

    if ((cnt % 2) == 0)
    {
        cout << "Yes\n";
    }
    else
    {
        cout << "No\n";
    }
}

void sol5()
{
    int n;
    cin >> n;
    vector<int> cnt(n, 0);

    for (int i = 0; i < n; i++)
    {
        int a;
        cin >> a;
        if (a < 0 || a >= n)
        {
            cout << 0 << endl;
            return;
        }
        cnt[a]++;
    }

    ll ans = 1;
    int m = n / 2;

    for (int s = 0; s < m; s++)
    {
        int t = n - 1 - s;
        if (cnt[s] + cnt[t] != 2)
        {
            cout << 0 << endl;
            return;
        }
        ans = ans * 2 % MOD2;
    }

    if (n % 2 == 1)
    {
        int mid = (n - 1) / 2;
        if (cnt[mid] != 1)
        {
            cout << 0 << endl;
            return;
        }
    }

    cout << ans << "\n";
}

void sol6()
{
    ll mex = 1, prevlen = 1, prevInvCnt = 0, lesssum = 0;
    ll m;
    cin >> m;

    fl(i, m)
    {
        int type;
        cin >> type;

        if (type == 1)
        {
            prevInvCnt = (prevInvCnt + prevlen);
            lesssum = (lesssum + prevlen);

            prevlen = (prevlen + 1);
            mex++;
        }
        else
        {
            prevInvCnt = (prevInvCnt * 2 + lesssum);
            lesssum = lesssum * 1ll * 4;
            prevlen = prevlen * 1ll * 2;
        }

        cout << prevInvCnt << " ";
    }

    cout << "\n";
}

void sol7()
{

    fl(n, 10)
    {
        vector<int> perm;

        fl(i, n)
        {
            perm.push_back(i);
        }

        set<int> uniqVals;

        do
        {
            int sum = 0;

            fl(i, n)
            {
                sum += abs(i - perm[i]);
            }

            uniqVals.insert(sum);
        } while (next_permutation(all(perm)));

        cout << n << " -> " << (int)uniqVals.size() << endl;

        for (auto i : uniqVals)
        {
            cout << i << " ";
        }

        cout << endl;
    }
}

void sol8()
{
    string s;
    cin >> s;

    vector<int> freq(26, 0);

    int n = s.size();
    fl(i, n)
    {
        freq[s[i] - 'a']++;
    }

    fl(i, 26)
    {
        if (freq[i] == 0)
        {
            char ch = 'a' + i;
            cout << ch << endl;
            return;
        }
    }
}

vector<vector<int>> adf;
vector<bool> vis;

void dfs(int u)
{
    vis[u] = true;
    for (int v : adj[u])
    {
        if (!vis[v])
        {
            dfs(v);
        }
    }
}

void sol9()
{
    int n, m;
    cin >> n >> m;

    adj.assign(n + 1, {});
    vis.assign(n + 1, false);
    vector<int> degree(n + 1, 0);

    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;

        adj[a].push_back(b);
        adj[b].push_back(a);
        degree[a]++;
        degree[b]++;
    }

    if (m != n)
    {
        cout << "No";
        return;
    }

    for (int i = 1; i <= n; i++)
    {
        if (degree[i] != 2)
        {
            cout << "No\n";
            return;
        }
    }

    dfs(1);
    for (int i = 1; i <= n; i++)
    {
        if (!vis[i])
        {
            cout << "No\n";
            return;
        }
    }

    cout << "Yes\n";
}

void rash1()
{
    int n, m;
    cin >> n >> m;

    vector<ll> cost(n);

    for (int i = 0; i < n; i++)
    {
        cin >> cost[i];
    }

    vector<vector<int>> v(n);

    for (int i = 0; i < m; i++)
    {
        int k;
        cin >> k;
        for (int j = 0; j < k; j++)
        {
            int a;
            cin >> a;
            v[a - 1].push_back(i);
        }
    }

    ll ans = LLONG_MAX;
    int max_m = pow(3, n);

    for (int mask = 0; mask < max_m; mask++)
    {
        vector<int> seen(m, 0);
        ll total = 0;
        int temp = mask;

        for (int i = 0; i < n; i++)
        {
            int cnt = temp % 3;
            temp /= 3;
            total += cnt * 1ll * cost[i];
            for (int animal : v[i])
            {
                seen[animal] += cnt;
            }
        }

        bool ok = true;
        for (int cnt : seen)
        {
            if (cnt < 2)
            {
                ok = false;
                break;
            }
        }

        if (ok)
        {
            ans = min(ans, total);
        }
    }

    if (ans == LLONG_MAX)
        cout << -1 << endl;
    else
        cout << ans << endl;
}

// simple bfs on the segments
// https://atcoder.jp/contests/abc404/tasks/abc404_e
int bfs(int n, vector<int> c,
        int src, int dest)
{
    if (src == dest)
        return 0;

    vector<int> dist(n, -1);
    dist[src] = 0;

    set<int> unvis;
    for (int i = dest; i < src; i++)
        unvis.insert(i);

    deque<int> q;
    q.push_back(src);

    while (!q.empty())
    {
        int x = q.front();
        q.pop_front();
        int d = dist[x] + 1;

        int lval = max(dest, x - c[x]);

        auto it = unvis.lower_bound(lval);
        vector<int> st;

        for (; it != unvis.end() && *it < x; ++it)
        {
            int y = *it;
            dist[y] = d;
            q.push_back(y);
            st.push_back(y);
            if (y == dest)
            {
                return d;
            }
        }

        for (int y : st)
            unvis.erase(y);
    }
    return -1;
}

void rash2()
{
    int n;
    cin >> n;

    vector<int> c(n), beans(n);

    c[0] = 0;
    beans[0] = 0;

    fl(i, n - 1)
    {
        cin >> c[i + 1];
    }

    fl(i, n - 1)
    {
        cin >> beans[i + 1];
    }

    vector<int> stops;
    stops.push_back(0);

    for (int i = 0; i < n; i++)
    {
        if (beans[i] != 0)
            stops.push_back(i);
    }

    reverse(stops.begin(), stops.end());

    ll total = 0;

    int curr = stops[0], nxt;

    for (int i = 1; i < stops.size(); i++)
    {
        nxt = stops[i];
        int d = bfs(n, c, curr, nxt);
        if (d == -1)
        {
            cout << -1;
            return;
        }
        total += d;
        curr = nxt;
    }

    cout << total;
}

void rash3()
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
        rash2();

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