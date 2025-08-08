#include <iostream>
#include <bitset>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

#include <bits/stdc++.h>
using namespace std;

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
#define fl(i, start, n) for (int i = start; i < n; i++)
#define loop(i, n) for (int i = 0; i < n; i++)
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

template <class T>
void print(const T &t)
{
    print_single(t);
}

template <class T, class... Args>
void print(const T &t, const Args &...args)
{
    print_single(t, 2);
    print(args...);
}

string readString()
{
    string s;
    cin >> s;
    return s;
}

void printarr(vector<int> &a)
{
    for (auto i : a)
    {
        cout << i << " ";
    }
    cout << endl;
}

// read unweighted undirected/directed graph
vector<vector<ll>>
readUnWeightedGraph(int n, int m, bool isDirected = true)
{
    vector<vector<ll>> g(n);
    fl(i, 0, m)
    {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        g[a].pb(b);
        if (isDirected == false)
            g[b].pb(a);
    }
    return g;
}
// read weighted undirected/directed graph
vector<vector<pll>> readWeightedGraph(int n, int m, bool isDirected = true)
{
    vector<vector<pll>> g(n);
    fl(i, 0, m)
    {
        ll a, b, w;
        cin >> a >> b >> w;
        a--;
        b--;
        g[a].pb({b, w});
        if (isDirected == false)
            g[b].pb({a, w});
    }
    return g;
}

#define khalaas return 0;
#define in1(t) \
    int t;     \
    cin >> t;
#define in2(a, b) \
    int a, b;     \
    cin >> a >> b
#define in3(a, b, c) \
    int a, b, c;     \
    cin >> a >> b >> c
#define in4(a, b, c, d) \
    int a, b, c, d;     \
    cin >> a >> b >> c >> d
#define in5(a, b, c, d, e) \
    ll a, b, c, d, e;      \
    cin >> a >> b >> c >> d >> e
#define in6(a, b, c, d, e, f) \
    ll a, b, c, d, e, f;      \
    cin >> a >> b >> c >> d >> e >> f

#define vecin(v, n) \
    vector<ll> v;   \
    loop(i, 0, n)   \
    {               \
        in1(x);     \
        v.pb(x);    \
    }

typedef priority_queue<int> pq;

typedef unordered_map<char, int> ump;

typedef unordered_set<ll> ust;

typedef priority_queue<int, vector<int>, greater<int>> minh;

typedef priority_queue<int> maxh;

#define TEST   \
    int t = 1; \
    cin >> t;  \
    while (t--)

#define QUERY \
    int q;    \
    cin >> q; \
    while (q--)

#define prec(n) fixed << setprecision(n)

int mod_add(int a, int b, int m)
{
    a %= m;
    b %= m;
    return ((a + b) % m);
}
int mod_sub(int a, int b, int m)
{
    a %= m;
    b %= m;
    return ((a - b) % m);
}
int mod_mul(ll a, ll b, ll m = mod)
{
    a %= m;
    b %= m;
    return ((a * b) % m);
}

// it returns the logarithm of n to the base k
// @param(long long n) the value
// @param(long long k) the base for the logarithm
int lognk(ll n, ll k)
{
    ll ans = log2(n) / log2(k);
    return ans;
}

const ll M = mod;

unsigned long long powerOptimum(unsigned long long x,
                                int y, int p = M)
{
    unsigned long long res = 1;

    x = x % p; // Update x if it is more than or
    // equal to p

    while (y > 0)
    {

        // If y is odd, multiply x with result
        if (y & 1)
            res = (res * x) % p;

        // y must be even now
        y = y >> 1; // y = y/2
        x = (x * x) % p;
    }
    return res;
}

unsigned long long power(unsigned long long x,
                         int y)
{
    unsigned long long res = 1;

    while (y > 0)
    {
        if (y & 1)
            res = (res * x);

        y = y >> 1;
        x = (x * x);
    }
    return res;
}

ll modInverse(ll A)
{
    return (powerOptimum(A, M - 2));
}

