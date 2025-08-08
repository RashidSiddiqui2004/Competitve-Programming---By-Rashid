
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

void r2()
{
    ll n, d;
    cin >> n >> d;

    vector<ll> a(n), b(n);
    fl(i, n)
    {
        cin >> a[i];
    }
    fl(i, n)
    {
        cin >> b[i];
    }

    vector<ll> ans(n, LLONG_MAX);

    for (int i = 1; i < n; i++)
    {
        if (a[i] < a[i - 1] || b[i] > b[i - 1])
        {
            cout << "NO" << endl;
            return;
        }
    }

    if (a[0] == b[0])
    {
        ans[0] = a[0];
    }
    else
    {
        cout << "NO\n";
        return;
    }

    for (int i = 1; i < n; i++)
    {
        if (a[i] != a[i - 1])
        {
            ans[i] = a[i];
        }
    }

    ll mini = ans[0];

    for (int i = 1; i < n; i++)
    {
        if (b[i] != b[i - 1])
        {
            if (ans[i] == LLONG_MAX)
                ans[i] = b[i];
            else
            {
                cout << "NO\n";
                return;
            }
        }
        mini = min(ans[i], mini);
        if (b[i] != mini)
        {
            cout << "NO\n";
            return;
        }
    }

    // for (auto i : ans)
    // {
    //     cout << i << " ";
    // }
    // cout << endl;

    for (int i = 1; i < n;)
    {
        while (i < n and ans[i] != LLONG_MAX)
        {
            i++;
        }

        if (i != n)
        {

            int j = i;

            while (j < n and ans[j] == LLONG_MAX)
            {
                j++;
            }

            // cout << i << " " << j << endl;

            if (j != n || (ans[n - 1] == LLONG_MAX))
            {
                j = n - 1;
                ll diff = (j == (n - 1)) ? 0 : abs(ans[j] - ans[i]);
                if (diff <= d)
                {
                    for (int p = i; p <= j; p++)
                    {
                        ans[p] = ans[i - 1];
                    }
                }
                else
                {
                    cout << "NO\n";
                    return;
                }
            }
        }
    }

    // for (auto i : ans)
    // {
    //     cout << i << " ";
    // }
    // cout << endl;

    ll maxi = ans[0];
    mini = ans[0];
    for (int i = 1; i < n; i++)
    {
        maxi = max(maxi, ans[i]);
        mini = min(mini, ans[i]);
        if (maxi != a[i] || mini != b[i])
        {
            cout << "NO\n";
            return;
        }
        ll diff = abs(a[i] - a[i - 1]);
        if (diff > d)
        {
            cout << "NO\n";
            return;
        }
    }

    cout << "YES\n";
    for (auto i : ans)
    {
        cout << i << " ";
    }
    cout << endl;
}

void r3()
{
    int n;
    cin >> n;
    vector<ll> a(n), b(n);
    vector<ll> diff(n);

    fl(i, n)
    {
        cin >> a[i];
    }
    fl(i, n)
    {
        cin >> b[i];
        diff[i] = a[i] - b[i];
    }

    // Sort the `diff` array by the first element of the pair
    sort(all(diff));

    ll ans = 0;

    for (int i = n - 1; i >= 0; i--)
    {
        if (diff[i] <= 0)
            break;
        else
        {
            ll lambda = 1 - diff[i];
            auto it = upper_bound(diff.begin(), diff.begin() + i, lambda - 1) - diff.begin();

            ans += (i - it);
        }
    }
    cout << ans << endl;
}

// https://codeforces.com/contest/1324/problem/F

vector<ll> a;
vector<ll> dp;
vector<ll> ans;
// returns {black, white}

void dfs(int node, vector<vector<ll>> &adj, int par)
{
    dp[node] = a[node];
    for (auto to : adj[node])
    {
        if (to == par)
            continue;
        dfs(to, adj, node);
        dp[node] += max(dp[to], 0ll);
    }
}

void dfs2(int v, vector<vector<ll>> &adj, int p = -1)
{
    ans[v] = dp[v];
    for (auto to : adj[v])
    {
        if (to == p)
            continue;

        dp[v] -= max(0ll, dp[to]);
        dp[to] += max(0ll, dp[v]);
        dfs2(to, adj, v);
        dp[to] -= max(0ll, dp[v]);
        dp[v] += max(0ll, dp[to]);
    }
}

