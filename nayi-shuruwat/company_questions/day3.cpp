
#include <bits/stdc++.h>
using namespace std;

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

struct Obj
{
    string value;
    int next;
};

string findReplaceString(string s, vector<int> &indices, vector<string> &sources, vector<string> &targets)
{

    int n = sources.size();
    int sz = s.size();
    vector<Obj> ans(sz);

    string p;
    for (int i = 0; i < sz; i++)
    {
        p = "";
        p += s[i];
        ans[i] = {p, (i != (sz - 1)) ? (i + 1) : -1};
    }

    for (int i = 0; i < n; i++)
    {
        int start = indices[i];
        string src = sources[i], tgt = targets[i];
        int len = src.size();
        string temp = s.substr(start, len);
        if (temp == src)
        {
            ans[start].next = start + len;
            ans[start].value = tgt;
        }
    }

    string result = "";

    for (int i = 0; i < sz;)
    {
        result += ans[i].value;
        i = ans[i].next;
        if (i == -1)
        {
            break;
        }
    }

    return result;
}

void solve1()
{
    int n;
    cin >> n;
    vector<int> v(1e4 + 2, 0);
    ll maxi = 1;

    fl(i, n)
    {
        ll e;
        cin >> e;
        maxi = max(maxi, e);
        v[e]++;
    }

    if (n == 2)
    {
        cout << 1 << " " << 1 << endl;
        return;
    }

    int x = maxi, y = 1;
    v[x]--;

    for (int i = 2; i <= sqrt(x); i++)
    {
        if ((maxi % i) == 0)
        {

            if ((maxi % i) == 0)
            {
                maxi /= i;

                v[i]--;
                ll other = (x / i);

                if (i != other)
                {
                    v[other]--;
                }
            }
        }
    }

    for (int i = x; i > 1; i--)
    {
        if (v[i])
        {
            y = i;
            break;
        }
    }

    cout << x << " " << y;
}

void r1()
{
    int n;
    cin >> n;

    int ans = n - 1;

    cout << ans << endl;
}

void r2()
{
    int n, a, b, c;
    cin >> n >> a >> b >> c;

    int maxi = min(n, a);
    int ans = maxi;
    int n1 = n - maxi;
    maxi = min(n, b);
    ans += maxi;
    int n2 = n - maxi;

    int rem = n1 + n2;
    ans += min(rem, c);
    cout << ans << endl;
}

void r3()
{
    int n;
    cin >> n;

    vector<int> v(n);

    fl(i, n)
    {
        cin >> v[i];
    }

    vector<int> mp(n + 1, 0);
    vector<int> ans(n);

    int maxfr = 0;
    int maxelem = -1;

    for (int i = 0; i < n; i++)
    {
        int curr = v[i];
        ans[i] = curr;
        mp[curr]++;
        maxfr = max(maxfr, mp[curr]);

        if (mp[curr] != maxfr)
        {
            int j = i - 1;
            while (j >= 0 and mp[curr] != maxfr)
            {
                if (ans[j] == maxelem)
                {
                    maxfr--;
                }
                mp[ans[j]]--;
                ans[j] = curr;
                mp[curr]++;

                j--;
            }
        }
        else
        {
            maxelem = curr;
        }
    }

    for (auto i : ans)
    {
        cout << i << " ";
    }

    cout << endl;
}

void s1()
{
    ll k, l1, r1, l2, r2;
    cin >> k >> l1 >> r1 >> l2 >> r2;

    ll ans = 0;
    for (int i = 0; i < 1000; i++)
    {
        ll curr = 0;
        ll pw = pow(k, i);
        ll x1 = (l2) / pw;
        x1 = max(l1, x1);

        ll x2 = (r2) / pw;
        x2 = min(x2, r1);

        curr += x2 - x1 + 1;
        // cout << x1 << " " << x2 << endl;
        // cout << curr << endl;

        if ((x2 < l1) || (x1 > r1))
        {
            continue;
        }

        ans += curr;
    }

    cout << ans << endl;
}

