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

void solve1()
{
    int m, k;
    cin >> m >> k;
    string s;
    cin >> s;
    int sw = 0;
    for (auto i : s)
    {
        if (i == 'S')
            sw++;
    }

    if (sw >= k)
    {
        cout << m << endl;
    }
    else
    {
        int rem = k - sw;
        int ans = m + rem - 1;
        cout << ans << endl;
    }
}

int oper(string s, string rgb)
{
    int n = s.size();
    int curr = 0, oper = 0;
    for (int i = 0; i < n; i++)
    {
        if (s[i] != rgb[curr])
        {
            oper++;
        }
        curr = (curr + 1) % 3;
    }
    return oper;
}

void solve2()
{
    int n;
    cin >> n;
    string s;
    cin >> s;

    string a = "", b = "", c = "";

    int minopers = n;

    string rgb1 = "BGR";

    do
    {
        minopers = min(minopers, oper(s, rgb1));
    } while (next_permutation(rgb1.begin(), rgb1.end()));

    cout << minopers << endl;
}

void solve3()
{
    int n, p;
    cin >> n >> p;

    vector<ll> v(n);

    fl(i, n)
    {
        cin >> v[i];
    }

    vector<ll> ans(n, LLONG_MAX);

    for (int i = 0; i < n; i++)
    {
        if (v[i] == 0)
        {
            ans[i] = 0;
            ll curhr = 0, time = 0;
            for (int j = i - 1; j >= 0; j--)
            {
                if (ans[j] <= time)
                {
                    break;
                }
                if (v[j] <= curhr)
                {
                    ans[j] = time;
                }
                else
                {
                    ll q = (v[j] + p - 1) / p;
                    time = max(time, q);
                    curhr = q * 1ll * p;
                    ans[j] = time;
                }
            }
            curhr = 0, time = 0;
            for (int j = i + 1; j < n; j++)
            {
                if (ans[j] <= time)
                {
                    break;
                }
                if (v[j] <= curhr)
                {
                    ans[j] = time;
                }
                else
                {
                    ll q = (v[j] + p - 1) / p;
                    time = max(time, q);
                    curhr = q * 1ll * p;
                    ans[j] = time;
                }
            }
        }
    }

    // vector<bool> vis(n, false);
    // priority_queue<pll> q;
    // ll level = 0;

    // for (int i = 0; i < n; i++)
    // {
    //     if (v[i] == 0)
    //     {
    //         q.push({0, i});
    //         vis[i] = true;
    //         ans[i] = 0;
    //     }
    // }

    // while (!q.empty())
    // {
    //     auto fr = q.top();
    //     q.pop();

    //     ll h = fr.first, ind = fr.second;

    //     // cout << ind << " " << h << endl;

    //     ll nextHeight, prevHeight;

    //     if (ind + 1 < n)
    //     {
    //         nextHeight = v[ind + 1];

    //         ll diff = (nextHeight + p - 1) / p;
    //         ll newheight = (diff * p);

    //         int ptr = ind + 1;
    //         int tm = newheight / p;

    //         bool isval = true;
    //         while (ptr < n and v[ptr] <= newheight)
    //         {
    //             if (ans[ptr] <= tm)
    //             {
    //                 isval = false;
    //                 break;
    //             }
    //             ans[ptr] = tm;
    //             vis[ptr] = true;
    //             ptr++;
    //         }

    //         if (ptr < n - 1 and isval and v[ptr] <= newheight)
    //         {
    //             q.push({newheight, ptr});
    //         }
    //     }
    //     if (ind - 1 >= 0)
    //     {
    //         prevHeight = v[ind - 1];
    //         ll diff = (prevHeight + p - 1) / p;
    //         ll newheight = (diff * p);

    //         int ptr = ind - 1;
    //         int tm = newheight / p;

    //         bool isval = true;

    //         // cout << newheight << endl;

    //         while (ptr >= 0 and v[ptr] <= newheight)
    //         {
    //             if (ans[ptr] <= tm)
    //             {
    //                 isval = false;
    //                 break;
    //             }
    //             ans[ptr] = tm;
    //             vis[ptr] = true;

    //             ptr--;
    //         }

    //         if (ptr > 0 and isval and v[ptr] <= newheight)
    //         {
    //             q.push({newheight, ptr});
    //         }
    //     }

    //     // for (auto i : ans)
    //     // {
    //     //     cout << i << " ";
    //     // }

    //     // cout << endl;
    // }

    for (auto i : ans)
    {
        cout << i << " ";
    }
    cout << endl;
}