void r4()
{
    int n;
    cin >> n;
    a = dp = ans = vector<ll>(n);
    fl(i, n)
    {
        cin >> a[i];
        if (a[i] == 0)
            a[i] = -1;
    }

    vector<vector<ll>> adj(n);

    fl(i, n - 1)
    {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(0, adj, -1);
    dfs2(0, adj, -1);

    for (int i = 0; i < n; i++)
    {
        cout << ans[i] << " ";
    }
}

ll sleepdp[2001][2001];

ll n, h, l, r;
ll solver(int pos, int lasttime, vector<int> &a)
{
    if (pos == n)
    {
        return 0;
    }
    if (sleepdp[pos][lasttime] != -1)
    {
        return sleepdp[pos][lasttime];
    }
    int time1 = (lasttime + a[pos] - 1) % h;
    int time2 = (lasttime + a[pos]) % h;
    // cout << time1 << " " << time2 << endl;
    ll ans1 = solver(pos + 1, time1, a), ans2 = solver(pos + 1, time2, a);
    if (time1 >= l and time1 <= r)
    {
        ans1++;
    }
    if (time2 >= l and time2 <= r)
    {
        ans2++;
    }

    return sleepdp[pos][lasttime] = max(ans1, ans2);
}

void solve1()
{
    int n;
    cin >> n;
    string a, b, c;
    cin >> a >> b >> c;

    fl(i, n)
    {
        if (c[i] != a[i] and c[i] != b[i])
        {
            py return;
        }
    }
    pn
}

void solve2()
{
    int n;
    cin >> n;

    vector<ll> v(n);

    fl(i, n)
    {
        cin >> v[i];
    }

    bool bl = true;
    for (auto i : v)
    {
        if (i != 0)
        {
            bl = false;
            break;
        }
    }

    if (bl)
    {
        cout << 0 << endl;
        return;
    }

    int p1 = 0, p2 = n - 1;

    while (p1 < n and v[p1] == 0)
        p1++;
    while (p2 > p1 and v[p2] == 0)
        p2--;

    for (int i = p1; i <= p2; i++)
    {
        if (v[i] == 0)
        {
            cout << 2 << endl;
            return;
        }
    }

    cout << 1 << endl;
}

void s3()
{
    int n;
    cin >> n;
    string s;
    cin >> s;

    int i = 0;
    while (i < n and s[i] != 'p')
    {
        i++;
    }
    if (i < n)
    {
        while (i < n and s[i] != 's')
        {
            i++;
        }
        if (i != n)
        {
            pn return;
        }
    }
    else
    {
        py return;
    }

    // second case

    bool sfound = (s.find('s') != string::npos), pfound = (s.find('p') != string::npos);

    if (!sfound || !pfound)
    {
        py
    }
    else
    {

        // int i = 0;

        // while (i < n and s[i] != 'p')
        // {
        //     i++;
        // }
        // while (i < n and s[i] != 's')
        // {
        //     i++;
        // }
        // if (i == n)
        // {
        //     py return;
        // }

        // pn

        if (s[n - 1] != 'p')
        {
            pn return;
        }

        int i = 0;

        while (i < n and s[i] == '.')
        {
            i++;
        }

        for (int j = 1; j < n - 1; j++)
        {
            if (s[j] == 'p')
            {
                pn return;
            }
        }

        py
    }
}

// educational contest

ll gridhelper(vector<vector<ll>> &grid, int k, int row, int col,
              vector<vector<vector<ll>>> &dp, int shifts)
{
    int n = grid.size(), m = grid[0].size();

    if ((row == n - 1) and (col == m - 1))
    {
        return 0;
    }

    if (dp[row][col][shifts] != -1)
        return dp[row][col][shifts];

    ll ans = LLONG_MAX;

    if ((col + 1 + shifts) < m)
        ans = min(ans, grid[row][col + 1 + shifts] + gridhelper(grid, k, row, col + 1 + shifts, dp, shifts));

    if ((row + 1) < n)
        for (int i = 0; i < m; i++)
        {
            int diff = abs((col + shifts) - i);
            if (i > col)
            {
                diff = m - i;
            }
            ans = min(ans, (k * 1ll * diff) + grid[row + 1][i] +
                               gridhelper(grid, k, row + 1, i, dp, diff));
        }

    return dp[row][col][shifts] = ans;
}

void solve3()
{
    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<ll>> grid(n, vector<ll>(m));
    vector<vector<vector<ll>>> dp(n, vector<vector<ll>>(m, vector<ll>(m, -1)));

    fl(i, n)
    {
        fl(j, m)
        {
            cin >> grid[i][j];
        }
    }

    ll ans = LLONG_MAX;

    for (int i = 0; i < m; i++)
    {
        int diff = abs(0 - i);
        if (i >= 0)
        {
            diff = m - i;
        }
        ans = min(ans, (k * 1ll * abs(i)) + grid[0][i] + gridhelper(grid, k, 0, i, dp, diff));
    }

    cout << ans << endl;
}

bool ispossible(int n, int x, vector<int> &a, int tank_capacity)
{
    int currpetrol = tank_capacity;
    int prev = 0;

    for (int i = 0; i < n; i++)
    {
        int dist = a[i] - prev;
        if (dist > currpetrol)
        {
            return false;
        }
        else
        {
            currpetrol = tank_capacity;
        }
        prev = a[i];
    }

    int dist = x - prev;
    if (dist > currpetrol)
    {
        return false;
    }
    else
    {
        currpetrol -= dist;
    }

    prev = x;

    for (int i = n - 1; i >= 0; i--)
    {
        int dist = prev - a[i];
        if (dist > currpetrol)
        {
            return false;
        }
        else
        {
            currpetrol = tank_capacity;
        }
        prev = a[i];
    }
    dist = prev;
    if (dist > currpetrol)
    {
        return false;
    }
    return true;
}

void solve4()
{
    int n, x;
    cin >> n >> x;

    vector<int> loc;
    fl(i, n)
    {
        int e;
        cin >> e;
        loc.push_back(e);
    }

    int l = 0, r = INT_MAX, mid, ans = -1;

    while (l <= r)
    {
        mid = l + (r - l) / 2;

        if (ispossible(n, x, loc, mid))
        {
            ans = mid;
            r = mid - 1;
        }
        else
        {
            l = mid + 1;
        }
    }

    cout << ans << endl;
}

void solve5()
{
    int n;
    cin >> n;

    vector<ll> v(n);

    fl(i, n) cin >> v[i];

    ll segments = 0, i = 0;
    ll res = 0;

    while (i < n)
    {
        while (i < n and v[i] == 0)
            i++;

        ll maxi = 0;
        if (i == n)
        {
            break;
        }
        while (i < n and v[i] != 0)
        {
            maxi = max(maxi, v[i]);
            i++;
        }
        segments++;
        res += (maxi - 1);
    }

    res += (segments - 1);

    cout << res << endl;
}

void solve6()
{
    int n;
    cin >> n;

    if (n == 1)
    {
        cout << "ALICE" << endl;
        return;
    }
    else
    {
        cout << "BOB" << endl;
        return;
    }
}

void sol7()
{
    ll n, k;
    cin >> n >> k;

    ll res = 0;
    vector<ll> v(n);
    fl(i, n)
    {
        cin >> v[i];
    }

    bool allk = true, alldiv = true;
    unordered_set<ll> s;

    for (auto a : v)
    {
        if (a != k)
            allk = false;
        if ((a % k) != 0)
            alldiv = false;
        s.insert(a);
    }

    if (allk)
    {
        cout << 0 << endl;
        return;
    }

    if (alldiv || (s.size() == 1))
    {
        cout << 1 << endl;
        return;
    }

    cout << 2 << endl;
}

void h1()
{

    int a, b, c;
    cin >> a >> b >> c;

    if (a == b and b == c)
    {
        cout << "Yes\n";
        return;
    }

    if (a == (b + c) or b == (a + c) or c == (a + b))
    {
        cout << "Yes\n";
        return;
    }

    cout << "No\n";
}

void h2()
{
    int h, w, x, y;
    cin >> h >> w >> x >> y;

    vector<string> grid(h);

    fl(i, h)
    {
        cin >> grid[i];
    }
    string t;
    cin >> t;

    x--, y--;
    set<pair<int, int>> s;

    if (grid[x][y] == '@')
    {
        s.insert({x, y});
    }

    for (auto i : t)
    {
        if (i == 'U')
        {
            if (x - 1 >= 0 and grid[x - 1][y] != '#')
            {
                x--;
                if (grid[x][y] == '@')
                {
                    s.insert({x, y});
                }
            }
        }
        else if (i == 'D')
        {
            if (x - 1 >= 0 and grid[x + 1][y] != '#')
            {
                x++;
                if (grid[x][y] == '@')
                {
                    s.insert({x, y});
                }
            }
        }
        else if (i == 'L')
        {
            if (y - 1 >= 0 and grid[x][y - 1] != '#')
            {
                y--;
                if (grid[x][y] == '@')
                {
                    s.insert({x, y});
                }
            }
        }
        else if (i == 'R')
        {
            if (y + 1 < w and grid[x][y + 1] != '#')
            {
                y++;
                if (grid[x][y] == '@')
                {
                    s.insert({x, y});
                }
            }
        }
    }

    cout << x + 1 << " " << y + 1 << " " << s.size() << endl;
}

int longestAP(vector<int> arr)
{
    int n = arr.size();

    if (n <= 2)
        return n;

    vector<unordered_map<int, int>> dp(n);

    int maxLength = 2;

    for (int j = 1; j < n; j++)
    {
        for (int i = 0; i < j; i++)
        {
            int diff = arr[j] - arr[i];

            if (dp[i].find(diff) != dp[i].end())
            {
                dp[j][diff] = dp[i][diff] + 1;
            }
            else
            {
                dp[j][diff] = 2;
            }
            maxLength = max(maxLength, dp[j][diff]);
        }
    }

    return maxLength;
}

void h3()
{
    int n;
    cin >> n;
    unordered_map<int, vector<int>> mp;
    for (int i = 0; i < n; ++i)
    {
        int e;
        cin >> e;
        mp[e].push_back(i);
    }

    int ans = 0;

    for (auto &p : mp)
    {
        if (!p.second.empty())
        {
            ans = max(ans, longestAP(p.second));
        }
    }

    cout << ans << endl;
}

void h4()
{
    ll n, m, x, y;
    cin >> n >> m >> x >> y;

    unordered_map<ll, vector<pair<ll, ll>>> xtohouse, ytohouse;

    fl(i, n)
    {
        ll a, b;
        cin >> a >> b;
        xtohouse[a].push_back({b, i});
        ytohouse[b].push_back({a, i});
    }

    for (auto &entry : xtohouse)
        sort(entry.second.begin(), entry.second.end());

    for (auto &entry : ytohouse)
        sort(entry.second.begin(), entry.second.end());

    unordered_set<ll> visited;

    fl(i, m)
    {
        char d;
        ll c;

        cin >> d >> c;

        if (d == 'U')
        {
            if (xtohouse.count(x))
            {
                auto ub = lower_bound(xtohouse[x].begin(), xtohouse[x].end(), make_pair(y, -1e9 - 2),
                                      [](const pair<ll, ll> &a, const pair<ll, ll> &b)
                                      { return a.first < b.first; }) -
                          xtohouse[x].begin();
                if (ub != xtohouse[x].size())
                {
                    for (int i = ub; i < xtohouse[x].size(); i++)
                    {
                        if (xtohouse[x][i].first > (y + c))
                            break;
                        visited.insert(xtohouse[x][i].second);
                    }
                }
            }
            y += c;
        }
        else if (d == 'D')
        {
            if (xtohouse.count(x))
            {
                auto ub = upper_bound(xtohouse[x].begin(), xtohouse[x].end(), make_pair(y + 1, -1e9 - 2),
                                      [](const pair<ll, ll> &a, const pair<ll, ll> &b)
                                      { return a.first < b.first; }) -
                          xtohouse[x].begin();
                ub--;
                if (ub >= 0)
                {
                    for (int i = ub; i >= 0; i--)
                    {
                        if (xtohouse[x][i].first < (y - c))
                            break;
                        visited.insert(xtohouse[x][i].second);
                    }
                }
            }
            y -= c;
        }
        else if (d == 'L')
        {
            if (ytohouse.count(y))
            {
                auto ub = upper_bound(ytohouse[y].begin(), ytohouse[y].end(), make_pair(x + 1, -1e9 - 2),
                                      [](const pair<ll, ll> &a, const pair<ll, ll> &b)
                                      { return a.first < b.first; }) -
                          ytohouse[y].begin();
                ub--;
                if (ub >= 0)
                {
                    for (int i = ub; i >= 0; i--)
                    {
                        if (ytohouse[y][i].first < (x - c))
                            break;
                        visited.insert(ytohouse[y][i].second);
                    }
                }
            }
            x -= c;
        }
        else
        {
            if (ytohouse.count(y))
            {
                auto ub = lower_bound(ytohouse[y].begin(), ytohouse[y].end(), make_pair(x, -1e9 - 2),
                                      [](const pair<ll, ll> &a, const pair<ll, ll> &b)
                                      { return a.first < b.first; }) -
                          ytohouse[y].begin();
                if (ub != ytohouse[y].size())
                {
                    for (int i = ub; i < ytohouse[y].size(); i++)
                    {
                        if (ytohouse[y][i].first > (x + c))
                            break;
                        visited.insert(ytohouse[y][i].second);
                    }
                }
            }
            x += c;
        }
    }

    cout << x << " " << y << " " << (ll)visited.size() << endl;
}

ll helper2(vector<int> &nums)
{
    unordered_map<int, int> frequency;
    int totalSum = 0;

    for (int num : nums)
    {
        frequency[num]++;
        totalSum += num;
    }

    int maxFrequency = 0;
    int targetValue = 0;
    for (const auto &pair : frequency)
    {
        if (pair.second > maxFrequency)
        {
            maxFrequency = pair.second;
            targetValue = pair.first;
        }
    }

    int removeSum = 0;
    for (int num : nums)
    {
        if (num != targetValue)
        {
            removeSum += num;
        }
    }

    return removeSum;
}

int minDecrementOperations(vector<int> &nums)
{
    sort(nums.begin(), nums.end());

    int n = nums.size();
    int minOperations = INT_MAX;

    for (int i = 0; i < n; ++i)
    {
        int target = nums[i];
        int operations = 0;

        for (int j = 0; j < n; ++j)
        {
            if (nums[j] > target)
            {
                operations += (nums[j] - target);
            }
            else if (nums[j] < target)
            {
                operations += nums[j];
                if (nums[j] == 0)
                {
                    operations++;
                }
            }
        }

        minOperations = min(minOperations, operations);
    }

    return minOperations;
}

void h5()
{
    int n;
    cin >> n;

    vector<vector<int>> adj(n, vector<int>());
    vector<int> degress(n, 0);

    fl(i, n - 1)
    {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
        degress[u]++;
        degress[v]++;
    }

    int ans = INT_MAX;

    for (int i = 0; i < n; i++)
    {

        int sz = adj[i].size();
        vector<int> t;

        for (auto j : adj[i])
        {
            t.push_back(degress[j]);
        }

        sort(all(t), greater<>());

        int ptr = 1;
        for (auto j : t)
        {
            ans = min(ans, n - (1 + ptr + ((ptr) * (j - 1))));
            ptr++;
        }
    }

    cout << ans << endl;
}

void h6()
{
    int n;
    cin >> n;

    unordered_map<int, vector<int>> freq;

    fl(i, n)
    {
        int a, b;
        cin >> a >> b;
        freq[a].push_back(b);
    }

    vector<int> maxi;
    int ans = 0;
    for (auto i : freq)
    {
        sort(all(i.second));
        int sz = i.second.size();
        int lgt = i.second[sz - 1];
        if (sz > 1)
        {
            int secondLarge = i.second[sz - 2];
            ans = max(ans, lgt + (secondLarge / 2));
        }
        maxi.push_back(lgt);
    }

    sort(all(maxi), greater<>());

    if (maxi.size() > 1)
    {
        ans = max(ans, maxi[0] + maxi[1]);
    }
    cout << ans << endl;
}

vector<int> topological_sort(vector<vector<int>> &graph, vector<int> &indegree)
{
    int n = graph.size();

    for (int i = 0; i < n; i++)
        for (int j : graph[i])
            indegree[j]++;
    vector<int> res;
    queue<int> que;
    for (int i = 0; i < n; i++)
        if (indegree[i] == 0)
            que.push(i);
    while (!que.empty())
    {
        int ver = que.front();
        que.pop();
        res.push_back(ver);
        for (int i : graph[ver])
        {
            indegree[i]--;
            if (indegree[i] == 0)
                que.push(i);
        }
    }
    return res;
}

vector<int> topological_sort2(vector<vector<int>> graph)
{
    int n = graph.size();
    vector<int> indegree(n);
    for (int i = 0; i < n; i++)
        for (int j : graph[i])
            indegree[j]++;
    vector<int> res;
    queue<int> que;
    for (int i = 0; i < n; i++)
        if (indegree[i] == 0)
            que.push(i);
    while (!que.empty())
    {
        int ver = que.front();
        que.pop();
        res.push_back(ver);
        for (int i : graph[ver])
        {
            indegree[i]--;
            if (indegree[i] == 0)
                que.push(i);
        }
    }
    return res;
}

void extendedTopologicalSortBooks()
{
    int n;
    cin >> n;

    vector<vector<int>> adj(n);

    vector<int> indegree(n, 0);

    fl(i, n)
    {
        int cnt;
        cin >> cnt;
        indegree[i] = cnt;
        fl(j, cnt)
        {
            int prebook;
            cin >> prebook;
            prebook--;
            adj[i].push_back(prebook);
        }
    }

    vector<int> relevantNodes(n, 0);

    // bfs with book 0
    queue<int> q;
    q.push(0);
    vector<int> vis(n, 0);
    vis[0] = 1;

    while (!q.empty())
    {
        int node = q.front();
        q.pop();
        relevantNodes[node] = 1;
        for (auto to : adj[node])
        {
            if (vis[to] == 0)
            {
                vis[to] = 1;
                q.push(to);
            }
        }
    }

    relevantNodes[0] = 0;

    vector<int> t = topological_sort2(adj);
    vector<int> order(n);

    fl(i, n)
    {
        order[t[i]] = i;
    }

    vector<int> ans;

    for (auto i : t)
    {
        if (relevantNodes[i])
        {
            ans.push_back(i);
        }
    }

    sort(all(ans), [&](int a, int b)
         { return order[a] > order[b]; });

    for (auto i : ans)
    {
        cout << i + 1 << " ";
    }
    cout << endl;
}

// Given 2 arrays A and B. Make B equal to A in minimum no. of operations. In each operation, you can
// remove any element from array B and put that element in front or end of array B. We need to output the
// number of operations.

// A = [1,4,5,4,5]
// B = [5,4,5,1,4]

// Steps
// 1. remove 4 from B and put it at the front of B => [4,5,4,5,1]
// 2. remove 1 from B and put it at the front of B => [1,4,5,4,5]
// 2 steps are required.
// it can be proven that minimum 2 steps are required to make B equal to A.

void solve7()
{
    int n;
    cin >> n;

    vector<int> a(n), b(n);

    fl(i, n)
    {
        cin >> a[i];
    }

    fl(i, n)
    {
        cin >> b[i];
    }

    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (a[i] == b[j])
            {
                dp[i + 1][j + 1] = dp[i][j] + 1;
            }
            else
            {
                dp[i + 1][j + 1] = dp[i + 1][j];
            }
        }
    }

    int ans = 0;
    for (auto i : dp)
    {
        for (auto j : i)
        {
            ans = max(ans, j);
        }
    }

    cout << "Max length of common subsequence is " << ans << endl;
    cout << "Required number of operations is/are : " << n - ans << endl;
}

