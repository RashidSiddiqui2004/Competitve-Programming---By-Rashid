#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

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

#define inputvector(v) \
    for (auto &i : v)  \
    {                  \
        cin >> i;      \
    }

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

bool isposs(ll n, vector<ll> &v, ll x, ll mid)
{
    vector<pair<ll, ll>> mp(n);
    fl(i, n)
    {
        mp[i] = {v[i] - mid, v[i] + mid};
    }
    ll prev = mp[0].second + x;
    bool tmp = 1;
    for (int i = 1; i < n; i++)
    {
        prev = min(prev, mp[i].second);
        if (prev < mp[i].first || prev > mp[i].second)
        {
            return 0;
        }
        prev += x;
    }
    return 1;
}

void solve1()
{
    ll n, x;
    cin >> n >> x;

    vector<ll> b(n);
    inputvector(b);

    ll low = 0, high = 1e9, mid, ans = -1;

    while (low <= high)
    {
        mid = (low + high) / 2;
        if (isposs(n, b, x, mid))
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
    vector<pair<ll, ll>> mp(n);

    fl(i, n)
    {
        mp[i] = {b[i] - ans, b[i] + ans};
    }

    ll prev = mp[0].second + x;
    cout << prev - x << ' ';

    for (int i = 1; i < n; i++)
    {
        prev = min(prev, mp[i].second);
        cout << prev << ' ';
        prev += x;
    }
    cout << '\n';
}

// https://www.codechef.com/problems/PREPER?tab=statement

void sol2()
{
    ll n, x;
    cin >> n >> x;

    vector<ll> v(n);

    inputvector(v);

    int ans = 1;

    fl(i, n)
    {
        ll prev = v[i];
        int len = 1;
        bool used = false;
        for (int j = i + 1; j < n; j++)
        {

            if (v[j] < prev)
            {
                ll ch = v[j] * x;
                if (ch >= prev and !used)
                {
                    len++;
                    used = true;
                    ans = max(ans, len);
                    prev = ch;
                }
                else
                {
                    break;
                }
            }
            else
            {
                prev = v[j];
                len++;
                ans = max(ans, len);
            }
        }
    }

    cout << ans << endl;
}

void sol3()
{
    string a, b;
    cin >> a >> b;

    int n = a.size(), m = b.size();
    int p1 = m - 1;

    vector<int> mark(n, false);

    for (int i = n - 1; i >= 0 and p1 >= 0; i--)
    {
        if (a[i] == b[p1])
        {
            mark[i] = true;
            p1--;
        }
    }

    if (p1 == -1)
    {
        ll ans = 0;
        int p = 1;
        for (int i = 0; i < n; i++)
        {
            if (mark[i])
            {
                p++;
            }
            else
            {
                ans += p;
            }
        }
        cout << ans << endl;
    }
    else
    {
        cout << -1 << endl;
    }
}

void sol4()
{
    int n;
    cin >> n;
    vector<int> v(n);

    fl(i, n)
    {
        cin >> v[i];
    }

    ll q;
    cin >> q;

    int prevans = v[0];

    if (n > 1)
    {
        prevans &= v[1];
    }

    if (n > 2)
    {
        prevans |= v[2];
    }

    if (n > 3)
    {
        prevans &= v[3];
    }

    set<int> odds, evens;

    for (int i = 0; i < n; i++)
    {
        if ((i % 2) != 0)
        {
            if (v[i] == 0)
            {
                evens.insert(i);
            }
        }
        else
        {
            if (v[i])
            {
                odds.insert(i);
            }
        }
    }

    fl(i, q)
    {
        int pos, val;
        cin >> pos >> val;
        pos--;
        v[pos] = val;

        if ((pos % 2) != 0)
        {
            if (v[pos] == 0)
            {
                evens.insert(pos);
            }
            else if (evens.count(pos))
            {
                evens.erase(pos);
            }
        }
        else
        {
            if (v[pos] == 1)
            {
                odds.insert(pos);
            }
            else if (odds.count(pos))
            {
                odds.erase(pos);
            }
        }

        if ((n % 2 == 0) and v[n - 1] == 0)
        {
            cout << 0 << endl;
            continue;
        }

        else if ((n % 2 != 0) and v[n - 1] == 1)
        {
            cout << 1 << endl;
            continue;
        }

        if (odds.empty())
        {
            cout << 0 << endl;
            continue;
        }

        int it = *odds.rbegin();

        auto e2 = evens.lower_bound(it);

        if (e2 == evens.end())
        {
            cout << 1 << endl;
        }
        else
        {
            cout << 0 << endl;
        }
    }
}

void solv6()
{
    int n, k;
    cin >> n >> k;
    vector<ll> v(n);
    inputvector(v);
    int len = n - k;
    int totalChosen = len / 2 + (len & 1);
    multiset<int> chosen, rest;
    ll sumChosen = 0;
    vector<bool> removed(n + 1, false);
    for (int i = 0; i < k; i++)
        removed[v[i]] = true;

    multiset<int> avail;
    for (int i = 1; i <= n; i++)
    {
        if (!removed[i])
            avail.insert(i);
    }

    for (int i = 0; i < totalChosen && !avail.empty(); i++)
    {
        auto it = avail.begin();
        chosen.insert(*it);
        sumChosen += *it;
        avail.erase(it);
    }
    rest = move(avail);
    auto getSum = [&]() -> ll
    {
        if (len & 1)
            return 2 * sumChosen - *chosen.rbegin();
        return 2 * sumChosen;
    };
    ll ans = getSum();
    auto balance = [&]()
    {
        if (chosen.size() < (size_t)totalChosen && !rest.empty())
        {
            auto it = rest.begin();
            chosen.insert(*it);
            sumChosen += *it;
            rest.erase(it);
        }
        if (!chosen.empty() && !rest.empty() && *rest.begin() < *chosen.rbegin())
        {
            int cand = *rest.begin();
            int last = *chosen.rbegin();
            chosen.erase(prev(chosen.end()));
            sumChosen -= last;
            rest.erase(rest.begin());
            chosen.insert(cand);
            sumChosen += cand;
            rest.insert(last);
        }
    };
    auto addAvail = [&](int x)
    {
        rest.insert(x);
        balance();
    };
    auto removeAvail = [&](int x)
    {
        auto it = chosen.find(x);
        if (it != chosen.end())
        {
            chosen.erase(it);
            sumChosen -= x;
            if (!rest.empty())
            {
                auto itR = rest.begin();
                chosen.insert(*itR);
                sumChosen += *itR;
                rest.erase(itR);
            }
        }
        else
        {
            auto itR = rest.find(x);
            if (itR != rest.end())
                rest.erase(itR);
        }
    };
    for (int i = k; i < n; i++)
    {
        int temp = v[i - k];
        int bll = v[i];
        addAvail(temp);
        removeAvail(bll);
        ans = max(ans, getSum());
    }
    cout << ans << endl;
}

void sol7()
{
    ll n, k;
    cin >> n >> k;

    vector<ll> v(k);

    inputvector(v);
    ll ans = 0;

    ll rem = factorial[n - k];

    for (int i = 1; i < v[0]; i++)
    {
        int prev = v[0] - i;
        // cout << "t: " << prev << " ";
        unordered_set<int> st;
        st.insert(i);
        st.insert(prev);
        bool poss = true;

        for (int j = 1; j < k - 1; j++)
        {
            int next = v[j] - prev;
            if (st.count(next) || next <= 0)
            {
                poss = false;
                break;
            }
            st.insert(next);
            // cout << next << " ";
            prev = next;
        }

        if (poss)
        {
            int next = v[k - 1] - prev;
            // cout << endl;
            // cout << i << " " << next << endl;
            if (next <= 0)
            {
                continue;
            }
            if (i == next)
            {
                ans += rem % MOD;
            }
        }
    }

    ans %= MOD;
    cout << ans << endl;
}

void sol8()
{
    int x, y;
    cin >> x >> y;

    if (x > y)
    {
        cout << 0 << " " << 0 << endl;
    }
    else if (x == y)
    {
        cout << 1 << " " << 1 << endl;
    }
    else
    {
        int q = y / x;
        int obx = q * x;
        if (obx == y)
        {
            cout << 1 << " " << q << endl;
        }
        else
        {
            cout << 0 << " " << 0 << endl;
        }
    }
}

void sol9()
{
    string s, t;
    cin >> s >> t;

    if (t == "a")
    {
        cout << 1 << endl;
    }
    else
    {
        if (t.find('a') == string::npos)
        {
            int n = s.size();
            ll ans = pow(2, n);
            cout << ans << endl;
        }
        else
        {
            cout << -1 << endl;
        }
    }
}

int dp[1001][1001];

int helper(vector<pll> &gifts, int pos, int currMoney)
{
    int n = gifts.size();

    if (pos == n)
    {
        return 0;
    }

    int *ans = &dp[pos][currMoney];

    if (*ans != -1)
    {
        return *ans;
    }

    int nextGap = 0;

    if ((pos + 1) < n)
    {
        nextGap = gifts[pos + 1].first - gifts[pos].first;
    }

    int take = (currMoney >= gifts[pos].second) ? 1 + helper(gifts, pos + 1, (currMoney - gifts[pos].second) + nextGap) : 0;

    int notTake = helper(gifts, pos + 1, currMoney + nextGap);

    return *ans = max(take, notTake);
}

void sol10()
{
    int n;
    cin >> n;

    vector<pll> gifts(n);

    fl(i, n)
    {
        cin >> gifts[i].first >> gifts[i].second;
    }

    // sorting in ascending order by gift date
    sort(all(gifts), [](pll &p1, pll &p2)
         {
        if(p1.first != p2.first){
            p1.first < p2.first;
        }
        
        return p1.second < p2.second; });

    // {day} => 2 choices => buy or no buy

    // dp[pos][money]
    // n <= 1e3, maxDuration or max(gifts[i].first) <= 1e3

    memset(dp, -1, sizeof(dp));

    int currMoney = gifts[0].first;

    int ans = helper(gifts, 0, currMoney);

    cout << "Maximum gifts to give to nephew are: " << ans << endl;
}

void sol11()
{
    int n, l, r;
    cin >> n >> l >> r;

    vector<ll> a(n);
    inputvector(a);

    vector<ll> subarr;
    --l, --r;

    for (int i = l; i <= r; i++)
    {
        subarr.push_back(a[i]);
    }

    sort(all(subarr), greater<>());

    ll origSum = accumulate(all(subarr), 0ll);

    // behind l [0....l-1]

    vector<ll> behind;

    for (int i = 0; i < l; i++)
    {
        behind.push_back(a[i]);
    }

    sort(all(behind));

    ll sumbehind = origSum;

    int ptr = 0;

    for (auto i : behind)
    {
        if (ptr == subarr.size())
        {
            break;
        }
        if (subarr[ptr] > i)
        {
            sumbehind += (i - subarr[ptr]);
            ptr++;
        }
        else
        {
            break;
        }
    }

    ll res = sumbehind;

    // after [r+1....n-1]

    vector<ll> after;
    for (int i = r + 1; i < n; i++)
    {
        after.push_back(a[i]);
    }

    sort(all(after));

    ll sumAfter = origSum;

    ptr = 0;

    for (auto i : after)
    {
        if (ptr == subarr.size())
        {
            break;
        }
        if (subarr[ptr] > i)
        {
            sumAfter += (i - subarr[ptr]);
            ptr++;
        }
        else
        {
            break;
        }
    }

    res = min(res, sumAfter);

    cout << res << endl;
}

// 1-2-3
//   |
//   4

void removeOptimalNode(vector<unordered_set<ll>> &adj)
{
    int maxConnNode = -1, maxConn = 0;
    int n = adj.size();

    for (int i = 0; i < n; i++)
    {
        int sz = adj[i].size();
        if (sz > maxConn)
        {
            maxConn = sz;
            maxConnNode = i;
        }
    }

    auto temp = adj[maxConnNode];
    vector<ll> v(all(temp));

    for (auto neigh : v)
    {
        adj[maxConnNode].erase(neigh);
    }
}

void dfs(vector<unordered_set<ll>> &adj, int node, int par, vector<int> &vis)
{
    if (adj[node].size() == 0)
    {
        return;
    }

    vis[node] = true;

    for (auto i : adj[node])
    {
        if (!vis[i])
            dfs(adj, i, node, vis);
    }
}

void connect()
{
    int n;
    cin >> n;

    vector<unordered_set<ll>> adj(n);

    fl(i, n - 1)
    {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].insert(v);
        adj[v].insert(u);
    }

    if (n <= 2)
    {
        cout << 0 << endl;
        return;
    }

    removeOptimalNode(adj);
    removeOptimalNode(adj);

    vector<int> vis(n, 0);
    int ans = 0;

    fl(i, n)
    {
        if (vis[i] == 0)
        {
            ans++;
            dfs(adj, i, -1, vis);
        }
    }

    ans -= 2;

    cout << ans << endl;
}

