
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
    vector<pll> v(n);

    fl(i, n)
    {
        cin >> v[i].first >> v[i].second;
    }

    int w = 0;

    for (int i = 0; i < n - 1; i++)
    {
        w += v[i].second;
        int diff = v[i + 1].first - v[i].first;
        w = max(0, w - diff);
    }

    w += v[n - 1].second;

    cout << w << endl;
    // last tip
}

int result = 0;
int h, w, d;

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

void bfs(vector<vector<char>> &grid, int x, int y, vector<vector<int>> &vis, int stx, int sty)
{
    int h = grid.size(), w = grid[0].size();
    vis[x][y] = 1;
    if (grid[x][y] == '#')
    {
        return;
    }

    for (int i = 0; i < 4; i++)
    {
        int newx = x + dx[i], newy = y + dy[i];
        if (newx >= 0 and newx < h and newy >= 0 and newy < w and vis[newx][newy] == 0 and grid[newx][newy] == '.')
        {
            int curr = abs(newx - stx) + abs(newy - sty);
            if (curr <= d)
            {
                vis[newx][newy] = 1;
                result++;
                grid[newx][newy] = '$';
                bfs(grid, newx, newy, vis, stx, sty);
            }
        }
    }
}

void solve2()
{
    cin >> h >> w >> d;

    vector<vector<char>> grid(h, vector<char>(w));

    vector<pii> humidifiers;

    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            cin >> grid[i][j];
            if (grid[i][j] == 'H')
            {
                humidifiers.push_back({i, j});
            }
        }
    }

    vector<vector<int>> vis(h, vector<int>(w, 0));

    for (auto i : humidifiers)
    {
        bfs(grid, i.first, i.second, vis, i.first, i.second);
    }

    result += (int)humidifiers.size();

    cout << result << endl;
}

void solve3()
{
    int n;
    cin >> n;
    vector<int> a(n);

    fl(i, n)
    {
        cin >> a[i];
    }

    vector<int> diff(n - 1);

    for (int i = 0; i < n - 1; i++)
    {
        diff[i] = a[i + 1] - a[i];
    }

    string s = "1$2$4$8$16";

    for (int i = 0; i < n - 1; i++)
    {
        string t = "";
        t += to_string(i + 1);
        if ((diff[i] < 0) and s.find(t) == string::npos)
        {
            cout << "NO\n";
            return;
        }
    }

    cout << "YES\n";
}

void solve4()
{
    int n, q;
    cin >> n >> q;

    vector<ll> a(n), queries(q);

    fl(i, n)
    {
        cin >> a[i];
    }

    fl(i, q)
    {
        cin >> queries[i];
    }

    ll minoper = INT_MAX;

    for (auto i : queries)
    {
        if (i >= minoper)
        {
            continue;
        }
        ll pw = pow(2, i);
        ll toadd = pow(2, i - 1);

        for (int j = 0; j < n; j++)
        {
            if ((a[j] % pw) == 0)
            {
                a[j] += toadd;
            }
        }
        minoper = min(minoper, i);
    }

    for (auto i : a)
    {
        cout << i << " ";
    }
    cout << endl;
}

void solve5()
{
    int n;
    cin >> n;

    vector<int> a(n);

    fl(i, n)
    {
        cin >> a[i];
    }

    sort(all(a));

    int p1 = 0, p2 = n - 1;
    ll opers = 0, x = 0;
    while (p1 <= p2)
    {
        if (p1 == p2)
        {
            opers++;
            opers += (a[p2] - x);
            a[p1] -= (a[p2] - x);
            x += a[p1];
            p1++;
            p2--;
        }
        else if ((a[p1] + x) >= a[p2])
        {
            opers++;
            opers += (a[p2] - x);
            a[p1] -= (a[p2] - x);
            x += a[p1];
            p1++;
            p2--;
        }
        else
        {
            opers += a[p1++];
            x += a[p1];
        }
        // debug
        // cout << opers << " " << x << " ";
    }

    cout << opers << endl;
}