void solve8()
{
    int n;
    cin >> n;
    string a, b, c;
    cin >> a >> b >> c;

    unordered_map<char, vector<int>> mp1, mp2, mp3;

    for (int i = 0; i < n; i++)
    {
        mp1[a[i]].push_back(i);
        mp2[b[i]].push_back(i);
        mp3[c[i]].push_back(i);
    }

    int ans = INT_MAX;
    for (int i = 0; i <= 9; i++)
    {
        int last = -1, curr = 0;
        if (mp1.count(i + '0') and mp2.count(i + '0') and mp3.count(i + '0'))
        {
            auto u1 = *upper_bound(mp1['0' + i].begin(), mp1['0' + i].end(), last);
            auto u2 = *upper_bound(mp2['0' + i].begin(), mp2['0' + i].end(), last);
            auto u3 = *upper_bound(mp3['0' + i].begin(), mp3['0' + i].end(), last);
            last = min({u1, u2, u3});
            curr = last;

            if (last == u2)
            {
                mp2 = mp1;
                mp3 = mp3;
            }
            else if (last == u3)
            {
                mp2 = mp1;
                mp3 = mp2;
            }

            // look for mp2 and mp3
            auto p2 = upper_bound(mp2['0' + i].begin(), mp2['0' + i].end(), last) - mp2['0' + i].begin();
            auto p3 = upper_bound(mp3['0' + i].begin(), mp3['0' + i].end(), last) - mp3['0' + i].begin();

            if (p2 < mp2['0' + i].size())
            {
                curr = max(curr, mp2['0' + i][p2]);
                last = curr;

                auto p3 = upper_bound(mp3['0' + i].begin(), mp3['0' + i].end(), last) - mp3['0' + i].begin();
                if (p3 < mp3['0' + i].size())
                {
                    curr = mp3['0' + i].size();
                }
                else
                {
                    curr = n;
                    auto p3 = upper_bound(mp3['0' + i].begin(), mp3['0' + i].end(), -1) - mp3['0' + i].begin();
                    curr += p3;
                }
            }
            else if (p3 < mp3['0' + i].size())
            {
                curr = mp3['0' + i][p3];
                last = curr;

                auto p2 = upper_bound(mp2['0' + i].begin(), mp2['0' + i].end(), last) - mp2['0' + i].begin();
                if (p2 < mp2['0' + i].size())
                {
                    curr = mp2['0' + i].size();
                }
                else
                {
                    curr = n;
                    auto p2 = upper_bound(mp2['0' + i].begin(), mp2['0' + i].end(), -1) - mp2['0' + i].begin();
                    curr += p2;
                }
            }
            else
            {
                curr = n;
                auto p2 = upper_bound(mp2['0' + i].begin(), mp2['0' + i].end(), -1) - mp2['0' + i].begin();
                auto p3 = upper_bound(mp3['0' + i].begin(), mp3['0' + i].end(), -1) - mp3['0' + i].begin();

                if (p2 < p3)
                {
                    curr += p2;
                }
                else
                {
                    curr += p3;
                }
            }
        }

        ans = min(ans, curr);
    }
}