void moviesfestival()
{
    ll n;
    cin >> n;

    vector<pll> v(n);

    fl(i, n)
    {
        cin >> v[i].first >> v[i].second;
    }

    sort(all(v), [](pll &p1, pll &p2)
         {
        if(p1.second != p2.second){
            return p1.second < p2.second;
        }  
        return p1.first < p2.first; });

    multiset<ll> st;

    ll maxMovies = 0;

    st.insert(0);

    for (auto i : v)
    {
        ll startTime = i.first, endTime = i.second;

        auto fr = st.upper_bound(startTime);

        if (fr == st.begin())
        {
            continue;
        }
        else
        {
            --fr;
            st.erase(fr);
            st.insert(endTime);
            maxMovies++;
        }
    }

    cout << maxMovies << endl;
}

void moviesfestival2()
{
    ll n, remPeople;
    cin >> n >> remPeople;

    vector<pll> v(n);

    fl(i, n)
    {
        cin >> v[i].first >> v[i].second;
    }

    sort(all(v), [](pll &p1, pll &p2)
         {
        if(p1.second != p2.second){
            return p1.second < p2.second;
        }  
        return p1.first < p2.first; });

    multiset<ll> st;

    ll maxMovies = 0;

    for (int i = 0; i < remPeople; i++)
        st.insert(0);

    for (auto i : v)
    {
        ll startTime = i.first, endTime = i.second;

        auto fr = st.upper_bound(startTime);

        if (fr == st.begin())
        {
            continue;
        }
        else
        {
            --fr;
            st.erase(fr);
            st.insert(endTime);
            maxMovies++;
        }
    }

    cout << maxMovies << endl;
}