void solve4()
{
    ll n, k;
    cin >> n >> k;

    ll m = 0;
    vector<ll> v(n);
    fl(i, n)
    {
        ll e;
        cin >> e;
        v[i] = e;
        if (e == 0)
        {
            m++;
        }
    }

    if (m == n)
    {
        ll res = 0;
        ll mul = factorial[m - 2] % MOD;

        for (ll i = 1; i <= k; i++)
        {
            ll curr = (mul) * (k - i + 1) % MOD;
            res = (res + curr) % MOD;
        }

        cout << res << endl;
    }

    else
    {
        ll total = 1;
        int i = 0;

        while (i < n)
        {
            while (i < n and v[i] != 0)
            {
                i++;
            }

            int len = 0;
            while (i < n and v[i] == 0)
            {
                i++;
                len++;
            }

            ll res = 1;

            for (ll j = 1; j <= len; j++)
            {
                res = ((res % MOD) * (k % MOD)) % MOD;
            }

            total = (total % MOD * res % MOD) % MOD;
        }

        cout << total << endl;
    }
}

void solve5()
{
    string s;
    cin >> s;
    int ones = 0;
    for (auto i : s)
    {
        if (i == '1')
            ones++;
    }

    cout << ones << endl;
}

void solve6()
{
    int n;
    cin >> n;
    vector<ll> v(n);
    bool chk = true;

    fl(i, n)
    {
        cin >> v[i];
        ll timetofront = i, timetoback = n - i - 1;
        ll maxtime = 2 * max(timetoback, timetofront);

        if ((v[i] - maxtime) <= 0 and chk)
        {
            cout << "NO\n";
            chk = false;
        }
    }

    if (chk)
        cout << "YES\n";
}

void solve7()
{
    int n;
    cin >> n;

    vector<ll> v(n);

    // inputting the array v[]
    fl(i, n) { cin >> v[i]; }

    // all negs [-1,-1]

    bool haspos = false;

    for (auto i : v)
    {
        if (i >= 0)
        {
            haspos = true;
            break;
        }
    }

    ll maxsum = accumulate(all(v), 0ll);

    // [-1,-3] => -1+3 = 2

    if (!haspos)
    {
        ll remsum = 0;

        for (int j = 0; j < v.size() - 1; j++)
        {
            remsum += (v[j] - v[j + 1]);
        }

        cout << maxsum << " " << remsum << endl;

        maxsum = max(maxsum, remsum);
        cout << maxsum << endl;
        return;
    }

    if (n > 1)
    {
        maxsum = abs(maxsum);
    }

    vector<ll> temp = v;

    while (temp.size() > 1)
    {
        vector<ll> curr;

        for (int j = 0; j < temp.size() - 1; j++)
        {
            curr.push_back(temp[j] - temp[j + 1]);
        }

        ll currsum = accumulate(all(curr), 0ll);

        int sz = temp.size();

        if (sz > 1)
        {
            currsum = abs(currsum);
        }

        maxsum = max(maxsum, currsum);

        temp = curr;
    }

    cout << maxsum << endl;
}

