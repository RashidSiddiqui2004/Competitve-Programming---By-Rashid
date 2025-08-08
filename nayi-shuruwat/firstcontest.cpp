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
int mod_mul(int a, int b, int m)
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
    int ans = 0;
    if (k == 1)
    {
        // Logarithm base 1 is undefined, return special value
        return n - 1; // Subtracting one repeatedly in this case
    }

    int currnum = 1;
    while ((currnum * k) <= n)
    {
        if (currnum > n / k) // Prevent multiplication overflow
            break;
        currnum *= k;
        ans++;
    }
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

void solve1()
{
    int a, b;
    cin >> a >> b;
    if (a >= b)
    {
        cout << a << endl;
        return;
    }

    int x = b - a;
    if (x > a)
    {
        cout << 0 << endl;
    }
    else
    {
        a = a - x;
        cout << a << endl;
    }
}

void solve2()
{
    ll n, k;
    cin >> n >> k;

    vector<ll> v(n);

    fl(i, 0, n)
    {
        cin >> v[i];
    }

    sort(all(v));

    ll ans = 0;
    ll pos = 0, zeros = 0;

    ll removedfromEach = 0;
    ll mininow = *min_element(all(v));

    while (k > 0)
    {
        ll left = (n - pos) * mininow;
        if (k <= left)
        {
            ans += k + zeros;
            k = 0;
            break;
        }
        else
        {
            ans += left + zeros;
            zeros = 0;
            k -= left;
            removedfromEach += mininow;
            for (int i = pos; i < n; i++)
            {
                if ((v[i] - removedfromEach) == 0)
                {
                    v[i] -= removedfromEach;
                    pos++;
                    zeros++;
                }
                else
                {
                    mininow = v[i] - removedfromEach;
                    break;
                }
            }
        }
    }

    cout << ans << endl;
}

void solve3()
{
    int n;
    cin >> n;

    vector<pll> v(n);

    fl(i, 0, n)
    {
        cin >> v[i].first >> v[i].second;
    }

    sort(all(v));

    for (auto i : v)
    {
        cout << i.first << " " << i.second << " ";
    }

    cout << endl;
}

void solve4()
{
    int n;
    cin >> n;

    int v[n] = {0};

    fl(i, 0, n)
    {
        cin >> v[i];
    }

    sort(v, v + n, greater<>());

    sort(v + 1, v + n);

    ll sum = 0;

    ll mini = v[0], maxi = v[0];

    fl(i, 0, n)
    {
        mini = min(mini, 1ll * v[i]);
        sum += (maxi - mini);
    }

    cout << sum << endl;
}

void solve5()
{
    int n;
    cin >> n;

    int ans = 0;

    if (n == 1)
    {
        cout << 0 << endl;
        return;
    }

    // ll curr = pow(2, n) + 1;
    for (int i = 0; i < n - 1; i++)
    {
        cout << 0;
    }
    for (int i = n - 1; i < n; i++)
    {
        cout << 1;
    }
    cout << endl;
}

// 0111111011
void solve6()
{
    int n;
    cin >> n;
    string s;
    cin >> s;

    if (n == 1)
    {
        if (s == "1")
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

        if (s[0] == '1' || s[n - 1] == '1')
        {
            cout << "YES\n";
        }
        else
        {
            bool check = false;
            for (int i = 0; i < n - 1; i++)
            {
                if (s[i] == '1' and s[i + 1] == '1')
                {
                    check = true;
                    break;
                }
            }
            if (check)
            {
                cout << "YES\n";
            }
            else
            {
                cout << "NO\n";
            }
        }
    }
}

