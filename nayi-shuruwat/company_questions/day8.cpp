
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

void r5()
{
    cin >> n >> h >> l >> r;
    vector<int> a(n);
    fl(i, n)
    {
        cin >> a[i];
    }
    memset(sleepdp, -1, sizeof(sleepdp));
    ll ans = solver(0, 0, a);
    cout << ans << endl;
}

ll codedp[2][2][2];
ll modulo, max_bugs;

ll aicoder(int n, int pos, int rem_lines, int bugs, vector<int> &a)
{
    if ((pos == n))
    {
        return (rem_lines == 0);
    }

    if (codedp[pos][rem_lines][bugs] != -1)
    {
        return codedp[pos][rem_lines][bugs] % modulo;
    }

    ll ans = 0;
    for (int i = 0; (rem_lines - i) >= 0; i++)
    {
        int rem_bugs = bugs - (i * a[pos]);

        if (rem_bugs >= 0)
        {
            ans += aicoder(n, pos + 1, rem_lines - i, rem_bugs, a) % modulo;
        }
    }

    return codedp[pos][rem_lines][bugs] = ans % modulo;
}

void r6()
{
    ll n, m;
    cin >> n >> m >> max_bugs >> modulo;

    vector<int> a(n);
    fl(i, n)
    {
        cin >> a[i];
    }

    // recursive dp
    // memset(codedp, -1, sizeof(codedp));

    // ll ways = aicoder(n, 0, m, max_bugs, a);
    // ways = ways % modulo;
    // cout << ways << endl;

    // iterative dp
    memset(codedp, 0, sizeof(codedp));
    codedp[0][0][0] = 1;

    // one way to perform for 0 lines of code with zero bugs

    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j <= m; j++)
        {
            for (int k = 0; k <= max_bugs; k++)
            {
                codedp[i][j][k] = codedp[i - 1][j][k] % modulo;
                int mere_bugs = a[i - 1];
                if (j > 0 and (k - mere_bugs) >= 0)
                    codedp[i][j][k] += codedp[i][j - 1][k - mere_bugs] % modulo;
            }
        }
    }

    ll ans = 0;

    for (int i = 0; i <= max_bugs; i++)
    {
        ans += codedp[n - 1][m][i] % modulo;
    }
    cout << ans << endl;
}

void v1()
{
    int n;
    cin >> n;
    string s;
    cin >> s;

    int fa = -1, la = -1;
    int fb = -1, lb = -1;

    for (int i = 0; i < n; i++)
    {
        if (s[i] == 'a')
        {
            if (fa == -1)
                fa = i;
            la = i;
        }
        else
        {
            if (fb == -1)
                fb = i;
            lb = i;
        }
    }
    int ans = 0;

    if (fa != -1)
    {
        ans = la - fa + 1;
    }
    if (fb != -1)
    {
        ans = max(ans, lb - fb + 1);
    }

    cout << ans << endl;
}

void solve3()
{
    int n;
    cin >> n;

    vector<ll> a(n), b(n);

    fl(i, n)
    {
        cin >> a[i];
    }
    fl(i, n)
    {
        cin >> b[i];
    }

    vector<int> vis(n, false);
    vector<pll> morecost, lesscost;

    fl(i, n)
    {
        if (b[i] >= a[i])
        {
            morecost.push_back({b[i] - a[i], i});
        }
        else
        {
            lesscost.push_back({a[i] - b[i], i});
        }
    }

    int morecostsz = morecost.size(), lesscostsz = lesscost.size();
    ll mini = 0;

    if (lesscostsz == 0 and n == 1)
    {
        mini = b[0];
        cout << mini << endl;
        return;
    }

    if ((morecostsz >= 2) || (morecostsz == 0))
    {
        for (int i = 0; i < n; i++)
        {
            mini += min(a[i], b[i]);
        }
        cout << mini << endl;
        return;
    }
    else
    {
        if (morecostsz)
            sort(all(morecost), greater<>());
        if (lesscostsz)
            sort(all(lesscost));
        ll mini = 0;

        ll loss = b[morecost[0].second] - a[morecost[0].second];
        ll gain = a[lesscost[0].second] - b[lesscost[0].second];

        if (gain >= loss)
        {
            vis[morecost[0].second] = 1;
            mini += b[morecost[0].second];
            for (int i = 0; i < n; i++)
            {
                if (vis[i] == 0)
                    mini += min(a[i], b[i]);
            }
            cout << mini << endl;
            return;
        }
        else
        {
            vis[morecost[0].second] = 1;
            vis[lesscost[0].second] = 1;
            mini += a[morecost[0].second];
            mini += a[lesscost[0].second];
            for (int i = 0; i < n; i++)
            {
                if (vis[i] == 0)
                    mini += min(a[i], b[i]);
            }
            cout << mini << endl;
            return;
        }
    }
}