void solve9()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    int cnt = 0;
    for (auto i : s)
    {
        if (i == '1')
            cnt++;
    }

    if (cnt == 0)
    {
        cout << "YES\n";
        return;
    }

    if (cnt % 2 != 0)
    {
        pn return;
    }

    else
    {
        if (cnt > 2)
        {
            cout << "YES\n";
            return;
        }
        else
        {
            int p1 = 0, p2 = n - 1;
            while (s[p1] != '1')
            {
                p1++;
            }
            while (s[p2] != '1')
            {
                p2--;
            }
            int diff = p2 - p1;
            if (diff >= 2)
            {
                cout << "YES\n";
                return;
            }
            else
            {
                cout << "NO\n";
                return;
            }
        }
    }
}

void solve10()
{
}

ll solve(string &s, int pos, int n, vector<ll> &dp)
{
    if (pos > n)
    {
        return 0;
    }

    if (pos == n - 1)
    {
        return 1;
    }

    if (dp[pos] != -1)
    {
        return dp[pos] % mod;
    }

    ll ans = 0;

    if (s[pos] == '0')
    {
        ans = solve(s, pos + 1, n, dp) + solve(s, pos + 2, n, dp) % mod;
    }

    else
    {
        ans = solve(s, pos + 1, n, dp) % mod;
    }

    return dp[pos] = ans % mod;
}