void solve7()
{
    int n, q;
    cin >> n >> q;
    vector<int> perm(n);

    fl(i, 0, n)
    {
        cin >> perm[i];
        --perm[i];
    }

    vector<int> invperm(n);

    fl(i, 0, n)
    {
        invperm[perm[i]] = i;
    }

    string s;
    cin >> s;

    vector<int> diffarr(n, 0);

    fl(i, 0, n)
    {
        if (i != invperm[i])
        {
            diffarr[min(i, invperm[i])]++;
            diffarr[max(i, invperm[i])]--;
        }
    }

    for (int i = 1; i < n; i++)
    {
        diffarr[i] += diffarr[i - 1];
    }

    unordered_set<int> problems;

    // LR is a error
    // baaki LL, RR, RL me easily sort ho jayega

    for (int i = 0; i < n - 1; i++)
    {
        if (s[i] == 'L' && s[i + 1] == 'R' && diffarr[i] != 0)
        {
            problems.insert(i);
        }
    }

    while (q--)
    {
        int pos;
        cin >> pos;
        --pos;

        if (s[pos] == 'L')
        {
            s[pos] = 'R';
        }
        else
        {
            s[pos] = 'L';
        }
        if (s[pos - 1] == 'L' && s[pos] == 'R' && diffarr[pos - 1] != 0)
        {
            problems.insert(pos - 1);
        }
        else if (problems.count(pos - 1))
        {
            problems.erase(pos - 1);
        }
        if (s[pos] == 'L' && s[pos + 1] == 'R' && diffarr[pos] != 0)
        {
            problems.insert(pos);
        }
        else if (problems.count(pos))
        {
            problems.erase(pos);
        }

        if (problems.size())
        {
            cout << "NO" << endl;
        }
        else
        {
            cout << "YES" << endl;
        }
    }
}

void rash1()
{
    int n;
    cin >> n;
    vector<string>
        v(n);

    fl(i, 0, n)
    {
        cin >> v[i];
    }

    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = 0; j < 4; j++)
        {
            if (v[i][j] == '#')
            {
                cout << j + 1 << " ";
            }
        }
    }

    cout << endl;
}
void rash2()
{
    ll x, y, k;
    cin >> x >> y >> k;

    ll minx = (x + k - 1) / k, miny = (y + k - 1) / k;
    ll ans = 2 * max(minx, miny);

    if (x > y and minx > miny)
    {
        --ans;
    }

    cout << ans << endl;
}

void rash3()
{
    int n;
    cin >> n;

    ll airpoints1 = 0, airpoints2 = 0;
    ll grdPoints = 0;
    vector<pll> vp(n + 1);
    // {ground,air}

    fl(i, 0, n)
    {
        ll x, y;
        cin >> x >> y;
        if (y == 1)
        {
            vp[x].second = 1;
        }
        else
        {
            vp[x].first = 1;
        }
    }

    fl(i, 0, n)
    {
        if (vp[i].second == 1)
        {
            if (vp[i].first)
            {
                airpoints2++;
            }
            else
            {
                airpoints1++;
            }
        }
    }

    grdPoints = n - airpoints1 - airpoints2;

    ll ans = 0;
    ll typeairFull = 0, typeairHalf = 0, typegrd = 0;

    for (int i = 0; i <= n; i++)
    {
        if (vp[i].second)
        {
            if (i - 1 >= 0 and i + 1 <= n)
            {
                if (vp[i - 1].first and vp[i + 1].first)
                {
                    typegrd++;
                }
            }
        }
        if (vp[i].first)
        {
            if (i - 1 >= 0 and i + 1 <= n)
            {
                if (vp[i - 1].second and vp[i + 1].second)
                {
                    typegrd++;
                }
            }
        }
        if (vp[i].second and vp[i].first)
        {
            typeairFull += airpoints1;
            typeairHalf += (airpoints2 - 1);
            typegrd += (grdPoints - 1);
        }
    }

    typeairHalf /= 2;

    ans = typeairHalf + typeairFull + typegrd;

    cout << ans << endl;
}

int minCost(int n)
{
    if (n == 0)
    {
        return 0;
    }
    if (n % 2 == 0)
    {
        int cost = n + 1;
        cost += minCost(n / 2) + minCost((n / 2) - 1);
        return cost;
    }
    else
    {
        int cost = 2 * ((n + 1) / 2);
        cost += 2 * 1ll * minCost(n / 2);
        return cost;
    }
}

void rash5()
{
    int n, k;
    cin >> n >> k;

    int maxi = n + ((n * (n + 1)) / 2);
    int mini = minCost(n);

    if (k < mini)
    {
        cout << -1 << endl;
    }
    else
    {
        if (k == mini)
        {
            cout << 0 << endl;
        }
        else
        {
            if (k > maxi)
            {
                int ans = k - maxi;
                cout << ans << endl;
            }
            else
            {
                cout << 0 << endl;
            }
        }
    }
}

