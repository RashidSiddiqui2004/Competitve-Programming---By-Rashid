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

// @usage => ./. see div3_2l.cpp for usage

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

void solve1()
{
    int n;
    cin >> n;
    vector<ll> v(n);

    loop(i, n)
    {
        cin >> v[i];
    }

    bool chk = true;
    for (int i = 1; i < n; i++)
    {
        if ((abs(v[i] - v[i - 1]) == 5) || (abs(v[i] - v[i - 1]) == 7))
        {
            continue;
        }
        else
        {
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
}

void sol2()
{
    int n, k;
    cin >> n >> k;

    unordered_map<ll, ll> cost;
    loop(i, k)
    {
        ll b, c;
        cin >> b >> c;
        cost[b] += c;
    }

    vector<ll> t;
    for (auto i : cost)
    {
        t.push_back(i.second);
    }
    sort(all(t), greater<>());
    n = min(n, (int)t.size());
    ll ans = accumulate(t.begin(), t.begin() + n, 0);

    cout << ans << endl;
}

void sol3()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> grid(n, vector<int>(m));

    loop(i, n)
    {
        string s;
        cin >> s;
        loop(j, m)
        {
            grid[i][j] = (s[j] - '0');
        }
    }

    ll ans = 0;
    int top = 0, bottom = n - 1, left = 0, right = m - 1;

    while (top <= bottom && left <= right)
    {
        vector<int> layer;

        for (int j = left; j <= right; ++j)
        {
            layer.push_back(grid[top][j]);
        }
        ++top;

        for (int i = top; i <= bottom; ++i)
        {
            layer.push_back(grid[i][right]);
        }
        --right;

        if (top <= bottom)
        {
            for (int j = right; j >= left; --j)
            {
                layer.push_back(grid[bottom][j]);
            }
            --bottom;
        }

        if (left <= right)
        {
            for (int i = bottom; i >= top; --i)
            {
                layer.push_back(grid[i][left]);
            }
            ++left;
        }
        int lz = layer.size();
        for (int i = 0; i < 3; i++)
        {
            layer.push_back(layer[i]);
        }

        for (int i = 0; i < lz; i++)
        {
            string s = "";
            for (int j = 0; j <= 3; j++)
                s += ('0' + layer[i + j]);
            // cout << s << " ";
            if (s == "1543")
            {
                ans++;
            }
        }
    }
    cout << ans << endl;
}

void sol5()
{
    string s;
    cin >> s;
    int n = s.size();
    ll q;
    cin >> q;

    unordered_set<int> st;
    bool prevans = false;
    for (int i = 0; i < n - 4; i++)
    {
        string curr = "";
        if (i + 3 >= n)
        {
            break;
        }
        for (int j = 0; j < 4; j++)
        {
            curr += s[i + j];
        }
        if (curr == "1100")
        {
            st.insert(i);
        }
    }
    if (st.size() > 0)
    {
        prevans = true;
    }
    while (q--)
    {
        int i;
        char val;
        cin >> i;
        cin >> val;
        --i;

        if (n <= 3)
        {
            cout << "NO\n";
        }

        else
        {
            if (s[i] == val)
            {
                if (prevans)
                {
                    cout << "YES\n";
                }
                else
                {
                    cout << "NO\n";
                }
                continue;
            }

            if (s[i] == '0')
            {
                string prev = "", next = "";
                if ((i - 2) >= 0 and (i + 1) < n)
                {
                    prev += s[i - 2];
                    prev += s[i - 1];
                    next += s[i + 1];
                    if ((prev == "11") and (next == "0"))
                    {
                        st.erase(i - 2);
                    }
                }
                if ((i - 3) >= 0)
                {
                    prev = "";
                    prev += s[i - 3];
                    prev += s[i - 2];
                    prev += s[i - 1];
                    if (prev == "110")
                    {
                        st.erase(i - 3);
                    }
                }
            }
            else if (s[i] == '1')
            {
                string prev = "", next = "";
                if ((i - 1) >= 0 and (i + 2) < n)
                {
                    prev = "", next = "";
                    prev += s[i - 1];
                    next += s[i + 1];
                    next += s[i + 2];
                    if (prev == "1" and next == "00")
                    {
                        st.erase(i - 1);
                    }
                }
                if ((i + 3) < n)
                {
                    next = "";
                    next += s[i + 1];
                    next += s[i + 2];
                    next += s[i + 3];
                    if (next == "100")
                    {
                        st.erase(i);
                    }
                }
            }

            s[i] = val;
            string curr = "";

            if (val == '0')
            {
                if ((i - 2 >= 0) and ((i + 1) < n))
                {
                    curr = "";
                    curr += s[i - 2];
                    curr += s[i - 1];
                    curr += s[i];
                    curr += s[i + 1];
                    if (curr == "1100")
                    {
                        st.insert(i - 2);
                    }
                }
                if ((i - 3) >= 0)
                {
                    curr = "";
                    curr += s[i - 3];
                    curr += s[i - 2];
                    curr += s[i - 1];
                    curr += s[i];
                    if (curr == "1100")
                    {
                        st.insert(i - 3);
                    }
                }
            }
            else
            {
                curr = "";
                if ((i + 3) < n)
                {
                    curr += s[i];
                    curr += s[i + 1];
                    curr += s[i + 2];
                    curr += s[i + 3];
                    if (curr == "1100")
                    {
                        st.insert(i);
                    }
                }

                curr = "";
                if ((i - 1) >= 0 and (i + 2) < n)
                {
                    curr += s[i - 1];
                    curr += s[i];
                    curr += s[i + 1];
                    curr += s[i + 2];
                    if (curr == "1100")
                    {
                        st.insert(i - 1);
                    }
                }
            }

            bool ans = ((int)st.size() > 0);

            if (ans)
            {
                prevans = true;
                cout << "YES\n";
            }
            else
            {
                prevans = false;
                cout << "NO\n";
            }
        }
    }
}

void sol6()
{
    string s;
    cin >> s;
    int n = s.size();
    ll q;
    cin >> q;

    unordered_set<int> st;

    auto checkPattern = [&](int i)
    {
        return (i >= 0 && i + 3 < n && s.substr(i, 4) == "1100");
    };

    for (int i = 0; i <= n - 4; i++)
    {
        if (checkPattern(i))
        {
            st.insert(i);
        }
    }

    bool prevans = !st.empty();

    while (q--)
    {
        int i;
        char val;
        cin >> i >> val;
        --i;

        if (n < 4)
        {
            cout << "NO\n";
            continue;
        }

        if (s[i] == val)
        {
            cout << (prevans ? "YES\n" : "NO\n");
            continue;
        }

        for (int j = max(0, i - 3); j <= i && j <= n - 4; j++)
        {
            if (checkPattern(j))
            {
                st.erase(j);
            }
        }

        s[i] = val;

        for (int j = max(0, i - 3); j <= i && j <= n - 4; j++)
        {
            if (checkPattern(j))
            {
                st.insert(j);
            }
        }

        prevans = !st.empty();
        cout << (prevans ? "YES\n" : "NO\n");
    }
}

void solve8()
{
    int n, k, q;
    cin >> n >> k >> q;

    vector<vector<ll>> v(n, vector<ll>(k));

    loop(i, n)
    {
        loop(j, k)
        {
            cin >> v[i][j];
        }
    }

    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < k; j++)
        {
            v[i][j] |= v[i - 1][j];
        }
    }

    ll maxi = 1e9 + 2;
    map<int, pll> req;

    while (q--)
    {
        int m;
        cin >> m;
        ll r, c;
        char o;

        req.clear();

        while (m--)
        {
            cin >> r;
            cin >> o;
            cin >> c;
            --r;

            ll prevf = 0;
            ll prevs = maxi;

            if (req.count(r))
            {
                prevf = req[r].first;
                prevs = req[r].second;
            }

            if (o == '<')
            {
                req[r] = {prevf, min(c, prevs)};
            }
            else
            {
                req[r] = {max(c, prevf), prevs};
            }
        }

        bool isposs = true;
        for (auto i : req)
        {
            if (i.second.first >= i.second.second)
            {
                cout << -1 << endl;
                isposs = false;
                continue;
            }
        }

        if (!isposs)
        {
            continue;
        }

        ll low = 0, high = n - 1;
        ll mid, ans = -1;

        while (low <= high)
        {
            mid = (low + high) / 2;
            bool poss = true;
            for (auto i : req)
            {
                if ((v[mid][i.first] <= i.second.first) || (v[mid][i.first] >= i.second.second))
                {
                    poss = false;
                    break;
                }
            }
            if (poss)
            {
                ans = mid;
                high = mid - 1;
            }
            else
            {
                low = mid + 1;
            }
        }
        if (ans == -1)
        {
            cout << ans << endl;
        }
        else
        {
            cout << ans + 1 << endl;
        }
    }
}

