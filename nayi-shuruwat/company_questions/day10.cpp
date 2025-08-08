
#include <bits/stdc++.h>

#include <bitset>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

using ll = long long;
using lld = long double;
using ull = unsigned long long;

// Constants
const ll INF = LONG_LONG_MAX;
const ll mod = 1e9 + 7;

// TypeDEf
typedef pair<ll, ll> pll;
typedef vector<ll> vll;
typedef vector<pll> vpll;
typedef vector<string> vs;
typedef unordered_map<ll, ll> umll;
typedef map<ll, ll> mll;

// Macros
#define ff first
#define ss second
#define pb push_back
#define pii pair<int, int>
#define fl(i, n) for (int i = 0; i < n; i++)
#define rl(i, m, n) for (int i = n; i >= m; i--)
#define py cout << "YES\n";
#define pm cout << "-1\n";
#define pn cout << "NO\n";
#define pimp cout << "IMPOSSIBLE\n";
#define vr(v) v.begin(), v.end()
#define rv(v) v.end(), v.begin()
#define len(s) (int)s.size()
#define forn(i, n) for (int i = 0; i < int(n); i++)
#define all(v) v.begin(), v.end()
#define one(x) memset(x, -1, sizeof(x))
#define zero(x) memset(x, 0, sizeof(x))
#define printn cout << endl;
template <class T>
void print(const T &t)
{
    print_single(t);
}

void r1()
{
    int n;
    cin >> n;

    vector<ll> v(n), odds, evens;

    fl(i, n)
    {
        cin >> v[i];
        if ((v[i] % 2 == 0))
            evens.push_back(v[i]);
        else
            odds.push_back(v[i]);
    }

    sort(all(odds));
    sort(all(evens));

    int osize = odds.size(), esize = evens.size();

    if (((osize % 2) != 0) || ((esize % 2) != 0))
    {
        cout << -1 << endl;
        return;
    }

    int p1 = 0, p2 = osize - 1;
    int s1 = 0;

    vector<int> ans(n);

    while (p1 < p2)
    {
        int a = (odds[p1] + odds[p2]) / 2;
        ans[s1] = a;
        ans[s1 + (n / 2)] = odds[p2] - a;
        s1++;
        p1++;
        p2--;
    }

    p1 = 0, p2 = esize - 1;

    while (p1 < p2)
    {
        int a = (evens[p1] + evens[p2]) / 2;
        ans[s1] = a;
        ans[s1 + (n / 2)] = evens[p2] - a;
        s1++;
        p1++;
        p2--;
    }

    for (auto i : ans)
    {
        cout << i << " ";
    }
    cout << endl;
}

void findCycle(int node, int parent, vector<vector<int>> &adj, vector<bool> &visited,
               vector<int> &path, vector<bool> &isCyclicNode, bool &foundCycle)
{
    if (foundCycle)
        return; // Stop processing if the cycle is already found

    visited[node] = true;
    path.push_back(node);

    for (int neighbor : adj[node])
    {
        if (!visited[neighbor])
        {
            findCycle(neighbor, node, adj, visited, path, isCyclicNode, foundCycle);
            if (foundCycle)
                return;
        }
        else if (neighbor != parent)
        { // Found a back edge, indicating a cycle
            foundCycle = true;
            auto it = find(all(path), neighbor);
            while (it != path.end())
            {
                isCyclicNode[*it] = true;
                ++it;
            }
            return;
        }
    }

    path.pop_back();
}

int bfs(int node, vector<vector<int>> &adj, vector<bool> &isCyclicNode)
{
    queue<int> q;
    q.push(node);
    int dist = 0;
    int n = isCyclicNode.size();
    vector<bool> vis(n + 1, false);
    vis[node] = true;
    while (!q.empty())
    {
        int sz = q.size();

        for (int i = 0; i < sz; i++)
        {
            auto fr = q.front();
            q.pop();

            if (isCyclicNode[fr])
            {
                return dist;
            }

            for (auto neighbor : adj[fr])
            {
                if (vis[neighbor] == false)
                {
                    q.push(neighbor);
                    vis[neighbor] = true;
                }
            }
        }

        dist++;
    }
}

