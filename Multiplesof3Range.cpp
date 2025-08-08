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

// https://www.codechef.com/problems/MULTQ3
struct Node
{
    vector<ll> modCounts;
    ll lazyInc; // Lazy increment propagation

public:
    Node()
    {
        modCounts.assign(3, 0ll);
        lazyInc = 0;
    }
};

vector<ll> v;
vector<Node> segTree;

// Apply lazy propagation updates
void propagate(int idx, int low, int high)
{
    if (segTree[idx].lazyInc != 0)
    {
        // Shift all values in this range
        if (segTree[idx].lazyInc == 1)
        {
            vector<ll> t = segTree[idx].modCounts;
            for (int i = 0; i < 3; i++)
                segTree[idx].modCounts[i] = t[(i + 1) % 3];
        }
        else
        {
            vector<ll> t = segTree[idx].modCounts;

            segTree[idx].modCounts[0] = t[2];
            segTree[idx].modCounts[1] = t[0];
            segTree[idx].modCounts[2] = t[1];
        }

        // Push lazy update to children if not a leaf
        if (low != high)
        {
            segTree[2 * idx + 1].lazyInc = (segTree[2 * idx + 1].lazyInc + segTree[idx].lazyInc) % 3;
            segTree[2 * idx + 2].lazyInc = (segTree[2 * idx + 2].lazyInc + segTree[idx].lazyInc) % 3;
        }

        // Clear lazy propagation flag
        segTree[idx].lazyInc = 0;
    }
}

// Build the segment tree
void build(int idx, int low, int high)
{
    if (low == high)
    {
        int mod = v[low] % 3;
        segTree[idx].modCounts[mod]++;
        return;
    }

    int mid = (low + high) / 2;
    build(2 * idx + 1, low, mid);
    build(2 * idx + 2, mid + 1, high);

    for (int i = 0; i < 3; i++)
        segTree[idx].modCounts[i] = segTree[2 * idx + 1].modCounts[i] + segTree[2 * idx + 2].modCounts[i];
}

// Range update with lazy propagation
void update(int idx, int low, int high, int l, int r)
{
    propagate(idx, low, high); // Ensure any pending updates are applied

    if (low > r || high < l) // Out of range
        return;

    if (low >= l && high <= r)
    { // Completely inside range
        segTree[idx].lazyInc = (segTree[idx].lazyInc + 1) % 3;
        propagate(idx, low, high);
        return;
    }

    int mid = (low + high) / 2;
    update(2 * idx + 1, low, mid, l, r);
    update(2 * idx + 2, mid + 1, high, l, r);

    for (int i = 0; i < 3; i++)
        segTree[idx].modCounts[i] = segTree[2 * idx + 1].modCounts[i] + segTree[2 * idx + 2].modCounts[i];
}

// Query the number of elements divisible by 3 in range [l, r]
ll query(int idx, int low, int high, int l, int r)
{
    propagate(idx, low, high);

    if (low > r || high < l)
        return 0;

    if (low >= l && high <= r)
        return segTree[idx].modCounts[0];

    int mid = (low + high) / 2;
    return query(2 * idx + 1, low, mid, l, r) + query(2 * idx + 2, mid + 1, high, l, r);
}

void s3()
{
    int n, q;
    cin >> n >> q;

    v.assign(n, 0);
    segTree.resize(4 * n);

    build(0, 0, n - 1);

    // for (auto i : segTree)
    // {
    //     cout << i.modCounts[0] << " ";
    // }
    // cout << endl;

    while (q--)
    {
        int type, l, r;
        cin >> type >> l >> r;

        if (type == 0)
        {
            update(0, 0, n - 1, l, r);
        }
        else
        {
            cout << query(0, 0, n - 1, l, r) << endl;
        }
    }
}

int main()
{
    fast_io;

    int t = 1;
    // cin >> t;

    while (t--)
    {
        s3();
    }

    return 0;
}