unsigned long long factdp[200000 + 1];

ll nCr(ll n, ll r)
{
    ll x = factdp[n - r];
    x = modInverse(x);

    n = factdp[n];
    r = factdp[r];
    r = modInverse(r);

    ll ans = (n * r) % M;
    ans *= x;
    ans %= M;

    return ans;
}

void factorialCalculation()
{
    memset(factdp, -1, sizeof(factdp));
    factdp[0] = 1;
    for (int i = 1; i <= 200000; i++)
        factdp[i] = (factdp[i - 1] * i) % mod;
}

// oh hello!

unordered_map<ll, ll> dp;

ll solve1()
{
    ll n, k;
    cin >> n >> k;
    if (k == 1)
        return n;
    int ans = 0;
    while (n)
    {
        ans += n % k;
        n /= k;
    }
    return ans;
}

void solve2()
{
    // vector<int> v(1000, 1);

    // for (int i = 1; i < 1000; i++)
    // {
    //     for (int j = i; j < 1000; j += i)
    //     {
    //         v[j] = !v[j];
    //     }
    // }
    // for (int i = 1; i < 100; i++)
    // {
    //     cout << v[i];
    // }
    ll k;
    cin >> k;

    ll root = sqrt(k);
    for (;; root++)
    {
        ll curr = pow(root, 2);
        curr += root;
        if (curr > k)
        {
            break;
        }
    }

    --root;
    // cout << "root " << root << endl;
    ll zeros = root;
    ll remones = k - (root) * 1ll * (root + 1);
    ll ans = (root) * 1ll * (root + 1) + zeros + (remones ? 1 : 0);

    ans += remones;
    cout << ans << endl;
}

void solve3()
{
    ll a = 0, b, c, d, pos = 1, bit_b, bit_c, bit_d, mask = 1;
    cin >> b >> c >> d;
    for (ll i = 0; i < 62; i++)
    {
        if (b & mask)
            bit_b = 1;
        else
            bit_b = 0;
        if (c & mask)
            bit_c = 1;
        else
            bit_c = 0;
        if (d & mask)
            bit_d = 1;
        else
            bit_d = 0;
        if ((bit_b && (!bit_c) && (!bit_d)) || ((!bit_b) && bit_c && bit_d))
        {
            pos = 0;
            break;
        }
        if (bit_b && bit_c)
        {
            a += (1ll - bit_d) * mask;
        }
        else
        {
            a += bit_d * mask;
        }
        mask <<= 1;
    }
    if (pos)
    {
        cout << a << "\n";
    }
    else
    {
        cout << -1 << "\n";
    }
}

class DSU
{
private:
    std::vector<int> parent, rank;

public:
    DSU(int n)
    {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++)
        {
            parent[i] = i; // Each node is its own parent initially
        }
    }

    // Path compression optimization for the find operation
    int find(int x)
    {
        if (parent[x] != x)
        {
            parent[x] = find(parent[x]); // Path compression
        }
        return parent[x];
    }

    // Union by rank optimization for the union operation
    void unionSets(int x, int y)
    {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX != rootY)
        {
            // Union by rank
            if (rank[rootX] < rank[rootY])
            {
                parent[rootX] = rootY;
            }
            else if (rank[rootX] > rank[rootY])
            {
                parent[rootY] = rootX;
            }
            else
            {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }
};

void solve4()
{
    ll n, k;
    DSU dsu = DSU(n);
    ll ans = 0;

    unordered_set<ll> leaders;
    vector<vector<int>> marked(n + 1, vector<int>(10, 0));

    for (int i = 0; i < k; i++)
    {
        ll a, d, k;
        cin >> a >> d >> k;
        marked[a][d] = 1;
    }

    for (int i = 1; i < n; i++)
    {
        ll curr = i;
    }
}

