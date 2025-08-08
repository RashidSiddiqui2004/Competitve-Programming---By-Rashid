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
#define input_vector(v) \
    for (auto &x : v)   \
        cin >> x;

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

// https://www.codechef.com/problems/CHEFSOC2
void dpsolver(int n, int m, int currDog, vector<int> &a, vector<ll> &ans, int turn = 0)
{
    if (turn == m)
    {
        ans[currDog] += 1 % MOD;
        return;
    }

    int prev = currDog - a[turn], next = currDog + a[turn];

    if (prev >= 0)
    {
        dpsolver(n, m, prev, a, ans, turn + 1);
    }

    if (next < n)
    {
        dpsolver(n, m, next, a, ans, turn + 1);
    }
}

ll dp[1001][1001];

ll dpsolver2(int n, int m, int currDog, int reqDog, vector<int> &a, int turn)
{
    if (currDog < 0 || currDog >= n)
    {
        return 0ll;
    }

    if (turn == -1)
    {
        return (currDog == reqDog);
    }

    ll ans = (dpsolver2(n, m, currDog + a[turn], reqDog, a, turn - 1) +
              dpsolver2(n, m, currDog - a[turn], reqDog, a, turn - 1)) %
             MOD;

    return dp[currDog][turn] = ans;
}

template <typename T>
void print_vector(const vector<T> &v)
{
    for (const auto &x : v)
        cout << x << " ";
    cout << endl;
}

void s4()
{
    int n, m, x;
    cin >> n >> m >> x;
    x--;

    memset(dp, -1, sizeof(dp));

    vector<int> a(m);
    input_vector(a);

    vector<ll> ans(n, 0ll);

    for (int i = 0; i < n; i++)
    {
        ans[i] = dpsolver2(n, m, i, x, a, m - 1);
    }

    print_vector(ans);
}

const int MAXN = 501;

vector<int> dx = {1, 0, 0};
vector<int> dy = {0, 1, -1};

ll vis[MAXN][MAXN];

// Movement: down, right, left
bool isposs(const vector<vector<ll>> &grid, ll mid)
{
    int n = grid.size();
    int m = grid[0].size();
    memset(vis, 0, sizeof(vis));

    queue<pii> q;

    q.push({0, 0});
    vis[0][0] = 1;

    while (!q.empty())
    {
        auto fr = q.front();
        auto x = fr.first, y = fr.second;
        q.pop();
        if (x == n - 1 && y == m - 1)
            return true;
        for (int i = 0; i < 3; i++)
        {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && !vis[nx][ny] && grid[nx][ny] <= mid)
            {
                vis[nx][ny] = 1;
                q.push({nx, ny});
            }
        }
    }

    return false;
}

void s5()
{
    // n, m <= 500
    int n, m;
    cin >> n >> m;
    vector<vector<ll>> grid(n, vector<ll>(m));

    ll low = 0, high = 0, mid, ans = LLONG_MAX;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> grid[i][j];
            high = max(high, grid[i][j]);
        }
    }

    while (low <= high)
    {
        mid = low + (high - low) / 2;

        if (isposs(grid, mid))
        {
            ans = mid;
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }

    cout << ans << endl;
}

void sol6()
{
    int n, b;
    cin >> n >> b;

    vector<vector<ll>> v;

    fl(i, n)
    {
        int ki;
        cin >> ki;

        fl(j, ki)
        {
            ll revenue, cost;
            cin >> revenue >> cost;

            v.push_back({i, revenue, cost});
        }
    }

    int k = v.size();

    ll maxRevenue = 0ll;

    for (ll i = 1; i <= ((1 << (k + 1)) - 1); i++)
    {
        vector<bool> st(k, 0);

        bool check = false;

        ll reqBudget = 0ll;

        for (ll j = 0; j < k; j++)
        {
            if (i & (1 << j))
            {
                ll id = v[j][0];

                if (st[id])
                {
                    check = true;
                    break;
                }

                st[id] = 1;
                reqBudget += v[j][2];
            }
        }

        if (!check and (b >= reqBudget))
        {
            ll revenue = 0ll;
            ll remBudget = b;

            for (ll j = 0; j < k; j++)
            {
                if (i & (1 << j))
                {
                    remBudget -= v[j][2];
                    revenue += v[j][1];
                }
            }

            maxRevenue = max(maxRevenue, revenue);
        }
    }

    cout << maxRevenue << endl;
}

void sol7()
{
    int n;
    cin >> n;
    string s;
    cin >> s;

    vector<int> blocks;

    int i = 0;

    while (i < n)
    {
        char ch = s[i];
        int len = 0;
        while (i < n and s[i] == ch)
        {
            len++;
            i++;
        }
        blocks.push_back(len);
    }

    int ans = (blocks[0] - 1);

    for (int i = 1; i < blocks.size(); i++)
    {
        if (blocks[i] == 1)
        {
            ans += ((blocks[i - 1]) + (i == (blocks.size() - 1) ? 0 : blocks[i + 1]) - 1);
            if (i + 1 < blocks.size())
                blocks[i + 1] = 1;
            i++;
        }
        else
        {
            ans += blocks[i] - 1;
        }
    }

    cout << ans << endl;
}