void solve6()
{
    int n;
    cin >> n;

    string s;
    cin >> s;

    vector<int> segments;

    int i = 0;
    bool is3found = false;

    while (i < n)
    {
        while (i < n and s[i] == '#')
        {
            i++;
        }
        int sz = 0;
        while (i < n and s[i] == '.')
        {
            sz++;
            i++;
        }
        if (sz >= 3)
        {
            is3found = true;
        }
        segments.push_back(sz);
    }
    if (is3found)
    {
        cout << 2 << endl;
    }
    else
    {
        ll sum = accumulate(all(segments), 0);
        cout << sum << endl;
    }
}

int dp[201][201];

int check1sol(int a, int b, int c)
{
    if (a < 0 || b < 0 || c < 0)
        return 0;
    if (a > 0 and b == 0 and c == 0)
    {
        return 1;
    }

    if (dp[a][b] != -1)
    {
        return dp[a][b];
    }

    int ans = 0;

    if (b > 0 and c > 0)
    {
        ans |= check1sol(a + 1, b - 1, c - 1);
    }

    if (a > 0 and b > 0)
    {
        ans |= check1sol(a - 1, b - 1, c + 1);
    }

    if (a > 0 and c > 0)
    {
        ans |= check1sol(a - 1, b + 1, c - 1);
    }

    return dp[a][b] = ans;
}

int dp2[201][201];

int check2sol(int a, int b, int c)
{
    if (a < 0 || b < 0 || c < 0)
        return 0;
    if (a == 0 and b > 0 and c == 0)
    {
        return 1;
    }

    if (dp2[a][b] != -1)
    {
        return dp2[a][b];
    }

    int ans = 0;
    if (a > 0 and c > 0)
    {
        ans |= check2sol(a - 1, b + 1, c - 1);
    }
    if (b > 0 and c > 0)
    {
        ans |= check2sol(a + 1, b - 1, c - 1);
    }

    if (a > 0 and b > 0)
    {
        ans |= check2sol(a - 1, b - 1, c + 1);
    }

    return dp2[a][b] = ans;
}

int dp3[201][201];

int check3sol(int a, int b, int c)
{
    if (a < 0 || b < 0 || c < 0)
        return 0;
    if (a == 0 and b == 0 and c > 0)
    {
        return 1;
    }

    if (dp3[a][b] != -1)
    {
        return dp3[a][b];
    }

    int ans = 0;

    if (a > 0 and b > 0)
    {
        ans |= check3sol(a - 1, b - 1, c + 1);
    }

    if (b > 0 and c > 0)
    {
        ans |= check3sol(a + 1, b - 1, c - 1);
    }

    if (a > 0 and c > 0)
    {
        ans |= check3sol(a - 1, b + 1, c - 1);
    }

    return dp3[a][b] = ans;
}

void solve7()
{
    int a, b, c;
    cin >> a >> b >> c;

    memset(dp, -1, sizeof(dp));
    memset(dp2, -1, sizeof(dp2));
    memset(dp3, -1, sizeof(dp3));

    int check1 = check1sol(a, b, c), check2 = check2sol(a, b, c),
        check3 = check3sol(a, b, c);

    cout << check1 << " " << check2 << " " << check3 << endl;
}

int memo[100000 + 5][3];

int dpsolver(int currnode, vector<pii> &adj, unordered_map<int, int> &mp)
{
    if (adj[currnode].first == -1 and adj[currnode].second == -1)
    {
        return 0;
    }

    int left = adj[currnode].first, right = adj[currnode].second;
    int ans = INT_MAX;

    if (left != -1) // left child hai to wha ja skte hai
    {
        int curr = dpsolver(left, adj, mp);
        if (mp[currnode] == 1)
        {
            ans = min(ans, curr);
        }
        else
        {
            ans = min(ans, 1 + curr);
        }
    }
    if (right != -1) // right child hai to wha ja skte hai
    {
        int curr = dpsolver(right, adj, mp);
        if (mp[currnode] == 1)
        {
            ans = min(ans, curr);
        }
        else
        {
            ans = min(ans, 1 + curr);
        }
    }

    return dp[currnode][mp[currnode]] = ans;
}

void solve8()
{
    int n;
    cin >> n;

    vector<pii> adj(n);
    string s;
    cin >> s;
    for (int i = 0; i < n; i++)
    {
        int l, r;
        cin >> l >> r;
        --l, --r;
        adj[i] = {l, r};
    }

    unordered_map<int, int> mp;

    for (int i = 0; i < n; i++)
    {
        if (s[i] == 'U')
            mp[i] = 0;
        else if (s[i] == 'L')
            mp[i] = 1;
        else
            mp[i] = 2;
    }

    int ans = dpsolver(0, adj, mp);

    cout << ans << endl;
}