int numWays(string &s)
{
    int n = s.size();
    vector<ll> dp(n + 1, -1);

    return solve(s, 0, n, dp);
}

string findSmallest(string &s, int k)
{
    int n = s.size();
    int p1 = 0, p2 = n - 1;

    while (p1 < p2)
    {
        int c1 = s[p1] - 'a', c2 = s[p2] - 'a';
        int diff = abs(c1 - c2);
        diff = min(diff, 26 - diff);
        int diff2 = min(c1, 26 - c1) + min(c2, 26 - c2);

        if (diff2 <= diff)
        {
            if (diff2 > k)
            {
                return "";
            }
            else
            {
                k -= diff2;
                s[p2] = s[p1] = 'a';
            }
        }
        else
        {
            if (diff > k)
            {
                return "";
            }
            k -= diff;
            if (c1 <= c2)
            {
                s[p2] = s[p1];
            }
            else
            {
                s[p1] = s[p2];
            }
        }
        p1++, p2--;
        // cout << s << " " << k << " \n";
    }

    for (int i = 0; i < n / 2; i++)
    {
        int diff = s[i] - 'a';
        diff = min(diff, 26 - diff);
        if ((2 * diff) <= k)
        {
            s[i] = s[n - i - 1] = 'a';
            k -= (2 * diff);
        }
        else
        {
            int maxdec = k / 2;
            char ch = (s[i] - 'a' - maxdec) + 'a';
            s[i] = s[n - i - 1] = ch;
            k -= 2 * (k / 2);
        }
        // cout << s << " " << k << " \n";
    }

    if ((n % 2) != 0)
    {
        int curr = s[n / 2] - 'a';
        int req = min(curr, 26 - curr);
        int maxdec = min(k, req);
        if (req <= k)
            s[n / 2] = 'a';
        else
            s[n / 2] = 'a' + ((s[n / 2] - 'a') - k);
    }

    return s;
}