void solve5()
{
    int a, b;
    cin >> a >> b;
    int kx, ky, qx, qy;
    cin >> kx >> ky >> qx >> qy;

    vector<pll> dir = {{a, b}, {a, -b}, {-a, b}, {-a, -b}};

    if (a != b)
    {
        for (int i = 0; i < 4; i++)
        {
            dir.push_back({dir[i].second, dir[i].first});
        }
    }

    int ans = 0;

    for (int i = 0; i < (int)dir.size(); i++)
    {
        int nx = kx + dir[i].first, ny = ky + dir[i].second;

        for (int j = 0; j < (int)dir.size(); j++)
        {
            int tx = nx + dir[j].first, ty = ny + dir[j].second;
            if (tx == qx and ty == qy)
            {
                ans++;
                break;
            }
        }
    }

    cout << ans << endl;
}

void solve6()
{
    int n;
    cin >> n;

    vector<pll> v(n);

    fl(i, 0, n)
    {
        cin >> v[i].first;
        v[i].second = i;
    }

    sort(all(v));

    vector<int> ans(n);

    int i = 0;
    int curr = 0;
    ll currsum = 0;

    while (i < n)
    {
        curr = i;
        currsum += v[i].first;
        vector<ll> posi = {v[i].second};
        i++;

        while (i < n and v[i].first <= currsum)
        {
            currsum += v[i].first;
            curr++;
            posi.push_back(v[i].second);
            i++;
        }

        for (auto j : posi)
        {
            ans[j] = curr;
        }
    }

    for (auto i : ans)
    {
        cout << i << " ";
    }

    cout << endl;
}

// gooooood Q on intuition and Binary search

void solve7()
{
    int n, k;
    cin >> n >> k;

    vector<ll> v(n);

    fl(i, 0, n)
    {
        cin >> v[i];
    }

    if (k >= 3)
    {
        cout << 0 << endl;
    }
    else if (k == 1)
    {
        sort(all(v));
        ll ans = *min_element(all(v));

        for (int i = 0; i < n - 1; i++)
        {
            ans = min(ans, v[i + 1] - v[i]);
        }
        cout << ans << endl;
    }
    else
    {
        sort(all(v));
        ll ans = *min_element(all(v));

        for (int i = 0; i < n - 1; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                ll val = abs(v[i] - v[j]);
                ans = min(ans, abs(v[i] - v[j]));
                int low = 0, high = n - 1, currans = -1, mid;

                // just bada element chahiye
                while (low <= high)
                {
                    mid = (low + high) / 2;
                    if (v[mid] < val)
                    {
                        low = mid + 1;
                    }
                    else
                    {
                        high = mid - 1;
                        currans = mid;
                    }
                }
                if (currans != -1)
                {
                    ans = min(ans, abs(val - v[currans]));
                }
                low = 0, high = n - 1, currans = -1, mid;

                // just chota element chahiye
                while (low <= high)
                {
                    mid = (low + high) / 2;
                    if (v[mid] > val)
                    {
                        high = mid - 1;
                    }
                    else
                    {
                        low = mid + 1;
                        currans = mid;
                    }
                }
                if (currans != -1)
                {
                    ans = min(ans, abs(val - v[currans]));
                }
            }
        }

        cout << ans << endl;
    }
}

void solve8()
{
    ll l, r, k;
    cin >> l >> r >> k;
    ll ans = 0;
    ll low = l, high = r, mid;

    while (low <= high)
    {
        mid = (low + high) / 2;
        ll upp = k * mid;
        if (upp <= r)
        {
            low = mid + 1;
            ans = mid;
        }
        else
        {
            high = mid - 1;
        }
    }
    if (ans != 0)
    {
        ans = ans - l + 1;
    }
    cout << ans << endl;
}

