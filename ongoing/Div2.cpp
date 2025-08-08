
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

#define int long long

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pll> vpll;

#define vvi vector<vector<int>>
// Constants
const int MOD = 1e9 + 7;
const ll InF = 1e18;
const double EPS = 1e-9;
const ll nEG = -1e18;

// Debugging
#ifndef OnLInE_JUDGE
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

// vector<ll> pow2;

// void mod_pow2_memo()
// {
//     pow2.resize(1e5 + 1);

//     ll curr = 1ll;
//     for (int i = 0; i <= 1e5; i++)
//     {
//         pow2[i] = curr;
//         curr = (curr * 2) % MOD;
//     }
// }

ll mod_inv(ll a, ll m = MOD)
{
    // Modular inverse using Fermat's Little Theorem: a^(m-2) % m
    return mod_pow(a, m - 2, m);
}

vector<ll> factorial, inv_factorial;

void precompute_factorials(int maxn, ll m = MOD)
{
    factorial.resize(maxn + 1);
    inv_factorial.resize(maxn + 1);

    factorial[0] = 1;
    for (int i = 1; i <= maxn; ++i)
    {
        factorial[i] = mod_mul(factorial[i - 1], i, m);
    }

    inv_factorial[maxn] = mod_inv(factorial[maxn], m);

    // (n)^-1 = ((n+1)^-1) * (n+1)
    for (int i = maxn - 1; i >= 0; --i)
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

vector<int> primes;
vector<bool> isPrime;

vector<int> sieve(int n)
{
    primes.clear();
    isPrime.assign(n + 1, true);

    for (int i = 2; i <= n; i++)
    {
        if (isPrime[i])
        {
            primes.pb(i);
            for (int j = i * 2; j <= n; j += i)
            {
                isPrime[j] = false;
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

#define yes          \
    cout << "Yes\n"; \
    return;

#define no          \
    cout << "No\n"; \
    return;

#define impossible  \
    cout << "-1\n"; \
    return;

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

const int mod_CC = 998244353;

int ceil_log2(int x)
{
    if (x <= 1)
        return 0;
    return 64 - __builtin_clzll(x - 1);
}

struct BIT
{
    int n;
    vector<int> f;
    BIT(int _n) : n(_n), f(n + 1, 0) {}
    void add(int index, int value)
    {
        while (index <= n)
        {
            f[index] += value;
            index += index & -index;
        }
    }

    int sum(int index)
    {
        int result = 0;
        while (index > 0)
        {
            result += f[index];
            index -= index & -index;
        }
        return result;
    }

    int sum(int l, int r)
    {
        if (l > r)
            return 0;
        return sum(r) - sum(l - 1);
    }
};

struct Node
{
    int key, type, pos, l, idx;
};

ll get_val(int c, int d, const vector<ll> &ps, int n)
{
    if (c < d)
        return ps[d - 1] - ps[c];
    return (ps[2 * n] - ps[c]) + ps[d - 1];
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
};

void usecase()
{
    yes;
    no;
    impossible;
}

void r1()
{
    int n;
    cin >> n;

    vector<int> v(n);
    read_vector(v);

    bool iszero = (v[n - 1] == 0);

    for (int i = 0; i < n - 1; i++)
    {
        if (v[i] == 0 and v[i + 1] == 0)
        {
            cout << "YES\n";
            return;
        }
        if (v[i] == 0)
        {
            iszero = true;
        }
    }

    if (!iszero)
    {
        cout << "YES\n";
        return;
    }

    cout << "NO\n";
    return;
}

int solve(int L, int p)
{
    return min(p, L - p + 1);
}

void r2()
{
    int n, m, a, b;
    cin >> n >> m >> a >> b;

    if (n == 1 && m == 1)
    {
        cout << 0 << endl;
        return;
    }

    int ans = LLONG_MAX;

    if (n > 1)
    {
        int t = solve(n, a);
        int p = (m + 1) / 2;
        int lval = (m > 1 ? solve(m, p) : 1);

        int turns = 0;
        turns += 1;
        turns += ceil_log2(t);

        if (m > 1)
        {
            turns += 1;
            turns += ceil_log2(lval);
        }

        ans = min(ans, turns);
    }

    if (m > 1)
    {
        int t = solve(m, b);
        int pw = (n + 1) / 2;
        int lval = (n > 1 ? solve(n, pw) : 1);

        int turns = 0;
        turns += 1;
        turns += ceil_log2(t);

        if (n > 1)
        {
            turns += 1;
            turns += ceil_log2(lval);
        }
        ans = min(ans, turns);
    }

    cout << ans << "\n";
}

void r3()
{
    int n;
    cin >> n;

    for (int i = 0; i < 3; i++)
    {
        cout << "digit" << endl
             << flush;
        cout.flush();
        int st;
        cin >> st;
    }

    int ad1;

    cout << "add -1" << endl
         << flush;

    cin >> ad1;
}

void r4()
{
    int xc, yc, k;
    cin >> xc >> yc >> k;

    // sum of X's should be xc
    // sum of Y's should be yc

    int currx = 0, curry = 0;

    for (int i = 1; i <= k / 2; i++)
    {
        cout << xc << " " << yc - i << "\n";
        cout << xc << " " << yc + i << "\n";
    }
    if (k % 2)
    {
        cout << xc << " " << yc << "\n";
    }
}

void r5()
{
    int n;
    cin >> n;
    vector<int> p(n);
    for (int &i : p)
        cin >> i;
    rotate(p.begin(), p.begin() + 1, p.end());
    for (int i : p)
        cout << i << " ";
    cout << "\n";
}

// https://codeforces.com/contest/1905/problem/A
void r6()
{
    int n, m;
    cin >> n >> m;

    cout << max(n, m) << endl;
}

// https://codeforces.com/contest/1905/problem/B
void r7()
{
    // answer is number of branches on the diameter of the tree
    // let k = number of branches on the diameter of the tree
    // ans = max(1, k)

    int n;
    cin >> n;

    vector<vector<int>> adj(n);
    vector<int> degree(n, 0);

    fl(i, n - 1)
    {
        int u, v;
        cin >> u >> v;
        --u, --v;
        degree[u]++;
        degree[v]++;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int leaves = 0;

    fl(i, n)
    {
        if (degree[i] == 1)
        {
            leaves++;
        }
    }

    cout << (leaves + 1) / 2 << endl;
}

// https://codeforces.com/contest/1905/problem/C
void r8()
{
    int n;
    cin >> n;

    string s;
    cin >> s;

    vector<int> largestright(n + 1);

    char ch = 'a';
    int index = -1;

    for (int i = n - 1; i >= 0; i--)
    {
        largestright[i + 1] = index;
        if (s[i] >= ch)
        {
            ch = s[i];
            index = i;
        }
    }

    largestright[0] = index;

    vector<int> isPartOfSubsequence(n, 0);

    int i = 0;

    while (i <= n)
    {
        if (largestright[i] == -1)
        {
            break;
        }
        isPartOfSubsequence[largestright[i]] = 1;
        i = largestright[i] + 1;
    }

    string temp = "", subs = "";

    fl(i, n)
    {
        if (!isPartOfSubsequence[i])
        {
            temp += s[i];
        }
        else
        {
            subs += s[i];
        }
    }

    string reversesubs = subs;
    reverse(all(reversesubs));

    int len = temp.size();

    for (int i = 0; i < len - 1; i++)
    {
        if (temp[i] > temp[i + 1])
        {
            cout << -1 << endl;
            return;
        }
    }

    int j = 0;

    for (int i = 0; i < n; i++)
    {
        if (isPartOfSubsequence[i])
        {
            s[i] = reversesubs[j++];
        }
    }

    for (int i = 0; i < n - 1; i++)
    {
        if (s[i] > s[i + 1])
        {
            cout << -1 << endl;
            return;
        }
    }

    int equallen = 0;
    i = 0;

    ch = subs[0];

    while (i < subs.size() and ch == subs[i])
    {
        equallen++;
        i++;
    }

    int ans = (int)subs.size() - equallen;

    cout << ans << endl;
}

// https://codeforces.com/contest/1858/problem/B

int solve(int d, vector<int> x)
{
    int ans = 0;
    for (int i = 1; i < x.size(); i++)
    {
        ans += (x[i] - x[i - 1] - 1) / d;
    }
    ans += ll(x.size()) - 2;
    return ans;
}

void r9()
{

    int n, m, d;
    cin >> n >> m >> d;
    vector<int> r(m);
    for (int i = 0; i < m; i++)
        cin >> r[i];

    r.insert(r.begin(), 1 - d);
    r.push_back(n + 1);

    int ans = 2e9;
    vector<int> res;

    for (int i = 1; i <= m; i++)
    {
        int A = r[i] - r[i - 1] - 1;
        int B = r[i + 1] - r[i] - 1;
        int C = r[i + 1] - r[i - 1] - 1;
        int D = C / d - (A / d + B / d);
        if (D < ans)
        {
            ans = D;
            res.clear();
        }
        if (D == ans)
        {
            res.push_back(r[i]);
        }
    }
    cout << ans + solve(d, r) - 1 << ' ' << res.size() << endl;
}

bool isPossible(vector<int> a, vector<int> b, int lasta, int lastb)
{
    int n = a.size();
    for (int i = 0; i < n - 1; i++)
    {
        if (a[i] > lasta)
        {
            if (b[i] <= lasta)
            {
                swap(a[i], b[i]);
            }
            else
            {
                return 0;
            }
        }
    }

    for (int i = 0; i < n - 1; i++)
    {
        if (b[i] > lastb)
        {
            return 0;
        }
    }
    return 1;
}

void r10()
{
    int n;
    cin >> n;

    vector<int> a(n), b(n);

    read_vector(a);
    read_vector(b);

    int lasta = a.back(), lastb = b.back();

    if (isPossible(a, b, lasta, lastb) || isPossible(a, b, lastb, lasta))
    {
        yes;
    }

    no;
}

// https://codeforces.com/contest/1798/problem/B
void r11()
{
    int d;
    cin >> d;

    static const int LIMIT = 50001;
    vector<bool> isPres(LIMIT, 0);

    vector<vector<int>> v(d);
    vector<int> temp;

    fl(i, d)
    {
        temp.clear();
        int n;
        cin >> n;

        temp.clear();

        fl(j, n)
        {
            int e;
            cin >> e;
            temp.push_back(e);
        }

        v[i] = (temp);
    }

    vector<int> ans(d, -1);

    for (int i = d - 1; i >= 0; i--)
    {
        bool foundWinner = false;

        for (auto j : v[i])
        {
            if (!isPres[j])
            {
                ans[i] = j;
                foundWinner = true;
            }
            isPres[j] = 1;
        }
    }

    for (auto i : ans)
    {
        if (i == -1)
        {
            impossible;
        }
    }

    print_vector(ans);
}

// https://codeforces.com/contest/1798/problem/D
void r12()
{
}

// 2 < 4 > 1 < 6 > 3
// n elements -> max peaks = (n-1)/2
// for k peaks => (2*k) + 1 elements

// 1 3 2 5 4 6 7

void r13()
{
    int n, k;
    cin >> n >> k;

    int maxPeaks = (n - 1) / 2;

    if (k > maxPeaks)
    {
        impossible;
    }

    else
    {
        int curr = 2;
        cout << 1 << " ";

        while (curr <= n)
        {
            if (curr == n)
            {
                cout << curr;
                break;
            }
            if (k)
            {
                k--;
                cout << curr + 1 << " " << curr << " ";
            }
            else
            {
                cout << curr << " " << curr + 1 << " ";
            }
            curr += 2;
        }

        cout << endl;
    }
}

void r14()
{
    int n;
    cin >> n;

    vector<int> v(n);
    read_vector(v);

    int mini = *min_element(all(v));
    int cnt = 0;

    for (auto &i : v)
    {
        if (i == mini)
            cnt++;

        if ((mini & i) < mini)
        {
            cout << 0 << endl;
            return;
        }
    }

    if (cnt < 2)
    {
        cout << 0 << endl;
    }
    else
    {
        ll ans = cnt * 1ll * (cnt - 1) % MOD;

        ans = (ans * 1ll * factorial[n - 2] + MOD) % MOD;

        cout << ans << endl;
    }
}

void s1()
{
    int n;
    cin >> n;
    vector<int> v(n);
    read_vector(v);

    vector<int> odds, evens;

    for (auto &i : v)
    {
        if (i % 2)
        {
            odds.push_back(i);
        }
        else
        {
            evens.push_back(i);
        }
    }

    for (auto i : odds)
    {
        cout << i << " ";
    }
    for (auto i : evens)
    {
        cout << i << " ";
    }

    cout << endl;
}

// https://codeforces.com/contest/1509/problem/B
void s2()
{
    int n;
    cin >> n;

    string s;
    cin >> s;

    int preft = 0, prefm = 0;

    fl(i, n)
    {
        if (s[i] == 'T')
        {
            preft++;
        }
        else
        {
            prefm++;
            if (prefm > preft)
            {
                no;
            }
        }
    }

    if (2 * prefm != preft)
    {
        no;
    }

    preft = 0, prefm = 0;

    fl(i, n)
    {
        if (s[n - i - 1] == 'T')
        {
            preft++;
        }
        else
        {
            prefm++;
            if (prefm > preft)
            {
                no;
            }
        }
    }
    yes;
}

const int MAX = 2e3 + 5;
ll mem[MAX][MAX], a[MAX];

ll dp(int l, int r)
{
    if (mem[l][r] != -1)
        return mem[l][r];
    if (l == r)
        return 0;
    return mem[l][r] = (a[r] - a[l]) + min(dp(l + 1, r), dp(l, r - 1));
}

void s3()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];

    sort(a, a + n);
    memset(mem, -1, sizeof mem);

    cout << dp(0, n - 1) << '\n';
}

string mix(string s, string t, char c)
{
    int n = s.size() / 2;
    vector<int> v1 = {-1}, v2 = {-1};
    for (int i = 0; i < 2 * n; i++)
    {
        if (s[i] == c)
            v1.push_back(i);
        if (t[i] == c)
            v2.push_back(i);
    }
    string ans;
    for (int i = 0; i < n; i++)
    {
        for (int j = v1[i] + 1; j < v1[i + 1]; j++)
            ans += s[j];
        for (int j = v2[i] + 1; j < v2[i + 1]; j++)
            ans += t[j];
        ans += c;
    }
    for (int j = v1[n] + 1; j < 2 * n; j++)
        ans += s[j];
    for (int j = v2[n] + 1; j < 2 * n; j++)
        ans += t[j];
    return ans;
}

void s4()
{
    vector<string> s0, s1;
    int n;
    cin >> n;
    for (int i = 0; i < 3; i++)
    {
        string s;
        cin >> s;
        int cnt_0 = 0;
        for (auto &c : s)
        {
            if (c == '0')
                cnt_0++;
        }
        if (cnt_0 >= n)
            s0.push_back(s);
        else
            s1.push_back(s);
    }
    if (s0.size() >= 2)
        cout << mix(s0[0], s0[1], '0') << '\n';
    else
        cout << mix(s1[0], s1[1], '1') << '\n';
}

void s5()
{
    vector<int> v(5);
    read_vector(v);

    sort(all(v));

    int currsum = accumulate(all(v), 0ll);

    int ans = 0;

    for (auto i : v)
    {
        if (currsum >= 35)
        {
            break;
        }
        int addition = (10 - i);
        currsum += addition;
        ans++;
    }

    cout << 100 * ans << endl;
}

void s6()
{
    int n, m, a, b;
    cin >> n >> m >> a >> b;

    if (a > b)
    {
        swap(a, b);
    }

    int i = (m - (b * n)) / (a - b);

    if ((m - (b * n)) % (a - b) == 0 && (i >= 0 && i <= n))
    {
        yes;
    }

    no;
}

void h1()
{
    int x, y, k;
    cin >> x >> y >> k;

    if (k >= min(x, y))
    {
        cout << "Alice\n";
        return;
    }

    cout << "Bob\n";
}

void h2()
{
    int n;
    cin >> n;

    vector<int> v(n);

    vector<int> freq(101, 0);

    fl(i, n)
    {
        int e;
        cin >> e;
        freq[e]++;
    }

    fl(i, 101)
    {
        if (freq[i])
        {
            cout << i << " ";
            freq[i]--;
        }
    }

    fl(i, 101)
    {
        fl(j, freq[i])
        {
            cout << i << " ";
        }
    }

    cout << endl;
}

void h3()
{
    int n, k;
    cin >> n >> k;

    vector<int> freq(k);

    fl(i, n)
    {
        int e;
        cin >> e;
        freq[e % k]++;
    }

    int ans = 0;

    fl(i, k)
    {
        int a = i, b = (k - i) % k;
        int mini = min(freq[a], freq[b]);

        if (freq[a])
        {
            ans += max(1ll, (freq[a] + freq[b]) - 2 * mini);
            freq[a] = 0;
            freq[b] = 0;
        }
    }

    cout << ans << endl;
}

void h4()
{
    int n, k;
    cin >> n >> k;

    if (n % 2)
    {
        cout << n / 2 << " " << n / 2 << " " << 1 << endl;
    }
    else
    {
        if (n % 4 == 0)
        {
            cout << n / 2 << " " << n / 4 << " " << n / 4 << endl;
        }
        else
        {
            cout << (n / 2) - 1 << " " << (n / 2) - 1 << " " << 2 << endl;
        }
    }
}

// https://codeforces.com/contest/1497/problem/C2
void h5()
{
    int n, k;
    cin >> n >> k;

    for (int i = 0; i < k - 3; i++)
    {
        cout << 1 << " ";
    }

    n -= (k - 3);
    k -= 3;

    if (n % 2) // n is odd
    {
        cout << n / 2 << " " << n / 2 << " " << 1 << endl;
    }
    else
    {
        if (n % 4 == 0) // n -> even and multiple of 4
        {
            cout << n / 2 << " " << n / 4 << " " << n / 4 << endl;
        }
        else // even but non multiple of 4
        {
            cout << (n / 2) - 1 << " " << (n / 2) - 1 << " " << 2 << endl;
        }
    }
}

void h6()
{
    int n;
    cin >> n;
    vector<long long> s(n), tag(n), dp(n, 0);
    for (int i = 0; i < n; ++i)
        cin >> tag[i];
    for (int i = 0; i < n; ++i)
        cin >> s[i];
    for (int j = 1; j < n; ++j)
    {
        for (int i = j - 1; i >= 0; --i)
        {
            if (tag[i] == tag[j])
                continue;
            long long dpi = dp[i], dpj = dp[j], p = abs(s[i] - s[j]);
            dp[i] = max(dp[i], dpj + p);
            dp[j] = max(dp[j], dpi + p);
        }
    }
    cout << *max_element(dp.begin(), dp.end()) << '\n';
}

// returns the square-free part of x
int square_free(int x, const vector<int> &primes)
{
    int sf = 1;
    for (int p : primes)
    {
        if ((long long)p * p > x)
            break;
        int cnt = 0;
        while (x % p == 0)
        {
            x /= p;
            cnt ^= 1;
        }
        if (cnt)
            sf *= p;
    }
    if (x > 1)
    {
        sf *= x;
    }
    return sf;
}

// https://codeforces.com/contest/1497/problem/E1

void h7()
{
    int n, k;
    cin >> n >> k;

    vector<int> v(n);
    read_vector(v);

    unordered_set<int> seen;

    int ans = 1;
    unordered_map<int, int> memo_sf;
    memo_sf.reserve(n);

    for (int x : v)
    {
        int sf;
        auto it = memo_sf.find(x);
        if (it != memo_sf.end())
        {
            sf = it->second;
        }
        else
        {
            sf = square_free(x, primes);
            memo_sf[x] = sf;
        }

        if (seen.count(sf))
        {
            ans++;
            seen.clear();
        }
        seen.insert(sf);
    }

    cout << ans << "\n";
}

void h8()
{
    int n;
    cin >> n;

    if (n <= 3)
    {
        cout << n - 1 << endl;
    }
    else if (n % 2 == 0)
    {
        cout << 2 << endl;
    }
    else
    {
        cout << 3 << endl;
    }
}

void h9()
{
    int n, q;
    cin >> n >> q;

    string s;
    cin >> s;

    while (q--)
    {
        int l, r;
        cin >> l >> r;
        --l;
        --r;

        bool found = false;

        for (int i = 0; i < l; i++)
        {
            if (s[i] == s[l])
            {
                found = true;
                break;
            }
        }
        for (int i = r + 1; i < n && !found; i++)
        {
            if (s[i] == s[r])
            {
                found = true;
                break;
            }
        }

        if (found)
            cout << "YES\n";
        else
            cout << "NO\n";
    }
}

// https://codeforces.com/contest/1451/problem/C
void h11()
{
    int n, k;
    cin >> n >> k;

    vector<int> freq1(26, 0), freq2(26, 0);

    string a, b;
    cin >> a >> b;

    for (auto &ch : a)
    {
        freq1[ch - 'a']++;
    }
    for (auto &ch : b)
    {
        freq2[ch - 'a']++;
    }

    fl(i, 26)
    {
        int remFreq = freq2[i] - freq1[i];
        if ((remFreq > 0) || (remFreq % k) != 0)
        {
            no;
        }
        if (i != 25)
        {
            freq1[i] += remFreq;
            freq1[i + 1] += -1ll * remFreq;
        }
    }

    fl(i, 26)
    {
        if (freq1[i] != freq2[i])
        {
            no;
        }
    }

    yes;
}

void h12()
{
    int n;
    cin >> n;
    vector<int> v(n + 1);

    fl(i, n)
    {
        int e;
        cin >> e;
        v[e]++;
    }

    int ans = 0;
    fl(i, n + 1)
    {
        ans = max(ans, v[i]);
    }

    cout << ans << endl;
}

void h13()
{
    // 51
    // 37 + 7 + 7

    int n, d;
    cin >> n >> d;

    fl(i, n)
    {
        int x;
        cin >> x;

        bool flag = false;

        fl(j, 11)
        {
            int remNum = x - (d * (j));
            if (remNum >= 0)
            {
                if (remNum % d == 0)
                {
                    flag = true;
                    break;
                }
                while (remNum)
                {
                    int dig = remNum % 10;
                    remNum /= 10;
                    if (dig == d)
                    {
                        flag = true;
                        break;
                    }
                }
            }
            if (flag)
                break;
        }

        if (flag)
        {
            cout << "YES\n";
        }
        else
        {
            cout << "NO\n";
        }
    }
}

void coderush()
{
    
}

int32_t main()
{
    fast_io;

    // precompute_factorials(maxn);

    // sieve(2e5 + 2);

    int t = 1;
    cin >> t;

    while (t--)
    {
        coderush();
    }

    return 0;
}

// precompute_factorials(maxn);

// mod_pow2_memo();

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

// long long use krna hai
// binary search thoroughly test krna hai
// multi test cases check krna hai
// yes/no me case check krna hai
// early returns me be careful for edge cases
// unordered_map / map me dhyan dena hai
// when to use map
// when to use unordered_map