void s2()
{
    int n, m, q;
    cin >> n >> m >> q;

    vector<int> a(n), b(m);
    ll A = 0, B = 0;

    unordered_set<int> st;
    fl(i, n)
    {
        cin >> a[i];
        st.insert(a[i]);
    }

    unordered_set<int> st2;
    fl(i, m)
    {
        cin >> b[i];
        st2.insert(b[i]);
    }

    A = accumulate(all(a), 0ll);
    B = accumulate(all(b), 0ll);

    ll sum = A * 1ll * B;

    while (q--)
    {
        ll x;
        cin >> x;

        vector<int> facts = {(int)abs(x)};

        for (int i = 1; i <= sqrt(abs(x)); i++)
        {
            if ((x % i) == 0)
            {
                facts.push_back(i);
                if (abs(x) != (i * i))
                {
                    facts.push_back(abs(x / i));
                }
            }
        }

        // for (auto i : facts)
        // {
        //     cout << i << " ";
        // }
        // cout << endl;

        bool f = false;

        for (int j = 0; j < facts.size(); j++)
        {
            int prod = facts[j];
            int rem = x / prod;

            // cout << prod << " " << rem << endl;
            if (st.count(A - prod) and st2.count(B - rem))
            {
                cout << "YES\n";
                f = true;
                break;
            }
            if (st.count(A - rem) and st2.count(B - prod))
            {
                cout << "YES\n";
                f = true;
                break;
            }
            prod = -facts[j];
            rem = x / prod;

            // cout << prod << " " << rem << endl;
            if (st.count(A - prod) and st2.count(B - rem))
            {
                cout << "YES\n";
                f = true;
                break;
            }
            if (st.count(A - rem) and st2.count(B - prod))
            {
                cout << "YES\n";
                f = true;
                break;
            }
            if (f)
                break;
        }

        if (f == false)
        {
            cout << "NO\n";
        }
    }
}

void s3()
{
    ll a, b, c;
    cin >> a >> b >> c;

    vector<ll> v = {a, b, c};

    ll maxi = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (i == j)
                continue;
            ll alice = v[i], bob = v[j];
            ll other = 3 - (i + j);
            ll total = v[other];
            ll diff = abs(alice - bob);
            if (alice <= bob)
            {
                if (total >= diff)
                {
                    alice = bob;
                    total -= diff;

                    alice += (total / 2);
                    bob += (total / 2);
                }
                else
                {
                    alice += total;
                    total = 0;
                    bob = alice;
                }
            }
            else
            {
                if (total >= diff)
                {
                    bob = alice;
                    total -= diff;
                    alice += (total / 2);
                    bob += (total / 2);
                }
                else
                {
                    bob += total;
                    total = 0;
                    alice = bob;
                }
            }

            maxi = max(maxi, alice);
        }
    }
    cout << maxi << endl;
}

void s4()
{
    int n, k;
    cin >> n >> k;

    vector<int> v(n);

    fl(i, n)
    {
        cin >> v[i];
        if ((v[i] % 2))
        {
            v[i] = 1;
        }
        else
        {
            v[i] = 0;
        }
    }

    bool isposs = true;

    vector<int> ans;
    int i = 0;
    int remsegs = k;

    while (i < n and v[i] == 0)
    {
        i++;
    }

    i++;
    while (i < n and remsegs > 1)
    {
        while (i < n and v[i] == 0)
        {
            i++;
        }
        ans.push_back(i);
        remsegs--;
        i++;
    }

    int remones = (i <= n) ? 1 : 0;

    while (i < n)
    {
        if (v[i] == 1)
            remones++;
        i++;
    }

    if ((remones % 2) == 0 || remsegs > 1)
    {
        cout << "NO\n";
        return;
    }

    cout << "YES\n";

    ans.push_back(n);

    for (auto i : ans)
    {
        cout << i << " ";
    }
    cout << endl;
}

