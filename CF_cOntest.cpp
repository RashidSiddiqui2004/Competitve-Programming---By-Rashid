
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
// typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
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
inline ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
inline ll lcm(ll a, ll b) { return a / gcd(a, b) * b; }

inline ll mod_add(ll a, ll b, ll m = MOD)
{
    return (a + b) % m;
}

inline ll mod_sub(ll a, ll b, ll m = MOD)
{
    return (a - b + m) % m;
}

inline ll mod_mul(ll a, ll b, ll m = MOD)
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

ll exp_fast(ll a, ll b)
{
    ll res = 1;
    while (b > 0)
    {
        if (b & 1)
            res = res * 1ll * a;
        a = 1 * 1ll * a;
        b >>= 1;
    }
    return res;
}

vector<ll> pow2;

void mod_pow2_memo()
{
    pow2.resize(1e5 + 1);

    ll curr = 1ll;
    for (int i = 0; i <= 1e5; i++)
    {
        pow2[i] = curr;
        curr = (curr * 2) % MOD;
    }
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

const int maxn = 1e6 + 1;
vector<int> spf;

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

void solve()
{
    int n;
    cin >> n;
    vector<int> v(n);

    read_vector(v);
    sort(all(v));

    int p = n / 2;

    cout << v[p] << endl;
}

void sol2()
{
    int n;
    cin >> n;
    string s;
    cin >> s;

    vector<int> freq(26, 0);

    for (char c : s)
    {
        freq[c - 'a']++;
    }

    vector<pair<int, char>> temp;
    for (int i = 0; i < 26; i++)
    {
        if (freq[i] > 0)
            temp.push_back({freq[i], 'a' + i});
    }

    sort(temp.rbegin(), temp.rend());

    string res(n, ' ');

    int idx = 0;

    for (auto &i : temp)
    {
        auto ch = i.second;
        while (i.first > 0 && idx < n)
        {
            res[idx] = ch;
            idx += 2;
            i.first--;
        }
    }

    idx = 1;
    for (auto i : temp)
    {
        auto ch = i.second;
        while (i.first > 0 && idx < n)
        {
            res[idx] = ch;
            idx += 2;
            i.first--;
        }
    }

    cout << res << "\n";
}

// https://codeforces.com/contest/2003/problem/D1
void sol3()
{
    const int N = 2 * 1e5 + 2;
    ll n, m;
    cin >> n >> m;

    ll maxmex = 0;

    fl(i, n)
    {
        int sz;
        cin >> sz;

        vector<bool> pres(N, 0);

        fl(h, sz)
        {
            ll e;
            cin >> e;
            if (e < N)
                pres[e] = 1;
        }

        ll mex;
        bool ch = true;

        for (int j = 0; j < N; j++)
        {
            if (!pres[j])
            {
                if (ch)
                {
                    ch = false;
                }
                else
                {
                    mex = j;
                    break;
                }
            }
        }

        maxmex = max(maxmex, mex);
    }

    ll k = min(maxmex, m);

    ll ans = (k + 1) * 1ll * maxmex;

    ll t1 = (m * 1ll * (m + 1)) / 2;
    ll t2 = (k * 1ll * (k + 1)) / 2;

    ans += (t1 - t2);

    cout << ans << endl;
}

// https://codeforces.com/contest/2003/problem/D2
void sol4()
{
    int n, m;
    cin >> n >> m;
    const int MAX = 200002;
    vector<ll> best(MAX, -1);
    vector<int> cnt(MAX, 0);

    // Process each sequence: compute its (a, b) pair.
    for (int i = 0; i < n; i++)
    {
        int sz;
        cin >> sz;
        vector<bool> pres(MAX, false);
        for (int j = 0; j < sz; j++)
        {
            int x;
            cin >> x;
            if (x < MAX)
                pres[x] = true;
        }
        int a = -1, b = -1;
        for (int j = 0; j < MAX; j++)
        {
            if (!pres[j])
            {
                if (a == -1)
                {
                    a = j;
                }
                else
                {
                    b = j;
                    break;
                }
            }
        }
        if (a != -1)
        {
            cnt[a]++;
            best[a] = max(best[a], (ll)b);
        }
    }

    // Precompute nxt[x]: the smallest y > x such that cnt[y] > 0.
    vector<int> nxt(MAX, -1);
    int last = -1;
    for (int x = MAX - 1; x >= 0; x--)
    {
        if (cnt[x] > 0)
            last = x;
        nxt[x] = last;
    }

    // Let max_mex be the maximum x for which some sequence exists.
    int max_mex = 0;
    for (int x = 0; x < MAX; x++)
    {
        if (cnt[x] > 0)
            max_mex = x;
    }

    // dp[x]: best final value when at x with matching option available.
    // h[x]: best final value when at x but matching option is lost.
    // For x > max_mex, we simply have dp[x] = h[x] = x.
    vector<ll> dp(MAX, 0), h(MAX, 0);
    for (int x = MAX - 1; x > max_mex; x--)
    {
        dp[x] = x;
        h[x] = x;
    }

    // Now compute dp[x] and h[x] for x = max_mex down to 0.
    for (int x = max_mex; x >= 0; x--)
    {
        ll candidate = x;
        // Option 1: if a sequence with a == x exists and you are in matching state,
        // you can use it to jump to its second mex.
        if (cnt[x] > 0 && best[x] != -1)
        {
            candidate = max(candidate, dp[best[x]]);
        }
        // Option 2: if there is some sequence available at a higher mex,
        // you may use a non–matching move.
        if (nxt[x] != -1 && nxt[x] > x)
        {
            int y = nxt[x];
            // If the available mex y has at least two sequences,
            // you can use one non–matching and still keep the matching option.
            if (cnt[y] >= 2)
                candidate = max(candidate, dp[y]);
            else
                candidate = max(candidate, h[y]);
        }
        dp[x] = candidate;

        ll candidate_h = x;
        if (nxt[x] != -1 && nxt[x] > x)
        {
            int y = nxt[x];
            // In the "lost" state you cannot use a matching move, so you only can do non–matching.
            if (cnt[y] >= 2)
                candidate_h = max(candidate_h, dp[y]);
            else
                candidate_h = max(candidate_h, h[y]);
        }
        h[x] = candidate_h;
    }

    // Finally, note that if you start with a value k > max_mex then f(k) = k.
    // And if k ≤ max_mex, then f(k) = dp[k].
    ll ans = 0;
    for (int k = 0; k <= m; k++)
    {
        if (k < MAX)
        {
            ans += (k <= max_mex ? dp[k] : k);
        }
        else
        {
            ans += k;
        }
    }
    cout << ans << "\n";
}

void rash1()
{
    int n, m;
    cin >> n >> m;

    vector<string> v(n);
    fl(i, n)
    {
        cin >> v[i];
    }

    vector<int> rowxor(n, 0);
    vector<int> colxor(m, 0);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            rowxor[i] ^= (v[i][j] - '0');
            colxor[j] ^= (v[i][j] - '0');
        }
    }

    int rows = 0, cols = 0;
    for (int i = 0; i < n; i++)
    {
        if (rowxor[i] == 1)
            rows++;
    }
    for (int j = 0; j < m; j++)
    {
        if (colxor[j] == 1)
            cols++;
    }

    cout << max(rows, cols) << "\n";
}