void solve9()
{
    int n;
    cin >> n;

    string a, b;
    cin >> a >> b;

    int p = 0, q = 0;

    fl(i, n)
    {
        if (a[i] == '0' and b[i] == '1')
            p++;
        else if (a[i] == '1' and b[i] == '0')
            q++;
    }

    if (p % 2 == q % 2)
    {
        cout << "YES\n";
    }
    else
    {
        cout << "NO\n";
    }
}

void solve10()
{
    string s;
    cin >> s;

    int mod0 = 0, mod1 = 0, mod2 = 0;
    int k = s.size();

    for (auto i : s)
    {
        int t = i - '0';
        if ((t % 3) == 0)
            mod0++;

        else if ((t % 3) == 1)
            mod1++;

        else
            mod2++;
    }

    int sum = (mod1 + (2 * mod2));
    int rem = sum % 3;

    if (rem == 0)
    {
        cout << 0;
    }
    else if (rem == 1)
    {
        if (mod1 and k > 1)
        {
            cout << 1;
        }
        else if (mod2 > 1 and k > 2)
        {
            cout << 2;
        }
        else
        {
            cout << -1;
        }
    }
    else
    {
        if (mod2 and k > 1)
        {
            cout << 1;
        }
        else if (mod1 > 1 and k > 2)
        {
            cout << 2;
        }
        else
        {
            cout << -1;
        }
    }
}

void solve11()
{
    int n;
    cin >> n;

    vector<ll> v(n);
    fl(i, n)
    {
        cin >> v[i];
    }

    ll max_x = 0, total_x = 0;
    ll currdist = 0, max_dist = 0;

    for (int i = 0; i < n; i++)
    {
        total_x += v[i];
        max_x = max(max_x, total_x);
        max_dist = max(max_dist, currdist + max_x);
        currdist += total_x;
    }

    cout << max_dist;
}

void solve12()
{
    ll n, a, b;
    cin >> n >> a >> b;

    if (b <= (2 * a))
    {
        ll cnt = n / 2;
        ll cost = cnt * 1ll * b;
        if (n % 2)
        {
            cost += a;
        }
        cout << cost << endl;
    }
    else
    {

        ll cost = n * 1ll * a;

        cout << cost << endl;
    }
}

void solve13()
{
    int n;
    cin >> n;
    vector<int> v(n);
    fl(i, n)
    {
        cin >> v[i];
    }

    vector<int> prefodd(n), prefeven(n);
    prefodd[0] = v[0], prefodd[1] = prefodd[0];
    prefeven[0] = 0, prefeven[1] = v[1];

    for (int i = 2; i < n; i += 2)
    {
        prefodd[i] = prefodd[i - 1] + v[i];
        if ((i + 1) < n)
            prefodd[i + 1] = prefodd[i];
    }

    for (int i = 2; i < n; i += 2)
    {
        prefeven[i] = prefeven[i - 1];
        if ((i + 1) < n)
            prefeven[i + 1] = prefeven[i] + v[i + 1];
    }

    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        int oddsum = ((i != 0) ? prefodd[i - 1] : 0) + prefeven[n - 1] - prefeven[i];
        int evensum = ((i != 0) ? prefeven[i - 1] : 0) + prefodd[n - 1] - prefodd[i];

        if (oddsum == evensum)
            ans++;
    }

    cout << ans << endl;
}

void rash1()
{
    int n;
    string s;
    char c1, c2;
    cin >> n >> c1 >> c2;
    cin >> s;

    for (int i = 0; i < n; i++)
    {
        if (s[i] != c1)
        {
            s[i] = c2;
        }
    }

    cout << s << endl;
}

void rash2()
{
    int n, r;
    cin >> n >> r;
    fl(i, n)
    {
        int d, a;
        cin >> d >> a;

        if (d == 1)
        {
            if (r >= 1600 and r <= 2799)
            {
                r += a;
            }
        }
        else
        {
            if (r >= 1200 and r <= 2399)
            {
                r += a;
            }
        }
    }

    cout << r;
}
vector<pair<int, string>> scores;