void v2()
{
    int n, m, k;
    cin >> n >> m >> k;

    int ans = INT_MAX;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            int c = 2 * (i + j);
            ans = min(ans, abs(c - k));
        }
    }

    cout << ans << endl;
}

void v3()
{
    int n;
    cin >> n;

    vector<ll> v(n);
    fl(i, n)
    {
        cin >> v[i];
    }

    int pos = 0, maxi = INT_MIN;

    map<int, int> mp;
    ll currgreater = INT_MIN;
    int ans = 0;
    // fl(i, n)
    // {
    //     auto it = mp.upper_bound(v[i] - 1);
    //     if (it == mp.end())
    //     {
    //         ans = max(ans, i + 1);
    //     }
    //     else
    //     {
    //         ans = max(ans, i - (it->second));
    //         --it;
    //     }
    //     ans--;
    //     mp[v[i]] = i;
    // }
    vector<int> gr(n, -1);
    stack<int> st;

    fl(i, n)
    {
        while (!st.empty() && v[st.top()] < v[i])
        {
            st.pop();
        }

        if (!st.empty())
        {
            gr[i] = st.top();
        }

        st.push(i);
    }

    for (int i = 1; i < n; i++)
    {
        if (gr[i] != -1)
            ans = max(ans, i - gr[i] - 1);
        else
        {
            ans = max(ans, i);
        }
    }

    cout << ans << endl;
}

bool check(int n, string s, int start)
{
    int end;
    if (n % 2 == 0)
    {
        end = !start;
    }
    else
    {
        end = start;
    }

    int next = start;

    int i = 0;
    for (; i < n; i++)
    {
        int curr = s[i] - '0';
        if (curr == next)
        {
            next = !next;
        }
        else
        {
            break;
        }
    }
    // cout << i << " ";
    if (i == n)
    {
        return true;
    }
    int j = n - 1;
    int prev = end;
    for (; j > i; j--)
    {
        int curr = s[j] - '0';
        if (curr == prev)
        {
            prev = !prev;
        }
        else
        {
            break;
        }
    }
    // cout << j << " ";
    while (i < j)
    {
        char temp = s[i];
        s[i] = s[j];
        s[j] = temp;
        i++;
        j--;
    }
    // cout << s << "\n";
    i = 0;
    next = start;
    for (; i < n; i++)
    {
        int curr = s[i] - '0';
        if (curr == next)
        {
            next = !next;
        }
        else
        {
            break;
        }
    }

    return (i == n);
}

void r34()
{
    int n;
    cin >> n;
    string s;
    cin >> s;

    bool ans = check(n, s, 0) || check(n, s, 1);

    if (ans)
    {
        cout << "Yes\n";
    }
    else
    {
        cout << "No\n";
    }
}

void v4()
{
    ll x1, x2, y1, y2, z1, z2, k;
    cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> k;

    ll dx = abs(x2 - x1), dy = abs(y2 - y1), dz = abs(z2 - z1);

    vector<ll> v = {dx, dy, dz};

    sort(all(v), greater<>());

    dx = v[0], dy = v[1], dz = v[2];

    ll rem = dy + dz;
    dx -= dy;
    dy = 0;
    ll ans = 0;
    ans += 2 * dy;
    ll tosub = max(0ll, dz);

    ans += 2 * tosub;
    dz -= tosub;
    dx -= tosub;

    ll t1 = ((dx + k - 1) / k);
    ll gapsx = t1 - 1;
    dx = 0;
    ans += gapsx;

    cout << "line1 : " << ans << " ";

    if (rem >= gapsx)
    {
        ll toy = min(dy, (gapsx + 1) / 2);
        ll toz = min(dz, gapsx / 2);

        dy -= toy;
        dz -= toz;

        gapsx -= (toy + toz);

        if (gapsx > 0)
        {
            dy -= gapsx;
            gapsx = 0;
        }

        cout << "\nline8: " << dy << " " << dz << " " << gapsx << endl;

        if (dy >= gapsx)
        {
            t1 = ((dy + k - 1) / k);
            ll gapsy = t1 - 1;
            ans += dy + gapsy;

            cout << "line2: " << ans << " " << dy << " " << gapsy << endl;

            if (dz >= gapsy)
            {
                dz -= gapsy;

                t1 = ((dz + k - 1) / k);
                ll gapsz = t1 - 1;

                ans += dz + (gapsz);

                cout << "line3: " << ans << " ";

                if (gapsz % 2 != 0)
                    ans++;
            }
            else
            {
                gapsy -= dz;
                ans += dz + (gapsy);

                if (gapsy % 2 != 0)
                    ans++;

                cout << "line4: " << ans << " ";
            }
        }

        else
        {
            gapsx -= dy;
            dy = 0;

            dz -= gapsx;
            t1 = ((dz + k - 1) / k);
            ll gapsz = t1 - 1;
            ans += dz + gapsz;

            if ((gapsz % 2) != 0)
                ans++;

            cout << "line4: " << ans << " ";
        }
    }
    else
    {
        if (gapsx % 2 != 0)
            ans++;
    }

    cout << ans << endl;
}