int getShiftCost(char from, char to)
{
    int direct = abs(from - to);
    int cyclic = 26 - direct;
    return min(direct, cyclic);
}

char shiftTowards(char from, char to)
{
    int forward = (to - from + 26) % 26;
    int backward = (from - to + 26) % 26;
    return forward <= backward ? to : to;
}

string lexicographicallySmallestPalindrome(string s, int k)
{
    int n = s.size();
    int operations = 0;

    // Step 1: Make the string a palindrome
    for (int i = 0; i < n / 2; ++i)
    {
        char left = s[i];
        char right = s[n - i - 1];
        if (left != right)
        {
            int cost = getShiftCost(left, right);
            if (operations + cost > k)
            {
                // Not enough operations left
                return "Not Possible";
            }
            // Choose the smaller character and update both sides
            if (left < right)
            {
                s[n - i - 1] = shiftTowards(right, left);
            }
            else
            {
                s[i] = shiftTowards(left, right);
            }
            operations += cost;
        }
    }

    // Step 2: Minimize the characters further if operations are left
    for (int i = 0; i <= n / 2 && operations < k; ++i)
    {
        char curr = s[i];
        if (curr != 'a')
        {
            int cost = getShiftCost(curr, 'a');
            if (operations + 2 * cost <= k)
            {
                // Update both sides of the palindrome
                s[i] = s[n - i - 1] = 'a';
                operations += 2 * cost;
            }
        }
    }

    // If operations still remain and are enough, convert the middle character (odd length) to 'a'
    if (n % 2 == 1 && operations < k)
    {
        char middle = s[n / 2];
        int cost = getShiftCost(middle, 'a');
        if (operations + cost <= k)
        {
            s[n / 2] = 'a';
            operations += cost;
        }
    }

    return s;
}

void t1()
{
    int n;
    cin >> n;

    vector<ll> a(n), b(n + 1);

    fl(i, n)
    {
        cin >> a[i];
    }

    fl(i, n)
    {
        cin >> b[i];
    }

    b[n] = (0);

    ll sum = 0;

    for (int i = 0; i < n; i++)
    {
        if (a[i] >= b[i + 1])
        {
            sum += a[i] - b[i + 1];
        }
    }

    cout << sum << endl;
}

void t2()
{
    ll n, a, b, c;
    cin >> n >> a >> b >> c;

    ll total = (a + b + c);

    ll req = (n) / total;

    n -= (req * 1ll * total);
    ll ans = req * 1ll * 3;

    if (n == 0)
    {
        cout << ans << endl;
    }

    else if (n <= a)
    {
        ans++;
        cout << ans << endl;
    }
    else if (n <= (a + b))
    {
        ans += 2;
        cout << ans << endl;
    }
    else
    {
        ans += 3;
        cout << ans << endl;
    }
}