void s5()
{
    int n;
    cin >> n;

    vector<int> a(n), occ(n + 1, 0);
    vector<int> ans(n, -1);

    fl(i, n)
    {
        cin >> a[i];
    }

    for (int i = 0; i < n; i++)
    {
        int e = a[i];
        if (occ[e] == 0)
        {
            ans[i] = e;
        }
        occ[e]++;
    }
    int j = 1;
    fl(i, n)
    {
        if (ans[i] == -1)
        {
            while (j < n and occ[j] >= 1)
            {
                j++;
            }
            ans[i] = j++;
        }
    }

    for (auto i : ans)
    {
        cout << i << " ";
    }
    cout << endl;
}

// functional graphs (each node has only 1 successor)
// it implies there is always a cycle in such graphs
// and each node is either part of the cycle or
// leads to the cycle

void dfs(vector<int> &vis, int node, vector<int> &succ, int id)
{
    vis[node]++;
    if (vis[succ[node]] < 2)
        dfs(vis, succ[node], succ, id);
}

int dfs2(int node, vector<int> &t, vector<int> &succ)
{
    if (t[node] != -1)
    {
        return t[node];
    }

    return t[node] = 1 + dfs2(succ[node], t, succ);
}

void s6()
{
    int n;
    cin >> n;
    vector<int> succ(n);
    vector<int> indegree(n, 0);

    fl(i, n)
    {
        cin >> succ[i];
        succ[i]--;
        indegree[succ[i]]++;
    }

    int id = 1;

    vector<int> vis(n, 0);
    vector<int> t(n, -1);
    bool fullcycle = true;

    fl(i, n)
    {
        if (indegree[i] == 1 and vis[i] == 0)
        {
            dfs(vis, i, succ, id);
            id++;
        }
        else if (indegree[i] == 0)
        {
            fullcycle = false;
        }
    }

    if (fullcycle)
    {
        cout << 2 << endl;
        return;
    }

    for (int i = 0; i < n; i++)
    {
        if (vis[i] >= 2)
        {
            t[i] = 0;
        }
    }

    int maxdist = 0;

    for (int i = 0; i < n; i++)
    {
        int currdist = dfs2(i, t, succ);
        maxdist = max(maxdist, currdist + 2);
    }

    // for (auto i : vis)
    // {
    //     cout << i << " ";
    // }
    cout << maxdist << endl;
}

void s7()
{
    int n;
    cin >> n;

    ll lx = -1e6, rx = 1e6, ly = -1e6, ry = 1e6;

    vector<pair<pair<int, int>, vector<int>>> vp(n);
    fl(i, n)
    {
        int x, y;
        vector<int> v(4);
        cin >> x >> y;
        fl(j, 4)
        {
            cin >> v[j];
        }
        vp[i] = make_pair(make_pair(x, y), v);
    }

    fl(i, n)
    {
        ll x = vp[i].first.first, y = vp[i].first.second;
        vector<int> v = vp[i].second;

        // if (!(x >= lx and x <= rx and y >= ly and y <= ry))
        // {
        //     cout << 0 << endl;
        //     return;
        // }

        if (v[1] == 1 and v[3] == 0)
        {
            if (ly <= y and y <= ry)
            {
            }
            else
            {
                cout << 0 << endl;
                return;
            }
        }
        if (v[1] == 0 and v[3] == 1)
        {
            if (ly <= y and y <= ry)
            {
            }
            else
            {
                cout << 0 << endl;
                return;
            }
        }
        if (v[0] == 1 and v[2] == 0)
        {
            if (lx <= x and x >= rx)
            {
            }
            else
            {
                cout << 0 << endl;
                return;
            }
        }
        if (v[0] == 0 and v[2] == 1)
        {
            if (lx <= x and x >= rx)
            {
            }
            else
            {
                cout << 0 << endl;
                return;
            }
        }
        if (v[1] == 0 and v[3] == 0)
        {
            if (y >= ly and y <= ry)
            {
                ly = y;
                ry = y;
            }
            else
            {
                cout << 0 << endl;
                return;
            }
        }
        if (v[0] == 0 and v[2] == 0)
        {
            if (x >= lx and x <= rx)
            {
                lx = x;
                rx = x;
            }
            else
            {
                cout << 0 << endl;
                return;
            }
        }
    }

    if ((lx > rx) || (ly > ry))
    {
        cout << 0 << endl;
        return;
    }

    lx = rx;
    ly = ry;

    if (lx > 1e5 and ly > 1e5)
    {
        lx = 1;
        ly = 1;
    }

    cout << 1 << " " << lx << " " << ly << endl;
}