void solve(vector<int> &v, int pos, string s, int score = 0)
{
    if (pos == 5)
    {
        if (s == "")
        {
            return;
        }
        scores.push_back({score, s});
        return;
    }
    // 2 ch
    solve(v, pos + 1, s, score);
    string news = s;
    news += 'A' + pos;
    solve(v, pos + 1, news, score + v[pos]);
}

void rash3()
{
    vector<int> v(5);
    fl(i, 5)
    {
        cin >> v[i];
    }

    solve(v, 0, "");

    sort(all(scores), [](pair<int, string> &p1, pair<int, string> &p2)
         {
        if(p1.first!=p2.first){
            return p1.first > p2.first;
        }
        return p1.second < p2.second; });

    for (auto i : scores)
    {
        cout << i.second << endl;
    }
}

void rash4()
{
    ll n, sum;
    cin >> n >> sum;
    ll actual = sum;
    vector<int> v(n);
    ll segsum = 0;

    fl(i, n)
    {
        cin >> v[i];
        segsum += v[i];
    }

    ll q = sum / segsum;
    sum -= (q * 1ll * segsum);

    unordered_map<ll, int> prefmp;
    prefmp[0] = 0;
    ll currsum = 0;

    for (int i = 0; i < n; i++)
    {
        currsum += v[i];
        if (prefmp.count(currsum - sum))
        {
            cout << "Yes\n";
            return;
        }
        prefmp[currsum] = 1;
    }

    unordered_map<ll, int> suffmp;
    suffmp[0] = 0;

    currsum = 0;
    for (int i = n - 1; i >= 0; i--)
    {
        currsum += v[i];
        suffmp[currsum] = 1;
    }

    if (suffmp.count(sum) || prefmp.count(sum))
    {
        cout << "Yes\n";
        return;
    }

    currsum = 0;
    for (int i = 0; i < n; i++)
    {
        currsum += v[i];
        if (suffmp.count(currsum - actual) || suffmp.count(currsum - sum))
        {
            cout << "Yes\n";
            return;
        }
    }

    cout << "No";
}

void r5()
{
    int h, w, X, p, q;
    cin >> h >> w >> X >> p >> q;

    vector<vector<ll>> grid(h, vector<ll>(w));

    fl(i, h)
    {
        fl(j, w)
        {
            cin >> grid[i][j];
        }
    }

    double currstr = 0;
    vector<int> dx = {0, 0, 1, -1}, dy = {1, -1, 0, 0};
    vector<vector<ll>> used(h, vector<ll>(w, 0));
    int curr, prev = 0;

    while (true)
    {
        curr = 0;
        priority_queue<pll, vector<pll>, greater<>> pq;
        pq.push({p - 1, q - 1});

        vector<vector<ll>> vis(h, vector<ll>(w, 0));
        while (!pq.empty())
        {
            auto fr = pq.top();
            pq.pop();

            int x = fr.first, y = fr.second;
            if (used[x][y] == 0)
                currstr += grid[x][y];
            vis[x][y] = 1;
            used[x][y] = 1;
            curr++;
            for (int i = 0; i < 4; i++)
            {
                int newx = x + dx[i], newy = y + dy[i];
                if (newx >= 0 and newx < h and newy >= 0 and newy < w and
                    vis[newx][newy] == 0)
                {
                    double val = grid[newx][newy];
                    double lim = currstr / X;
                    if (val < lim)
                    {
                        pq.push({newx, newy});
                    }
                }
            }
        }
        if (curr == prev)
        {
            break;
        }
        prev = curr;
    }

    cout << currstr << endl;
}

