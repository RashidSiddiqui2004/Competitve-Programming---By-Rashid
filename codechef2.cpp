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

template <typename T>
void input_vector(vector<T> &v)
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

// const int maxn = 1e6 + 2;
// int spf[maxn];

void sol1()
{
    int x, y;
    cin >> x >> y;

    int ans = x + 10 * y;
    cout << ans << endl;
}

void sol2()
{
    int n;
    cin >> n;

    unordered_map<ll, ll> mp;

    fl(i, n)
    {
        ll e;
        cin >> e;
        mp[e]++;
    }

    for (auto i : mp)
    {
        if (i.second > 1)
        {
            cout << 1 << endl;
            cout << i.first << "\n";
            return;
        }
    }
    cout << -1 << "\n";
    return;
}

void r1()
{
    ll n, m;
    cin >> n >> m;

    vector<ll> a(n), b(m);
    input_vector(a);
    input_vector(b);

    vector<ll> rotation = b;

    for (int i = 0; i < m; i++)
    {
        vector<ll> rotated;
        for (int j = 0; j < m; j++)
        {
            rotated.push_back(b[(i + j) % m]);
        }
        if (rotated < rotation)
        {
            rotation = rotated;
        }
    }

    for (int i = 0; i + m <= n; i++)
    {
        vector<ll> current_subarray(a.begin() + i, a.begin() + i + m);

        if (current_subarray > rotation)
        {
            copy(rotation.begin(), rotation.end(), a.begin() + i);
        }
    }

    print_vector(a);
}

vector<ll> helper(vector<ll> &b)
{
    int m = b.size();
    int minIndex = min_element(b.begin(), b.end()) - b.begin();
    vector<ll> temp(m);

    for (int i = 0; i < m; i++)
    {
        temp[i] = b[(minIndex + i) % m];
    }

    return temp;
}

void r2()
{
    ll n, m;
    cin >> n >> m;

    vector<ll> a(n), b(m);
    for (ll &x : a)
        cin >> x;
    for (ll &x : b)
        cin >> x;

    vector<ll> smallestRotation = helper(b);

    for (int i = 0; i <= n - m;)
    {
        bool shouldReplace = false;

        for (int j = 0; j < m; j++)
        {
            if (a[i + j] > smallestRotation[j])
            {
                shouldReplace = true;
                break;
            }
            else if (a[i + j] < smallestRotation[j])
            {
                break;
            }
        }

        if (shouldReplace)
        {
            while (i + m <= n)
            {
                a[i] = min(a[i], smallestRotation[0]);
                i++;
            }
            int j = 1;
            while (i < n)
            {
                a[i++] = smallestRotation[j++];
            }
        }
        else
        {
            i++;
        }
    }

    for (ll x : a)
        cout << x << " ";
    cout << "\n";
}

void r3()
{
    int n;
    cin >> n;

    vector<ll> v(n);
    for (auto &x : v)
        cin >> x;

    unordered_map<ll, ll> freq;
    for (ll x : v)
    {
        freq[x]++;
    }

    ll nonzeroOdd = 0;
    ll totalZeros = 0;

    if (freq.find(0) != freq.end())
        totalZeros += freq[0];

    for (auto &p : freq)
    {
        ll value = p.first;
        ll count = p.second;
        if (value == 0)
            continue;
        if (count % 2 == 1)
            nonzeroOdd++;
        totalZeros += (count / 2);
    }

    ll ans = nonzeroOdd + (totalZeros > 0 ? 1 : 0);

    ans = max(ans, 1LL);

    cout << ans << endl;
}

int n;
vector<ll> v;

ll dp_fwd[55][1100];
bool vis_fwd[55][1100];

ll fwd(int i, ll cur)
{
    if (i == n)
        return cur;
    vis_fwd[i][cur] = true;
    ll opt1 = fwd(i + 1, max(0LL, cur - v[i]));
    ll opt2 = fwd(i + 1, max(0LL, v[i] - cur));
    dp_fwd[i][cur] = max(opt1, opt2);
    return dp_fwd[i][cur];
}

ll df()
{
    memset(vis_fwd, 0, sizeof(vis_fwd));
    return fwd(1, v[0]);
}

vector<ll> rev;
ll dp_bwd[55][1100];
bool vis_bwd[55][1100];

ll bwd(int i, ll cur)
{
    if (i == n)
        return cur;
    vis_bwd[i][cur] = true;
    ll opt1 = bwd(i + 1, max(0LL, cur - rev[i]));
    ll opt2 = bwd(i + 1, max(0LL, rev[i] - cur));
    dp_bwd[i][cur] = max(opt1, opt2);
    return dp_bwd[i][cur];
}

ll df2()
{
    rev = v;
    reverse(rev.begin(), rev.end());
    memset(vis_bwd, 0, sizeof(vis_bwd));
    return bwd(1, rev[0]);
}

int main()
{
    fast_io;

    int t = 1;
    cin >> t;

    while (t--)
    {
        cin >> n;
        v.resize(n);
        for (int i = 0; i < n; i++)
        {
            cin >> v[i];
        }
        ll ans = max(df(), df2());
        cout << ans << "\n";
    }

    return 0;
}

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
