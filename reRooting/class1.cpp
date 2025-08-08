#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template <typename T>
using ordered_set = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

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
const int MOD_ATCODER = 998244353;
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
    int n;
    cin >> n;

    vector<pair<string, string>> v(n, {"", ""});

    fl(i, ((2 * n) - 2))
    {
        string s;
        cin >> s;

        int len = s.size();

        if (v[len].first == "")
        {
            v[len].first = s;
        }
        else
        {
            v[len].second = s;
        }
    }

    pair<string, string> cand = v[1];

    bool usedfirst = true;
    string prev = "", res = "";

    prev = cand.first;
    // for first candidate

    for (int len = 2; len < n; len++)
    {
        string curr = v[len].first.substr(0, len - 1);
        if (curr == prev)
        {
            prev = v[len].first;
        }
        else
        {
            curr = v[len].second.substr(0, len - 1);
            if (curr == prev)
            {
                prev = v[len].second;
            }
            else
            {
                usedfirst = false;
                break;
            }
        }
    }

    if (usedfirst)
    {
        res = prev + cand.second;
        int p1 = 0, p2 = n - 1;
        bool check = true;
        while (p1 < p2)
        {
            if (res[p1] != res[p2])
            {
                check = false;
                break;
            }
            p1++, p2--;
        }
        if (check)
        {
            ha
        }
    }

    res = "";
    prev = cand.second;

    for (int len = 2; len < n; len++)
    {
        string curr = v[len].first.substr(0, len - 1);
        if (curr == prev)
        {
            prev = v[len].first;
        }
        else
        {
            prev = v[len].second;
        }
    }

    res = prev + cand.first;

    int p1 = 0, p2 = n - 1;

    while (p1 < p2)
    {
        if (res[p1] != res[p2])
        {
            na
        }
        p1++, p2--;
    }

    ha
}

void sol2()
{
    int n;
    cin >> n;

    vector<pair<string, string>> v(n, {"", ""});

    fl(i, ((2 * n) - 2))
    {
        string s;
        cin >> s;

        int len = s.size();

        if (v[len].first == "")
        {
            v[len].first = s;
        }
        else
        {
            v[len].second = s;
        }
    }

    string s1 = v[n - 1].first, s2 = v[n - 1].second;

    reverse(all(s2));

    if (s1 == s2)
    {
        ha
    }

    na
}

// abcd dcba => abcd
// abc cba

void sol3()
{
    int n;
    cin >> n;

    vector<ll> a(n);
    input_vector(a);

    for (int i = 1; i < n; i++)
    {
        if (a[i] % a[i - 1] == 0)
        {
            if (a[i - 1] == 1)
            {
                a[i - 1]++;
                // fix previous part
                for (int j = i - 1; j > 0; j--)
                {
                    if (a[j] % a[j - 1] == 0)
                    {
                        a[j]++;
                    }
                }
            }
            if (a[i] % a[i - 1] == 0)
            {
                a[i]++;
            }
        }
    }

    print_vector(a);
}

void sol4()
{
    int n;
    cin >> n;
    vector<ll> a(n);
    input_vector(a);

    ll curr = 0;
    for (int i = 0; i < n; i++)
    {
        int L = i + 1;
        // Try to extend the subsequence from length curr to curr+1
        if (curr < L && a[L - curr - 1] >= curr + 1)
        {
            curr++;
        }
        cout << max(curr, 1LL) << " ";
    }
    cout << endl;
}

vector<int> isPrime;

void generatePrimes(int n)
{
    isPrime.assign(n + 10, true);
    isPrime[0] = isPrime[1] = false;

    for (int i = 2; i * i <= n; ++i)
    {
        if (isPrime[i])
        {
            for (int j = i * i; j <= n; j += i)
            {
                isPrime[j] = false;
            }
        }
    }
}

// checks if n is prime
bool is_prime(ll n)
{
    if (n == 1)
    {
        return false;
    }
    for (ll i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            return false;
        }
    }
    return true;
}

ll solveDP(const vector<int> &uniqprimes, const vector<int> &counts, int n)
{
    int k = uniqprimes.size();
    vector<ll> dp(n + 1, 0);
    dp[0] = 1;
    for (int i = 0; i < k; i++)
    {
        int cnt = counts[i];
        vector<ll> newdp(n + 1, 0);
        for (int j = 0; j <= n; j++)
        {
            newdp[j] = mod_add(newdp[j], mod_mul(dp[j], inv_factorial[cnt], MOD_ATCODER), MOD_ATCODER);

            if (j < n)
            {
                newdp[j + 1] = mod_add(newdp[j + 1], mod_mul(dp[j], inv_factorial[cnt - 1], MOD_ATCODER), MOD_ATCODER);
            }
        }
        dp = move(newdp);
    }

    return mod_mul(factorial[n], dp[n], MOD_ATCODER);
}