void rash6()
{
    int n;
    cin >> n;
    string s1, s2;
    cin >> s1 >> s2;
    int sum = 0;
    vector<vector<int>> v(n, vector<int>(2, 0));

    fl(i, 0, n)
    {
        if (s2[i] - s1[i] >= 0)
        {
            v[i][0] = s2[i] - s1[i];
            v[i][1] = s2[i] - s1[i] - 26;
        }
        else
        {
            v[i][0] = s2[i] - s1[i];
            v[i][1] = s2[i] - s1[i] + 26;
        }
    }
    fl(i, 0, n)
    {
        if (abs(sum + v[i][0]) <= abs(sum + v[i][1]))
        {
            sum += v[i][0];
        }
        else
        {
            sum += v[i][1];
        }
    }
    cout << abs(sum) << "\n";
}

void rash7()
{
    int n;
    cin >> n;
    vector<int> v(n);
    unordered_map<int, int> freq;
    fl(i, 0, n)
    {
        cin >> v[i];
        freq[v[i]]++;
    }

    int ans = 0;

    for (auto i : freq)
    {
        ans = max(ans, i.second);
    }

    for (auto i : freq)
    {
        if (freq.count(i.first + 1))
        {
            if ((i.first ^ (i.first + 1)) == 1)
            {
                ans = max(ans, i.second + freq[i.first + 1]);
            }
        }
    }
    cout << n - ans << endl;
}

void rash8()
{
    int n;
    cin >> n;
    string s;
    cin >> s;

    for (int i = 0; i < n - 1; i++)
    {
        if (s[i] > s[i + 1])
        {
            string res = "";
            res += s.substr(0, i);
            res += s.substr(i + 1);
            cout << res << endl;
            return;
        }
    }
    string res = "";
    res += s.substr(0, n - 1);
    cout << res << endl;
}

void solve16()
{
    int n;
    cin >> n;

    vector<int> v(n);

    fl(i, 0, n)
    {
        cin >> v[i];
    }

    if (n <= 2)
    {
        cout << -1 << endl;
    }
    else
    {
        int odds = 1, evens = 2;
        bool toskip = false;
        for (auto i : v)
        {
            if (i % 2 == 0)
            {
                cout << evens << " ";
                evens += 2;
            }
            else
            {
                if (i == 1)
                {
                    if (odds == 1)
                    {
                        cout << 3 << " ";
                        toskip = true;
                    }
                    else
                    {
                        cout << odds << " ";
                        odds += 2;
                    }
                }
                else
                {
                    cout << odds << " ";
                    odds += 2;
                    if (toskip)
                    {
                        odds += 2;
                        toskip = false;
                    }
                }
            }
        }

        cout << endl;
    }
}

void solve17()
{
    int n;
    cin >> n;

    vector<int> v(n);
    fl(i, 0, n)
    {
        cin >> v[i];
    }

    int turn = 0;
    // 0 => alice, 1 => bob

    while (true)
    {
        bool check = v.size() > 0;

        vector<int> temp;
        int last = v[0];

        for (int i = 1; i < v.size(); i++)
        {
            if (v[i] == last)
            {
                temp.push_back(v[i]);
            }
            else
            {
                last = v[i];
            }
        }

        if (!check)
        {
            break;
        }

        v = temp;

        turn = !turn;
    }

    if (!turn)
    {
        cout << "Bob\n";
    }
    else
    {
        cout << "Alice\n";
    }
}

void solve18()
{
    ll n, m;
    cin >> n >> m;
    ll i, j;
    cin >> i >> j;
    ll minInf = min({i * 1ll * m,
                     j * 1ll * n,
                     (n - i + 1) * 1ll * m,
                     (m - j + 1) * 1ll * n});

    ll maxVacc = (n * 1ll * m) - minInf;

    cout << maxVacc << endl;
}

void solve19()
{
    ll x, y, n;
    cin >> x >> y >> n;

    ll ulimit = (n - y) / x;

    ll ans = ulimit * x + y;
    cout << ans << endl;
}

unordered_map<ll, ll> dpans;

void solution(ll num, ll steps)
{
    if (!dpans.count(num))
    {
        dpans[num] = steps;
    }

    if (num * 1ll * 6 <= 1e9)
    {
        solution(num * 1ll * 6, steps + 1);
    }

    if (num % 2 == 0)
    {
        if (!dpans.count(num / 2))
            solution(num / 2, steps + 1);
    }
}