int findOper(string s, string target)
{
    int k = target.size();
    int pos = 0;
    int minopers = INT_MAX, curroper = 0;
    int n = s.size();
    for (int i = 0; i < k; i++)
    {
        if (s[i] != target[i])
        {
            curroper++;
        }
    }

    minopers = min(minopers, curroper);

    if (minopers == 0)
        return 0;
    for (int i = 1; i <= (n - k); i++)
    {
        curroper = 0;
        for (int j = 0; j < k; j++)
        {
            if (s[i + j] != target[j])
            {
                curroper++;
            }
        }
        minopers = min(minopers, curroper);
        if (minopers == 0)
            return 0;
    }
    return minopers;
}

void rgbInfiniteStringSimple()
{
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;

    string rgb = "RGB";
    string temp = "";
    int pos = 0, modrgb = 3;
    for (int i = 0; i < k; i++)
    {
        temp += rgb[pos];
        pos = (pos + 1) % modrgb;
    }
    // cout << temp << endl;
    int minoper = findOper(s, temp);

    temp = "";
    pos = 1;
    for (int i = 0; i < k; i++)
    {
        temp += rgb[pos];
        pos = (pos + 1) % modrgb;
    }

    minoper = min(minoper, findOper(s, temp));

    temp = "";
    pos = 2;

    for (int i = 0; i < k; i++)
    {
        temp += rgb[pos];
        pos = (pos + 1) % modrgb;
    }

    minoper = min(minoper, findOper(s, temp));

    cout << minoper << endl;
}

int findOperEnhanced(vector<int> &diff, int k)
{
    int minoper = INT_MAX;
    int curroper = 0;
    int n = diff.size();

    for (int i = 0; i < k; i++)
    {
        curroper += diff[i];
    }

    minoper = min(minoper, curroper);

    for (int i = k; i < n; i++)
    {
        curroper -= diff[i - k];
        curroper += diff[i];
        minoper = min(minoper, curroper);
    }

    return minoper;
}

void rgbInfiniteString()
{
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;

    string rgb = "RGB";
    string temp = "";
    int pos = 0, modrgb = 3;
    for (int i = 0; i < n; i++)
    {
        temp += rgb[pos];
        pos = (pos + 1) % modrgb;
    }

    vector<int> diff(n);

    fl(i, n)
    {
        diff[i] = (s[i] != temp[i]);
    }

    int minopers = findOperEnhanced(diff, k);
    // cout << temp << endl;

    temp = "";
    pos = 1;
    for (int i = 0; i < n; i++)
    {
        temp += rgb[pos];
        pos = (pos + 1) % modrgb;
    }

    vector<int> diff2(n);
    fl(i, n)
    {
        diff2[i] = (s[i] != temp[i]);
    }
    // cout << temp << endl;

    minopers = min(minopers, findOperEnhanced(diff2, k));

    temp = "";
    pos = 2;
    for (int i = 0; i < n; i++)
    {
        temp += rgb[pos];
        pos = (pos + 1) % modrgb;
    }

    vector<int> diff3(n);
    fl(i, n)
    {
        diff3[i] = (s[i] != temp[i]);
    }
    // cout << temp << endl;

    minopers = min(minopers, findOperEnhanced(diff3, k));

    cout << minopers << endl;
}