void r1()
{
    int n;
    cin >> n;
    vector<int> v(n * n);

    unordered_map<int, int> freq;
    fl(i, n * n)
    {
        cin >> v[i];
        freq[v[i]]++;
    }

    if (n % 2 == 0)
    {
        for (auto i : freq)
        {
            if (i.second % 4 != 0)
            {
                cout << "NO\n";
                return;
            }
        }
        cout << "YES\n";
        sort(all(v));
        int grid[n][n];
        int pos = 0;
        for (int i = 0; i < n / 2; i++)
        {
            for (int j = 0; j < n / 2; j++)
            {
                grid[i][j] = v[pos++];
                grid[n - i - 1][j] = v[pos++];
                grid[i][n - j - 1] = v[pos++];
                grid[n - i - 1][n - j - 1] = v[pos++];
            }
        }
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cout << grid[i][j] << " ";
            }
            cout << endl;
        }
    }
    else
    {
        int cnt2freq = 0;
        int max2freq = (n / 2) * 2;
        bool alag = false;
        int diff;
        vector<int> fourwale, twowale;

        for (auto i : freq)
        {
            if ((i.second % 4) != 0)
            {
                if ((i.second % 2) == 0)
                {
                    cnt2freq++;
                }
                else if (alag == false)
                {
                    if ((i.second - 1) % 4 == 0)
                    {
                        for (int j = 0; j < (i.second - 1); j++)
                        {
                            fourwale.push_back(i.first);
                        }
                    }
                    else
                    {
                        cnt2freq += (i.second / 2);
                        for (int j = 0; j < (i.second - 1); j++)
                        {
                            twowale.push_back(i.first);
                        }
                    }

                    alag = true;
                    diff = i.first;
                }
                else
                {
                    cout << "NO\n";
                    return;
                }
            }
        }
        if (max2freq > cnt2freq)
        {
            cout << "NO\n";
            return;
        }
        cout << "YES\n";

        for (auto i : freq)
        {
            if ((i.second % 4) != 0 and (i.second % 2) == 0)
            {
                for (int j = 0; j < i.second; j++)
                {
                    twowale.push_back(i.first);
                }
            }
            else if (i.second % 4 == 0)
            {
                for (int j = 0; j < i.second; j++)
                {
                    fourwale.push_back(i.first);
                }
            }
        }

        int grid[n][n] = {0};
        int pos = 0;

        for (int i = 0; i < n / 2; i++)
        {
            for (int j = 0; j < n / 2; j++)
            {
                grid[i][j] = fourwale[pos++];
                grid[n - i - 1][j] = fourwale[pos++];
                grid[i][n - j - 1] = fourwale[pos++];
                grid[n - i - 1][n - j - 1] = fourwale[pos++];
            }
        }
        for (; pos < fourwale.size(); pos++)
        {
            twowale.push_back(fourwale[pos]);
        }
        pos = 0;

        for (int i = 0; i < n / 2; i++)
        {
            grid[n / 2][i] = twowale[pos++];
            grid[n / 2][n - i - 1] = twowale[pos++];
        }
        for (int i = 0; i < n / 2; i++)
        {
            grid[i][n / 2] = twowale[pos++];
            grid[n - i - 1][n / 2] = twowale[pos++];
        }

        // for (auto i : twowale)
        // {
        //     cout << i << " ";
        // }
        // cout << endl;

        grid[n / 2][n / 2] = diff;

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cout << grid[i][j] << " ";
            }
            cout << endl;
        }
    }
}

bool isposs(int n, int pages, vector<ll> &v, ll mid)
{
    ll sub = 0, pageswritten = 0;

    for (int i = 0, pos = 0; pos < n; pos++)
    {
        pageswritten += max(0ll, v[pos] - sub);
        if (i == mid - 1)
        {
            sub++;
        }
        if (pageswritten >= pages)
        {
            return true;
        }
        i = (i + 1) % mid;
    }

    return pageswritten >= pages;
}