void solve20()
{
    ll n;
    cin >> n;
    if (!dpans.count(n))
    {
        cout << -1 << endl;
        return;
    }
    cout << dpans[n] << endl;
}

void solve21()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    int ans = 0;
    int balance = 0;

    for (int i = 0; i < n; i++)
    {
        if (s[i] == '(')
        {
            ans++;
        }
        else
        {
            ans--;
        }
        if (ans < 0)
        {
            ans++;
            balance = 0;
        }
    }

    cout << ans << endl;
}

void solve22()
{
    ll n, k;
    cin >> n >> k;

    vector<int> pq;
    ll ones = 0;
    loop(i, n)
    {
        ll elem;
        cin >> elem;
        if (elem % k != 0)
        {
            if ((elem % k) == k - 1)
            {
                ones++;
            }
            else
            {
                pq.push_back(elem % k);
            }
        }
    }
    // cout << ones << " ";
    sort(pq.begin(), pq.end());
    ll ans = 0;
    ll x = 0;
    int ptr = (int)pq.size() - 1;

    while (ptr >= 0)
    {
        ll top = pq[ptr];
        ll newval = (top + x) % k;
        ll toadd = (k - newval) % k;
        ans += toadd;
        ans++;
        // cout << ans << " ";
        x += toadd + 1;
        ptr--;
    }

    cout << ans << endl;
}

void solve23()
{
    ll n, m, x;
    cin >> n >> m >> x;

    ll col = (x + (n - 1)) / n;
    ll row = x - (n) * (col - 1);
    ll res = (row - 1) * m;
    res += col;
    cout << res << endl;
}

void solve24()
{
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;

    int count = 0;
    for (auto i : s)
    {
        if (i == '*')
        {
            count++;
        }
    }
    if (count == 0)
    {
        cout << 0 << endl;
    }
    else if (count == 1)
    {
        cout << 1 << endl;
    }
    else if (count == 2)
    {
        cout << 2 << endl;
    }
    else
    {
        int lastPos = 0, recentStar = -1;
        int ans = 2;

        vector<int> pos;
        for (int i = 0; i < n; i++)
        {
            if (s[i] == '*')
            {
                pos.push_back(i);
            }
        }

        int currstar = pos[0];
        int sz = pos.size();
        int laststar = pos[sz - 1];

        while (currstar != laststar)
        {
            int lb = upper_bound(all(pos), currstar + k) - pos.begin();
            --lb;
            // cout << lb << " ";
            currstar = pos[lb];
            ans++;
        }
        cout << ans - 1 << endl;
    }
}

bool helper(string &t, string &b)
{
    int n = t.size(), m = b.size();
    for (int i = 0; i <= m - n; i++)
    {
        string curr = b.substr(i, n);
        if (curr == t)
        {
            return true;
        }
    }
    return false;
}

void solve25()
{
    string a, b;
    cin >> a >> b;
    int n = a.size(), m = b.size();
    int ans = n + m;
    for (int i = 0; i < n; i++)
    {
        string t = "";
        for (int j = i; j < n; j++)
        {
            t += a[j];
            int sz = t.size();
            int currcost = n - sz;
            if (helper(t, b))
            {
                ans = min(ans, currcost + (m - sz));
            }
        }
    }

    cout << ans << endl;
}

void solve26()
{
    int n;
    cin >> n;
    map<int, int> mp;
    loop(i, n)
    {
        ll e;
        cin >> e;
        mp[e]++;
    }
    priority_queue<int> pq;
    for (auto i : mp)
    {
        pq.push(i.second);
    }

    int sz = n;
    while (pq.size() >= 2)
    {
        auto t1 = pq.top();
        pq.pop();
        auto t2 = pq.top();
        pq.pop();
        sz -= 2;
        t1--;
        t2--;
        if (t1)
        {
            pq.push(t1);
        }
        if (t2)
        {
            pq.push(t2);
        }
    }
    cout << sz << endl;
}