void r3()
{
    int n, a, b;
    cin >> n >> a >> b; // Number of nodes, a and b nodes

    vector<vector<int>> adj(n + 1); // Adjacency list (1-based indexing)
    for (int i = 0; i < n; ++i)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    if (a == b)
    {
        pn return;
    }

    vector<bool> visited(n + 1, false);
    vector<int> path;
    vector<bool> isCyclicNode(n + 1, false);
    bool foundCycle = false;

    findCycle(1, -1, adj, visited, path, isCyclicNode, foundCycle);

    // for (auto i : isCyclicNode)
    // {
    //     cout << i << " ";
    // }
    // cout << endl;

    int dist1 = bfs(a, adj, isCyclicNode), dist2 = bfs(b, adj, isCyclicNode);

    if ((isCyclicNode[a] and isCyclicNode[b]) || (dist1 > dist2))
    {
        cout << "YES\n";
    }
    else
    {
        cout << "NO\n";
    }
}

const int N = 200005;

vector<int> adj[N];
vector<bool> vis(N);

int entry_node = -1;
vector<int> path;

bool dfs1(int u, int p)
{
    vis[u] = true;
    for (auto v : adj[u])
    {
        if (v != p && vis[v])
        {
            entry_node = v;
            return true;
        }
        else if (v != p && !vis[v])
        {
            if (dfs1(v, u))
            {
                return true;
            }
        }
    }
    return false;
}

int dfs2(int u)
{
    vis[u] = true;
    int distbruh = N;
    for (auto v : adj[u])
    {
        if (v == entry_node)
        {
            return 1;
        }
        if (!vis[v])
        {
            int dist = dfs2(v) + 1;
            distbruh = min(dist, distbruh);
        }
    }
    return distbruh;
}