void slidingWindowMedian()
{
    ll n, k;
    cin >> n >> k;

    vector<ll> v(n);
    for (ll &x : v)
        cin >> x;

    ordered_set<pair<ll, int>> st; // Store (value, index) to handle duplicates

    for (int i = 0; i < k; i++)
    {
        st.insert({v[i], i});
    }

    auto medianIterator = st.find_by_order((k - 1) / 2); // Get median

    cout << medianIterator->first << " ";

    for (int i = k; i < n; i++)
    {
        st.erase({v[i - k], i - k});
        st.insert({v[i], i});

        auto medianIterator = st.find_by_order((k - 1) / 2);

        cout << medianIterator->first << " ";
    }
    cout << endl;
}

void slidingWindowCost()
{
    ll n, k;
    cin >> n >> k;

    vector<ll> v(n);
    for (ll &x : v)
        cin >> x;

    ordered_set<pair<ll, int>> st; // Store (value, index) to handle duplicates

    for (int i = 0; i < k; i++)
    {
        st.insert({v[i], i});
    }

    ll midIndex = (k - 1) / 2;

    for (int i = k; i <= n; i++)
    {
        auto medianIt = st.find_by_order(midIndex);
        ll median = medianIt->first;

        // Compute cost
        ll cost = 0;
        for (auto it = st.begin(); it != st.end(); it++)
        {
            cost += abs(it->first - median);
        }

        cout << cost << " ";

        if (i < n)
        {
            st.erase({v[i - k], i - k});
            st.insert({v[i], i});
        }
    }
    cout << endl;
}

int main()
{
    fast_io;
    // precompute_factorials(1e5 + 100);

    int t = 1;

    while (t--)
    {
        slidingWindowCost();
    }

    return 0;
}
