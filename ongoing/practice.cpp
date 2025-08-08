

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

// vector<ll> pow2;

// void mod_pow2_memo()
// {
//     pow2.resize(1e5 + 1);

//     ll curr = 1ll;
//     for (int i = 0; i <= 1e5; i++)
//     {
//         pow2[i] = curr;
//         curr = (curr * 2) % MOD;
//     }
// }

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
vector<bool> isPrime;

vector<int> sieve(int n)
{
    primes.clear();
    isPrime.assign(n + 1, true);

    for (int i = 2; i <= n; i++)
    {
        if (isPrime[i])
        {
            primes.pb(i);
            for (int j = i * 2; j <= n; j += i)
            {
                isPrime[j] = false;
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

#define yes          \
    cout << "Yes\n"; \
    return;

#define no          \
    cout << "No\n"; \
    return;

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

int ceil_log2(int x)
{
    if (x <= 1)
        return 0;
    return 64 - __builtin_clzll(x - 1);
}

struct BIT
{
    int n;
    vector<int> f;
    BIT(int _n) : n(_n), f(n + 1, 0) {}
    void add(int index, int value)
    {
        while (index <= n)
        {
            f[index] += value;
            index += index & -index;
        }
    }

    int sum(int index)
    {
        int result = 0;
        while (index > 0)
        {
            result += f[index];
            index -= index & -index;
        }
        return result;
    }

    int sum(int l, int r)
    {
        if (l > r)
            return 0;
        return sum(r) - sum(l - 1);
    }
};

struct Node
{
    int key, type, pos, l, idx;
};

ll get_val(int c, int d, const vector<ll> &ps, int n)
{
    if (c < d)
        return ps[d - 1] - ps[c];
    return (ps[2 * n] - ps[c]) + ps[d - 1];
}

class DSU
{
    vector<int> parent, size;

public:
    DSU(int n)
    {
        parent.resize(n);
        size.resize(n, 1);
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int find(int x)
    {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    void unionSets(int x, int y)
    {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX != rootY)
        {
            if (size[rootX] < size[rootY])
                swap(rootX, rootY);
            parent[rootY] = rootX;
            size[rootX] += size[rootY];
        }
    }
};

void usecase()
{
    yes;
    no;
    impossible;
}

void sol1()
{
    int n;
    cin >> n;
    string s1, s2;
    cin >> s1 >> s2;

    int red = 0, blue = 0;

    fl(i, n)
    {
        int a = s1[i] - '0';
        int b = s2[i] - '0';
        if (a > b)
        {
            red++;
        }
        else if (a < b)
        {
            blue++;
        }
    }

    if (red == blue)
    {
        cout << "EQUAL\n";
    }
    else if (red > blue)
    {
        cout << "RED\n";
    }
    else
    {
        cout << "BLUE\n";
    }
}

vector<int> dx = {0, 0, 1, -1};
vector<int> dy = {1, -1, 0, 0};

void sol2()
{
    int n;
    cin >> n;

    set<pair<int, int>> points;

    unordered_map<char, vector<char>> mp;

    mp['E'] = {'N', 'S'};
    mp['w'] = {'N', 'S'};
    mp['N'] = {'E', 'W'};
    mp['S'] = {'E', 'W'};

    unordered_map<char, int> mp2;

    queue<array<int, 4>> q;
}

void sol3()
{
    int n, k;
    cin >> n >> k;
    vector<int> v(n);
    read_vector(v);

    int ans = 0;

    int p1 = 0, p2 = n - 1;

    while (p1 < n)
    {
        if (v[p1] <= k)
        {
            p1++;
            ans++;
        }
        else
        {
            break;
        }
    }

    while (p2 > p1)
    {
        if (v[p2] <= k)
        {
            p2--;
            ans++;
        }
        else
        {
            break;
        }
    }

    cout << ans << endl;
}

void sol4()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    // rocesfedoc - 1
    // orcesfedoc - 2
    // secrofedoc - 5

    for (int i = 2; i <= n; i++)
    {
        if ((n % i) == 0)
        {
            reverse(s.begin(), s.begin() + i);
        }
    }

    cout << s;
}

void sol5()
{
    int n, k;
    cin >> n >> k;

    string s;
    cin >> s;

    vector<vector<int>> v(26);

    fl(i, n)
    {
        int ind = s[i] - 'a';
        v[ind].push_back(i);
    }

    string res(n, '@');

    fl(i, 26)
    {
        char ch = 'a' + i;
        if (k == 0)
        {
            for (auto x : v[i])
            {
                res[x] = ch;
            }
            continue;
        }
        if (v[i].size() <= k)
        {
            k -= (int)v[i].size();
        }
        else
        {
            int sz = v[i].size();
            for (int x = k; x < sz; x++)
            {
                res[v[i][x]] = ch;
            }
            k = 0;
        }
    }

    string ans = "";

    for (auto ch : res)
    {
        if (ch != '@')
        {
            ans += ch;
        }
    }

    cout << ans << endl;
}

void sol6()
{
    int n, m;
    cin >> n >> m;

    vector<int> v(n);
    read_vector(v);

    vector<vector<int>> buckets(m);
    vector<int> ans = v;
    int req = n / m;

    for (int i = 0; i < n; i++)
    {
        buckets[v[i] % m].push_back(i);
    }

    queue<int> need;
    for (int i = 0; i < 2 * m; i++)
    {
        int mod = i % m;

        while ((int)buckets[mod].size() > req)
        {
            need.push(mod);
            break;
        }
    }

    int moves = 0;

    for (int i = 0; i < 2 * m; i++)
    {
        int mod = i % m;
        while ((int)buckets[mod].size() < req && !need.empty())
        {
            int from = need.front();
            if ((int)buckets[from].size() <= req)
            {
                need.pop();
                continue;
            }

            int idx = buckets[from].back();
            buckets[from].pop_back();

            int diff = (mod - (v[idx] % m) + m) % m;
            ans[idx] += diff;
            moves += diff;

            buckets[mod].push_back(idx);
        }
    }

    cout << moves << '\n';
    for (int val : ans)
        cout << val << " ";
    cout << '\n';
}

void lis()
{
    int n;
    cin >> n;
    vector<int> v(n);
    read_vector(v);

    vector<int> lisv;
    lisv.push_back(v[0]);

    for (int i = 1; i < n; i++)
    {
        if (v[i] > lisv.back())
        {
            lisv.push_back(v[i]);
        }
        else
        {
            auto it = lower_bound(lisv.begin(), lisv.end(), v[i]);
            *it = v[i];
        }
    }

    cout << lisv.size() << endl;
    print_vector(lisv);
}

// Recursive function which finds the
// maximum sum increasing Subsequence
// ending at index i.
int maxSumRecur(int i, vector<int> &arr, vector<int> &memo)
{

    // If value is computed,
    // return it.
    if (memo[i] != -1)
        return memo[i];

    int ans = arr[i];

    // Compute values for all
    // j in range (0, i-1)
    for (int j = i - 1; j >= 0; j--)
    {
        if (arr[j] < arr[i])
        {
            ans = max(ans, arr[i] + maxSumRecur(j, arr, memo));
        }
    }

    return memo[i] = ans;
}

int helper(vector<int> &arr)
{
    int ans = 0;

    vector<int> memo(arr.size(), -1);

    // Compute maximum sum for each
    // index and compare it with ans.
    for (int i = 0; i < arr.size(); i++)
    {
        ans = max(ans, maxSumRecur(i, arr, memo));
    }

    return ans;
}

void maxSumIS()
{
    int n;
    cin >> n;
    vector<int> v(n);
    read_vector(v);

    int ans = 0;
    vector<int> memo(n, 0);

    for (int i = 0; i < n; i++)
    {
        memo[i] = v[i];

        for (int j = 0; j < i; j++)
        {
            if (v[i] > v[j])
            {
                memo[i] = max(memo[i], memo[j] + v[i]);
            }
        }

        ans = max(ans, memo[i]);
    }

    cout << ans << endl;
}

// https://codeforces.com/contest/977/problem/F
void indexlis()
{
    int n;
    cin >> n;
    vector<int> v(n);
    read_vector(v);

    map<int, int> dp;
    dp[v[0]] = 1;

    int ans = 1, index = 0, endValue = v[0];

    for (int i = 1; i < n; i++)
    {
        dp[v[i]] = 1;
        if (dp.count(v[i] - 1))
        {
            dp[v[i]] = max(dp[v[i]], dp[v[i] - 1] + 1);
            if (dp[v[i]] > ans)
            {
                index = i;
                endValue = v[i];
                ans = dp[v[i]];
            }
        }
    }

    cout << ans << endl;

    vector<int> lics = {index + 1};
    int reqvalue = endValue - 1;

    for (int i = index - 1; i >= 0; i--)
    {
        if (v[i] == reqvalue)
        {
            lics.push_back(i + 1);
            reqvalue--;
        }
    }

    reverse(lics.begin(), lics.end());
    print_vector(lics);
}

void rash1()
{
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n);

    fl(i, m)
    {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int numCyclicCompo = 0;
    vector<int> vis(n, 0);
    vector<int> comp;
    queue<int> q;

    fl(i, n)
    {
        if (!vis[i])
        {
            comp.clear();
            vis[i] = 1;
            q.push(i);
            while (!q.empty())
            {
                auto front = q.front();
                q.pop();
                comp.push_back(front);
                for (auto x : adj[front])
                {
                    if (!vis[x])
                    {
                        vis[x] = 1;
                        q.push(x);
                    }
                }
            }
            bool check = true;
            for (auto x : comp)
            {
                if (adj[x].size() != 2)
                {
                    check = false;
                    break;
                }
            }
            if (check)
            {
                numCyclicCompo++;
            }
        }
    }
    cout << numCyclicCompo << endl;
}

void rash2()
{
    int n;
    cin >> n;
    int zero = 0, ans = 0;

    fl(i, n)
    {
        int e;
        cin >> e;
        if (e == 0)
        {
            ans++;
        }
        else
        {
            ans += e;
        }
    }

    cout << ans << endl;
}

void rash3()
{
    int n;
    cin >> n;
    vector<vector<pair<int, int>>> adj(n);
    vector<int> vis(2 * n + 5);
    vector<int> ans(n, 0);

    int a, b;
    fl(i, n)
    {
        cin >> a >> b;
        --a, --b;
        adj[a].push_back({b, i});
        adj[b].push_back({a, i});
        vis[a] = 1;
        vis[b] = 1;
    }

    // yaha vis ulta kaam krega
    // mark vis[node] = 0, once it is visited
    fl(i, 2 * n + 5)
    {
        if (vis[i])
        {
            queue<int> q;
            q.push(i);
            vis[i] = 0;
            while (!q.empty())
            {
                auto front = q.front();
                q.pop();
                for (auto x : adj[front])
                {
                    if (vis[x.first])
                    {
                        ans[x.second] = 1;
                        vis[x.first] = 0;
                        q.push(x.first);
                    }
                }
            }
        }
    }

    int numInt = 0;
    for (auto i : ans)
    {
        if (i)
            numInt++;
    }

    cout << numInt << endl;

    fl(i, n)
    {
        if (ans[i])
        {
            cout << i + 1 << " ";
        }
    }

    cout << endl;
}

void abc1()
{
    int n;
    cin >> n;
    vector<int> v(n);
    read_vector(v);

    vector<int> a(n);
    unordered_map<int, int> fr;
    fl(i, n)
    {
        a[i] = v[i] + i + 1;
        fr[i + 1 - v[i]]++;
    }

    int ans = 0;
    fl(i, n)
    {
        ans += fr[a[i]];
    }

    cout << ans << endl;
}

void abc2()
{
    
}

int32_t main()
{
    fast_io;

    // precompute_factorials(maxn);
    // sieve(2e5 + 2);

    int t = 1;
    // cin >> t;

    while (t--)
    {
        abc2();
    }

    return 0;
}

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