void solve()
{
    int n, a, b;
    cin >> n >> a >> b;
    for (int i = 0; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs1(b, -1);
    vis.assign(n + 1, false);
    int distMarcel = N, distValeriu = 0;
    if (entry_node == a)
    {
        distMarcel = 0;
    }
    else
    {
        distMarcel = dfs2(a);
    }
    vis.assign(n + 1, false);
    if (entry_node == b)
    {
        distValeriu = 0;
    }
    else
    {
        distValeriu = dfs2(b);
    }
    if (distValeriu < distMarcel)
    {
        cout << "YES" << endl;
    }
    else
    {
        cout << "NO" << endl;
    }
    for (int i = 1; i <= n; i++)
    {
        adj[i].clear();
        vis[i] = false;
    }
}

// https://www.codechef.com/problems/GRDXOR
void r4()
{
    int n, m;
    cin >> n >> m;

    vector<vector<ll>> grid(n, vector<ll>(m, 0));

    fl(i, n)
    {
        fl(j, m)
        {
            cin >> grid[i][j];
        }
    }

    vector<vector<int>> rows(31, vector<int>(n, 0)), cols(31, vector<int>(m, 0));

    vector<int> bitsloc(31, 0);

    fl(i, 31)
    {
        int cnt = 0;
        fl(j, n)
        {
            fl(k, m)
            {
                if (((1 << i) & grid[j][k]) != 0)
                {
                    cnt++;
                }
            }
        }
        bitsloc[i] = cnt;
    }

    // rowwise set bits
    for (int k = 0; k < 31; k++)
    {
        for (int i = 0; i < n; i++)
        {
            int cnt = 0;
            for (int j = 0; j < m; j++)
            {
                if (((1 << k) & grid[i][j]) != 0)
                {
                    cnt++;
                }
            }
            rows[k][i] = cnt;
        }
    }

    // colwise set bits
    for (int k = 0; k < 31; k++)
    {
        for (int i = 0; i < m; i++)
        {
            int cnt = 0;
            for (int j = 0; j < n; j++)
            {
                if (((1 << k) & grid[j][i]) != 0)
                {
                    cnt++;
                }
            }
            cols[k][i] = cnt;
        }
    }

    ll res = 0;

    fl(i, n)
    {
        fl(j, m)
        {
            ll sum = 0;

            for (int bitpos = 0; bitpos < 30; bitpos++)
            {
                if (((1 << bitpos) & grid[i][j]) == 0)
                {
                    ll total = bitsloc[bitpos];

                    total = total - (rows[bitpos][i] + cols[bitpos][j]);

                    sum += (1 << bitpos) * total;
                }
                else
                {
                    ll total = (n * m) - bitsloc[bitpos];

                    total = total - ((m - rows[bitpos][i]) + (n - cols[bitpos][j]));

                    sum += (1 << bitpos) * total;
                }
            }

            res = max(res, sum);
        }
    }

    cout << res << endl;
}

void r5()
{

    int n;
    cin >> n;

    vector<ll> v(n);

    fl(i, n)
    {
        cin >> v[i];
    }

    sort(all(v));

    ll seclar = v[n - 2];

    if (seclar != v[n - 1])
    {
        if (v[0] < seclar)
        {
            py
        }
        else
        {
            pn
        }
        return;
    }

    ll smallcnt = 0, seclarcnt = 0;
    for (auto i : v)
    {
        if (i < seclar)
        {
            smallcnt++;
        }
        else if (i == seclar)
        {
            seclarcnt++;
        }
    }

    if (smallcnt >= (seclarcnt - 1))
        py else pn
}

const long long int MOD = 1e9 + 7;

// Function to calculate (a^b) % mod
long long power(long long a, long long b, long long mod)
{
    long long result = 1;
    while (b > 0)
    {
        if (b % 2 == 1)
        {
            result = (result * a) % mod;
        }
        a = (a * a) % mod;
        b /= 2;
    }
    return result % mod;
}

// @uncomment this for factorial questions
const int factSize = 100000 + 5;
ll fact[factSize];
ll invFact[factSize];

set<ll> primes;
// Precompute factorials and modular inverses
void precomputeFactorials(int n, long long mod)
{
    fact[0] = 1;
    for (int i = 1; i <= n; ++i)
    {
        fact[i] = (fact[i - 1] * i) % mod;
    }
    invFact[n] = power(fact[n], mod - 2, mod); // Modular inverse using Fermat's theorem
    for (int i = n - 1; i >= 0; --i)
    {
        invFact[i] = (invFact[i + 1] * (i + 1)) % mod;
    }
}

// Function to calculate nCr % mod
long long nCr(int n, int r, const vector<long long> &fact, const vector<long long> &invFact, long long mod)
{
    if (r > n)
        return 0;
    return (fact[n] * invFact[r] % mod * invFact[n - r] % mod) % mod;
}

// https://www.codechef.com/problems/AWESUM_OR
void r6(vector<long long> fact, vector<long long> invfact)
{
    ll n;
    cin >> n;

    bitset<sizeof(ll) * 61> bits(n);

    int cnt = 0;
    for (int i = 0; i < 61; i++)
    {
        if (bits[i] == 1)
            cnt++;
    }

    ll res = ((power(3, cnt, mod) - (3 * 1ll * power(2, cnt, MOD))) % MOD + 3 + MOD) % MOD;

    cout << res << endl;
}

void r7()
{
    ll n, x, k;
    cin >> n >> x >> k;
    ll y = n - x;
    x = x - (x / k) * k;
    y = y - (y / k) * k;

    ll alpha = min(x, y);
    ll ans = (x - alpha) + (y - alpha);
    cout << ans << endl;
}

void r8()
{
    ll a, b;
    cin >> a >> b;

    ll mini = a + b;

    for (ll i = 0; i < a; i++)
    {
        ll newa = a - i, newb = b + i;
        if (newa % newb == 0)
        {
            mini = min(mini, i);
        }
    }

    for (ll i = 0; i < b; i++)
    {
        ll newa = a + i, newb = b - i;
        if (newa % newb == 0)
        {
            mini = min(mini, i);
        }
    }

    cout << mini << endl;
}

vector<int> primes;

void generatePrimes(int n)
{
    vector<bool> isPrime(n + 1, true); // Initialize all numbers as prime
    isPrime[0] = isPrime[1] = false;   // 0 and 1 are not prime

    for (int i = 2; i * i <= n; ++i)
    {
        if (isPrime[i])
        {
            for (int j = i * i; j <= n; j += i)
            {
                isPrime[j] = false; // Mark multiples of i as non-prime
            }
        }
    }

    // Collect all prime numbers into a vector

    for (int i = 2; i <= n; ++i)
    {
        if (isPrime[i])
        {
            primes.insert(i);
        }
    }
}

void r9()
{
    ll h;
    cin >> h;

    if (primes.count(h))
    {
        cout << 1 << endl;
        return;
    }

    for (int i = 0;; i++)
    {
        h -= (1 << i);
        if (h == 0)
        {
            cout << (i + 1) << endl;
            return;
        }
        if (h < 0)
        {
            cout << -1 << endl;
            return;
        }
        if (primes.count(h))
        {
            cout << (i + 2) << endl;
            return;
        }
    }
}

void code1()
{
    ll n, d;
    cin >> n >> d;

    cout << 1 << " ";

    if (n > 2)
    {
        cout << 3 << " ";
    }
    else
    {
        if (d % 3 == 0)
        {
            cout << 3 << " ";
        }
    }

    if (d == 5)
    {
        cout << 5 << " ";
    }

    // for 7

    if (d == 7)
    {
        cout << 7 << " ";
    }
    else
    {
        if (n >= 7)
        {
            cout << 7 << " ";
        }
    }

    // for 9

    if (n >= 6)
    {
        cout << 9;
    }
    else
    {
        if ((d % 3) == 0)
        {
            if (n > 2)
                cout << 9 << " ";
            else
            {
                if (d == 9)
                {
                    cout << 9 << " ";
                }
            }
        }
    }

    cout << endl;
}

set<ll> distinctSubarraySums(vector<int> &arr)
{
    set<ll> st;
    int n = arr.size();

    vector<ll> prefixSum(n + 1, 0);
    for (int i = 0; i < n; ++i)
    {
        prefixSum[i + 1] = prefixSum[i] + arr[i];
    }

    for (int start = 0; start < n; ++start)
    {
        for (int end = start; end < n; ++end)
        {
            ll subarraySum = prefixSum[end + 1] - prefixSum[start];
            st.insert(subarraySum);
        }
    }

    return st;
}

void code2()
{
    ll n;
    cin >> n;

    vector<int> v1, v2;

    ll x = -1;
    fl(i, n)
    {
        ll e;
        cin >> e;
        if (abs(e) != 1)
        {
            x = e;
        }
        else
        {
            if (x == -1)
            {
                v1.push_back(e);
            }
            else
            {
                v2.push_back(e);
            }
        }
    }

    set<ll> st;
    st.insert(0);

    int n1 = v1.size(), n2 = v2.size();
    ll sum = 0;
    for (int i = 0; i < n1; i++)
    {
        sum += v1[i];
        st.insert(sum);
        vector<ll> temp(all(st));
        for (auto j : temp)
        {
            st.insert(sum - j);
        }
    }

    // for (auto i : st)
    // {
    //     cout << i << " ";
    // }
    // cout << endl;

    if (x != -1)
    {
        sum = 0;

        set<ll> st2;
        st2.insert(0);
        for (int i = 0; i < n2; i++)
        {
            sum += v2[i];
            st.insert(sum);
            vector<ll> temp(all(st2));
            for (auto j : temp)
            {
                st.insert(sum - j);
            }
        }

        for (auto i : st2)
        {
            st.insert(i);
        }

        // for (auto i : st)
        // {
        //     cout << i << " ";
        // }
        // cout << endl;

        st.insert(x);

        set<ll> pref, suff;
        sum = 0;
        pref.insert(sum);
        suff.insert(sum);

        for (int i = n1 - 1; i >= 0; i--)
        {
            sum += v1[i];
            suff.insert(sum);
        }
        sum = 0;

        for (int i = 0; i < n2; i++)
        {
            sum += v2[i];
            pref.insert(sum);
        }

        vector<ll> pre(all(pref)), suf(all(suff));

        for (int i = 0; i < suf.size(); i++)
        {
            for (int j = 0; j < pre.size(); j++)
            {
                ll curr = x + suf[i] + pre[j];
                st.insert(curr);
            }
        }
    }

    cout << (ll)st.size() << endl;
    for (auto i : st)
    {
        cout << i << " ";
    }
    cout << endl;
}

// probability q => setprecision(num_digits)

void h1()
{
    double n, m, b, k;
    cin >> b >> m >> n >> k;

    double mi = m;
    double ni = n;

    double t = (double)m / (m + n);
    mi += (double)t * (k - 1);

    ni += (double)(k - 1) * (double)n / (m + n);

    if (b != k)
    {
        double t = (double)mi / (mi + ni);
        mi -= (double)(k)*t;
    }

    cout << setprecision(7) << mi << endl;
}

// tricky 1
void h2()
{
    ll x;
    cin >> x;

    if (x == 1)
        cout << -1 << endl;
    else if (x <= (1e6 + 1))
    {
        cout << "1 1 " << x - 1 << endl;
    }
    else if (x > 1e6 && x % 1000000 != 0)
        cout << 1000000 << " " << x / 1000000 << " " << x % 1000000 << endl;
    else
        cout << 1000000 << " " << (x / 1000000) - 1 << " " << 1000000 << endl;
}

// https://www.codechef.com/problems/SUBSEQINV
// good question
void h3()
{
    int n;
    cin >> n;

    vector<ll> v(n);

    fl(i, n)
    {
        cin >> v[i];
    }

    int cnt = 0;
    vector<int> less(n), greater(n);

    ll mini = INT_MAX;

    for (int i = n - 1; i >= 0; i--)
    {
        less[i] = mini;
        mini = min(mini, v[i]);
    }

    ll maxi = 0;
    fl(i, n)
    {
        greater[i] = maxi;
        maxi = max(maxi, v[i]);
    }

    for (int i = n - 1; i >= 0; i--)
    {
        if (v[i] < less[i] and v[i] > greater[i])
        {
            cnt++;
        }
    }

    ll mod2 = 998244353;
    ll res = power(2, cnt, mod2);

    if (cnt == n)
    {
        res--;
    }

    cout << res << endl;
}

void h4()
{
    int n;
    cin >> n;

    vector<ll> v(n);
    ll sum = 0;
    fl(i, n)
    {
        cin >> v[i];
        sum += v[i];
    }

    ll mini = *min_element(all(v));
    ll rem = sum - (n * 1ll * mini);
    if (mini % 2 == 0)
    {
        if (rem % 2 == 0)
        {
            cout << "CHEFINA\n";
        }
        else
        {
            cout << "CHEF\n";
        }
    }
    else
    {
        if (rem % 2 == 0)
        {
            cout << "CHEF \n";
        }
        else
        {
            cout << "CHEFINA\n";
        }
    }
}

int getChar(string &s, int pos)
{
    return s[pos - 1] - '0';
}

// nice one
void h5()
{
    ll n;
    cin >> n;
    string s;
    cin >> s;

    ll ans = 1;
    ll mod2 = 1e9 + 7;

    for (int i = 3; i <= n; i += 2)
    {
        int curr = getChar(s, i);
        int s_n_2 = getChar(s, i - 2), s_n_1 = getChar(s, i - 1);
        int and_ = s_n_1 & s_n_2, or_ = s_n_1 | s_n_2, xor_ = s_n_1 ^ s_n_2;
        int cnt = (and_ == curr) + (or_ == curr) + (xor_ == curr);
        if (cnt == 0)
        {
            cout << 0 << endl;
            return;
        }
        else
        {
            ans = (ans * 1ll * cnt) % mod2;
        }
    }
    cout << ans << endl;
}

void h6()
{
    int n, k;
    cin >> n >> k;
    ll odds = 0, evens = 0;

    fl(i, n)
    {
        ll num;
        cin >> num;
        if (num % 2 == 0)
        {
            evens++;
        }
        else
        {
            odds++;
        }
    }

    ll oddplaces = (n + 1) / 2, evenplaces = (n / 2);

    if ((odds == oddplaces) || (odds == evenplaces))
    {
        ll ans = 1;

        if (k == 1)
        {
            ans = (fact[oddplaces] * 1ll * fact[evenplaces]) % mod;

            // cout << oddplaces << " " << evenplaces << endl;

            if (oddplaces == evenplaces)
            {
                ans = (ans * 1ll * 2) % mod;
            }
        }
        else
        {
            bool allsame = evens == 0 || odds == 0;

            if (allsame)
            {
                ans = fact[n] % mod;
            }
            else
            {
                ans = 0;
            }
        }

        cout << ans << endl;
    }
    else if (((odds == n) || (evens == n)) and k == 0)
    {
        ll ans = fact[n] % mod;

        cout << ans << endl;
    }
    else
    {
        cout << 0 << endl;
    }
}

void h7()
{
    ll n, k;
    cin >> n >> k;

    vector<ll> v(n, 1);
    for (int i = 0; i < n; i += 2)
    {
        v[i] = 2;
    }

    ll sum = accumulate(all(v), 0ll);
    ll rem = k - sum;

    for (int i = 0; i < n and rem > 0; i++)
    {
        if ((v[i] + rem) <= 1e5)
        {
            ll inc = rem;
            if ((v[i] % 2) != ((v[i] + rem) % 2))
            {
                inc--;
            }
            v[i] += inc;
            rem -= inc;
        }
        else
        {
            if (i % 2 == 0)
            {
                ll inc = 1e5 - v[i];
                v[i] = 1e5;
                rem -= inc;
            }
            else
            {
                ll inc = (1e5 - 1) - v[i];
                v[i] = (1e5 - 1);
                rem -= inc;
            }
        }
    }

    if (rem == 0)
    {
        for (auto i : v)
        {
            cout << i << " ";
        }
        cout << "\n";
    }
    else
    {
        cout << -1 << "\n";
    }
}

void h8()
{
    int n;
    cin >> n;
    vector<int> a(n);
    map<int, vector<int>> factors;
    unordered_map<int, int> dp;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        int x = a[i];
        if (factors.find(x) == factors.end())
        {
            for (int d = 1; d * d <= x; d++)
            {
                if (x % d == 0)
                {
                    factors[x].push_back(d);
                    if ((x / d) != d)
                    {
                        factors[x].push_back(x / d);
                    }
                }
            }
            sort(factors[x].begin(), factors[x].end());
        }
    }
    ll ans = 0;
    sort(a.rbegin(), a.rend());

    for (int i = 0; i < n; i++)
    {
        vector<int> f = factors[a[i]];
        for (auto &d : f)
        {
            dp[d] = max(dp[d], 1 + dp[a[i]]);
        }
    }

    for (int i = 0; i < n; i++)
    {
        ans = max(ans, 1LL * dp[a[i]] * a[i]);
    }

    cout << ans << endl;
}

