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

void sol1()
{
    int n;
    cin >> n;

    vector<ll> v(n);

    read_vector(v);

    sort(all(v));

    if (n == 1)
    {
        if (v[0] == 0)
        {
            cout << -1 << endl;
        }
        else
        {
            cout << v[0] << " " << v[0] << endl;
        }
        return;
    }

    ll sum = v[n - 1] * 2, sum2 = 2 * v[0];

    unordered_set<int> st(all(v));

    if (!st.count(sum))
    {
        cout << v[n - 1] << " " << v[n - 1] << endl;
    }
    else if (!st.count(sum2))
    {
        cout << v[0] << " " << v[0] << endl;
    }
    else
    {
        cout << -1 << endl;
    }
}

void sol2()
{
    int n;
    cin >> n;

    string s;
    cin >> s;

    int ones = 0, zeros = 0;
    int ans = 1;

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
        if (ones == zeros)
        {
            ans = ans * 2;
        }
    }

    cout << ans << endl;
}

void sol3()
{
    int n, m;
    cin >> n >> m;

    vector<vector<int>> v(n, vector<int>(m));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> v[i][j];
        }
    }

    int total = n * m;

    int ans = total;

    map<int, int> freq;

    for (int p : {1, -1})
    {
        for (int q : {1, -1})
        {
            freq.clear();

            fl(i, n)
            {
                fl(j, m)
                {
                    int diff = v[i][j] - (i * p + j * q);
                    freq[diff]++;
                }
            }

            int mx = 0;

            for (auto e : freq)
            {
                mx = max(mx, e.second);
            }

            int curr = total - mx;

            ans = min(ans, curr);
        }
    }

    cout << ans << "\n";
}

void sol4()
{
    string s;
    cin >> s;
    int n = s.size();

    int ptr = n - 1;

    while (ptr >= 0 and s[ptr] == '0')
    {
        ptr--;
    }

    int ans = (n - 1 - ptr);

    while (ptr >= 0)
    {
        if (s[ptr] != '0')
        {
            ans++;
        }
        ptr--;
    }

    ans--;

    cout << ans << endl;
}

void sol5()
{
    ll n;
    int k;
    cin >> n >> k;

    if (k > 1)
    {
        if (n == 1)
        {
            if (k == 2)
            {
                cout << "YES\n";
            }
            else
            {
                cout << "NO\n";
            }
        }
        else
        {
            cout << "NO\n";
        }
    }
    else
    {
        if (n == 1)
        {
            cout << "NO\n";
            return;
        }
        for (int i = 2; i <= sqrt(n); i++)
        {
            if ((n % i) == 0)
            {
                cout << "NO\n";
                return;
            }
        }
        cout << "YES\n";
    }
}

typedef long long ll;
typedef pair<int, int> pii;

// Convert (x,y) coordinates to a serial number (d value) based on the ordering.
// Here `level` is such that the grid is of size 2^(level) x 2^(level).
// Base case: level == 1 means the grid is 2x2.
ll solveType1(int level, int x, int y, ll offset = 0)
{
    // Base 2x2 mapping:
    if (level == 1)
    {
        if (x == 0 && y == 0)
            return offset + 1;
        else if (x == 1 && y == 1)
            return offset + 2;
        else if (x == 1 && y == 0)
            return offset + 3;
        else
            return offset + 4;
    }

    // For level > 1, the full grid is 2^level x 2^level.
    // The half–size (side length of each quadrant) is 2^(level-1)
    ll half = 1 << (level - 1);
    // Each quadrant holds quadrantSize = 2^(2*(level-1)) numbers.
    ll quadrantSize = 1LL << (2 * (level - 1));

    // Determine which quadrant the (x,y) point lies in:
    // quadrant 0: bottom-left    (x < half, y < half)
    // quadrant 1: top-right      (x >= half, y >= half)
    // quadrant 2: bottom-right   (x >= half, y < half)
    // quadrant 3: top-left       (x < half, y >= half)
    if (x < half && y < half)
    {
        return solveType1(level - 1, x, y, offset);
    }
    else if (x >= half && y >= half)
    {
        return solveType1(level - 1, x - half, y - half, offset + 1 * quadrantSize);
    }
    else if (x <= half && y >= half)
    {
        return solveType1(level - 1, x, y - half, offset + 3 * quadrantSize);
    }

    return solveType1(level - 1, x - half, y, offset + 2 * quadrantSize);
}