void r2()
{
    ll n, m;
    cin >> n >> m;

    vector<ll> v(n);
    fl(i, n)
    {
        cin >> v[i];
    }

    sort(all(v), greater<int>());
    ll maxpages = accumulate(all(v), 0);

    if (m > maxpages)
    {
        cout << -1 << endl;
        return;
    }
    else
    {
        ll low = 1, high = n, mid, ans = -1;

        while (low <= high)
        {
            mid = (low + high) / 2;
            if (isposs(n, m, v, mid))
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
    }
}

int res = 0;

vector<int> dfs(vector<int> &v, vector<vector<int>> &adj, int node, vector<int> &vis,
                vector<vector<int>> &dp, int prevred = 0, int prevblue = 0)
{
    int red = prevred, blue = prevblue;
    vis[node] = 1;

    if (v[node] == 1)
    {
        red++;
    }
    else if (v[node] == 2)
    {
        blue++;
    }

    for (auto i : adj[node])
    {
        if (vis[i] == 0)
        {
            // int prevred = dp[node][0], prevblue = dp[node][1];
            auto tmp = dfs(v, adj, i, vis, dp, red, blue);

            int newred = tmp[0], newblue = tmp[1];

            // for 1st subtree

            bool hasred = red > 0, hasblue = blue > 0;

            // for 2nd subtree

            bool hasred2 = newred > 0, hasblue2 = newblue > 0;

            cout << node << " " << i << endl;
            cout << hasred << " " << hasblue << " " << hasred2 << " " << hasblue2 << endl;

            if (((hasred != hasblue) || (hasred == hasblue and hasred == false)) and
                ((hasred2 != hasblue2) || (hasred == hasblue and hasred == false)))
            {
                res++;
            }

            red += tmp[0], blue += tmp[1];
        }
    }

    dp[node] = {red, blue};

    return dp[node];
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
    vector<vector<int>> adj(n);
    vector<int> deg(n, 0);

    fl(i, n - 1)
    {
        int u, v;
        cin >> u >> v;
        adj[u - 1].push_back(v - 1);
        adj[v - 1].push_back(u - 1);
        deg[u - 1]++, deg[v - 1]++;
    }

    int root = -1;
    for (int i = 0; i < n; i++)
    {
        if (deg[i] == 1)
        {
            root = i;
            break;
        }
    }

    vector<int> vis(n, 0);
    vector<int> temp = {0, 0};
    vector<vector<int>> dp(n, temp);

    dfs(v, adj, root, vis, dp);

    for (auto i : dp)
    {
        cout << i[0] << " " << i[1] << endl;
    }

    cout << res << endl;
}

int helper(int m, int n)
{
    // cout << m << endl;
    if (m == n)
    {
        return 0;
    }
    if (m < n)
    {
        return 200;
    }

    int ans = 200;

    if (m % 3 == 0 and (m / 3) >= n)
    {
        ans = min(ans, 1 + helper(m / 3, n));
    }
    if (m % 2 == 0 and (m / 2) >= n)
    {
        ans = min(ans, 1 + helper(m / 2, n));
    }
    return ans;
}

void r8()
{
    int n, m;
    cin >> n >> m;

    int ans = helper(m, n);
    if (ans >= 200)
    {
        cout << -1;
        return;
    }
    cout << ans;
}

void r9()
{
    int n;
    cin >> n;
    vector<int> v(n), t;
    fl(i, n)
    {
        cin >> v[i];
    }
    t = v;
    for (auto i : v)
    {
        t.push_back(i);
    }
    int maxrest = 0;
    int i = 0, curr = 0;
    while (i < (2 * n))
    {
        while (i < 2 * n and t[i] == 0)
        {
            i++;
        }
        curr = 0;
        while (i < 2 * n and t[i])
        {
            curr++;
            i++;
        }
        maxrest = max(maxrest, curr);
    }
    cout << maxrest;
}

void r10()
{
    int n;
    cin >> n;
    vector<int> q(n - 1), p(n, -1);
    fl(i, n - 1)
    {
        cin >> q[i];
    }

    fl(i, n)
    {
        int p1 = (i + 1) - q[0];
        if (p1 >= 1 and p1 <= n and p1 != (i + 1))
        {
            p[1] = (i + 1);
            p[0] = p1;
        }
    }

    if (p[1] == -1)
    {
        cout << -1;
        return;
    }

    vector<int> mark(n, 0);
    mark[p[0]] = 1, mark[p[1]] = 1;

    cout << p[0] << " " << p[1] << endl;

    for (int i = 2; i < n; i++)
    {
        int pi = p[i - 1] + q[i - 1];
        if (pi >= 1 and pi <= n and mark[pi] == 0)
        {
            p[i] = pi;
            mark[pi] = 1;
        }
        else
        {
            cout << -1;
            return;
        }
    }

    for (auto i : p)
    {
        cout << i << " ";
    }
}

void r11()
{
    int n;
    cin >> n;
    string l, r;
    cin >> l >> r;

    vector<vector<int>> v1(27), v2(27);
    fl(i, n)
    {
        if (l[i] == '?')
        {
            v1[26].push_back(i);
        }
        else
        {
            v1[l[i] - 'a'].push_back(i);
        }
        if (r[i] == '?')
        {
            v2[26].push_back(i);
        }
        else
        {
            v2[r[i] - 'a'].push_back(i);
        }
    }

    int ans = 0;
    vector<pair<int, int>> arr;

    for (int i = 0; i < 26; i++)
    {
        int mini = min((int)v1[i].size(), (int)v2[i].size());
        for (int j = 0; j < mini; j++)
        {
            arr.push_back({v1[i][v1[i].size() - 1], v2[i][v2[i].size() - 1]});
            v1[i].pop_back();
            v2[i].pop_back();
            ans++;
        }
    }

    int q1 = v1[26].size() - 1;

    for (int i = 0; i < 26 and q1 >= 0; i++)
    {
        int mini = min((int)v1[26].size(), (int)v2[i].size());
        // condition

        for (int j = 0; j < mini; j++)
        {
            arr.push_back({v1[26][q1--], v2[i][v2[i].size() - 1]});
            v1[26].pop_back();
            v2[i].pop_back();
            ans++;
        }
    }

    int q2 = v2[26].size() - 1;
    for (int i = 0; i < 26 and q2 >= 0; i++)
    {
        int mini = min((int)v2[26].size(), (int)v1[i].size());

        for (int j = 0; j < mini; j++)
        {
            arr.push_back({v1[i][v1[i].size() - 1], v2[26][q2--]});
            v1[i].pop_back();
            v2[26].pop_back();
            ans++;
        }
    }

    // ? with ?

    int mini = min((int)v2[26].size(), (int)v1[26].size());

    for (int j = 0; j < mini; j++)
    {
        arr.push_back({v1[26][v1[26].size() - 1], v2[26][v2[26].size() - 1]});
        v1[26].pop_back();
        v2[26].pop_back();
        ans++;
    }

    cout << ans << endl;

    for (auto i : arr)
    {
        cout << i.first + 1 << " " << i.second + 1 << endl;
    }
}

void r12()
{
    ll h, n;
    cin >> h >> n;
    vector<ll> v(n);

    fl(i, n)
    {
        cin >> v[i];
    }

    ll sum = accumulate(all(v), 0ll);

    if (sum >= 0)
    {
        for (int i = 0; i < n; i++)
        {
            h += v[i];
            if (h <= 0)
            {
                cout << i + 1;
                return;
            }
        }
        cout << -1;
    }
    else
    {
        sum = abs(sum);

        ll low = 0, high = (h / sum) + 2;
        ll mid, ans = -1;

        while (low <= high)
        {
            mid = (low + high) / 2;
            bool poss = false;
            ll currh = h - (mid * 1ll * sum);
            ll time = mid * 1ll * n;

            for (int i = 0; i < n; i++)
            {
                time++;
                currh += (int)v[i];
                if (currh <= 0)
                {
                    poss = true;
                    break;
                }
            }

            if (poss)
            {
                high = mid - 1;
                ans = time;
            }
            else
            {
                low = mid + 1;
            }
        }

        cout << ans;
    }
}

pair<int, vector<pii>> samesumblock(vector<int> &v, ll sum)
{
    int n = v.size();
    unordered_map<ll, int> mp;
    mp[0] = -1;
    ll currsum = 0;
    vector<pii> ans;

    for (int i = 0; i < n; i++)
    {
        currsum += v[i];
        if (mp.count(currsum - sum))
        {
            ans.push_back({mp[currsum - sum] + 2, i + 1});
            currsum = 0ll;
            mp.clear();
            mp[0] = i;
        }
        else
        {
            mp[currsum] = i;
        }
    }
    return {(int)ans.size(), ans};
}

void r13()
{
    int n;
    cin >> n;
    vector<int> v(n);
    fl(i, n)
    {
        cin >> v[i];
    }

    set<ll> uniqsum;

    ll maxsize = 0;
    vector<pii> ans;

    for (int i = 0; i < n; i++)
    {
        ll sum = 0;
        for (int j = i; j < n; j++)
        {
            sum += v[j];
            if (!uniqsum.count(sum))
            {
                uniqsum.insert(sum);
                auto t = samesumblock(v, sum);
                int currsize = t.first;
                if (currsize > maxsize)
                {
                    maxsize = currsize;
                    ans = t.second;
                }
            }
        }
    }

    cout << maxsize << endl;
    for (auto i : ans)
    {
        cout << i.first << " " << i.second << endl;
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    r13();

    // ll t;
    // cin >> t;
    // while (t--)
    // {
    // rash1();
    // }

    return 0;
}