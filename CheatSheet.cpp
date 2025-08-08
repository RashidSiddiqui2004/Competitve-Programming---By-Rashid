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
const int MOD_ATCODERS = 998244353;

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

const int maxN = 50001;
bitset<maxN> ans[maxN]; // biset[i] tells to which nodes can be reached by node i => maintains uniqueness
// so instead of using simple numbers, use bitset (here), to avoid duplication of nodes

void reachableNodes()
{
    ll n, m;
    cin >> n >> m;

    vector<vector<ll>> adj(n), revAdj(n);
    vector<ll> outdegree(n, 0ll);

    fl(i, m)
    {
        ll u, v;
        cin >> u >> v;
        --u, --v;
        revAdj[v].push_back(u);
        outdegree[u]++;
    }

    queue<ll> q;

    fl(i, n)
    {
        if (outdegree[i] == 0)
        {
            ans[i].set(i);
            q.push(i);
        }
    }

    while (!q.empty())
    {
        auto top = q.front();
        q.pop();

        ll node = top;

        for (auto i : revAdj[node])
        {
            ans[i] |= ans[node];
            outdegree[i]--;

            if (outdegree[i] == 0)
            {
                ans[i].set(i);
                q.push(i);
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        cout << ans[i].count() << " ";
    }

    cout << "\n";
}

vector<bitset<maxN>> dp(maxN);
vector<int> adj[maxN], revAdj[maxN], cond[maxN];
vector<int> v;
int comp[maxN];
int cnt = 0;
int vis[maxN];

void dfs(int s, vector<int> adj[])
{
    if (vis[s])
        return;

    vis[s] = 1;

    for (auto i : adj[s])
        dfs(i, adj);

    v.push_back(s);
}

void dfs2(int s, int cnt)
{
    if (comp[s])
        return;

    comp[s] = cnt;

    for (auto i : revAdj[s])
        dfs2(i, cnt);
}

void reachableNodeQueries()
{
    int n, m, t;
    cin >> n >> m >> t;
    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y);
        revAdj[y].push_back(x);
    }
    // topological sort
    for (int i = 1; i <= n; i++)
    {
        if (!vis[i])
            dfs(i, adj);
    }
    // condensing SCCs
    reverse(v.begin(), v.end());
    for (auto i : v)
    {
        if (!comp[i])
        {
            dfs2(i, ++cnt);
        }
    }
    // condensed graph.
    for (int i = 1; i <= n; i++)
    {
        for (auto j : adj[i])
            if (comp[i] != comp[j])
            {
                cond[comp[i]].push_back(comp[j]);
            }
    }

    memset(vis, 0, sizeof vis);
    v.clear();
    // topological sort of condensed graphs
    for (int i = 1; i <= cnt; i++)
    {
        if (!vis[i])
            dfs(i, cond);
    }

    for (auto s : v)
    {
        dp[s][s] = 1;
        for (auto i : cond[s])
            dp[s] |= dp[i];
    }

    while (t--)
    {
        int x, y;
        cin >> x >> y;
        cout << (dp[comp[x]][comp[y]] ? "YES" : "NO") << endl;
    }
}

const int maxLen = 5000;

bool grid[maxLen + 1][maxLen + 1];
ll prefixSumGrid[maxLen + 1][maxLen + 1];

void maxSquareGoodLand()
{
    int n, m;
    cin >> n >> m;

    // considering 1-based indexing

    fl(i, n)
    {
        fl(j, m)
        {
            cin >> grid[i + 1][j + 1];
        }
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            prefixSumGrid[i][j] = grid[i][j] + prefixSumGrid[i - 1][j] + prefixSumGrid[i][j - 1] -
                                  prefixSumGrid[i - 1][j - 1];
        }
    }

    ll maxGoodArea = 0;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            for (int k = 0; k <= min(n, m); k++)
            {
                int from_row = i, to_row = i + k, from_col = j, to_col = j + k;
                if (to_row <= n and to_col <= m)
                {
                    ll side = k + 1;

                    ll currArea = prefixSumGrid[to_row][to_col] - prefixSumGrid[from_row - 1][to_col] -
                                  prefixSumGrid[from_row][from_col - 1] + prefixSumGrid[from_row - 1][from_col - 1];

                    if (currArea == (side * side))
                    {
                        maxGoodArea = max(maxGoodArea, currArea);
                    }
                }
            }
        }
    }

    cout << maxGoodArea << endl;
}