// Inverse mapping: given a number d, return the coordinates (x,y) in the grid.
// The grid is 2^(level) x 2^(level) and the ordering is the inverse of solveType1.
pll solveType2(int level, ll d)
{
    if (level == 1)
    {
        // Base case: 2x2 grid mapping.
        if (d == 1)
            return {0, 0};
        else if (d == 2)
            return {1, 1};
        else if (d == 3)
            return {1, 0};
        else
            return {0, 1};
    }

    ll half = 1 << (level - 1);
    ll quadrantSize = 1LL << (2 * (level - 1));

    // Determine quadrant index (0-based):
    // quadrant 0: bottom-left,
    // quadrant 1: top-right,
    // quadrant 2: bottom-right,
    // quadrant 3: top-left.
    ll quadrant = (d - 1) / quadrantSize;
    ll newd = d - quadrant * quadrantSize; // relative d inside the chosen quadrant

    pll sub = solveType2(level - 1, newd);

    // Adjust coordinates based on quadrant:
    if (quadrant == 0)
    {
        // bottom-left: no change
        return sub;
    }
    else if (quadrant == 1)
    {
        // top-right: add half to both x and y.
        return {sub.first + half, sub.second + half};
    }
    else if (quadrant == 2)
    {
        // bottom-right: add half to x.
        return {sub.first + half, sub.second};
    }
    else // quadrant == 3
    {
        // top-left: add half to y.
        return {sub.first, sub.second + half};
    }
}

void sol6()
{
    int level;
    cin >> level;

    int q;
    cin >> q;

    while (q--)
    {
        string op;
        cin >> op;
        if (op == "->")
        {
            ll x, y;
            cin >> x >> y;
            --x;
            --y;
            cout << solveType1(level, x, y) << "\n";
        }
        else
        {
            ll d;
            cin >> d;
            pii ans = solveType2(level, d);
            cout << ans.first + 1 << " " << ans.second + 1 << "\n";
        }
    }
}

void sol7()
{
    int n, m;
    cin >> n >> m;

    int minOper = 0;

    queue<int> q;
    q.push(m);

    vector<bool> vis(1e5, 0);
    vis[m] = 1;

    while (true)
    {
        int sz = q.size();

        fl(_, sz)
        {
            int top = q.front();
            q.pop();

            if (top == n)
            {
                cout << minOper << endl;
                return;
            }

            if ((top % 2) == 0)
            {
                if (!vis[top / 2])
                {
                    q.push(top / 2);
                    vis[top / 2] = 1;
                }
            }

            if (!vis[top + 1])
            {
                q.push(top + 1);
                vis[top + 1] = 1;
            }
        }

        minOper++;
    }
}

void sol8()
{
    int m, s;
    cin >> m >> s;

    if (s == 0)
    {
        if (m > 1)
            cout << -1 << " " << -1 << endl;
        else
            cout << 0 << " " << 0 << endl;
        return;
    }

    string largest = "";
    int remsum = s;

    if ((m * 9) < s)
    {
        largest = "-1";
    }
    else
    {
        for (int i = 0; i < m; i++)
        {
            if (remsum >= 9)
            {
                remsum -= 9;
                largest += '9';
            }
            else
            {
                largest += ('0' + remsum);
                remsum = 0;
            }
        }
    }

    string smallest = string(m, '0');
    smallest[0] = '1';

    if ((m * 9) < s)
    {
        smallest = "-1";
    }
    else
    {
        remsum = s - 1;
        for (int i = 0; i < m; i++)
        {
            if (remsum >= 9)
            {
                remsum -= 9;
                smallest[m - i - 1] = '9';
            }
            else
            {
                char curr = '0' + remsum;

                if (i == (m - 1))
                {
                    curr = '1' + remsum;
                }

                smallest[m - i - 1] = curr;
                break;
            }
        }
    }

    cout << smallest << " " << largest << endl;
}

const int SIZE = 1e5 + 20;
ll dp[SIZE][3];

ll dpspl(const vector<vector<int>> &grid, int n, int col, int lastRow)
{
    if (col == n)
    {
        return 0;
    }

    ll &ret = dp[col][lastRow + 1];
    if (ret != -1)
    {
        return ret;
    }

    ll ans = 0;

    if (lastRow != 0)
    {
        ans = grid[0][col] + dpspl(grid, n, col + 1, 0);
    }

    if (lastRow != 1)
    {
        ans = max(ans, grid[1][col] + dpspl(grid, n, col + 1, 1));
    }

    ans = max(ans, dpspl(grid, n, col + 1, lastRow));

    return ret = ans;
}

void sol9()
{
    int n;
    cin >> n;

    vector<vector<int>> v(2, vector<int>(n));
    read_vector(v[0]);
    read_vector(v[1]);

    memset(dp, -1, sizeof(dp));

    ll ans = dpspl(v, n, 0, -1);
    cout << ans << endl;
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

    int getParentSize(int x)
    {
        return size[find(x)];
    }
};

void sol10()
{
    int n, m;
    cin >> n >> m;

    DSU dsu(n);

    fl(i, m)
    {
        int sz;
        cin >> sz;
        vector<int> v(sz);
        read_vector(v);

        for (int j = 1; j < sz; j++)
        {
            dsu.unionSets(v[0] - 1, v[j] - 1);
        }
    }

    fl(i, n)
    {
        cout << dsu.getParentSize(i) << " ";
    }
}

vector<ll> generatePowerfulNos()
{
    unordered_set<ll> st;

    // Add factorials
    for (ll fact = 1, i = 1; fact <= 1e12; fact *= ++i)
        st.insert(fact);

    // Add powers of 2
    for (ll pw = 1; pw <= 1e12; pw *= 2)
        st.insert(pw);

    vector<ll> powerfulNos(st.begin(), st.end());
    sort(powerfulNos.begin(), powerfulNos.end());
    return powerfulNos;
}