void solve9()
{
    int n;
    cin >> n;
    string s, r;
    cin >> s >> r;

    cout << "\ndebug\n";
    string prev = "";

    for (int i = 0, t = 0; i < n - 1 and (t < n); i++)
    {
        char pr = (i == 0) ? s[t] : prev[len(prev) - 1];
        cout << prev << endl;

        if ((prev.size() > 1) and prev[len(prev) - 2] != pr)
        {
            prev.pop_back();
            prev.pop_back();
            prev.push_back(r[i]);
        }
        else
        {
            while (t < (n - 1))
            {
                if (prev.size() > 0 and s[t] != prev[len(prev) - 1])
                {
                    prev.pop_back();
                    t--;
                    break;
                }
                else if (s[t] == s[t + 1])
                {
                    prev += s[t++];
                }
                else
                {
                    break;
                }
            }

            if (t < n - 1)
            {
                t += 2;
                prev.push_back(r[i]);
            }
            else
            {
                cout << "NO\n";
                return;
            }
        }
        cout << t << " ";
    }

    cout << "YES\n";
}

void solve10()
{
    int n, a, b;
    cin >> n >> a >> b;
    int x = 0, y = 0;
    string s;
    cin >> s;
    string curr = s;
    for (int i = 1; i < 100; i++)
    {
        s = s + curr;
    }
    for (auto dir : s)
    {
        if (x == a and y == b)
        {
            cout << "YES\n";
            return;
        }
        if (dir == 'N')
        {
            y += 1;
        }
        else if (dir == 'S')
        {
            y -= 1;
        }
        else if (dir == 'E')
        {
            x += 1;
        }
        else
        {
            x -= 1;
        }
    }
    cout << "NO\n";
}

void solve11()
{
    ll n, b, c;
    cin >> n >> b >> c;

    if (b == 0)
    {
        if (c >= n)
        {
            cout << n << endl;
            return;
        }
        else if (c == n - 1 || c == n - 2)
        {
            cout << n - 1 << endl;
        }
        else
        {
            cout << -1 << endl;
        }
        return;
    }

    if (c >= n)
        cout << n << "\n";
    else
        cout << n - max(0ll, 1 + (n - c - 1) / b) << "\n";
}

void solve12()
{
    ll n, m, v;
    cin >> n >> m >> v;

    vector<ll> a(n), prefsum(n, 0);
    fl(i, 0, n)
    {
        cin >> a[i];
        if (i != 0)
            prefsum[i] = a[i] + prefsum[i - 1];
        else
            prefsum[i] = a[i];
    }

    ll prefcountSatisfied = 0;
    ll curr = 0;

    vector<ll> prf(n, 0), suff(n, 0);

    for (int i = 0; i < n; i++)
    {
        curr += a[i];
        if (curr >= v)
        {
            curr = 0;
            prefcountSatisfied++;
        }
        prf[i] = prefcountSatisfied;
    }

    // for (auto i : prf)
    // {
    //     cout << i << " ";
    // }
    // cout << endl;

    ll suffcountSatisfied = 0;
    curr = 0;

    for (int i = n - 1; i >= 0; i--)
    {
        curr += a[i];
        if (curr >= v)
        {
            curr = 0;
            suffcountSatisfied++;
        }
        suff[i] = suffcountSatisfied;
    }
    // for (auto i : suff)
    // {
    //     cout << i << " ";
    // }
    // cout << endl;

    ll maxi = -1;

    for (int i = 0; i < n; i++)
    {
        ll low = i, high = n - 1, mid, ans = -1;

        while (low <= high)
        {
            mid = (low + high) / 2;
            ll currsatis = ((i == 0) ? 0 : prf[i - 1]) +
                           ((mid == n - 1)
                                ? 0
                                : suff[mid + 1]);
            if (currsatis >= m)
            {
                low = mid + 1;
                ans = mid;
            }
            else
            {
                high = mid - 1;
            }
        }

        if (ans != -1)
        {
            ll curr = prefsum[ans] - ((i == 0) ? 0 : prefsum[i - 1]);
            maxi = max(maxi, curr);
        }
    }

    // for 0 case

    ll currsatis = prf[n - 1];
    if (currsatis >= m)
    {
        maxi = max(maxi, 0ll);
    }

    cout << maxi << endl;
}

signed main()
{

    ll t;
    cin >> t;

    while (t--)
    {
        solve12();
    }

    khalaas
}