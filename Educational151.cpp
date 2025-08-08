
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

vector<int> sieve(int n)
{
    primes.clear();

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

#define yes \
    cout << "YES\n";

#define no \
    cout << "NO\n";

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

void r1()
{
    string s;
    cin >> s;

    for (auto i : primes)
    {
        if (i > 10)
        {
            // check if i is present in s
            string curr = to_string(i);
            int p1 = 0, p2 = 0;
            while (p1 < s.size() and p2 < curr.size())
            {
                if (s[p1] == curr[p2])
                {
                    p2++;
                }
                p1++;
            }
            bool check = (p2 == curr.size());

            if (check)
            {
                cout << curr << endl;
                return;
            }
        }
    }
}

void r2()
{
    string a, b;
    cin >> a >> b;
    bool ok = false;

    for (int i = 0; i + 1 < a.size(); ++i)
    {
        if (a[i] == b[i] && a[i] == '0' && a[i + 1] == b[i + 1] && a[i + 1] == '1')
        {
            ok = true;
        }
    }

    if (ok)
        yes else no;
}

void r3()
{
    int n;
    cin >> n;

    vector<int> v(n);
    read_vector(v);

    int twos = count(all(v), 2);

    if ((twos % 2) == 0)
    {
        int curr = 0;
        fl(i, n - 1)
        {
            if (v[i] == 2)
            {
                curr++;
            }

            if (curr == (twos / 2))
            {
                cout << i + 1 << endl;
                return;
            }
        }
    }
    else
    {
        cout << -1 << endl;
    }
}

void r4()
{
    int n;
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        int rem = n - i;
        int sum1 = 0;

        while (rem > 0)
        {
            sum1 += (rem % 10);
            rem /= 10;
        }

        int sum2 = 0;
        int t = i;
        while (t > 0)
        {
            sum2 += (t % 10);
            t /= 10;
        }

        if (abs(sum1 - sum2) <= 1)
        {
            cout << i << " " << n - i << endl;
            return;
        }
    }
}

void r5()
{
    int x, y, a;
    cin >> x >> y >> a;
    a++;

    int m = (a) / (x + y);

    if ((a % (x + y)) == 0)
    {
        m--;
    }

    a = a - (m * (x + y));

    if (a <= x)
    {
        cout << "NO\n";
    }
    else
    {
        cout << "YES\n";
    }
}

void r6()
{
    int n, m;
    cin >> n >> m;

    vector<string> grid(n);
    fl(i, n)
    {
        cin >> grid[i];
    }

    vector<vector<bool>> marked(n, vector<bool>(m, 0));

    fl(i, n)
    {
        fl(j, m)
        {
            if (grid[i][j] == '0')
            {
                break;
            }
            marked[i][j] = 1;
        }
    }

    fl(i, m)
    {
        fl(j, n)
        {
            if (grid[j][i] == '0')
            {
                break;
            }
            marked[j][i] = 1;
        }
    }

    fl(i, n)
    {
        fl(j, m)
        {
            if (grid[i][j] == '1' and !marked[i][j])
            {
                cout << "NO\n";
                return;
            }
        }
    }

    cout << "YES\n";
}

list<pll> genP()
{
    int sz = 0;
    list<pll> p;
    const int REQ_SIZE = 50000;

    for (int i = 0;; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            sz++;
            p.push_back({j, i - j});
            if (sz == REQ_SIZE)
            {
                break;
            }
        }
        if (sz == REQ_SIZE)
        {
            break;
        }
    }

    return p;
}

list<pll> temp;

void r7()
{
    list<pll> v(temp.begin(), temp.end());

    map<pll, int> freq;

    int n;
    cin >> n;

    fl(i, n)
    {
        int t;
        cin >> t;

        if (t == 0)
        {
            auto curr = v.front();
            cout << (curr.first * 3) + 1 << " " << (curr.second * 3) + 1 << endl;
            v.pop_front();
            freq[curr]++;
        }
        else
        {
            if (freq.empty())
            {
                auto curr = v.front();
                cout << (curr.first * 3) + 1 << " " << (curr.second * 3) + 1 << endl;
                v.pop_front();
                freq[curr]++;
                continue;
            }

            auto curr = freq.begin()->first;
            int x = 3 * curr.first, y = 3 * curr.second;

            if (freq[curr] == 1)
            {
                x++, y += 2;
            }
            else if (freq[curr] == 2)
            {
                x += 2, y++;
            }
            else
            {
                x += 2, y += 2;
            }

            cout << x << " " << y << endl;
            freq[curr]++;

            if (freq[curr] == 4)
            {
                freq.erase(curr);
            }
        }
    }
}