void solve()
{
    int n;
    cin >> n;

    ll ans = 0;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; (i * j) <= n; j++)
        {
            ll c = n - (i * 1ll * j);
            if (c > 0)
            {
                ans++;
            }
        }
    }

    cout << ans << endl;
}

ll helper(int pos, vector<int> &moves, vector<ll> &dp)
{

    if (pos <= 0)
    {
        return 0;
    }

    if (pos == 1)
    {
        return 1;
    }

    if (dp[pos] != -1)
    {
        return dp[pos] % MOD_ATCODERS;
    }

    ll ans = 0;

    for (auto i : moves)
    {
        ans += helper(pos - i, moves, dp) % MOD_ATCODERS;
    }

    return dp[pos] = ans % MOD_ATCODERS;
}

// iterative DP

void solve2()
{
    int n, k;
    cin >> n >> k;

    vector<int> moves;
    int minMove = INT_MAX;

    for (int i = 0; i < k; i++)
    {
        int l, r;
        cin >> l >> r;
        minMove = min(minMove, l);
        for (int j = l; j <= r; j++)
        {
            moves.push_back(j);
        }
    }

    sort(moves.begin(), moves.end());

    vector<ll> dp(n + 1, 0);
    dp[1] = 1;

    for (int pos = minMove; pos <= n; pos++)
    {
        for (auto move : moves)
        {
            if ((pos - move) >= 1)
            {
                dp[pos] = (dp[pos] + dp[pos - move]) % MOD_ATCODERS;
            }
            else
            {
                break;
            }
        }
    }

    cout << dp[n] << endl;
}

// https://atcoder.jp/contests/abc179/tasks

// Optimized approach using combining DP
void leapingTak()
{
    ll n, k;
    cin >> n >> k;

    vector<pll> moves;

    for (int i = 0; i < k; i++)
    {
        ll l, r;
        cin >> l >> r;
        moves.push_back({l, r + 1});
    }

    sort(moves.begin(), moves.end());

    vector<ll> dp(n + 1, 0ll);
    dp[1] = 1;
    dp[2] = -1;

    // use prefix sum approach here :)
    for (int pos = 1; pos <= n; pos++)
    {
        // just like prefix-sum
        if (pos > 1)
            dp[pos] += dp[pos - 1] % MOD_ATCODERS;

        for (auto &move : moves)
        {
            ll l = move.first, r = move.second;
            if ((pos + l) <= n)
                dp[pos + l] = (dp[pos] + dp[pos + l]) % MOD_ATCODERS;
            if ((pos + r) <= n)
                dp[pos + r] = (dp[pos + r] - dp[pos] + MOD_ATCODERS) % MOD_ATCODERS;
        }
    }

    dp[n] %= MOD_ATCODERS;

    cout << dp[n] << endl;
}

// https://atcoder.jp/contests/abc179/tasks/abc179_e
void sequenceSum()
{
    ll n, x, m;
    cin >> n >> x >> m;

    if (n <= 1e5)
    {
        ll sum = 0, prev = x, curr;

        sum += prev;
        for (int i = 2; i <= n; i++)
        {
            curr = (prev * prev) % m; // Fixed power calculation
            sum += curr;
            prev = curr;
        }
        cout << sum << endl;
        return;
    }

    ll prev = x, curr = x;
    unordered_set<ll> st;
    vector<ll> v;

    st.insert(curr);
    v.push_back(curr);

    ll startValue = -1;

    for (ll i = 2; i <= n; i++)
    {
        curr = (prev * prev) % m;

        if (st.count(curr))
        { // Cycle detected
            startValue = curr;
            break;
        }

        st.insert(curr);
        v.push_back(curr);
        prev = curr;
    }

    ll sumBeforeCycle = 0, sumInCycle = 0;
    bool cycleStart = false;
    ll reqTerms = n, cycleSize = 0;
    vector<ll> cycleElems;

    for (ll i : v)
    {
        if (i == startValue || cycleStart)
        {
            cycleStart = true;
            sumInCycle += i;
            cycleSize++;
            cycleElems.push_back(i);
        }
        else
        {
            sumBeforeCycle += i;
            reqTerms--;
        }
    }

    ll cycleRepeats = reqTerms / cycleSize;
    ll sum = sumBeforeCycle + (cycleRepeats * sumInCycle);

    reqTerms %= cycleSize;
    for (int i = 0; i < reqTerms; i++)
    {
        sum += cycleElems[i];
    }

    cout << sum << endl;
}