void solve27()
{
    int x1, y1, x2, y2, x3, y3;
    cin >> x1 >> y1;
    cin >> x2 >> y2;
    cin >> x3 >> y3;
    if (x1 == x2)
    {
        if (x3 == x1 and (min(y1, y2) < y3 and y3 < max(y1, y2)))
        {
            int ans = abs(x1 - x2) + abs(y2 - y1);
            cout << ans + 2 << endl;
        }
        else
        {
            int ans = abs(x1 - x2) + abs(y2 - y1);
            cout << ans << endl;
        }
    }
    else if (y1 == y2)
    {
        if (y3 == y1 and (min(x1, x2) < x3 and x3 < max(x1, x2)))
        {
            int ans = abs(x1 - x2) + abs(y2 - y1);
            cout << ans + 2 << endl;
        }
        else
        {
            int ans = abs(x1 - x2) + abs(y2 - y1);
            cout << ans << endl;
        }
    }
    else
    {
        int ans = abs(x1 - x2) + abs(y2 - y1);
        cout << ans << endl;
    }
}

void solve28()
{
    int n, m, k;
    cin >> k >> n >> m;
    vector<int> a(n), b(m);
    loop(i, n)
    {
        cin >> a[i];
    }
    loop(i, m)
    {
        cin >> b[i];
    }
    int p1 = 0, p2 = 0;

    vector<int> ans;

    while (p1 < n and p2 < m)
    {
        bool chk = false;
        int john = a[p1], bob = b[p2];
        if (john == 0)
        {
            k++;
            ans.push_back(0);
            p1++;
            chk = true;
        }
        if (bob == 0)
        {
            k++;
            ans.push_back(0);
            p2++;
            chk = true;
        }
        if (john > 0)
        {
            if (k >= john)
            {
                ans.push_back(john);
                p1++;
                chk = true;
            }
        }
        if (bob > 0)
        {
            if (k >= bob)
            {
                ans.push_back(bob);
                p2++;
                chk = true;
            }
        }
        if (!chk)
        {
            cout << -1 << endl;
            return;
        }
    }

    while (p1 < n)
    {
        bool chk = false;

        int john = a[p1];
        if (john == 0)
        {
            k++;
            chk = true;
            ans.push_back(0);
            p1++;
        }
        else if (k >= john)
        {
            chk = true;
            ans.push_back(john);
            p1++;
        }
        if (!chk)
        {
            cout << -1 << endl;
            return;
        }
    }
    while (p2 < m)
    {
        bool chk = false;

        int bob = b[p2];
        if (bob == 0)
        {
            k++;
            chk = true;
            ans.push_back(0);
            p2++;
        }

        if (k >= bob)
        {
            chk = true;
            ans.push_back(bob);
            p2++;
        }
        if (!chk)
        {
            cout << -1 << endl;
            return;
        }
    }
    if (p1 < n || p2 < m)
    {
        cout << -1 << endl;
        return;
    }
    printarr(ans);
}

void solve29()
{
    ll n, m, r, c;
    cin >> n >> m >> r >> c;

    ll ans = ((n - r) * (m - 1)) + ((n - r) * m) + (m - c);

    cout << ans << endl;
}

void solve30()
{
    ll n;
    cin >> n;

    if ((n % 2) != 0)
    {
        cout << n << endl;
        cout << 2 << " " << 1 << " ";
        for (int i = 2; i < n; i++)
        {
            cout << i + 1 << " ";
        }
        cout << endl;
    }
    else
    {
        ll ans = 0;
        ll maxhelp = -1;
        for (int i = 1; i < n; i++)
        {
            ll curr = n | i;
            if (curr >= ans)
            {
                ans = curr;
                maxhelp = i;
            }
        }

        cout << ans << endl;
        cout << 2 << " " << 1 << " ";
        for (int i = 3; i < n; i++)
        {
            if (i != maxhelp)
            {
                cout << i << " ";
            }
        }
        cout << maxhelp << " " << n;
        cout << endl;
    }
}

void solve31()
{
    ll n;
    cin >> n;
    if (n == 1 || n == 3)
    {
        cout << -1 << endl;
    }
    else if (n == 2)
    {
        cout << 66 << endl;
    }
    else if (n % 2 == 0)
    {
        int num3s = n - 2;
        for (int i = 1; i <= num3s; i++)
        {
            cout << 3;
        }
        cout << "66";
        cout << endl;
    }
    else
    {
        int num3s = n - 5;
        for (int i = 1; i <= num3s; i++)
        {
            cout << 3;
        }
        cout << "36366";
        cout << endl;
    }
}

