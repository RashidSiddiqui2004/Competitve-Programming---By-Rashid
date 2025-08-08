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

// const int maxn = 1e6 + 2;
// int spf[maxn];

ll getcost(string req, vector<int> tempb, vector<int> tempg, int type)
{
    set<int> b, g;

    int pos = 0;

    for (auto i : req)
    {
        if (i == 'B')
        {
            b.insert(pos++);
        }
        else
        {
            g.insert(pos++);
        }
    }

    vector<int> vb, vg;

    for (auto i : tempb)
    {
        if (!b.count(i))
        {
            vb.push_back(i);
        }
    }

    for (auto i : tempg)
    {
        if (!g.count(i))
        {
            vg.push_back(i);
        }
    }

    int p1 = 0, p2 = 0;

    ll cost = 0;

    while (p1 < (int)vb.size())
    {
        cost += 1ll * pow(abs(vb[p1] - vg[p2]), type);

        p1++, p2++;
    }

    return cost;
}

void s1()
{
    int k;
    cin >> k;

    string s;
    cin >> s;

    int pos = 0;
    int bs = 0;

    vector<int> vb, vg;
    for (auto i : s)
    {
        if (i == 'B')
        {
            bs++;
            vb.push_back(pos++);
        }
        else
        {
            vg.push_back(pos++);
        }
    }

    int n = s.size();
    int gs = n - bs;

    int diff = abs(bs - gs);

    if (diff == 0)
    {
        string req = "";

        for (int i = 0; i < n / 2; i++)
        {
            req += "GB";
        }

        ll cost = getcost(req, vb, vg, k);

        req = "";

        for (int i = 0; i < n / 2; i++)
        {
            req += "BG";
        }

        cost = min(cost, getcost(req, vb, vg, k));

        cout << cost << endl;
    }
    else if (diff == 1)
    {
        string req = "";
        if (bs < gs)
        {
            for (int i = 0; i < n / 2; i++)
            {
                req += "GB";
            }
            req += 'G';
        }
        else
        {
            for (int i = 0; i < n / 2; i++)
            {
                req += "BG";
            }
            req += 'B';
        }

        // cout << req << endl;

        ll cost = getcost(req, vb, vg, k);
        cout << cost << endl;
    }
    else
    {
        cout << -1 << endl;
    }
}

void s2()
{
    int n;
    cin >> n;
    string s;
    cin >> s;

    int p1 = 0, p2 = n - 1;
    int ans = 0;

    vector<bool> v(n, 0);

    while (p1 < p2)
    {
        if (s[p1] == s[p2])
        {
            p1++;
            p2--;
        }
        else
        {
            if (s[p1 + 1] == s[p2] and v[p1] == 0 and v[p1 + 1] == 0 and (p1 + 1) != (p2))
            {
                ans++;
                swap(s[p1], s[p1 + 1]);
                v[p1] = 1;
                v[p1 + 1] = 1;
                p1++;
                p2--;
            }
            else if (s[p1] == s[p2 - 1] and v[p2] == 0 and v[p2 - 1] == 0 and (p1 + 1) != p2)
            {
                ans++;
                v[p2] = 1;
                v[p2 - 1] = 1;
                swap(s[p2], s[p2 - 1]);
                p1++;
                p2--;
            }
            else
            {
                cout << "NO\n";
                return;
            }
        }
    }

    cout << "YES\n";

    cout << ans << endl;
}

ll dfs(vector<vector<int>> &adj, int node, vector<ll> &prof, vector<bool> &vis)
{
    if (adj[node].empty())
    {
        return max(0ll, prof[node]);
    }

    ll maxProf = prof[node];

    vis[node] = 1;

    for (auto i : adj[node])
    {
        if (!vis[i])
            maxProf = max(maxProf, maxProf + dfs(adj, i, prof, vis));
    }

    return maxProf;
}

void s3()
{
    ll n, s;
    cin >> n >> s;
    ll startMoney = s;

    vector<ll> profit(n);
    vector<vector<int>> adj(n);
    vector<int> indegree(n, 0);

    fl(i, n)
    {
        ll a, b;
        cin >> a >> b;
        profit[i] = a;

        if (b != 0)
        {
            adj[b - 1].push_back(i);
            indegree[i]++; // Increase dependency count
        }
    }

    // Min-Heap (max profit first), if equal then lower index first
    priority_queue<pll> pq;

    // Push independent jobs (no prerequisites)
    fl(i, n)
    {
        if (indegree[i] == 0)
        {
            pq.push({profit[i], i});
        }
    }

    ll maxProf = s;

    while (!pq.empty() && s >= 0)
    {
        auto top = pq.top();

        auto pr = top.first, node = top.second;

        pq.pop();

        if ((s + pr) >= 0)
        {
            s += pr;
            maxProf = max(maxProf, s);
            cout << node << " " << maxProf << " ";
        }
        else
        {
            continue;
        }

        // Process dependencies
        for (auto next : adj[node])
        {
            indegree[next]--;        // Reduce dependency count
            if (indegree[next] == 0) // Add only when all dependencies are done
            {
                pq.push({profit[next], next});
            }
        }
    }

    ll finalProfit = maxProf - startMoney;
    cout << finalProfit << endl;
}

void s4()
{
    ll l, r, k;
    cin >> l >> r >> k;

    ll low = 0, high = (r - l + 1), mid, ans = 0;

    while (low <= high)
    {
        mid = (low + high) / 2;
        ll req = (l + mid) * (k);

        if (req <= r)
        {
            ans = mid + 1;
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    cout << ans << endl;
}

void s5()
{
    int n;
    cin >> n;
    string s, r;
    cin >> s >> r;

    int ones = 0, zeros = 0;

    for (auto i : s)
    {
        if (i == '0')
        {
            zeros++;
        }
        else
        {
            ones++;
        }
    }

    for (auto i : r)
    {
        if (zeros == 0 || ones == 0)
        {
            na
        }
        if (i == '0')
        {
            ones--;
        }
        else
        {
            zeros--;
        }
    }

    ha
}

// https://codeforces.com/contest/2029/problem/C
void s6()
{
    //  Note that kevin has to skip at least one contest.

    int n;
    cin >> n;
    vector<ll> v(n);
    input_vector(v);
}

int main()
{
    fast_io;

    int t = 1;
    cin >> t;

    while (t--)
    {
        s6();
    }

    return 0;
}