void t3()
{
    ll n, m, k;
    cin >> n >> m >> k;

    vector<int> a(m), b(n, 0);

    fl(i, m)
    {
        cin >> a[i];
        a[i]--;
    }

    fl(i, k)
    {
        int e;
        cin >> e;
        b[e - 1] = 1;
    }

    if (n == k)
    {
        for (int i = 0; i < m; i++)
        {
            cout << 1;
        }
        cout << endl;
    }

    else if (n > (k + 1))
    {
        for (int i = 0; i < m; i++)
        {
            cout << 0;
        }
        cout << endl;
    }
    else
    {
        int notk = -1;
        for (int i = 0; i < m; i++)
        {
            if (b[i] == 0)
            {
                notk = i;
            }
        }
        for (int i = 0; i < m; i++)
        {
            if (a[i] == notk)
            {
                cout << 1;
            }
            else
            {
                cout << 0;
            }
        }
        cout << endl;
    }
}

void t4()
{
    ll n, x, y;
    cin >> n >> x >> y;

    vector<ll> a(n);
    for (ll i = 0; i < n; ++i)
    {
        cin >> a[i];
    }

    sort(a.begin(), a.end());

    ll ans = 0;
    ll sum = accumulate(a.begin(), a.end(), 0ll);

    for (ll i = 0; i < n - 1; ++i)
    {
        ll diff = sum - a[i];

        auto ub = upper_bound(a.begin() + i + 1, a.end(), diff - y - 1);
        int p1 = ub - a.begin();

        if (p1 < n)
        {
            auto lb = upper_bound(a.begin() + i + 1, a.end(), diff - x);
            int p2 = lb - a.begin() - 1;

            if (p2 >= p1 && p1 < n)
            {
                ans += (p2 - p1 + 1);
            }
        }
    }

    cout << ans << endl;
}

pair<bool, ll> possible(vector<ll> &a, vector<ll> &b, ll k, ll mid)
{
    int n = b.size();
    ll buys = 0;
    for (int i = 0; i < n; i++)
    {
        if (mid <= b[i])
        {
            buys++;
        }
        if (a[i] >= mid)
        {
            continue;
        }
        if (mid <= b[i])
        {
            k--;
            if (k < 0)
            {
                return {false, 0ll};
            }
        }
    }

    return {(k >= 0), buys};
}

void t5()
{
    ll n, k;
    cin >> n >> k;

    vector<ll> a(n), b(n);

    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 0; i < n; i++)
        cin >> b[i];

    ll low = 0, high = 100, ans = -1, mid;
    ll prevBought = 0, maxBought = 0;

    while (low <= high)
    {
        mid = (low + high) / 2;
        auto t = possible(a, b, k, mid);

        if (t.first)
        {
            cout << mid << " " << t.second << " " << endl;
            if ((t.second >= prevBought) and (t.second != 0))
            {
                low = mid + 1;
                ans = mid;
                prevBought = t.second;
                maxBought = max(maxBought, prevBought);
            }
            else
            {
                high = mid - 1;
            }
        }
        else
        {
            high = mid - 1;
        }
    }

    // cout << ans << " ";

    ll cost = (maxBought * 1ll * ans);

    cout << cost << endl;
}

// dp[i][j] => minimum cost to hoard i tickets till jth day

void t6()
{
    ll n, m, k;
    cin >> n >> m >> k;

    vector<ll> v(n);

    fl(i, n)
    {
        cin >> v[i];
    }

    ll dp[n + 1][k + 1] = {0};
    memset(dp, 0ll, sizeof(dp));

    for (int i = n - 1; i >= 0; i--)
    {
        ll maxTickets = m;
        for (int j = 0; j <= maxTickets; j++)
        {
            ll cost = (v[i] + (k - j)) * j;
            dp[i][j] = min(dp[i][j], dp[i + 1][k - j] + (cost));
        }
    }

    ll ans = dp[0][k];

    cout << ans << endl;
}

void t7()
{
    ll n, k;
    cin >> n >> k;

    ll q = n / k;
    if (q == 0)
        q++;
    ll bought = n / q;

    if (bought == k)
    {
        cout << "YES\n";
        cout << 1 << endl;
        cout << q << " ";

        cout << endl;
    }
    else
    {
        cout << "NO\n";
    }
}

void t8()
{
    int n, q;
    cin >> n >> q;
    int ones = 0, zeros = 0;
    vector<int> v(n);
    fl(i, n)
    {
        int e;
        cin >> e;
        v[i] = e;
        if (e)
            ones++;
        else
            zeros++;
    }

    fl(i, q)
    {
        int type;
        cin >> type;

        if (type == 1)
        {
            int x;
            cin >> x;
            x--;
            if (v[x] == 0)
            {
                ones++;
                zeros--;
            }
            else
            {
                ones--;
                zeros++;
            }
            v[x] = 1 - v[x];
        }
        else
        {
            int k;
            cin >> k;

            if (ones >= k)
            {
                cout << 1 << endl;
            }
            else
            {
                cout << 0 << endl;
            }
        }
    }
}

void t9()
{
    ll n, u, v;
    cin >> n >> u >> v;

    vector<ll> a(n);
    fl(i, n)
    {
        cin >> a[i];
    }

    bool allequal = true;
    for (auto i : a)
    {
        if (i != a[0])
            allequal = false;
    }

    if (allequal)
    {
        ll ans = min(2 * 1ll * v, u + v);
        cout << ans << endl;
        return;
    }

    for (int i = 1; i < n; i++)
    {
        int absdiff = abs(a[i] - a[i - 1]);
        if (absdiff > 1)
        {
            cout << 0 << endl;
            return;
        }
    }
    ll ans = min(u, v);
    cout << ans << endl;
}