void sol5()
{
    int n;
    cin >> n;

    vector<ll> v(2 * n);
    unordered_map<int, int> freq;
    unordered_set<int> primes;

    for (int i = 0; i < 2 * n; i++)
    {
        int a;
        cin >> a;
        v[i] = a;
        freq[a]++;
        if (is_prime(a))
        {
            primes.insert(a);
        }
    }

    int numPrimes = (int)primes.size();
    if (numPrimes < n)
    {
        if (v[0] == 1 && v[1] == 1)
        {
            cout << 1 << endl;
            return;
        }
        cout << 0 << endl;
        return;
    }

    vector<pair<int, int>> prime_counts;
    vector<int> uniqprimes;
    vector<int> counts;

    for (int p : primes)
    {
        prime_counts.push_back({p, freq[p]});
    }

    ll factb = 1ll;

    for (auto i : freq)
    {
        if (!primes.count(i.first))
        {
            factb = mod_mul(factb, inv_factorial[i.second], MOD_ATCODER);
        }
    }

    sort(prime_counts.begin(), prime_counts.end());

    for (auto &pr : prime_counts)
    {
        uniqprimes.push_back(pr.first);
        counts.push_back(pr.second);
    }

    ll ans = solveDP(uniqprimes, counts, n);

    ans = mod_mul(ans, factb);

    cout << ans << endl;
}

void sol6()
{
    ordered_set<ll> st;
    int q;
    cin >> q;

    while (q--)
    {
        int type;
        cin >> type;

        if (type == 1)
        { // Insert x into set
            ll x;
            cin >> x;
            st.insert(x);
        }
        else if (type == 2)
        { // k-th largest element ≤ x
            ll x, k;
            cin >> x >> k;

            auto it = st.upper_bound(x); // First element > x
            if (it == st.begin())
            {
                cout << -1 << endl;
                continue;
            }

            // Move to the last element ≤ x
            --it;

            // Move k-1 steps back
            while (k > 1 && it != st.begin())
            {
                --it;
                --k;
            }

            if (k > 1)
            {
                cout << -1 << endl;
            }
            else
            {
                cout << *it << endl;
            }
        }
        else if (type == 3)
        { // k-th smallest element ≥ x
            ll x, k;
            cin >> x >> k;

            auto it = st.lower_bound(x); // First element ≥ x
            if (it == st.end())
            {
                cout << -1 << endl;
                continue;
            }

            // Move k-1 steps forward
            while (k > 1 && next(it) != st.end())
            {
                ++it;
                --k;
            }

            if (k > 1)
            {
                cout << -1 << endl;
            }
            else
            {
                cout << *it << endl;
            }
        }
    }
}

// https://atcoder.jp/contests/abc241/tasks/abc241_e
void sol7()
{
    ll n, k;
    cin >> n >> k;

    unordered_set<ll> st;
    vector<ll> a(n);
    input_vector(a);

    ll prev = 0, curr = 0;
    st.insert(curr);

    vector<pll> v;
    v.push_back({curr, 0ll});

    ll startValue = -1;

    while (true)
    {
        curr = curr + a[(curr % n)];

        if (st.count(curr % n))
        { // Cycle detected
            startValue = curr % n;
            break;
        }

        st.insert(curr % n);
        v.push_back({curr, curr % n});
        prev = curr;
    }

    // cout << startValue << endl;

    ll sumBeforeCycle = 0, sumInCycle = 0;

    bool cycleStart = false;
    ll reqTerms = k + 1, cycleSize = 0;
    vector<ll> cycleElems;

    for (auto i : v)
    {
        if (i.second == startValue || cycleStart)
        {
            cycleStart = true;
            sumInCycle += i.first;
            cycleSize++;
            cycleElems.push_back(i.first);
        }
        else
        {
            sumBeforeCycle += i.first;
            reqTerms--;
        }
    }

    // cout << sumBeforeCycle << " " << sumInCycle << endl;

    // for (auto e : v)
    // {
    //     cout << e.first << " " << e.second << endl;
    // }

    ll cycleRepeats = reqTerms / cycleSize;
    ll sum = sumBeforeCycle + (cycleRepeats * sumInCycle);

    reqTerms %= cycleSize;

    cout << reqTerms << endl;

    sum += v[reqTerms % n].first;

    cout << sum << endl;
}

int main()
{
    fast_io;

    // precompute_factorials(1e6 + 2, MOD_ATCODER);

    int t = 1;

    while (t--)
    {
        sol7();
    }

    return 0;
}