void solve9()
{
    int n, k;
    cin >> n >> k;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < k; j++)
        {
            char ch = 'a' + j;
            cout << ch;
        }
    }
    cout << endl;
}

void sovle10()
{
    // x,n
    // divide x into n subproblems (smaller integers > 0) such that
    // gcd(x1,x2,.....) maximizes

    // x=12, n=2 => {6,6}
    // x=12, n=3 => {4,4,4}
    // x=16, n=3 => {4,4,8}
    // x=17, n=3 => {5,5,7}
    // x=420 n=69

    int x, n;
    cin >> x >> n;

    if (x == n)
    {
        cout << 1 << endl;
        return;
    }
    else if (n > x)
    {
        cout << -1 << endl;
        return;
    }

    // gcd will always be a factor of x
    int ans = 1;
    for (int i = 1; i * i <= x; i++)
    {
        if (x % i == 0)
        {
            if (n <= (x / i))
                ans = max(ans, i);
            if (n <= i)
                ans = max(ans, x / i);
        }
    }
    cout << ans << '\n';
}

// avoid eye contact
// https://atcoder.jp/contests/abc317/tasks/abc317_e

void sol10()
{
    int n, m;
    cin >> n >> m;

    vector<string> grid(n);

    loop(i, n)
    {
        cin >> grid[i];
    }
    int startx, starty, goalx, goaly;
    // 1=> free, 0 => obstacle
    vector<vector<int>> obs(n, vector<int>(m, 1));

    loop(i, n)
    {
        loop(j, m)
        {
            if (grid[i][j] == 'S')
            {
                startx = i;
                starty = j;
            }
            else if (grid[i][j] == 'G')
            {
                goalx = i;
                goaly = j;
            }
            else if (grid[i][j] == '>')
            {
                obs[i][j] = 0;
                for (int k = j + 1; k < m; k++)
                {
                    if (grid[i][k] != '.')
                    {
                        break;
                    }
                    obs[i][k] = 0;
                }
            }
            else if (grid[i][j] == '<')
            {
                obs[i][j] = 0;
                for (int k = j - 1; k >= 0; k--)
                {
                    if (grid[i][k] != '.')
                    {
                        break;
                    }
                    obs[i][k] = 0;
                }
            }
            else if (grid[i][j] == '^')
            {
                obs[i][j] = 0;
                for (int k = i - 1; k >= 0; k--)
                {
                    if (grid[k][j] != '.')
                    {
                        break;
                    }
                    obs[k][j] = 0;
                }
            }
            else if (grid[i][j] == 'v')
            {
                obs[i][j] = 0;
                for (int k = i + 1; k < n; k++)
                {
                    if (grid[k][j] != '.')
                    {
                        break;
                    }
                    obs[k][j] = 0;
                }
            }
            else if (grid[i][j] == '#')
            {
                obs[i][j] = 0;
            }
        }
    }

    // bfs lga do

    int dx[] = {0, 0, 1, -1}, dy[] = {1, -1, 0, 0};

    queue<pair<int, int>> q;
    q.push({startx, starty});

    int ans = 0;

    while (!q.empty())
    {
        int qsize = q.size();

        for (int i = 0; i < qsize; i++)
        {
            auto fr = q.front();
            int x = fr.first, y = fr.second;
            q.pop();

            if (x == goalx and y == goaly)
            {
                cout << ans;
                return;
            }

            for (int j = 0; j < 4; j++)
            {
                int newx = x + dx[j], newy = y + dy[j];
                if (newx >= 0 and newy >= 0 and newx < n and newy < m and obs[newx][newy])
                {
                    q.push({newx, newy});
                    obs[newx][newy] = 0;
                }
            }
        }

        ans++;
    }

    cout << -1 << endl;
}