void s10()
{
    int n;
    cin >> n;
    string s, t;
    cin >> s >> t;

    vector<vector<int>> v(26);
    int d = 0;
    for (int i = 0; i < n; i++)
    {
        v[t[i] - 'a'].push_back(i);
    }
    vector<int> f1(26, 0), f2(26, 0);
    fl(i, n)
    {
        f1[s[i] - 'a']++;
        f2[t[i] - 'a']++;
    }
    fl(i, 26)
    {
        if (f1[i] != f2[i])
        {
            cout << -1 << endl;
            return;
        }
    }
    vector<int> ans;

    for (int i = 0; i < n; i++)
    {
        if (s[i] == t[i - d])
        {
            continue;
        }
        else
        {
            int last = v[s[i] - 'a'].back();
            v[s[i] - 'a'].pop_back();
            for (int j = i; j < last + d; j++)
            {
                ans.push_back(j - d);
            }
            d++;
        }
    }

    cout << (int)ans.size() << "\n";
    for (auto i : ans)
    {
        cout << i + 1 << " ";
    }
}

void s11()
{
    int n;
    cin >> n;
    vector<int> a(n);
    fl(i, n)
    {
        cin >> a[i];
        --a[i];
    }

    vector<bool> occupied(n, false);
    occupied[a[0]] = true;

    for (int j = 1; j < n; j++)
    {
        int i = a[j];
        bool isFollowing = false;
        occupied[i] = true;
        if (i - 1 >= 0 and occupied[i - 1])
        {
            isFollowing = true;
        }
        if (i + 1 < n and occupied[i + 1])
        {
            isFollowing = true;
        }
        if (!isFollowing)
        {
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
}

void s12()
{
    int n;
    cin >> n;
    vector<ll> v(n);
    vector<char> s(n);

    fl(i, n)
    {
        cin >> v[i];
    }

    fl(i, n)
    {
        cin >> s[i];
    }

    vector<int> rights;

    vector<ll> pref(n, 0);
    pref[0] = v[0];

    for (int i = 1; i < n; i++)
    {
        pref[i] = pref[i - 1] + v[i];
    }

    for (int i = n - 1; i >= 0; i--)
    {
        if (s[i] == 'R')
            rights.push_back(i);
    }

    ll sum = 0;
    int pos = 0;

    for (int i = 0; i < n; i++)
    {
        if (s[i] == 'L')
        {
            if (pos < (int)rights.size() and rights[pos] > i)
            {
                int l = i, r = rights[pos];
                pos++;
                sum += (pref[r] - (l == 0 ? 0 : pref[l - 1]));
            }
            else
            {
                break;
            }
        }
    }

    cout << sum << endl;
}

vector<vector<ll>> calculateFrequency(int n, int m, int k)
{
    vector<vector<ll>> grid(n + 1, vector<ll>(m + 1, 0));

    // Step 1: Apply the difference array updates
    for (int i = 0; i <= n - k; i++)
    {
        for (int j = 0; j <= m - k; j++)
        {
            grid[i][j]++;
            grid[i + k][j + k]++;
            grid[i][j + k]--;
            grid[i + k][j]--;
        }
    }

    // Step 2: Perform row-wise prefix sums
    for (int i = 0; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            grid[i][j] += grid[i][j - 1];
        }
    }

    // Step 3: Perform column-wise prefix sums
    for (int j = 0; j <= m; j++)
    {
        for (int i = 1; i <= n; i++)
        {
            grid[i][j] += grid[i - 1][j];
        }
    }

    // Step 4: Trim the grid to size n x m
    vector<vector<ll>> result(n, vector<ll>(m, 0));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            result[i][j] = grid[i][j];
        }
    }

    return result;
}

void s13()
{
    int n, m;
    cin >> n >> m;
    int k;
    cin >> k;
    int w;
    cin >> w;

    vector<ll> gor(w);
    fl(i, w)
    {
        cin >> gor[i];
    }
    sort(all(gor), greater<>());

    vector<vector<ll>> grid = calculateFrequency(n, m, k);

    map<ll, ll> freq;

    for (auto i : grid)
    {
        for (auto j : i)
        {
            freq[j]++;
        }
    }

    auto it = freq.rbegin();

    ll ans = 0;
    int pos = 0;

    while (it != freq.rend())
    {
        auto f = it->second, val = it->first;
        // f kya hai ? kitne cells hai iss freq ke

        for (int i = 0; i < f and pos < w; i++)
        {
            ans += gor[pos++] * 1ll * val;
        }

        ++it;
    }

    cout << ans << endl;
}