// Generate all subset sums and track count
void generateSubsets(const vector<ll> &v, vector<pair<ll, int>> &res)
{
    int n = v.size();
    for (int mask = 0; mask < (1 << n); ++mask)
    {
        ll sum = 0;
        int cnt = 0;
        for (int i = 0; i < n; ++i)
        {
            if (mask & (1 << i))
            {
                sum += v[i];
                ++cnt;
            }
        }
        if (sum <= 1e12)
            res.emplace_back(sum, cnt);
    }
}

int findMinCountSumToN(const vector<ll> &powerfulNos, ll n)
{
    int sz = powerfulNos.size();
    int mid = sz / 2;

    vector<ll> left(powerfulNos.begin(), powerfulNos.begin() + mid);
    vector<ll> right(powerfulNos.begin() + mid, powerfulNos.end());

    vector<pair<ll, int>> sumLeft, sumRight;
    generateSubsets(left, sumLeft);
    generateSubsets(right, sumRight);

    // Use a map for fast lookup of minimal counts
    map<ll, int> rightMap;
    for (auto e : sumRight)
    {
        ll sum = e.first;
        int cnt = e.second;
        if (rightMap.count(sum))
            rightMap[sum] = min(rightMap[sum], cnt);
        else
            rightMap[sum] = cnt;
    }

    int ans = INT_MAX;

    for (auto e : sumLeft)
    {
        ll s1 = e.first;
        int c1 = e.second;
        if (s1 > n)
            continue;
        ll rem = n - s1;
        auto it = rightMap.find(rem);
        if (it != rightMap.end())
            ans = min(ans, c1 + it->second);
    }

    return (ans == INT_MAX || ans > 54) ? -1 : ans;
}

void sol11()
{
    int n, k;
    cin >> n >> k;

    vector<vector<int>> adj(n);

    fl(i, n - 1)
    {
        int u, v, x;
        cin >> u >> v >> x;

        if (x == 0)
        {
            adj[u - 1].push_back(v - 1);
            adj[v - 1].push_back(u - 1);
        }
    }

    ll total = mod_pow(n, k);

    vector<int> vis(n, 0);

    queue<int> q;

    for (int i = 0; i < n; i++)
    {
        if (!vis[i])
        {
            q.push(i);
            vis[i] = 1;
            ll currnodes = 1;

            while (!q.empty())
            {
                auto fr = q.front();
                q.pop();

                for (auto &node : adj[fr])
                {
                    if (!vis[node])
                    {
                        currnodes++;
                        vis[node] = 1;
                        q.push(node);
                    }
                }
            }
            total = mod_sub(total, mod_pow(currnodes, k));
        }
    }

    cout << total << endl;
}

void sol12()
{
    int n;
    cin >> n;
    vector<ll> v(n);
    read_vector(v);

    ll smallest = *min_element(all(v));

    for (int i = 0; i < 10 * n; i++)
    {
        ll nextSmallest = LONG_MAX;

        for (int j = 0; j < n; j++)
        {
            if (v[j] == smallest)
            {
                if (smallest % 2 == 0)
                {
                    v[j] = smallest - 1;
                }
                else
                {
                    v[j] = smallest + 1;
                    nextSmallest = min(nextSmallest, v[j]);
                }
            }
            else if (v[j] > smallest)
                nextSmallest = min(nextSmallest, v[j]);
        }

        smallest = nextSmallest;
    }

    print_vector(v);
}

void sol13()
{
    int n, k;
    cin >> n >> k;

    vector<ll> v(n);
    read_vector(v);

    vector<ll> copiedV(all(v));
    sort(all(copiedV), greater<>());

    ll maxScore = 0;
    unordered_set<ll> st;

    fl(i, k)
    {
        maxScore += copiedV[i];
        st.insert(copiedV[i]);
    }

    cout << maxScore << endl;

    int daysLeft = k, prev = 0;

    fl(i, n)
    {
        if (st.count(v[i]))
        {
            if (daysLeft == 1)
            {
                cout << (n - prev) << " ";
                return;
            }
            cout << (i + 1 - prev) << " ";
            daysLeft--;
            prev = i + 1;
        }
    }
}

void sol14()
{
    ll n;
    cin >> n;

    // x = 2^a * b^2

    ll ans = 0;

    for (int i = 1;; i++)
    {
        ll curr = pow(2, i);

        if (curr > 1e18)
        {
            break;
        }

        double lambda = n / curr;

        double sq = sqrt(lambda);

        if ((sq * sq) == lambda)
        {
            lambda++;
        }

        ans += lambda - 1;
    }

    cout << ans << endl;
}

int main()
{
    fast_io;
    int t = 1;
    // cin >> t;

    // vector<ll> powerfulNos = generatePowerfulNos();

    while (t--)
    {
        sol14();
    }

    return 0;
}