ll floor(ll v)
{
    return (v % 2 == 0) ? v / 2 : (v - 1) / 2;
}

ll ceil(ll v)
{
    return (v % 2 == 0) ? v / 2 : (v + 1) / 2;
}

void rash2()
{
    int x, n, m;
    cin >> x >> n >> m;

    n = min(n, 32);
    m = min(m, 32);

    vector<pll> dp(m + 1);

    dp[0] = {x, x};
    for (int j = 1; j <= m; j++)
    {
        ll newVal = ceil(dp[j - 1].first);
        dp[j] = {newVal, newVal};
    }

    for (int i = 1; i <= n; i++)
    {
        vector<pll> new_dp(m + 1);
        new_dp[0] = {floor(dp[0].first), floor(dp[0].second)};

        for (int j = 1; j <= m; j++)
        {
            ll cur_min = min(floor(dp[j].first), ceil(new_dp[j - 1].first));
            ll cur_max = max(floor(dp[j].second), ceil(new_dp[j - 1].second));
            new_dp[j] = {cur_min, cur_max};
        }

        dp = move(new_dp);
    }

    cout << dp[m].first << " " << dp[m].second << "\n";
}

void rash3()
{
    double x;
    cin >> x;

    int ans;
    if (x >= 38.0)
    {
        x = 1;
    }
    else if (x < 37.5)
    {
        x = 3;
    }
    else
    {
        x = 2;
    }

    cout << x << endl;
}

