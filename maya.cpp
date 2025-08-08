#include <bits/stdc++.h>
using namespace std;

// Fast I/O
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

void solve()
{

    ll n;
    cin >> n;

    vector<ll> v(n);

    ll ones = 0, twos = 0;

    fl(i, n)
    {
        cin >> v[i];
        if (v[i] == 1)
        {
            ones++;
        }
        else
        {
            twos++;
        }
    }

    ll sum = ones + 2 * 1ll * twos;

    if (sum % 2 != 0)
    {
        na
    }

    if ((twos % 2) == 0)
    {
        if ((ones % 2) == 0)
        {
            ha
        }
        else
        {
            na
        }
    }

    else
    {
        if ((ones % 2) == 0 and ones != 0)
        {
            ha
        }
        else
        {
            na
        }
    }
}

void solve2()
{

    int n;
    cin >> n;

    string s;
    cin >> s;

    ll up = 0, down = 0;

    for (auto i : s)
    {
        if (i == '_')
        {
            down++;
        }
        else
        {
            up++;
        }
    }

    ll v1 = up / 2, v2 = up / 2;

    if (up % 2 != 0)
    {
        v1++;
    }

    ll ans = v1 * 1ll * v2 * 1ll * down;

    cout << ans << endl;
}

void sol3()
{
    ll n, x;
    cin >> n >> x;

    ll orval = 0;

    unordered_set<ll> st;
    ll currval = 0;

    for (int i = 0; i < n - 1; i++)
    {
        if ((i | x) != x)
        {
            cout << "0 ";
        }
        else
        {
            st.insert(i);
            orval |= i;
            cout << i << " ";
            currval = i + 1;
        }
    }

    ll t = 0;

    for (int i = 0; i < 32; i++)
    {
        if (((orval >> i) & 1) == 0 && ((x >> i) & 1) == 1)
        {
            t |= (1LL << i);
        }
    }

    if (st.count(t))
    {
        if ((currval | x) != x)
        {
            t = 0;
        }
        else
        {
            t = currval;
        }
    }

    cout << t << endl;
}

void sol4()
{
    int n;
    cin >> n;

    vector<ll> v(n);
    fl(i, n)
    {
        cin >> v[i];
    }

    int l = 0, r = 0;

    for (int i = 0; i < n; i++)
    {
        bool check = false;
        for (int j = i + 1; j < n; j++)
        {
            if (v[j] < v[i])
            {
                check = true;
                break;
            }
        }
        if (check == true)
        {
            l = i + 1;
            break;
        }
    }

    if (l != 0)
    {
        r = n;
    }
    else
    {
        l = 1;
        r = 1;
    }

    cout << l << " " << r << endl;
}

bool isPoss(ll n, ll k, string &t, vector<ll> &v, ll mid)
{
    ll ops = 0;
    ll i = 0;
    while (i < n)
    {
        if (t[i] == 'B' && v[i] > mid)
        {
            ops++;
            while (i < n && !(t[i] == 'R' && v[i] > mid))
                i++;
        }
        else
        {
            i++;
        }
    }
    return ops <= k;
}

void sol6()
{
    ll n, k;
    cin >> n >> k;

    string s;
    cin >> s;

    vector<ll> v(n);

    fl(i, n)
    {
        cin >> v[i];
    }

    ll mx = *max_element(all(v));

    ll low = 0, high = INT_MAX, mid, ans = mx;

    while (low <= high)
    {
        mid = (low + high) / 2;
        if (isPoss(n, k, s, v, mid))
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

const ll M = 998244353;

void sol7()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> par(n + 1, 0);
    vector<int> par_input(n - 1);

    for (int i = 0; i < n - 1; i++)
    {
        cin >> par_input[i];
    }

    vector<vector<int>> children(n + 1);
    for (int i = 2; i <= n; i++)
    {
        int p = par_input[i - 2];
        children[p].push_back(i);
    }

    vector<int> depth(n + 1, -1);
    depth[1] = 0;
    queue<int> q;
    q.push(1);

    int max_de = 0;

    while (!q.empty())
    {
        int v = q.front();
        q.pop();
        max_de = max(max_de, depth[v]);
        for (int nxt : children[v])
        {
            depth[nxt] = depth[v] + 1;
            q.push(nxt);
        }
    }

    vector<vector<int>> levels(max_de + 1);

    for (int v = 1; v <= n; v++)
    {
        levels[depth[v]].push_back(v);
    }

    vector<ll> dp(n + 1, 0);
    vector<ll> S(max_de + 2, 0);

    for (int d = max_de; d >= 0; d--)
    {
        for (int v : levels[d])
        {
            if (d == max_de)
            {
                dp[v] = 1;
            }
            else
            {
                ll total_next = S[d + 1];
                if (v == 1)
                {
                    dp[v] = (1 + total_next) % M;
                }
                else
                {
                    ll sum_children = 0;
                    for (int c : children[v])
                    {
                        sum_children = (sum_children + dp[c]) % M;
                    }
                    dp[v] = (1 + ((total_next - sum_children) % M + M) % M) % M;
                }
            }
        }

        ll sum_level = 0;

        for (int v : levels[d])
        {
            sum_level = (sum_level + dp[v]) % M;
        }

        S[d] = sum_level;
    }

    ll ans = dp[1] % M;

    cout << ans << "\n";
}

int main()
{
    fast_io;

    int t;
    cin >> t;
    while (t--)
    {
        sol7();
    }
    return 0;
}