void solve32()
{
    int n;
    cin >> n;

    vector<int> v(n);
    fl(i, 0, n)
    {
        cin >> v[i];
    }

    int mx = *max_element(all(v));
    int cnt = 0;
    vector<int> fr(n + 1, 0);

    for (auto i : v)
    {
        if (i == mx)
            cnt++;

        fr[i]++;
    }

    if (cnt % 2 == 0)
    {
        bool isoddfr = false;
        for (int i = 1; i <= n; i++)
        {
            if (fr[i] % 2 != 0)
            {
                isoddfr = true;
                break;
            }
        }
        if (isoddfr)
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
        cout << "YES\n";
    }
}

void solve33()
{
    ll n;
    cin >> n;
    if (n <= 4)
    {
        cout << -1 << endl;
        return;
    }
    for (int i = 2; i <= n; i += 2)
    {
        if (i != 4)
        {
            cout << i << " ";
        }
    }
    cout << "4 5 ";
    for (int i = 1; i <= n; i += 2)
    {
        if (i != 5)
        {
            cout << i << " ";
        }
    }
    cout << endl;
}

void slv()
{
    ll n, m, l;
    cin >> n >> m >> l;

    vector<pll> v(n);

    loop(i, n)
    {
        cin >> v[i].first >> v[i].second;
    }

    vector<pll> b(m);

    loop(i, m)
    {
        cin >> b[i].first >> b[i].second;
    }

    bool poss = true;
    ll ans = 0;
    int j = 0;
    priority_queue<ll> pq;

    ll jumppower = 1;

    for (int i = 0; i < n; i++)
    {
        int minPos = (v[i].first);
        int block_len = v[i].second - v[i].first + 2;

        while (j < m and b[j].first < minPos)
        {
            pq.push(b[j].second);
            j++;
        }

        while (jumppower < block_len and !pq.empty())
        {
            jumppower += pq.top();
            ans++;
            pq.pop();
        }

        if (jumppower < block_len)
        {
            ans = -1;
            break;
        }
    }

    if (poss)
    {
        cout << ans << endl;
    }
    else
    {
        cout << -1 << endl;
    }
}

void cod1()
{
    int n;
    cin >> n;
    vector<int> b(n - 1);
    for (int i = 0; i < n - 1; i++)
    {
        cin >> b[i];
    }
    sort(all(b));

    ll prev = 1;
    cout << prev << " ";

    for (int i = 0; i < n - 1; i++)
    {
        ll curr = b[i] - prev;
        cout << curr << " ";
        prev = curr;
    }
    cout << endl;
}

void cod2()
{
    int a, x, y;
    cin >> a >> x >> y;

    if ((x + y) >= a)
    {
        cout << "YES\n";
    }

    else
    {
        cout << "NO\n";
    }
}

void cod3()
{
    int n, k;
    cin >> n >> k;
    int m = (n + 1) / 2;
    if ((n % 2) == 0 and (k == (n / 2)))
    {
        cout << "YES\n";
    }
    else if (k == (n / 2) || (k == (n + 1) / 2))
    {
        cout << "YES\n";
    }
    else
    {
        cout << "NO\n";
    }
}

void hl1()
{
    ll n, x;
    cin >> n >> x;

    vector<pll> v(n, {-1, -1});
    fl(i, 0, n)
    {
        cin >> v[i].first;
    }
    fl(i, 0, n)
    {
        cin >> v[i].second;
    }

    sort(all(v), [](pll &p1, pll &p2)
         {
             ll c1 = p1.first * 1ll * p1.second;
             ll c2 = p2.first * 1ll * p2.second;

             if (c1 != c2)
             {
                 return c1 > c2;  
             }
             return p1.first > p2.first; });

    ll ans = 0;

    for (int i = 0; i < n; i++)
    {
        if (x <= 0)
            break;
        x -= (v[i].first * v[i].second);
        ans++;
    }

    if (x > 0)
    {
        cout << -1 << endl;
        return;
    }
    cout << ans << endl;
}

void s23()
{
    // int j = (-4 + 2) / 3;
    // cout << j << " ";

    ll n, k;
    cin >> n >> k;

    ll pos = 0, neg = 0;
    ll sum = 0;
    for (int i = 0; i < n; i++)
    {
        ll a;
        cin >> a;
        if ((a % k) != 0)
        {
            if (a < 0)
            {
                neg++;
            }
            else
            {
                pos++;
            }
        }
        sum += (a / k);
    }

    if (sum == 0)
    {
        cout << "YES\n";
    }
    else
    {
        ll diff = sum;
        if (sum > 0 and neg >= abs(diff))
        {
            cout << "YES\n";
        }
        else if (sum < 0 and pos >= abs(diff))
        {
            cout << "YES\n";
        }
        else
        {
            cout << "NO\n";
        }
    }
}