void solv8()
{
    int n;
    cin >> n;
    vector<pll> v(n);

    fl(i, n)
    {
        cin >> v[i].first >> v[i].second;
    }

    // find the tile with longest width
    int pos = 0;
    ll maxWidth = -1;

    fl(i, n)
    {
        if (v[i].second > maxWidth)
        {
            pos = i;
            maxWidth = v[i].second;
        }
        else if (v[i].second == maxWidth and v[i].first > v[pos].first)
        {
            pos = i;
        }
    }

    ll heightOfMaxWidthTile = v[pos].first;

    vector<pll> remTiles;

    ll highestTileHeight = 0;

    fl(i, n)
    {
        if (v[i].first > heightOfMaxWidthTile)
        {
            remTiles.push_back(v[i]);
            highestTileHeight = max(highestTileHeight, v[i].first);
        }
    }

    sort(all(remTiles), greater<>()); // arrange on basis of height

    ll ans = maxWidth + heightOfMaxWidthTile;

    int nextWidth = maxWidth, nextHeight = heightOfMaxWidthTile;
    int i = remTiles.size() - 1;

    if (remTiles.size() == 0)
    {
        ans += maxWidth + heightOfMaxWidthTile;
    }
    else
    {
        ans += highestTileHeight;
        while (i >= 0)
        {
            while (i >= 0 and remTiles[i].first <= nextHeight)
            {
                i--;
            }

            if (i < 0)
            {
                break;
            }

            ll currx = nextWidth - remTiles[i].second;
            ll curry = remTiles[i].first - nextHeight;

            nextWidth = remTiles[i].second;
            nextHeight = remTiles[i].first;

            // cout << currx << " " << curry << endl;

            ans += currx + curry;

            if (i == 0)
            {
                ans += remTiles[i].second;
            }

            i--;
        }
    }

    cout << ans << endl;
}

void solve9()
{
    int n;
    cin >> n;
    vector<ll> v(n);
    fl(i, n)
    {
        cin >> v[i];
    }

    ll ans = v[n - 1], secmax = *max_element(v.begin(), v.begin() + n - 1);

    ans += secmax;
    cout << ans << endl;
}

void solve10()
{
    ll n, a, b;
    cin >> n >> a >> b;

    ll k = (2 * (b - a)) + 1;
    k /= 2;

    k = max(0ll, k);
    k = min(k, n);

    ll sum = (k * b) + ((n - k) * a);
    sum -= (k * (k - 1)) / 2;

    cout << sum << endl;
}

// https://codeforces.com/contest/1978/problem/C
void sol11()
{
    ll n, k;
    cin >> n >> k;
    vector<ll> v(n);
    iota(all(v), 1);

    ll a = 2 * (n - 1);
    ll firstterm = a;

    ll maxsum = 0;

    while (a > 0)
    {
        maxsum += a;
        a -= 4;
    }

    if ((k % 2 != 0) || k > maxsum)
    {
        cout << "No\n";
    }
    else
    {
        int i = 0, lastTaken = n;
        while (k > 0 and i < lastTaken)
        {
            int low = i, high = lastTaken - 1, mid, ans = -1;
            while (low <= high)
            {
                mid = (low + high) / 2;
                int currVal = 2 * (mid - i);
                if (currVal <= k)
                {
                    ans = mid;
                    low = mid + 1;
                }
                else
                {
                    high = mid - 1;
                }
            }
            if (ans != -1)
            {
                k -= 2 * (ans - i);
                lastTaken = ans;
                swap(v[i], v[ans]);
            }
            i++;
        }

        cout << "Yes\n";
        for (auto i : v)
        {
            cout << i << " ";
        }
        cout << endl;
    }
}

void sol12()
{

    ll n, k;
    cin >> n >> k;

    vector<ll> v(n);

    fl(i, n)
    {
        cin >> v[i];
    }

    vector<int> ans(n);
    ll maxVotes = 0, posWinner = -1;
    v[0] += k;

    for (int i = 0; i < n; i++)
    {
        if (v[i] > maxVotes)
        {
            maxVotes = v[i];
            posWinner = i;
        }
    }

    ans[posWinner] = 0;

    vector<ll> suffmax(n, INT_MIN);
    suffmax[n - 1] = v[n - 1];

    for (int i = n - 2; i >= 0; i--)
    {
        suffmax[i] = max(suffmax[i + 1], v[i]);
    }

    ll piche = 0;
    ll maxBehind = 0;

    fl(i, n)
    {
        ll curr = v[i];
        ll toremove = 0;

        bool firstplace = (i == 0);

        if (maxBehind >= curr)
        {
            firstplace = true;
            toremove += i;
            curr += piche;
        }

        maxBehind = max(maxBehind, v[i]);
        piche += v[i];

        if (i == posWinner)
        {
            continue;
        }

        if (suffmax[i] > curr)
        {
            toremove++;
        }

        ans[i] = toremove;
    }

    for (auto i : ans)
    {
        cout << i << " ";
    }

    cout << endl;
}