// https://atcoder.jp/contests/hhkb2020/tasks/hhkb2020_d
// https://atcoder.jp/contests/hhkb2020/tasks/hhkb2020_e

void tidyLamps()
{
    int n, m;
    cin >> n >> m;

    ll tidyCells = 0;
    vector<string> grid(n);

    for (int i = 0; i < n; i++)
    {
        cin >> grid[i];
        for (char j : grid[i])
        {
            if (j == '.')
                tidyCells++;
        }
    }

    // Initialize row and column prefix arrays
    vector<vector<pii>> rowPref(n, vector<pii>(m, {-1, -1}));
    vector<vector<pii>> colPref(n, vector<pii>(m, {-1, -1}));

    // Compute row-wise closest '.' indices
    for (int i = 0; i < m; i++)
    {
        int prev = -1;
        for (int j = 0; j < n; j++)
        { // Top to bottom
            if (prev == -1 and grid[j][i] == '.')
                prev = j;
            else if (grid[j][i] == '#')
                prev = -1;
            rowPref[j][i].first = prev;
        }
        prev = -1;
        for (int j = n - 1; j >= 0; j--)
        { // Bottom to top
            if (prev == -1 and grid[j][i] == '.')
                prev = j;
            else if (grid[j][i] == '#')
                prev = -1;
            rowPref[j][i].second = prev;
        }
    }

    for (int i = 0; i < n; i++)
    {
        int prev = -1;
        for (int j = 0; j < m; j++)
        { // Left to right
            if (prev == -1 and grid[i][j] == '.')
                prev = j;
            else if (grid[i][j] == '#')
                prev = -1;
            colPref[i][j].first = prev;
        }
        prev = -1;
        for (int j = m - 1; j >= 0; j--)
        { // Right to left
            if (prev == -1 and grid[i][j] == '.')
                prev = j;
            else if (grid[i][j] == '#')
                prev = -1;
            colPref[i][j].second = prev;
        }
    }

    // Compute total ways
    ll totalWays = tidyCells * 1ll * pow(2, tidyCells);

    ll nonAchWays = 0;

    // Compute non-achievable ways
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (grid[i][j] == '.')
            {
                ll t = 1;

                if (i - 1 >= 0)
                {
                    int p = rowPref[i - 1][j].first;

                    if (p != -1)
                        t += (i - 1 - p + 1);
                }
                if (i + 1 < n)
                {
                    int p = rowPref[i + 1][j].second;

                    if (p != -1)
                        t += (p - (i + 1) + 1);
                }
                if (j - 1 >= 0)
                {
                    int p = colPref[i][j - 1].first;

                    if (p != -1)
                        t += (j - 1 - p + 1);
                }
                if (j + 1 < m)
                {
                    int p = colPref[i][j + 1].second;

                    if (p != -1)
                        t += (p - (j + 1) + 1);
                }

                nonAchWays += 1ll * pow(2, tidyCells - t);
            }
        }
    }

    ll ans = totalWays - nonAchWays;

    cout << ans << endl;
}

void movement()
{
    int n;
    cin >> n;
    vector<ll> v(n);
    input_vector(v);
    int i = 0;

    while ((i + 1) < n)
    {
        if (v[i] == v[i + 1])
        {
            i++;
        }
        else
            break;
    }

    cout << (n - i - 1) << endl;
}

int main()
{
    fast_io;

    int t = 1;
    cin >> t;

    while (t--)
    {
        movement();
    }

    return 0;
}