void rash4()
{
    string s;
    cin >> s;

    int ans = 0;
    int pos = 0, i = 0;
    int n = s.size();

    while (i < n)
    {
        if ((pos % 2) == 0)
        {
            if (s[i] != 'i')
            {
                ans++;
            }
            else
            {
                i++;
            }
        }
        else
        {
            if (s[i] != 'o')
            {
                ans++;
            }
            else
            {
                i++;
            }
        }
        pos++;
    }

    if ((pos % 2) != 0)
    {
        ans++;
    }

    cout << ans << endl;
}

void rash5()
{
    int n;
    cin >> n;

    vector<int> v(n);
    unordered_map<int, int> mp;

    fl(i, n)
    {
        cin >> v[i];
        mp[v[i]]++;
    }

    unordered_map<int, int> mp2;

    int ans = 0;

    fl(i, n - 1)
    {
        mp2[v[i]]++;
        mp[v[i]]--;

        if (mp[v[i]] == 0)
        {
            mp.erase(v[i]);
        }
        ans = max(ans, (int)mp.size() + (int)mp2.size());
    }

    cout << ans << endl;
}

void splitVarietyhardF()
{
}

void cubes()
{
    ll n;
    cin >> n;

    for (ll i = 1; i <= 1e6; i++)
    {
        ll y = n + i * i * i;
        ll c = round(cbrt(y));

        if (c * c * c == y)
        {
            if (i < c)
            {
                swap(i, c);
            }
            cout << i << " " << c << endl;
            return;
        }
    }

    cout << -1 << endl;
}

// div 2
// https://codeforces.com/contest/1853

// https://codeforces.com/contest/1853/problem/A
void a1()
{
    int n;
    cin >> n;
    vector<ll> v(n);
    read_vector(v);

    int ans = INT_MAX;
    for (int i = 0; i < n - 1; i++)
    {
        if (v[i] > v[i + 1])
        {
            cout << 0 << endl;
            return;
        }
        else
        {
            int diff = v[i + 1] + 1 - v[i];
            ans = min(ans, (diff + 1) / 2);
        }
    }

    cout << ans << endl;
}

// https://codeforces.com/contest/1853/problem/B
void a2()
{
    ll n, k;
    cin >> n >> k;

    // f1, f2 ..... => fk = n

    ll ans = 0;

    if (k == 3)
    {
        for (int i = 0; i <= n; i++)
        {
            if (i > (n - i))
            {
                break;
            }

            ans++;
        }
    }
    else
    {
        for (int i = 0; i <= n; i++)
        {
            ll rem = n - i;

            if (i > rem)
            {
                break;
            }

            bool check = true;

            ll curr = i, next = rem;

            int remTerms = k - 3;

            while (remTerms--)
            {
                ll prev = next - curr;
                if (prev > curr || prev < 0)
                {
                    check = false;
                    break;
                }
                next = curr;
                curr = prev;
            }

            if (check)
            {
                ans++;
            }
        }
    }

    cout << ans << endl;
}