void s865()
{
    int n;
    cin >> n;
    string s;
    cin >> s;

    string p;
    cin >> p;
    map<char, int> mp;

    for (int i = 0; i < 26; i++)
    {
        mp[p[i]] = i + 1;
    }

    vector<int> temp(n, false);
    string v = s;
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        int pos = mp[s[i]];
        pos = 27 - pos;
        char ch = p[pos - 1];

        if (i == n - 1)
        {
            if ((s[i] < s[i - 1]) and (ch >= s[i + 1]))
            {
                temp[i] = true;
                v[i] = ch;
                ans++;
            }
        }
        else
        {
            if ((s[i] > s[i + 1]) and (ch <= s[i + 1]))
            {
                temp[i] = true;
                v[i] = ch;
                ans++;
            }
        }
    }

    cout << v << endl;

    for (int i = 0; i < n - 1; i++)
    {
        if (v[i] > v[i + 1])
        {
            cout << -1 << endl;
            return;
        }
        else
        {
            if (temp[i] == true)
            {
                if (v[i] <= s[i + 1])
                {
                    ans--;
                }
            }
        }
    }

    cout << ans << endl;
}

void s1()
{
    int n;
    cin >> n;

    string s;
    cin >> s;

    int a = 0, b = 0, ans = 0;

    for (auto i : s)
    {
        if (i == 'A')
        {
            if (b > 0)
            {
                b--;
                a++;
            }
            else
            {
                a++;
                ans++;
            }
        }
        else
        {
            if (a > 0)
            {
                a--;
                b++;
            }
            else
            {
                b++;
                ans++;
            }
        }
    }

    cout << ans << endl;
}

void s2()
{
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    fl(i, 0, n)
    {
        cin >> a[i];
    }
    fl(i, 0, n)
    {
        cin >> b[i];
    }

    int maxpos = 0, maxi = INT_MIN;

    fl(i, 0, n)
    {
        int currmaxi = max(a[i], b[i]);
        if (currmaxi > maxi)
        {
            maxi = currmaxi;
            maxpos = i;
        }
    }

    int secmax = INT_MIN, pos = -1;

    fl(i, 0, n)
    {
        if (i == maxpos)
        {
            continue;
        }
        if (a[i] > secmax)
        {
            secmax = a[i];
            pos = i;
        }
    }

    secmax = max(a[pos], b[pos]);
    if (secmax < maxi and (secmax != INT_MIN))
    {
        cout << "Yes\n";
    }
    else
    {
        cout << "No\n";
    }
}

bool binary_Search(vector<int> &a, int n, int k, int max_savoriness)
{
    int mn = INT_MAX, mx = INT_MIN;
    int required_sub = 1;
    for (int i = 0; i < n; i++)
    {
        mn = min(mn, a[i]);
        mx = max(mx, a[i]);
        int currmid = (mx - mn + 1) / 2;
        if (currmid > max_savoriness)
        {
            required_sub++;
            mn = a[i], mx = a[i];
            if (required_sub > (k + 1))
            {
                return false;
            }
        }
    }

    return true;
}