// apply lcs on itself
int LongestRepeatingSubsequence(string &s)
{

    string s1 = s, s2 = s;

    int dp[1001][1001] = {0};

    int n1 = s1.size(), n2 = s2.size();
    int ans = 0;

    for (int i = 1; i <= n1; i++)
    {
        for (int j = 1; j <= n2; j++)
        {
            dp[i][j] = max({dp[i - 1][j - 1], dp[i - 1][j],
                            dp[i][j - 1]});

            if (s1[i - 1] == s2[j - 1] and i != j)
                dp[i][j] = max(dp[i][j], 1 + dp[i - 1][j - 1]);
            ans = max(ans, dp[i][j]);
        }
    }

    return ans;
}

void h9()
{
    ll n;
    cin >> n;
    vector<ll> v(n);
    fl(i, n)
    {
        cin >> v[i];
    }
    sort(all(v));
    ll sum = 0;
    int i = 0;
    for (; i < n / 2; i++)
    {
        sum -= v[i];
    }
    for (; i < n; i++)
    {
        sum += v[i];
    }
    cout << sum << endl;
}

int ha;

void h10()
{
    int n;
    cin >> n;

    vector<ll> a(n), b(n);

    fl(i, n)
    {
        cin >> a[i];
        b[i] = a[i];
    }

    sort(all(b));
    ll res = 0;

    for (int i = 0; i < n; i++)
    {
        ha = (i + 1);
        auto it = lower_bound(b.begin(), b.end(), a[i], [](ll x, ll y)
                              {
            ll pw = pow(x, ha);
            return pw <= y; });
        res += distance(b.begin(), it);
    }

    cout << res << endl;
}