// https://www.codechef.com/practice/course/5-star-and-above-problems/DIFF2500/problems/TRAVELLING
void travellingGraph()
{
    // add an edge b/w u and v with a cost of (u-v)^2
    // 1-N => (2-1)^2 + (3-1)^2 + ..... = (N-1)
    // upper bound of N-1

    // perform bfs, if reached => 0, else upper_bound = N-1, lower_bound = 1
}

// 2,6,5  => 6,3 => 4

// ((a1+a2)/2 +  a3)
// ((a1+a3)/2 +  a2)

void solve13()
{
    int n;
    cin >> n;
    vector<ll> v(n);

    fl(i, n)
    {
        cin >> v[i];
    }

    sort(all(v));

    ll res = (v[0] + v[1]) / 2;

    for (int i = 2; i < n; i++)
    {
        res = (res + v[i]) / 2;
    }

    cout << res << endl;
}

void solve14()
{
    ll n, x;
    cin >> n >> x;

    vector<ll> v(n);

    vector<ll> freq(n + 1, 0);

    fl(i, n)
    {
        cin >> v[i];
        if (v[i] < n)
            freq[v[i]]++;
    }

    ll currmex = 0;

    for (int i = 0; i < n; i++)
    {
        if (freq[i] == 0)
        {
            break;
        }
        else if (freq[i] == 1)
        {
            currmex++;
        }
        else
        {
            if ((i + x) < n)
                freq[i + x] += (freq[i] - 1);

            freq[i] = 1;
            currmex++;
        }
    }

    cout << currmex << endl;
}

void solve15()
{
    int n, m, q;
    cin >> n >> m >> q;

    vector<int> a(n), b(m);

    fl(i, n)
    {
        cin >> a[i];
    }

    fl(i, m)
    {
        cin >> b[i];
    }

    unordered_set<int> st;

    int i = 0;

    for (auto bi : b)
    {
        if (st.size() == n)
        {
            break;
        }
        if (st.count(bi))
        {
            continue;
        }
        else if (i < n and a[i] == bi)
        {
            st.insert(a[i]);
            i++;
        }
        else
        {
            cout << "TIDAk\n";
            return;
        }
    }

    cout << "YA\n";
    return;
}

void solve16()
{
    int n;
    cin >> n;
    unordered_set<ll> a, b;

    fl(i, n)
    {
        ll e;
        cin >> e;
        a.insert(e);
    }
    fl(i, n)
    {
        ll e;
        cin >> e;
        b.insert(e);
    }

    int n1 = a.size(), n2 = b.size();
    if ((n1 >= 2 and n2 >= 2) || (n1 >= 3 || n2 >= 3))
    {
        ha
    }
    else
    {
        na
    }
}

void solve17()
{
    int n, k;
    cin >> n >> k;

    vector<ll> v(n);
    inputvector(v);

    if (k == n)
    {
        vector<ll> b;
        for (int i = 1; i < n; i += 2)
        {
            b.push_back(v[i]);
        }
        for (int i = 0; i < n / 2; i++)
        {
            if (b[i] != (i + 1))
            {
                cout << i + 1 << endl;
                return;
            }
        }
        cout << (n / 2) + 1 << endl;
    }
    else
    {
        bool notonefound = false;
        for (int i = 1; i <= n - k + 1; i++)
        {
            if (v[i] != 1)
            {
                notonefound = true;
                break;
            }
        }
        if (notonefound)
        {
            cout << 1 << endl;
        }
        else
        {
            cout << 2 << endl;
        }
    }
}

void rash1()
{
    int n;
    cin >> n;

    vector<ll> v(n);
    inputvector(v);

    int numOper = 0;

    while (true)
    {
        bool issorted = true;
        int diff;

        for (int i = 1; i < n; i++)
        {
            if (v[i] < v[i - 1])
            {
                diff = v[i - 1];
                numOper += diff;
                issorted = false;
                break;
            }
        }

        if (issorted)
        {
            break;
        }
        else
        {
            for (int j = 0; j < n; j++)
            {
                v[j] = max(0ll, v[j] - diff);
            }
        }
    }

    cout << numOper << endl;
}