void a3()
{
    int n;
    long long k;
    cin >> n >> k;
    vector<long long> a(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    // If the first removal-index is greater than 1 then the very first element is never removed.
    if (a[0] > 1)
    {
        cout << 1 << "\n";
        return;
    }

    // Otherwise a[0] == 1.
    // Initially if there were no “gaps” the answer would be k*n + 1.
    long long ans = k * n + 1;
    // Each gap between consecutive a[i] saves some removals.
    for (int i = 0; i < n - 1; i++)
    {
        long long gap = a[i + 1] - a[i] - 1; // gap between a[i] and a[i+1]
        ans -= min(k, gap);
    }
    cout << ans << "\n";
}

void a4()
{
    string s;
    cin >> s;

    int n = s.size();

    if (n == 2)
    {
        if (s == "()")
        {
            no
        }
        else
        {
            yes;
            if (s == "))" || s == "((")
            {
                cout << "()()\n";
            }
            else
            {
                cout << "(())\n";
            }
        }
    }
    else
    {
        yes;
        bool ch = false;

        for (int i = 0; i < n - 1; i++)
        {
            string t = s.substr(i, 2);
            if (t == "((" || t == "))")
            {
                ch = true;
                break;
            }
        }

        if (ch)
        {
            fl(i, n)
            {
                cout << "()";
            }
            cout << endl;
        }
        else
        {
            fl(i, n)
            {
                cout << "(";
            }
            fl(i, n)
            {
                cout << ")";
            }
            cout << endl;
        }
    }
}

void a5()
{
    ll m, k, a1, ak;
    cin >> m >> k >> a1 >> ak;

    ll reqk = m / k;

    if (reqk <= ak)
    {
        m -= reqk * 1ll * k;

        ll ans = 0;

        if (a1 < m)
        {
            ans = (m - a1);
        }

        cout << ans << endl;
    }
    else
    {
        // consider both scenarios

        ll ans = 0;

        {
            ll m1 = m - (ak * 1ll * k);

            if (a1 < m1)
            {
                ans = (m1 - a1);
            }
        }

        {
            ll half = a1 / k;

            for (int i = 0; (reqk - i) >= ak and i <= half; i++)
            {
                ll ans2 = (reqk - i) - ak;

                ll m2 = m - (k * 1ll * (reqk - i));

                if (a1 < m2)
                {
                    ans2 += (m2 - a1);
                }

                ans = min(ans, ans2);
            }
        }

        cout << ans << endl;
    }
}

void a5Optimized()
{
    ll m, k, a1, ak;
    cin >> m >> k >> a1 >> ak;

    ll taken_k = m / k;
    ll taken_1 = m % k;

    ll fancy_k = max(0ll, taken_k - ak);
    ll fancy_1 = max(0ll, taken_1 - a1);

    ll left_regular1 = max(0ll, a1 - taken_1);
    ll to_replace = min(left_regular1 / k, fancy_k);

    ll ans = fancy_1 + fancy_k - to_replace;

    cout << ans << endl;
}

// https://codeforces.com/contest/1860/problem/C
void a6()
{
    int n;
    cin >> n;
    vector<int> v(n);
    read_vector(v);

    int alpha = INT_MAX, curr_smallest = INT_MAX;
    int ans = 0;

    fl(i, n)
    {
        curr_smallest = min(curr_smallest, v[i]);
        if (v[i] > curr_smallest)
        {
            alpha = min(alpha, v[i]);
        }

        if (v[i] == alpha)
        {
            ans++;
        }
    }

    cout << ans << endl;
}

void a7()
{
    int n;
    cin >> n;

    vector<int> v(1e6 + 10, 0);

    fl(i, n)
    {
        int e;
        cin >> e;
        v[e]++;
    }

    int ans = 0;

    int total = n;

    fl(i, 1e6 + 2)
    {
        if (v[i] > 0)
        {
            ans += total;
            total -= v[i];
        }
    }

    cout << ans << endl;
}

void getFactorization(ll n, unordered_map<ll, ll> &mp)
{
    while (n > 0)
    {
        if (spf[n] == n)
        {
            mp[n]++;
            break;
        }
        mp[spf[n]]++;
        n /= spf[n];
    }
    return;
}

void a8()
{
    int n, k;
    cin >> n >> k;

    unordered_map<ll, ll> mp;

    fl(i, 6)
    {
        mp[i + 1] = 0;
    }

    getFactorization(k, mp);

    for (auto i : mp)
    {
        if (i.first > 6)
        {
            cout << -1 << endl;
            return;
        }
    }

    int maxsum = 0;

    if (mp[5] > 0)
        maxsum += 5 * mp[5];

    n -= mp[5];

    int min_23 = min(mp[2], mp[3]);

    if (min_23 > 0)
        maxsum += 6 * min_23;

    n -= min_23;

    int fr3 = mp[3] - min_23;
    if (fr3 > 0)
        maxsum += 3 * fr3;
    n -= fr3;

    int fr2 = mp[2] - min_23;
    int fr4 = fr2 / 2;

    if (fr4 > 0)
        maxsum += 4 * fr4;
    n -= fr4;

    fr2 -= (fr4 * 2);
    if (fr2 > 0)
        maxsum += 2 * fr2;
    n -= fr2;

    maxsum += n;

    cout << maxsum << endl;
}

void a9()
{
    int h, k, n;
    cin >> h >> k >> n;

    vector<pair<int, int>> v(n);

    fl(i, n)
    {
        cin >> v[i].first >> v[i].second;
    }

    int maxRadius = 0;

    fl(i, h + 1)
    {
        fl(j, k + 1)
        {
            int minDist = min({i * i, (h - i) * (h - i), j * j, (k - j) * (k - j)});
            for (auto m : v)
            {
                int curr = (i - m.first) * (i - m.first) + (j - m.second) * (j - m.second);
                minDist = min(minDist, curr);
            }
            maxRadius = max(maxRadius, minDist);
        }
    }

    double ans = sqrt(maxRadius);

    cout << setprecision(10) << ans << endl;
}

void a10()
{
    int l, r;
    cin >> l >> r;

    int sum1 = mod_sub(pow2[r], pow2[l - 1]);

    int cntOdd = ((r + 1) / 2) - (l / 2);

    int cntEven = (r / 2) - ((l - 1) / 2);

    int odd_first = (l % 2 == 1 ? l : l + 1);

    int m0 = odd_first / 2;

    int even_first = (l % 2 == 0 ? l : l + 1);

    int m1 = even_first / 2;

    int sumOdd = mod_sub(pow2[m0 + cntOdd], pow2[m0]);

    int sumEven = mod_sub(pow2[m1 + cntEven], pow2[m1]);

    int totSub = mod_add(sumOdd, sumEven);

    int ans = mod_sub(sum1, totSub);

    cout << ans << "\n";
}

int32_t main()
{
    fast_io;
    // precompute_factorials(maxn);

    // spf => smallest prime factor
    // modified sieves for faster factorization

    mod_pow2_memo();

    // spf.resize(maxn + 1, 0ll);

    // spf[1] = 1;

    // for (ll i = 2; i < maxn; i++)
    // {
    //     if (spf[i])
    //         continue;
    //     spf[i] = i;
    //     for (ll j = i * i; j < maxn; j += i)
    //     {
    //         if (!spf[j])
    //             spf[j] = i;
    //     }
    // }

    bool isMulti = true;

    int t = 1;

    if (isMulti)
        cin >> t;

    while (t--)
        a10();

    return 0;
}

// long long use krna hai
// binary search thoroughly test krna hai
// multi test cases check krna hai
// yes/no me case check krna hai
// early returns me be careful for edge cases
// unordered_map / map me dhyan dena hai
// when to use map
// when to use unordered_map