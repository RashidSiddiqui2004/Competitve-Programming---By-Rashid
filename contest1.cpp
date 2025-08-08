
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
#define fl(i, n) for (int i = 0; i < n; i++)

// Debugging
#ifndef ONLINE_JUDGE
#define debug(x) cerr << #x << " = " << (x) << endl;
#else
#define debug(x)
#endif

// Utility Functions
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
ll lcm(ll a, ll b) { return a / gcd(a, b) * b; }
ll mod_add(ll a, ll b, ll m = MOD) { return (a + b) % m; }
ll mod_sub(ll a, ll b, ll m = MOD) { return (a - b + m) % m; }
ll mod_mul(ll a, ll b, ll m = MOD) { return (a * b) % m; }
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

class DSU
{
    int n;
    vector<int> parent, rank;

public:
    DSU(int _n) : n(_n)
    {
        parent.resize(n);
        rank.assign(n, 1);
        for (int i = 0; i < n; i++)
        {
            parent[i] = i; // Initialize each node as its own parent
        }
    }

    int find(int u)
    {
        // Path compression: make the parent of all nodes in the path point to the root
        if (parent[u] != u)
        {
            parent[u] = find(parent[u]);
        }
        return parent[u];
    }

    void unionSets(int u, int v)
    {
        int rootU = find(u);
        int rootV = find(v);

        if (rootU != rootV)
        {
            // Union by rank
            if (rank[rootU] < rank[rootV])
            {
                parent[rootU] = rootV;
                rank[rootV] += rank[rootU];
            }
            else if (rank[rootU] > rank[rootV])
            {
                parent[rootV] = rootU;
                rank[rootU] += rank[rootV];
            }
            else
            {
                parent[rootU] = rootV;
                rank[rootV]++;
            }
        }
    }

    void makeDSU(set<pair<int, int>> &edges)
    {
        for (auto i : edges)
        {
            unionSets(i.first, i.second);
        }
    }

    bool isConnected(int u, int v)
    {
        return find(u) == find(v);
    }

    int getNumberOfComponents()
    {
        unordered_set<int> uniqparents;
        for (auto i : parent)
        {
            uniqparents.insert(find(i));
        }
        return (int)uniqparents.size();
    }

    vector<int> getparent()
    {
        for (int i = 0; i < n; i++)
        {
            this->find(i);
        }
        return this->parent;
    }

    unordered_map<int, vector<int>> getComponents()
    {
        getparent();
        unordered_map<int, vector<int>> mp;

        for (int i = 0; i < n; i++)
        {
            mp[parent[i]].push_back(i);
        }

        return mp;
    }
};

// In one operation, you can choose any two indices i and j and swap nums[i] and nums[j]
// if |nums[i] - nums[j]| <= limit.

vector<int> lexicographicallySmallestArray(vector<int> &nums, int limit)
{
    int n = nums.size();
    DSU dsuObj = DSU(n);

    vector<pair<int, int>> vp;

    for (int i = 0; i < n; i++)
    {
        vp.push_back({nums[i], i});
    }

    sort(all(vp));
    int lasttaken = 1;

    for (int i = 0; i < n; i++)
    {
        auto itr = lower_bound(vp.begin(), vp.end(), make_pair(vp[i].first + limit + 1, -1)) - vp.begin();

        // fill indices in the DSU
        for (int j = max(lasttaken, i + 1); j < itr; j++)
        {
            dsuObj.unionSets(vp[i].second, vp[j].second);
        }

        lasttaken = itr;
    }

    auto comp = dsuObj.getComponents();

    for (auto pos : comp)
    {
        vector<int> elems;
        for (auto i : pos.second)
        {
            elems.push_back(nums[i]);
        }

        sort(all(elems));

        int p = 0;
        for (auto i : pos.second)
        {
            nums[i] = elems[p++];
        }
    }

    return nums;
}

void solve()
{
    int n;
    cin >> n;
    vector<ll> a(n), b(n), c(n);

    fl(i, n)
    {
        cin >> a[i];
    }

    fl(i, n)
    {
        cin >> b[i];
    }

    fl(i, n)
    {
        cin >> c[i];
    }

    vector<int> ans(n);
    ans[0] = a[0];

    for (int i = 1; i < n - 1; i++)
    {
        int prev = ans[i - 1];
        if (a[i] != prev)
        {
            ans[i] = a[i];
        }
        else if (b[i] != prev)
        {
            ans[i] = b[i];
        }
        else
        {
            ans[i] = c[i];
        }
    }

    // for n-1
    int prev = ans[n - 2], next = ans[0];
    if (a[n - 1] != prev and a[n - 1] != next)
    {
        ans[n - 1] = a[n - 1];
    }
    else if (b[n - 1] != prev and b[n - 1] != next)
    {
        ans[n - 1] = b[n - 1];
    }
    else
    {
        ans[n - 1] = c[n - 1];
    }

    for (auto i : ans)
    {
        cout << i << " ";
    }

    cout << endl;
}

void solve2()
{
    int n, m;
    cin >> n >> m;

    vector<ll> v(n);

    fl(i, n)
    {
        cin >> v[i];
    }

    set<ll> st;

    for (int i = 0; i < n; i++)
    {
        st.insert(v[i]);
    }

    if (m >= (int)st.size())
    {
        cout << 1 << endl;
        return;
    }

    if (m == 1)
    {
        cout << -1 << endl;
    }
    else
    {
        vector<ll> dist(all(st));
        int sz = dist.size();

        int len = 0;

        for (int i = 0; i < sz; i++)
        {
            int j = 0;

            for (; j < n and (dist[j] == 0); j++)
            {
            }

            int kahatak = m - 1 - (j != 0);
            int last = ((j + kahatak) < sz) ? dist[j + kahatak] : -1;

            for (int k = 0; (k < kahatak) && (j + k) < sz; k++, j++)
            {
                dist[j] = 0;
            }

            while (j < sz)
            {
                dist[j] -= last;
                j++;
            }

            len++;

            bool all0s = true;
            for (auto elem : dist)
            {
                // cout << elem << " ";
                if (elem != 0)
                {
                    all0s = false;
                    break;
                }
            }
            // cout << endl;
            if (all0s)
            {
                break;
            }
        }

        cout << len << endl;
    }
}

int main()
{
    fast_io;
    int t = 1;
    cin >> t; // Uncomment if there are multiple test cases
    while (t--)
    {
        solve2();
    }
    return 0;
}