void r10()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<int> altlen(n, 0);
    altlen[0] = 1;

    for (int i = 1; i < n; i++)
    {
        if (s[i] == s[i - 1])
        {
            altlen[i] = 1;
        }
        else
        {
            altlen[i] = altlen[i - 1] + 1;
        }
    }

    ll ans = 1ll;

    for (int i = 1; i < n; i++)
    {
        int prev = i - altlen[i];
        ans += (altlen[i]);

        if (prev >= 0)
        {
            int len = prev - altlen[prev];

            if (len >= 0)
            {
                cout << i << " " << prev << " " << len << " \n";

                ans += altlen[len];
            }
        }
    }

    cout << ans << endl;
}

void reversesegmet()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        string s;
        cin >> s;

        set<int> bad;
        for (int i = 0; i + 1 < n; ++i)
            if (s[i] == s[i + 1])
                bad.insert(i);
        bad.insert(n - 1);
        bad.insert(n);
        bad.insert(n + 1);
        ll ans = 0;
        for (int i = 0; i < n; ++i)
        {
            auto it = bad.lower_bound(i);
            auto it2 = bad.lower_bound(*it + 1);
            auto it3 = bad.lower_bound(*it2 + 1);

            int j = *it;
            int k = min(n - 1, *it2);
            int l = min(n - 1, *it3);

            ans += j - i + 1;
            if (s[i] != s[j])
                ans += k - j;
            else
                ans += (k - j) / 2;

            if (s[j] == s[k])
                continue;
            ans += l - k;
        }
        cout << ans << '\n';
    }
}

void h2()
{
    ll x1, x2, y1, y2, z1, z2, k;
    cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> k;

    ll dx = abs(x2 - x1), dy = abs(y2 - y1), dz = abs(z2 - z1);

    vector<ll> v = {dx, dy, dz};

    sort(all(v), greater<>());

    dx = v[0], dy = v[1], dz = v[2];

    ll t = ((dy + dz + 1) * 1ll * k);
    ll ans = dx + dy + dz;

    if (dx > t)
    {
        ll rmid = (dx - t + k - 1) / k;
        ans += rmid;
        ans += (rmid % 2);
    }

    cout << ans << endl;
}

void h3()
{
    string s;
    cin >> s;
    int n = s.size();

    string ans = "";
    string pref = "", suff = "";
    string temp;

    for (int i = 0; i < n; i++)
    {
        pref += s[i];
        suff = s.substr(n - i - 1);

        if (pref == suff)
        {
            int slen = suff.size();
            temp = s.substr(1, n - 2);
            if (temp.find(pref) != string::npos)
            {
                ans = pref;
            }
        }
    }

    if (ans.size() == 0)
    {
        cout << "Just a legend";
    }
    else
    {
        cout << ans;
    }
}

void h4()
{
    int n;
    cin >> n;
    vector<int> v(2 * n);

    int s = 0, r = 0;
    fl(i, 2 * n)
    {
        cin >> v[i];
        if (v[i] == 1)
            s++;
        else
            r++;
    }

    unordered_map<int, int> rmap;
    int diff = s - r;
    int diffl = 0, diffr = 0;

    for (int i = n; i < 2 * n; i++)
    {
        if (v[i] == 1)
            diffr++;
        else
            diffr--;
        if (!rmap.count(diffr))
        {
            rmap[diffr] = (i - n + 1);
        }
    }
    int ans = 2 * n;
    if (diff == 0)
    {
        ans = 0;
    }
    else
    {
        for (int i = n - 1; i >= 0; i--)
        {
            if (v[i] == 1)
                diffl++;
            else
                diffl--;
            if (rmap.count(diff - diffl))
            {
                ans = min(ans, (n - i) + rmap[diff - diffl]);
            }
        }
    }

    cout << ans << endl;
}