// 1 2 1 2 1 3 1 2 1 1 1 2
// 2 1 2 1 2   2 1 2 2 2 1

void rash2()
{
    int n;
    cin >> n;

    vector<ll> v(n);
    inputvector(v);

    int ones = 0;
    ll sum = 0;

    for (auto i : v)
    {
        if (i == 1)
            ones++;
    }

    for (auto i : v)
    {
        if (i != 1)
            sum += i - 1;
        if (sum >= ones)
        {
            break;
        }
    }

    if ((sum >= ones) and n > 1)
    {
        ha
    }
    else
    {
        na
    }
}

bool isposs(vector<ll> v, ll mid, ll k)
{
    int n = v.size();

    for (int i = 0; i < n - 1; i++)
    {
        ll reqOper = 0, reqValue = mid;
        bool done = false;
        for (int j = i; j < n; j++)
        {
            // f(i,y) = y-v[i] + f(i+1, y-1)
            if (v[j] >= reqValue)
            {
                done = true;
                break;
            }
            else
            {
                ll curr = (reqValue - v[j]);
                if ((reqOper + curr) <= k)
                {
                    reqOper += curr;
                }
                else
                {
                    reqOper = INT_MAX;
                    break;
                }
            }

            reqValue--;
        }

        if (reqOper <= k and done)
        {
            return true;
        }
    }

    return false;
}