void s3()
{
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    fl(i, 0, n)
    {
        cin >> a[i];
    }

    ll low = 0, high = INT_MAX, mid;
    ll ans = -1;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if (binary_Search(a, n, k, mid))
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

void s4()
{
    int n, m;
    cin >> n >> m;
    string s, t;
    cin >> s >> t;

    int p1 = n - 1, p2 = m - 1;

    while ((p1 >= 0) and (p2 >= 0))
    {
        if (s[p1] == t[p2])
        {
            p1--;
            p2--;
        }
        else
        {
            if (s[p1] == 'a')
            {
                p2--;
            }
            else
            {
                p1--;
            }
        }
    }
    // cout << p1 << " " << p2 << endl;
    if (p1 != -1 or p2 != -1)
    {
        cout << "No\n";
    }
    else
    {
        cout << "Yes\n";
    }
}

void s6()
{
    int n, m;
    cin >> n >> m;

    vector<int> v(n);
    fl(i, 0, n)
    {
        string s;
        cin >> s;
        v[i] = ((int)s.size());
    }

    int curr = 0, x = 0;
    for (auto i : v)
    {
        curr += i;
        if (curr <= m)
        {
            x++;
        }
        else
        {
            break;
        }
    }

    cout << x << endl;
}

void s7()
{
    int n;
    cin >> n;

    vector<int> v(n);

    ll sum = 0;
    fl(i, 0, n)
    {
        cin >> v[i];
        sum += v[i];
    }

    ll req = sum / n;
    // cout << req << " ";

    for (int i = 1; i < n - 1; i++)
    {
        int diff = abs(v[i - 1] - req);
        if (v[i - 1] <= req)
        {
            v[i - 1] += diff;
            v[i + 1] -= diff;
        }
        else
        {
            v[i - 1] -= diff;
            v[i + 1] += diff;
        }
        if (v[i - 1] != req and v[i + 1] != req)
        {
            cout << "NO\n";
            return;
        }
    }

    for (auto i : v)
    {
        if (i != req)
        {
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
}

void s8()
{
    string s;
    cin >> s;

    ll sum = 0;
    ll count2s = 0, count3s = 0;

    for (auto i : s)
    {
        sum += (i - '0');
        if (i == '2')
        {
            count2s++;
        }
        if (i == '3')
        {
            count3s++;
        }
    }

    for (int i = 0; i <= min(count2s, 8ll); i++)
    {
        for (int j = 0; j <= min(count3s, 3ll); j++)
        {
            ll currsum = sum + (i * 2) + (j * 6);
            int rem = currsum % 9;
            if (rem == 0)
            {
                cout << "YES\n";
                return;
            }
        }
    }
    cout << "NO\n";
    return;
}

int dp[1001][1001];

int dpbuilder(string &a, string &b, string &c, int n, int m, int p1, int p2, int pos = 0)
{
    if (p1 == n and p2 == m)
    {
        return 0;
    }

    if (dp[p1][p2] != -1)
    {
        return dp[p1][p2];
    }

    char ch1 = (p1 < n) ? a[p1] : '$';
    char ch2 = (p2 < m) ? b[p2] : '$';

    int ans = 0;

    if (ch1 == '$')
    {
        ans = (b[p2] != c[pos]) + dpbuilder(a, b, c, n, m, p1, p2 + 1, pos + 1);
    }
    else if (ch2 == '$')
    {
        ans = (a[p1] != c[pos]) + dpbuilder(a, b, c, n, m, p1 + 1, p2, pos + 1);
    }
    else if (ch1 != '$' and ch2 != '$')
    {
        ans = min({(a[p1] != c[pos]) + dpbuilder(a, b, c, n, m, p1 + 1, p2, pos + 1),
                   (b[p2] != c[pos]) + dpbuilder(a, b, c, n, m, p1, p2 + 1, pos + 1)});
    }

    return dp[p1][p2] = ans;
}

void s9()
{
    string a, b, c;
    cin >> a >> b >> c;

    memset(dp, -1, sizeof(dp));
    // dp2.clear();
    int p1 = 0, p2 = 0;
    int n = a.size(), m = b.size();

    int ans = dpbuilder(a, b, c, n, m, p1, p2);

    cout << ans << endl;
}

void s10()
{
    int n, q;
    cin >> n >> q;

    vector<ll> a(n);

    fl(i, 0, n)
    {
        cin >> a[i];
    }

    fl(i, 0, q)
    {
        int l, r;
        cin >> l >> r;
        --l, --r;

        bool allsame = true;
        ll ans = -1;

        for (int j = l; j <= r; j++)
        {
            if (a[j] != a[l])
            {
                allsame = false;
            }
            if (j == r)
            {
                break;
            }
            if (ans == -1)
            {
                ans = abs(a[j + 1] - a[j]);
            }
            else
            {
                ans = __gcd(ans, abs(a[j + 1] - a[j]));
            }
        }
        if (allsame)
        {
            ans = 0;
        }
        cout << ans << " ";
    }

    cout << endl;
}

//  the end

signed main()
{
    // dpans.clear();
    // factorialCalculation();

    ll t;
    cin >> t;
    while (t--)
        s11();
    khalaas
}