#define bulbula bool bula = false

void h5()
{
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    if (is_sorted(a.begin(), a.end()))
        cout << n << "\n";
    else
    {
        if (n == 2)
            cout << 0 << "\n";
        else
        {
            bool ok = false;
            for (int i = 0; i < n; ++i)
            {
                if (a[i] == i + 1)
                {
                    ok = true;
                    break;
                }
            }
            cout << (ok ? (n - 1) : (n - 2)) << "\n";
        }
    }
}

ll memo[3 * 1000 + 5];

ll summer(int pos, int n, vector<int> &v)
{
    if (pos == n - 1)
    {
        // for (auto i : v)
        // {
        //     cout << i << " ";
        // }
        // cout << endl;
        return v[pos];
    }

    if (memo[pos] != -1)
    {
        return memo[pos];
    }
    ll ans = INT_MAX;
    if ((v[pos - 1] + v[pos + 1]) == 4)
    {
        v[pos] = (4 - v[pos]);
        ans = (v[pos]) + summer(pos + 1, n, v);
        v[pos] = (4 - v[pos]);
    }
    ans = min(ans, v[pos] + summer(pos + 1, n, v));
    return memo[pos] = ans;
}

void h6()
{
    int n;
    cin >> n;

    vector<int> v(n);

    fl(i, n)
    {
        cin >> v[i];
    }

    memset(memo, -1, sizeof(memo));

    ll sum = v[0] + summer(1, n, v);

    cout << sum << endl;
}

void h61()
{
    int n;
    cin >> n;

    vector<int> v(n);

    fl(i, n)
    {
        cin >> v[i];
    }

    vector<int> temp = v;
    for (int i = 0; i < n - 2; i++)
    {
        if ((v[i] + v[i + 2]) == 4)
        {
            if (v[i + 1] == 3)
            {
                v[i + 1] = 1;
            }
        }
    }

    ll sum = accumulate(all(v), 0ll);
    for (int i = n - 1; i > 1; i--)
    {
        if ((temp[i] + temp[i - 2]) == 4)
        {
            if (temp[i - 1] == 3)
            {
                temp[i - 1] = 1;
            }
        }
    }

    sum = min(sum, accumulate(all(temp), 0ll));
    cout << sum << endl;
}

void aq()
{
    ll n;
    cin >> n;

    if (n % 33 == 0)
    {
        py
    }
    else
        pn
}

void bq()
{
    int n, k;
    cin >> n >> k;

    int curr = 1;
    vector<int> ans(n, 0);
    int lim = (n / k);

    for (int i = 1; i <= (lim); i++)
    {
        ans[(i * k) - 1] = curr++;
    }

    for (int i = 0; i < n; i++)
    {
        if (ans[i] == 0)
        {
            ans[i] = curr++;
        }
    }

    for (auto i : ans)
    {
        cout << i << " ";
    }
    cout << endl;
}

void cq()
{
}

void dq()
{
    ll n, k;
    cin >> n >> k;
    vector<ll> v(n);
    fl(i, n)
    {
        cin >> v[i];
    }

    sort(all(v), greater<>());
    ll sum = 0;

    for (int i = 0; i < n; i++)
    {
        sum += v[i];
        if (sum > k)
        {
            sum -= v[i];
            break;
        }
    }

    ll ans = k - sum;
    cout << ans << endl;
}

void eq()
{
    int n;
    cin >> n;
    unordered_map<int, int> freq;

    fl(i, n)
    {
        int e;
        cin >> e;
        freq[e]++;
    }

    int singlefreq = 0;
    for (auto i : freq)
    {
        if (i.second == 1)
            singlefreq++;
    }

    int rem = (int)freq.size() - singlefreq;

    int ans = (singlefreq + 1) / 2;
    ans *= 2;
    ans += rem;

    cout << ans << endl;
}