void sol11()
{
    int n;
    cin >> n;

    int ans = n / 4;
    n -= (ans * 4);
    ans += (n / 2);

    cout << ans << endl;
}

void sol12()
{
    int n, q;
    cin >> n >> q;

    string a, b;
    cin >> a >> b;

    vector<vector<int>> f1(26, vector<int>(n, 0)), f2(26, vector<int>(n, 0));

    int pos = 0;
    for (auto i : a)
    {
        f1[i - 'a'][pos]++;
        pos++;
    }

    pos = 0;
    for (auto i : b)
    {
        f2[i - 'a'][pos]++;
        pos++;
    }

    for (int i = 0; i < 26; i++)
    {
        for (int j = 1; j < n; j++)
        {
            f1[i][j] += f1[i][j - 1];
            f2[i][j] += f2[i][j - 1];
        }
    }

    while (q--)
    {

        int l, r;
        cin >> l >> r;
        --l, --r;

        ll ans = 0;

        for (int i = 0; i < 26; i++)
        {
            ll freq1 = f1[i][r] - ((l == 0) ? 0 : f1[i][l - 1]);
            ll freq2 = f2[i][r] - ((l == 0) ? 0 : f2[i][l - 1]);
            ans += abs(freq1 - freq2);
        }

        ans /= 2;

        cout << ans << endl;
    }
}

bool isposs(int n, multiset<ll> a, multiset<ll> b, ll mid)
{
    for (auto i : a)
    {
        auto it = b.upper_bound(i - mid);
        if (it != b.begin())
        {
            --it;
            b.erase(it);
        }
        else
        {
            it = b.lower_bound(i + mid);
            if (it != b.end())
            {
                b.erase(it);
            }
            else
            {
                return false;
            }
        }
    }

    return true;
}

void sol13()
{
    int n;
    cin >> n;

    multiset<ll> a, b;

    loop(i, n)
    {
        ll e;
        cin >> e;
        a.insert(e);
    }
    loop(i, n)
    {
        ll e;
        cin >> e;
        b.insert(e);
    }

    ll low = 0, high = INT_MAX, ans = -1, mid;

    while (low <= high)
    {
        mid = (low + high) / 2;

        bool chk = isposs(n, a, b, mid);
        if (chk)
        {
            ans = mid;
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
        cout << mid << " " << chk << endl;
    }

    cout << ans << endl;
}

signed main()
{
    // factorialCalculation();
    ll t;
    cin >> t;

    while (t--)
    {
        sol13();
    }

    khalaas
}