void r1()
{
    int n;
    cin >> n;

    int e;

    vector<int> ans(2 * n, -1);
    unordered_set<int> st;

    fl(i, n)
    {
        fl(j, n)
        {
            cin >> e;
            ans[((i + 1) + (j + 1)) - 1] = e;
            st.insert(e);
        }
    }

    int f = -1;

    fl(i, 2 * n)
    {
        if (!st.count(i + 1))
        {
            f = i + 1;
            break;
        }
    }

    ans[0] = f;

    print_vector(ans);
}

void r2()
{
    int n, m, l, r;
    cin >> n >> m >> l >> r;

    if (n == m)
    {
        cout << l << " " << r << endl;
        return;
    }

    else
    {
        int diff = n - m;
        int dpos = r, dneg = -l;

        if (diff <= dpos)
        {
            r -= diff;
        }
        else if (diff <= dneg)
        {
            l += diff;
        }
        else
        {
            diff -= r;
            r = 0;
            l += diff;
        }

        cout << l << " " << r << endl;
    }
}

void r3()
{
    string s1, s2, s3;
    cin >> s1 >> s2 >> s3;

    string res;

    res += s1[0];
    res += s2[0];
    res += s3[0];

    cout << res << endl;
}

void r4()
{
    string p, s;
    cin >> p >> s;

    int np = p.size(), ns = s.size();

    int p1 = 0, p2 = 0;

    while (p1 < np and p2 < ns)
    {
        if (p[p1] == 'L')
        {
            int numls1 = 0, numls2 = 0;

            while (p1 < np and p[p1] == 'L')
            {
                numls1++;
                p1++;
            }

            while (p2 < ns and s[p2] == 'L')
            {
                numls2++;
                p2++;
            }

            if ((numls1 * 2) < numls2 || (numls2 < numls1))
            {
                cout << "NO\n";
                return;
            }
        }
        else
        {
            int numls1 = 0, numls2 = 0;

            while (p1 < np and p[p1] == 'R')
            {
                numls1++;
                p1++;
            }

            while (p2 < ns and s[p2] == 'R')
            {
                numls2++;
                p2++;
            }

            if ((numls1 * 2) < numls2 || (numls2 < numls1))
            {
                cout << "NO\n";
                return;
            }
        }
    }

    if (p1 == np and p2 == ns)
        cout << "YES\n";
    else
        cout << "NO\n";
}

void r5()
{
    int n;
    cin >> n;

    vector<ll> v(n);
    input_vector(v);

    ll maxi = *max_element(all(v));
    ll sum = 0;

    vector<int> freq(32, 0);

    fl(i, n)
    {
        fl(j, 32)
        {
            if (((1 << j) & v[i]) != 0)
            {
                freq[j]++;
            }
        }
    }

    fl(i, n)
    {
        ll curr = 0;
        fl(j, 32)
        {
            if (((1 << j) & v[i]) == 0)
            {
                curr += (1 << j) * 1ll * (freq[j]);
            }
            else
            {
                curr += (1 << j) * 1ll * (n - freq[j]);
            }
        }

        sum = max(sum, curr);
    }

    cout << sum << endl;
}

void r7()
{
    int n, m, k;
    cin >> n >> m >> k;

    if (m % k != 0)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                int color = ((i * m + j) % k) + 1;
                cout << color << " ";
            }
            cout << "\n";
        }
    }

    else if (n % k != 0)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                int color = ((j * n + i) % k) + 1;
                cout << color << " ";
            }
            cout << "\n";
        }
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                int color = ((i + j) % k) + 1;
                cout << color << " ";
            }
            cout << "\n";
        }
    }
}

void r8()
{
    int q;
    cin >> q;

    list<ll> v;
    ll sumElems = 0, riz = 0;

    bool reversed = false;

    while (q--)
    {
        int type;
        cin >> type;

        int n = v.size();

        if (type == 1)
        {
            riz += sumElems;

            if (reversed)
            {
                riz -= n * v.front();
                ll first = v.front();
                v.pop_front();
                v.push_back(first);
            }
            else
            {
                riz -= n * v.back();
                ll last = v.back();
                v.pop_back();
                v.insert(v.begin(), last);
            }
        }
        else if (type == 2)
        {
            riz = (n + 1) * 1ll * sumElems - riz;
            reversed = !reversed;
        }
        else
        {
            int k;
            cin >> k;

            if (reversed)
            {
                v.push_front(k);
            }
            else
            {
                v.push_back(k);
            }

            sumElems += k;
            riz += (n + 1) * 1ll * k;
        }

        cout << riz << endl;
    }
}

const int MAXnODES = 1e5 + 20;

ll dptree[MAXnODES][2];

void dphelper(vector<vector<int>> &adj, int node, int par)
{
    dptree[node][0] = 1ll;
    dptree[node][1] = 1ll;

    for (auto i : adj[node])
    {
        if (i == par)
        {
            continue;
        }

        dphelper(adj, i, node);

        dptree[node][0] = (dptree[node][0] * 1ll * (mod_add(dptree[i][0], dptree[i][1]))) % MOD;

        dptree[node][1] = (dptree[node][1] * 1ll * dptree[i][0]) % MOD;
    }
}

void r9()
{
    int n;
    cin >> n;

    vector<vector<int>> adj(n);

    fl(i, n - 1)
    {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dphelper(adj, 0, -1);

    ll ans = mod_add(dptree[0][0], dptree[0][1]);

    cout << ans << endl;
}

int main()
{
    fast_io;

    int t = 1;

    while (t--)
    {
        r9();
    }

    return 0;
}