// https://codeforces.com/contest/2042/problem/C
void div2c()
{
    ll n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    vector<int> v(n);

    fl(i, n)
    {
        v[i] = (s[i] == '1');
    }

    int ones = 0, zeros = 0;
    vector<ll> suff(n);

    for (int i = n - 1; i >= 0; i--)
    {
        ones += v[i];
        zeros += (!v[i]);
        suff[i] = (ones - zeros);
    }
    // 1st element can't be included in sum because it is * by 0
    // so it has no significance in summation :)

    vector<ll> t(suff.begin() + 1, suff.end());
    sort(all(t), greater<>());
    ll sum = 0ll;
    ll ans = 1;
    for (auto i : t)
    {
        sum += i;
        ans++;
        if (sum >= k)
        {
            break;
        }
    }
    if (sum < k)
    {
        cout << -1 << endl;
        return;
    }
    cout << ans << endl;
}

int vitdp[1001][3][3][3];

struct Vitamins
{
    int cost;
    int a, b, c;

    // default constructor is required if we need to create a containner of this structure
    // If the Vitamins object is being used in a context where a default constructor is required
    // (such as in an array
    // or container), the absence of a default constructor will cause the compilation to fail.

    // other way to handle this is to always use parameterized constructor, so we need to use push_back
    // and can't declare size of vector upfront.

    // Vitamins() : cost(0), a(0), b(0), c(0) {}
    Vitamins(int cost_, int a_, int b_, int c_) : cost(cost_), a(a_), b(b_), c(c_) {};
};

ll dphelper(vector<Vitamins> &v, int pos = 0, int a = 0, int b = 0, int c = 0)
{
    if (a and b and c)
    {
        return 0ll;
    }
    int n = v.size();

    if (pos == n)
    {
        return INT_MAX;
    }

    // if (vitdp[pos][a][b][c] != -1)
    // {
    //     return vitdp[pos][a][b][c];
    // }

    ll ans = v[pos].cost + dphelper(v, pos + 1, a + v[pos].a, b + v[pos].b, c + v[pos].c);

    ans = min(ans, dphelper(v, pos + 1, a, b, c));

    return vitdp[pos][a][b][c] = ans;
}

void dp1q()
{
    int n;
    cin >> n;
    std::vector<Vitamins> v;

    fl(i, n)
    {
        int cost;
        cin >> cost;
        string s;
        cin >> s;
        int a = 0, b = 0, c = 0;
        if (s.find("A") != string::npos)
        {
            a = 1;
        }
        if (s.find("B") != string::npos)
        {
            b = 1;
        }
        if (s.find("C") != string::npos)
        {
            c = 1;
        }
        Vitamins vi(cost, a, b, c);
        v.push_back(vi);
    }

    memset(vitdp, -1, sizeof(vitdp));
    ll ans = dphelper(v);

    ans = (ans > 3 * 1ll * 1e5) ? -1 : ans;

    cout << ans << endl;
}

void sole()
{
    int n;
    cin >> n;
    if ((n % 2) != 0)
    {
        cout << 0;
    }
    else
    {
        ll ans = pow(2, n / 2);
        cout << ans << endl;
    }
}

#define pss pair<string, string>

void lyricist()
{
    int n;
    cin >> n;

    unordered_map<char, vector<pair<string, int>>> lastvowel;
    unordered_map<int, vector<pair<string, int>>> lengthtoWord;
    int numVowels;
    string s, vowels = "aeiou";
    vector<int> vis(n, 0);

    fl(i, n)
    {
        cin >> s;
        char lastv;
        numVowels = 0;
        for (auto j : s)
        {
            if (vowels.find(j) != string::npos)
            {
                lastv = j;
                numVowels++;
            }
        }
        lengthtoWord[numVowels].push_back({s, i});
        lastvowel[lastv].push_back({s, i});
    }

    vector<pss> completeduos, semicompleteduos;
    unordered_map<int, vector<pair<string, int>>> mp;

    for (auto i : lastvowel)
    {
        auto vt = i.second;
        mp.clear();

        for (auto j : vt)
        {
            numVowels = 0;
            for (auto p : j.first)
            {
                if (vowels.find(p) != string::npos)
                {
                    numVowels++;
                }
            }
            mp[numVowels].push_back(j);
        }

        for (auto j : mp)
        {
            int len = j.second.size();
            for (int k = 0; k < len - 1; k += 2)
            {
                completeduos.push_back({j.second[k].first, j.second[k + 1].first});
                vis[j.second[k].second] = 1;
                vis[j.second[k + 1].second] = 1;
            }
        }
    }

    for (auto i : lengthtoWord)
    {
        auto vt = i.second;
        int pos = 0;

        // cout << i.first << ":- ";
        // for (auto j : vt)
        // {
        //     cout << j.first << " ";
        // }
        // cout << endl;

        while (pos < (int)vt.size() - 1)
        {
            if (vis[vt[pos].second])
            {
                pos++;
                continue;
            }
            else
            {
                string fr = vt[pos].first;
                pos++;
                while (pos < (int)vt.size())
                {
                    if (vis[vt[pos].second])
                    {
                        pos++;
                    }
                    else
                    {
                        break;
                    }
                }
                if (pos < vt.size())
                {
                    string sec = vt[pos].first;
                    semicompleteduos.push_back({fr, sec});
                    pos++;
                }
            }
        }
    }

    // for (auto i : completeduos)
    // {
    //     cout << i.first << " " << i.second << endl;
    // }

    // cout << "Semi duos\n";
    // for (auto i : semicompleteduos)
    // {
    //     cout << i.first << " " << i.second << endl;
    // }

    vector<pair<pss, pss>> ans;

    int i = 0, j = 0;

    while (i < (int)semicompleteduos.size() and j < (int)completeduos.size())
    {
        ans.push_back({semicompleteduos[i], completeduos[j]});
        i++;
        j++;
    }
    while ((j + 1) < (int)completeduos.size())
    {
        ans.push_back({completeduos[j], completeduos[j + 1]});
        j += 2;
    }

    cout << (int)ans.size() << endl;
    for (auto i : ans)
    {
        cout << i.first.first << " " << i.second.first << "\n"
             << i.first.second << " " << i.second.second << "\n";
    }
}