void r8()
{
    int n, k, x;
    cin >> n >> k >> x;

    if (n % 2 == 0)
    {
        if (k == x and x == 1)
        {
            cout << "NO\n";
        }
        else
        {
            cout << "YES\n";
            if (x == 2)
            {
                cout << n << endl;
                for (int i = 1; i <= n; i++)
                {
                    cout << 1 << " ";
                }
                cout << endl;
            }
            else
            {
                cout << n / 2 << endl;
                for (int i = 1; i <= n / 2; i++)
                {
                    cout << 2 << " ";
                }
                cout << endl;
            }
        }
    }
    else
    {
        if (x == 1)
        {
            if (k >= 3)
            {
                cout << "YES\n";
                n -= 3;
                cout << (n / 2) + 1 << endl;

                cout << 3 << " ";
                for (int i = 1; i <= n / 2; i++)
                {
                    cout << 2 << " ";
                }
                cout << endl;
            }
            else
            {

                cout << "NO\n";
            }
        }
        else
        {
            cout << "YES\n";
            cout << n << endl;
            for (int i = 1; i <= n; i++)
            {
                cout << 1 << " ";
            }
            cout << endl;
        }
    }
}

void r9()
{
    int x1, x2, x3, y1, y2, y3;
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;

    int dx1 = x1 - x2, dy1 = y1 - y2;
    int dx2 = x1 - x3, dy2 = y1 - y3;

    bool sx1 = dx1 >= 0, sx2 = dx2 >= 0;
    bool sy1 = dy1 >= 0, sy2 = dy2 >= 0;

    int ans = 0;

    if (sx1 == sx2)
    {
        ans += min(abs(dx1), abs(dx2));
    }

    if (sy1 == sy2)
    {
        ans += min(abs(dy1), abs(dy2));
    }

    cout << ans + 1 << endl;
}

void r10()
{
    int n;
    cin >> n;
    ll delta = 0, ans = 0;
    ll sum = 0, mx = 0;
    for (int i = 0; i < n; ++i)
    {
        ll x;
        cin >> x;
        sum += x;
        mx = max(mx, sum);
        if (sum - mx < delta)
        {
            delta = sum - mx;
            ans = mx;
        }
    }
    cout << ans << '\n';
}

void r11()
{
    int n, m;
    cin >> n;

    vector<int> v(n);
    read_vector(v);

    unordered_set<ll> st(all(v));

    cout << (int)st.size() << endl;
}

void r12()
{
    int n;
    cin >> n;

    string s;
    cin >> s;

    vector<pair<int, int>> vp;

    char curr;
    int cnt, i = 0;

    while (i < n)
    {
        curr = s[i++];
        cnt = 1;
        while (i < n and s[i] == curr)
        {
            i++;
            cnt++;
        }
        vp.push_back({curr - '0', cnt});
    }

    int m = vp.size();

    // merge to get lastest grp of 0s or lastest grp of 1s

    int ans = n + m - 1 + (vp[0].first == 1);
    cnt = ans;

    for (int i = 0; i < m - 1; i++)
    {
        // swap (vp[i], vp[i+1])
        if (i == 0)
        {
            if (vp[0].first == 0)
            {
                ans = min(ans, cnt);
            }
            else
            {
                ans = min(ans, cnt - 1);
            }
        }
        else
        {
            ans = min(ans, cnt - 1 - (i != (m - 2)));
        }
    }

    cout << ans << endl;
}

void r13()
{
    int n;
    cin >> n;

    vector<int> v(n);
    read_vector(v);

    bool allequal = true;
    int non1;

    for (int i = 0; i < n; i++)
    {
        if (v[i] != v[0])
        {
            allequal = false;
        }
        if (v[i] != 1)
        {
            non1 = i;
        }
    }

    if (allequal)
    {
        cout << "No\n";
        return;
    }

    cout << "Yes\n";

    for (int i = 0; i < n; i++)
    {
        if (non1 == i)
        {
            cout << 1 << " ";
        }
        else
        {
            cout << 2 << " ";
        }
    }

    cout << endl;
}

void r14()
{
    int n, k;
    cin >> n >> k;

    int half = n / 2;

    if (k < half)
    {
        cout << -1 << endl;
        return;
    }
    else
    {
        vector<char> S(n);
        vector<char> T(n);
        for (int i = 0; i < n; i++)
        {
            if (i % 2 == 0)
            {
                S[i] = 'A';
                T[i] = 'B';
            }
            else
            {
                S[i] = 'C';
                T[i] = 'C';
            }
        }
        for (int i = 0; i < (k - n / 2); i++)
        {
            S[i * 2] = 'B';
        }
        for (char ch : S)
            cout << ch;
        cout << endl;
        for (char ch : T)
            cout << ch;
        cout << endl;
    }
}

const int mod = 998244353;

void s1()
{
    int n;
    cin >> n;
    vector<int> v(n);
    read_vector(v);

    // -1 -> missing element, it can take value between [1, k]

    
}

int32_t main()
{
    fast_io;

    int t = 1;
    cin >> t;

    while (t--)
        s1();

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