void r100()
{
    int n;
    cin >> n;
    vector<ll> v(n);
    fl(i, n)
    {
        cin >> v[i];
    }

    ll ans = 0ll;

    for (int i = 0; i < n; i++)
    {
        if (v[i] > 1)
        {
            int ops = v[i] - 1;

            ans += ops;

            for (int jumps = 2; jumps <= min((int)v[i], n - i - 1); jumps++)
            {
                for (int k = (i + jumps); k < n; k += jumps)
                {
                    v[k] = max(1ll, v[k] - 1);
                }
            }

            v[i] = 1;
        }
    }

    cout << ans << endl;
}

// brute force se thoda accha
void r101()
{
    int q;
    cin >> q;

    fl(i, q)
    {
        ll u, v;
        cin >> u >> v;

        queue<ll> q;
        q.push(u);

        unordered_set<ll> vis;
        bool found = false;

        vis.insert(u);

        while (!q.empty())
        {
            auto fr = q.front();
            q.pop();

            if (fr == v)
            {
                cout << "YES\n";
                found = true;
                break;
            }

            bitset<sizeof(ll) * 31> bits(fr);

            for (int j = 0; j < 32; j++)
            {
                if (bits[j] == 1)
                {
                    ll node = fr + (1 << j);
                    if (node <= v and !vis.count(node))
                    {
                        q.push(node);
                        vis.insert(node);
                    }
                }
            }
        }

        if (!found)
        {
            cout << "NO\n";
        }
    }
}

// best solution :)

void r102()
{
    int q;
    cin >> q;

    fl(j, q)
    {
        ll u, v;
        cin >> u >> v;

        if (u > v)
        {
            cout << "NO\n";
            continue;
        }

        bool ok = true;
        int z = 0;

        for (int i = 0; i < 30; i++)
        {
            if (((1 << i) & u) != 0)
                z++;
            if (((1 << i) & v) != 0)
                z--;
            if (z < 0)
            {
                ok = false;
                break;
            }
        }

        if (!ok)
        {
            cout << "NO\n";
        }
        else
        {
            cout << "YES\n";
        }
    }
}

// https://codeforces.com/contest/1491/problem/E

ll dfs3(vector<vector<ll>> &adj, ll node, vector<ll> &v, int par = -1)
{
    ll sz = 0;
    for (auto neigh : adj[node])
    {
        if (neigh != par)
            sz += dfs3(adj, neigh, v, node);
    }

    v[node] = 1ll + sz;
    return v[node];
}

void fibtree()
{
    ll n;
    cin >> n;

    vector<vector<ll>> adj(n);
    vector<ll> deg(n, 0);

    fl(i, n - 1)
    {
        ll u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        deg[u]++;
        deg[v]++;
    }

    if (n <= 2)
    {
        py return;
    }

    int sz = 36;
    ll fib[sz] = {0};
    fib[0] = 1;
    fib[1] = 1;

    for (int i = 2; i < sz; i++)
    {
        fib[i] = fib[i - 2] + fib[i - 1];
    }

    // for (int i = 0; i < sz; i++)
    // {
    //     cout << fib[i] << " ";
    // }

    int loc = -1;
    for (int i = 0; i < sz; i++)
    {
        if (fib[i] > n)
        {
            break;
        }
        else if (fib[i] == n)
        {
            loc = i;
            break;
        }
    }

    if (loc == -1)
    {
        pn return;
    }
    else
    {
        ll subtree1 = fib[loc - 1], subtree2 = fib[loc - 2];
        ll root = -1;
        for (int i = 0; i < n; i++)
        {
            if (deg[i] == 1)
            {
                root = i;
                break;
            }
        }
        vector<ll> sizes(n, 0);
        dfs3(adj, root, sizes);

        for (auto i : sizes)
        {
            // cout << i << " ";
            if (i == subtree1 || i == subtree2)
            {
                py return;
            }
        }
        pn
    }
}

void sol1()
{
    int n, k;
    cin >> n >> k;

    ll prod = 1ll;
    fl(i, n)
    {
        ll e;
        cin >> e;
        prod *= e;
    }
    ll req = 2023;
    if (req % prod == 0)
    {
        py;
        ll ans = req / prod;
        cout << ans << " ";
        for (int i = 1; i < k; i++)
        {
            cout << 1 << " ";
        }
        cout << endl;
    }
    else
    {
        pn
    }
}

void sol2()
{
    ll a, b;
    cin >> a >> b;

    for (int i = 2; i <= sqrt(b); i++)
    {
        if ((b % i) == 0)
        {
            ll p2 = (b * i) / a;
            ll prod1 = i * b;
            ll prod2 = p2 * a;
            if (prod1 == prod2)
            {
                cout << prod1 << endl;
                return;
            }
        }
    }

    ll prod = a * 1ll * b;

    if (prod <= b)
    {
        prod = b * 1ll * b;
    }
    cout << prod << endl;
}

void solv3()
{
    int n, k;
    cin >> n >> k;

    vector<int> ans(n + 1, -1);

    int curr = 1;

    for (int i = k; i <= n; i += k)
    {
        ans[i] = curr++;
    }
    for (int i = n; i >= 1; i--)
    {

        if (ans[i] == -1)
        {
            ans[i] = curr++;
        }
    }

    for (int i = 1; i <= n; i++)
    {
        cout << ans[i] << " ";
    }

    cout << endl;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--)
        solv3();
    return 0;
}