void tetris()
{
    int n, m;
    cin >> n >> m;
    vector<int> v(n, 0);

    fl(i, m)
    {
        int e;
        cin >> e;
        v[e - 1]++;
    }

    int mini = *min_element(all(v));

    cout << mini;
}

void lines()
{
    int n;
    cin >> n;

    vector<pll> points, rem;

    if (n <= 4)
    {
        py;
        return;
    }

    fl(i, n)
    {
        ll x, y;
        cin >> x >> y;
        points.push_back({x, y});
    }

    sort(all(points));

    ll dx = points[1].first - points[0].first;
    ll dy = points[1].second - points[0].second;

    double slope;

    if (dx != 0)
    {
        slope = dy / dx;

        for (int i = 2; i < n; i++)
        {
            dx = points[i].first - points[0].first;
            dy = points[i].second - points[0].second;

            if (dx != 0)
            {
                double m = (dy / dx);
                if (m != slope)
                {
                    rem.push_back(points[i]);
                }
            }
            else
            {
                rem.push_back(points[i]);
            }
        }

        if (rem.size() <= 2)
        {
            py;
            return;
        }

        dx = rem[1].first - rem[0].first;
        dy = rem[1].second - rem[0].second;

        double slope2;

        if (dx != 0)
        {
            slope2 = dy / dx;
            for (int i = 2; i < rem.size(); i++)
            {
                dx = rem[i].first - rem[0].first;
                dy = rem[i].second - rem[0].second;

                if (dx != 0)
                {
                    double m = (dy / dx);
                    if (m != slope2)
                    {
                        pn;
                        return;
                    }
                }
                else
                {
                    pn;
                    return;
                }
            }
        }
        else
        {
            for (auto i : rem)
            {
                if (i.first != rem[0].first)
                {
                    pn;
                    return;
                }
            }
            py;
            return;
        }
    }
    else
    {
        for (int i = 2; i < n; i++)
        {
            if (points[i].first == points[0].first)
            {
                continue;
            }
            else
            {
                rem.push_back(points[i]);
            }
        }

        if (rem.size() <= 2)
        {
            py;
            return;
        }

        dx = rem[1].first - rem[0].first;
        dy = rem[1].second - rem[0].second;

        double slope2;

        if (dx != 0)
        {
            slope2 = dy / dx;
            for (int i = 2; i < rem.size(); i++)
            {
                dx = rem[i].first - rem[0].first;
                dy = rem[i].second - rem[0].second;

                if (dx != 0)
                {
                    double m = (dy / dx);
                    if (m != slope2)
                    {
                        pn;
                        return;
                    }
                }
                else
                {
                    pn;
                    return;
                }
            }
        }
        else
        {
            for (auto i : rem)
            {
                if (i.first != rem[0].first)
                {
                    pn;
                    return;
                }
            }
            py;
            return;
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // ll t;
    // cin >> t;

    // while (t--)
    lines();

    return 0;
}