void s14()
{
    int n, points;
    cin >> n >> points;

    vector<int> rows(n), cols(n);

    fl(i, n)
    {
        cin >> rows[i] >> cols[i];
    }

    vector<vector<ll>> cost(n + 1, vector<ll>(points + 1, 1e9));

    for (int i = 0; i <= n; i++)
    {
        cost[i][0] = 0;
    }

    fl(i, n)
    {
        fl(j, rows[i] + 1)
        {
            fl(k, cols[i] + 1)
            {
                int total = j + k;
                if (total <= points)
                {
                    ll val = (rows[i] * (k)) + (cols[i] * (j)) - (j * k);

                    cost[i][total] = min(cost[i][total], val);
                }
            }
        }
    }

    // for (auto i : cost)
    // {
    //     for (auto j : i)
    //     {
    //         cout << j << " ";
    //     }
    //     cout << endl;
    // }

    vector<vector<ll>> dp(n + 1, vector<ll>(points + 1, 1e9));

    for (int i = 0; i <= n; i++)
    {
        dp[i][0] = 0;
    }

    for (int i = 1; i <= n; i++)
    {
        int r = rows[i - 1], c = cols[i - 1];
        int total = r + c;
        for (int j = 0; j <= min(total, points); j++)
        {
            for (int t = 0; (j + t) <= points; t++)
            {
                dp[i][j + t] = min(dp[i][j + t], dp[i - 1][t] + cost[i - 1][j]);
            }
        }
    }

    ll ans = (dp[n][points] >= 1e9) ? -1 : dp[n][points];

    cout << ans << endl;
}

bool ispossible(int n, int m, ll to, ll t1, ll t2, vector<vector<vector<ll>>> &adj, ll mid)
{
    vector<ll> time(n, 1e16);
    priority_queue<ll, vector<pll>, greater<>> pq;
    time[0] = mid;
    pq.push({mid, 0});

    while (!pq.empty())
    {
        auto front = pq.top();
        pq.pop();
        auto currtime = front.first, node = front.second;

        if (currtime > to)
        {
            continue;
        }

        for (auto state : adj[node])
        {
            ll neighbour = state[0], bustime = state[1], walktime = state[2];
            if ((currtime + bustime) <= to)
            {
                if (((currtime + bustime) <= t1))
                {
                    if ((bustime + currtime) < time[neighbour])
                    {
                        time[neighbour] = (bustime + currtime);
                        pq.push({time[neighbour], neighbour});
                    }
                }
                if ((bustime + max(t2, currtime)) < time[neighbour])
                {
                    time[neighbour] = (bustime + max(t2, currtime));
                    pq.push({time[neighbour], neighbour});
                }
                if ((walktime + currtime) < time[neighbour])
                {
                    time[neighbour] = (walktime + currtime);
                    pq.push({time[neighbour], neighbour});
                }
            }
        }
    }

    return (time[n - 1] <= to);
}

// Binary search approach
void s15()
{
    int n, m;
    ll to, t1, t2;
    cin >> n >> m >> to >> t1 >> t2;

    vector<vector<vector<ll>>> adjlist(n);

    fl(i, m)
    {
        int u, v, l1, l2;
        cin >> u >> v >> l1 >> l2;
        --u, --v;
        adjlist[u].push_back({v, l1, l2});
        adjlist[v].push_back({u, l1, l2});
    }

    ll low = 0, high = to - 1;
    ll mid, ans = -1;

    while (low <= high)
    {
        mid = (low + high) / 2;
        if (ispossible(n, m, to, t1, t2, adjlist, mid))
        {
            ans = mid;
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    cout << ans << endl;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    ll t;
    cin >> t;

    while (t--)
    {
        s15();
    }

    return 0;
}