void rash3()
{
    ll n, k;
    cin >> n >> k;

    vector<ll> v(n);
    inputvector(v);

    ll maxi = *max_element(all(v));

    ll low = maxi, high = maxi + k, mid, ans = low;

    while (low <= high)
    {
        mid = (low + high) / 2;

        if (isposs(v, mid, k))
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

void rash4()
{
    int n;
    cin >> n;

    vector<pll> v(n);

    fl(i, n)
    {
        cin >> v[i].first;
        v[i].second = i;
    }

    sort(all(v), greater<>());

    vector<int> b(n);
    int j = 1;

    for (auto i : v)
    {
        b[i.second] = j++;
    }

    for (auto i : b)
    {
        cout << i << " ";
    }

    cout << endl;
}

void rah5()
{
    int n;
    cin >> n;
    string s;
    cin >> s;

    if (n % 2 == 0)
    {
        int req = 0, p1 = 0, p2 = n - 1;
        int match = 0;
        while (p1 < p2)
        {
            if (s[p1] != s[p2])
            {
                req++;
            }
            else
            {
                match++;
            }
            p1++;
            p2--;
        }
        vector<int> ans(n + 1, 0);
        ans[req] = 1;
        for (int i = 1; i <= match; i++)
        {
            ans[req + 2 * i] = 1;
        }
        for (auto i : ans)
        {
            cout << i;
        }
        cout << endl;
    }
    else
    {
        int req = 0, p1 = 0, p2 = n - 1;
        int match = 0;

        while (p1 < p2)
        {
            if (s[p1] != s[p2])
            {
                req++;
            }
            else
            {
                match++;
            }
            p1++;
            p2--;
        }

        vector<int> ans(n + 1, 0);

        for (int i = 0; i <= match; i++)
        {
            ans[req + (2 * i)] = 1;
            ans[req + (2 * i) + 1] = 1;
        }

        for (auto i : ans)
        {
            cout << i;
        }

        cout << endl;
    }
}

void rash6()
{
    int n;
    cin >> n;
    vector<ll> v(n);
    fl(i, n)
    {
        cin >> v[i];
    }

    sort(all(v));

    int currmex = 0;

    for (auto i : v)
    {
        if (i == currmex)
        {
            currmex++;
        }
        else
        {
            break;
        }
    }

    cout << currmex << endl;
    cout << endl;

    cout.flush();

    for (int i = 0; i < 2 * (n + 1); i++)
    {
        ll e;
        cin >> e;
        if (e == -1)
        {
            return;
        }
        cout << e << endl;
        cout << endl;
        cout.flush();
    }
}

void rash7()
{
    int n, k;
    cin >> n >> k;

    vector<ll> v(n);
    inputvector(v);

    if (k == 1)
    {
        // check if v[i]=i
        for (int i = 1; i <= n; i++)
        {
            if (v[i - 1] != i)
            {
                na
            }
        }

        ha
    }

    else
    {
        // check if cycle exists or not
        unordered_set<int> indices;
        int i = v[0] - 1;
        indices.insert(0);

        while (true)
        {
            if (indices.count(i))
            {
                break;
            }
            else
            {
                indices.insert(i);
                i = v[i] - 1;
            }
        }

        // for (auto i : indices)
        // {
        //     cout << i << " ";
        // }
        // cout << endl;

        int sz = indices.size();
        if (sz == n)
        {
            ha
        }
        else
        {
            na
        }
    }
}

void radh8()
{
    int n, k;
    cin >> n >> k;

    vector<ll> v(n);

    fl(i, n)
    {
        cin >> v[i];
    }

    if (k == 0)
    {
        // all same
        bool allsame = true;
        int first = v[0] % 2;

        for (int i = 1; i < n; i++)
        {
            if ((v[i] % 2) != first)
            {
                cout << 0 << endl;
                return;
            }
        }

        ll ans = factorial[n];

        cout << ans << endl;
    }
    else
    {
        ll odds = 0, evens = 0;

        for (auto i : v)
        {
            if (i % 2 == 0)
                evens++;
            else
                odds++;
        }

        if ((n % 2) == 0)
        {
            if (odds != (n / 2))
            {
                cout << 0 << endl;
                return;
            }
            else
            {
                ll ans = (factorial[odds] * 1ll * factorial[evens]) % MOD;
                ans = (ans * 2) % MOD;
                cout << ans << endl;
            }
        }
        else
        {
            if (odds != (n / 2) and evens != (n / 2))
            {
                cout << 0 << endl;
                return;
            }
            else
            {
                ll ans = (factorial[odds] * 1ll * factorial[evens]) % MOD;
                cout << ans << endl;
            }
        }
    }
}

ll maxAllowed = (1e5 - 2) / 2;

void rash9()
{
    ll n, k;
    cin >> n >> k;

    ll req = k - (n / 2) - n;

    if (req < 0)
    {
        cout << -1 << endl;
        return;
    }

    req /= 2;
    vector<ll> ans(n, 0);

    for (int i = n - 1; i >= 0 and req > 0; i--)
    {
        if (req > maxAllowed)
        {
            ans[i] = maxAllowed;
            req -= maxAllowed;
        }
        else
        {
            ans[i] = req;
            req = 0;
            break;
        }
    }

    for (int i = 0; i < n / 2; i++)
    {
        ans[i] = (2 * ans[i]) + 1;
    }

    for (int i = n / 2; i < n; i++)
    {
        ans[i] = (2 * 1ll * ans[i]) + 2;
    }

    ll sum = accumulate(all(ans), 0ll);

    if (sum != k)
    {

        cout << -1 << endl;
        return;
    }

    for (auto i : ans)
    {
        cout << i << " ";
    }
    cout << endl;
}

void rash10()
{
    int n;
    cin >> n;
    map<ll, ll> freq;

    fl(i, n)
    {
        ll e;
        cin >> e;
        freq[e]++;
    }

    ll ans = 0;
    vector<vector<pll>> v;

    while (!freq.empty())
    {
        auto it = freq.begin();
        ll elem = it->first;
        ll currfr = it->second;

        freq.erase(it);

        vector<pll> temp;
        temp.push_back({elem, currfr});

        ans = max(ans, elem * 1ll * currfr);

        vector<ll> toErase;

        for (auto &i : freq)
        {
            ll e = i.first;
            if ((e % elem) == 0)
            {
                toErase.push_back(e);
                temp.push_back({e, i.second});
                ans = max(ans, e * 1ll * i.second);
            }
        }

        for (ll e : toErase)
        {
            freq.erase(e);
        }

        v.push_back(temp);
    }

    // Finding maximum value considering pairs
    for (auto &arr : v)
    {
        int sz = arr.size();
        for (int i = 0; i < sz; i++)
        {
            for (int j = i + 1; j < sz; j++)
            {
                // cout << arr[i].first << " " << arr[j].first << endl;
                if ((arr[j].first % arr[i].first) == 0)
                {
                    ll curr = min(arr[i].first, arr[j].first) * 1ll * (arr[i].second + arr[j].second);
                    ans = max(ans, curr);
                }
            }
        }
    }

    cout << ans << endl;
}

void sof1()
{
    ll a, b;
    cin >> a >> b;

    ll side = max(2 * min(a, b), max(a, b));

    cout << side * side << endl;
}

void sof2()
{
    int n;
    cin >> n;
    vector<int> v(n);
    inputvector(v);

    int ans = INT_MAX;
    sort(all(v));

    for (int i = 0; i < n - 1; i++)
    {
        ans = min(ans, v[i + 1] - v[i]);
    }

    cout << ans << endl;
}

void sof3()
{
    int n;
    cin >> n;
    vector<int> odds, evens;

    fl(i, n)
    {
        ll e;
        cin >> e;
        if ((e % 2) == 0)
            evens.push_back(e);
        else
            odds.push_back(e);
    }

    int a = odds.size(), b = evens.size();

    if (a % 2 == 0)
    {
        ha
    }
    else
    {
        unordered_set<int> oddelems;
        for (auto i : odds)
        {
            oddelems.insert(i);
        }

        for (auto i : evens)
        {
            if (oddelems.count(i + 1) || oddelems.count(i - 1))
            {
                ha
            }
        }

        na
    }
}

void sof4()
{
    ll n, k;
    cin >> n >> k;

    vector<ll> factors;

    for (int i = 1; i <= sqrt(n); i++)
    {
        if (i > k)
        {
            break;
        }

        if ((n % i) == 0)
        {
            factors.push_back(i);
            int p = n / i;
            if (p < k)
                factors.push_back(n / i);
        }
    }

    ll ans = INT_MAX;

    for (auto i : factors)
    {
        ans = min(ans, n / i);
        ll q = k / i;
        ll mul = i * q;
        ll rem = n % mul;
        if (rem == 0 and mul != 0)
        {
            ans = min(ans, n / mul);
        }
    }

    cout << ans << endl;
}

void sof5()
{
    int n;
    cin >> n;
    vector<string> grid(n);

    fl(i, n)
    {
        cin >> grid[i];
    }

    fl(i, n)
    {
        fl(j, n)
        {
            if (grid[i][j] == '1')
            {
                bool all1sright = true, all1sdown = true;

                if ((i + 1) < n and grid[i + 1][j] == '0')
                    all1sdown = false;
                if ((j + 1) < n and grid[i][j + 1] == '0')
                    all1sright = false;
                if (!all1sdown and !all1sright)
                {
                    na
                }
            }
        }
    }

    ha
}

bool tester(int n, int m, vector<string> &v, int pos, string &ans)
{
    ans = "";

    unordered_set<int> st;

    for (int i = 0; i < m; i++)
    {
        char toPush = '$';

        if (!st.empty())
        {
            auto it = *st.begin();
            toPush = v[it][i];

            for (auto t : st)
            {
                if (v[t][i] != toPush)
                {
                    return false;
                }
            }
        }
        else
        {
            toPush = v[pos][i];
        }

        for (int j = 0; j < n; j++)
        {
            if (v[j][i] != toPush)
            {
                if (st.count(j))
                {
                    return false;
                }
                else
                {
                    st.insert(j);
                }
            }
        }

        ans += toPush;
    }

    return true;
}

void sof6()
{
    // n strs of len = m
    int n, m;
    cin >> n >> m;

    vector<string> v(n);

    fl(i, n)
    {
        cin >> v[i];
    }

    string ans = "";

    for (int i = 0; i < n; i++)
    {
        bool chk = tester(n, m, v, i, ans);
        if (chk)
        {
            cout << ans << endl;
            return;
        }
    }

    cout << -1 << endl;
}

int main()
{
    fast_io;
    // precompute_factorials(1e5 + 100);

    int t = 1;
    cin >> t;

    while (t--)
    {
        sof6();
    }
    return 0;
}