void h11()
{
    int n;
    cin >> n;

    string s;
    cin >> s;

    int lastb = -1, firstb = -1;
    int cnta = 0, cntc = 0;

    int i = n - 1;

    while (i >= 0)
    {
        if (s[i] == 'c')
        {
            i--;
            break;
        }
        i--;
    }

    while (i >= 0 and s[i] != 'b')
    {
        i--;
    }

    while (i >= 0)
    {
        if (s[i] == 'a')
        {
            cnta++;
        }
        i--;
    }

    i = 0;

    while (i < n)
    {
        if (s[i] == 'a')
        {
            i++;
            break;
        }
        i++;
    }

    while (i < n and s[i] != 'b')
    {
        i++;
    }

    while (i < n)
    {
        if (s[i] == 'c')
        {
            cntc++;
        }
        i++;
    }

    ll ans = min(cnta, cntc);
    cout << ans << endl;
}

void toofar()
{
    int n;
    cin >> n;

    unordered_map<ll, ll> mp;
    fl(i, n)
    {
        ll diff = i + 1;
        ll e;
        cin >> e;
        if (mp.count(e))
        {
            mp[e] = max(mp[e], diff);
        }
        else
        {
            mp[e] = diff;
        }
    }

    ll sum = 0;
    for (auto i : mp)
    {
        sum += i.second;
    }
    cout << sum << endl;
}

void s116()
{
    ll n;
    cin >> n;

    vector<pll> v(n);

    fl(i, n)
    {
        cin >> v[i].first;
        v[i].second = i;
    }

    sort(all(v));

    vector<ll> t;

    for (auto i : v)
    {
        t.push_back(i.second);
    }

    ll ans = n;

    int i = 0;

    while (i < n)
    {
        int prev = t[i];
        i++;
        int len = 1;
        while (i < n and abs(t[i] - prev) <= 1)
        {
            prev = t[i];
            i++;
            len++;
        }
        ans -= (len - 1);
    }

    cout << ans << endl;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // precomputeFactorials(factSize, MOD);
    primes.clear();
    generatePrimes(1e5);

    ll t;
    cin >> t;

    while (t--)
        s116();

    return 0;
}