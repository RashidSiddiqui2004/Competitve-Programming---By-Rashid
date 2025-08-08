
#include <bits/stdc++.h>

#include <bitset>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

using ll = long long;
using lld = long double;
using ull = unsigned long long;

// Constants
const ll INF = LONG_LONG_MAX;
const ll mod = 1e9 + 7;
const ll new_mod = 998244353;

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
#define printn cout << endl;
#define printarr(v)       \
    for (auto x : v)      \
        cout << x << ' '; \
    cout << endl;
#define setBits(x) __builtin_popcountll(x)
#define getunique(v)                      \
    {                                     \
        sort(all(v));                     \
        v.erase(unique(all(v)), v.end()); \
    }

template <class T>
void print(const T &t)
{
    cout << t << endl;
}

#define inputvector(v) \
    for (auto &x : v)  \
    {                  \
        cin >> x;      \
    }

const int N = 1e7 + 1;
vector<bool> isPrime;
vector<ll> sprime;

ll multiply(ll a, ll b, ll m = mod)
{
    return (a % m) * (b % m) % m;
}

ll add(ll a, ll b, ll m = mod)
{
    return (a % m) + (b % m) % m;
}

ll subtract(ll a, ll b, ll m = mod)
{
    return ((a % m) - (b % m) + m) % m;
}

// Function to calculate (a^b) % mod
long long power(long long a, long long b, long long mod)
{
    long long result = 1;
    while (b > 0)
    {
        if (b % 2 == 1)
        {
            result = (result * a) % mod;
        }
        a = (a * a) % mod;
        b /= 2;
    }
    return result % mod;
}

using ll = long long;

ll mul_inverse(ll a)
{
    ll res = 1;
    ll b = mod - 2;
    ll m = mod;
    while (b > 0)
    {
        if (b & 1)
        {
            res = (res * 1ll * a) % m;
        }
        a = (a * 1ll * a) % m;
        b >>= 1;
    }
    return res;
}

void generatePrimes()
{
    isPrime.assign(N, true);
    sprime.assign(N, 1);
    for (int i = 2; i * i < N; i++)
    {
        if (isPrime[i])
        {
            for (int j = i * i; j < N; j += i)
            {
                isPrime[j] = false;
                if (sprime[j] == 1)
                {
                    sprime[j] = i;
                }
            }
        }
    }
}

void getFactorization(ll n, unordered_map<ll, ll> &mp)
{
    while (n > 0)
    {
        if (sprime[n] == 1)
        {
            mp[n]++;
            break;
        }
        mp[sprime[n]]++;
        n /= sprime[n];
    }
    return;
}

// @uncomment this for factorial questions
const int factSize = 100000 + 5;
ll fact[factSize];
ll invFact[factSize];

// Precompute factorials and modular inverses
void precomputeFactorials(int n, long long mod)
{
    fact[0] = 1;
    for (int i = 1; i <= n; ++i)
    {
        fact[i] = (fact[i - 1] * i) % mod;
    }
    invFact[n] = power(fact[n], mod - 2, mod); // Modular inverse using Fermat's theorem
    for (int i = n - 1; i >= 0; --i)
    {
        invFact[i] = (invFact[i + 1] * (i + 1)) % mod;
    }
}

vector<int> primes;

void generatePrimes(int n)
{
    vector<bool> isPrime(n + 1, true); // Initialize all numbers as prime
    isPrime[0] = isPrime[1] = false;   // 0 and 1 are not prime

    for (int i = 2; i * i <= n; ++i)
    {
        if (isPrime[i])
        {
            for (int j = i * i; j <= n; j += i)
            {
                isPrime[j] = false; // Mark multiples of i as non-prime
            }
        }
    }

    // Collect all prime numbers into a vector

    for (int i = 2; i <= n; ++i)
    {
        if (isPrime[i])
        {
            primes.push_back(i);
        }
    }
}

vector<int> palindromicNos;

void precomputePalindromes()
{
    for (int i = 0; i <= 32768; i++)
    {
        string curr = to_string(i);
        string rev = curr;
        reverse(all(curr));
        if (curr == rev)
        {
            palindromicNos.push_back(i);
        }
    }
}

void sol1()
{
    int n;
    cin >> n;
    int zeros = 0;
    vector<int> freq(n + 1, 0);

    fl(i, n)
    {
        int e;
        cin >> e;
        if (e == 0)
            zeros++;
        else
            freq[e]++;
    }

    int maxfr = *max_element(all(freq));
    int pos = 0;
    ll res = 0;
    bool used = false;

    fl(i, n + 1)
    {
        if (i == 0)
            continue;
        if (freq[i] == maxfr)
        {
            if (!used)
            {
                freq[i] += zeros;
                res += (freq[i] * (freq[i] - 1)) / 2;
                used = true;
            }
            else
            {
                res += (freq[i] * (freq[i] - 1)) / 2;
            }
        }
        else
        {
            res += (freq[i] * (freq[i] - 1)) / 2;
        }
    }

    if (!used)
    {
        res += (zeros * (zeros - 1)) / 2;
    }

    cout << res << endl;
}

// https://www.codechef.com/problems/MAXEQUAL

void sl2()
{
    int n;
    cin >> n;

    ll zeros = n;
    vector<ll> freq(n + 1, 0);

    ll maxfreq = 0;
    ll kiskimaxfreq;

    ll residue = 0ll;

    fl(i, n)
    {
        ll x, y;
        cin >> x >> y;

        ll curr = 0;

        residue -= (freq[y] * (freq[y] - 1)) / 2;
        freq[y]++;
        residue += (freq[y] * (freq[y] - 1)) / 2;

        maxfreq = max(maxfreq, freq[y]);

        if (maxfreq == freq[y])
        {
            kiskimaxfreq = y;
        }

        zeros--;

        curr += (((maxfreq + zeros) * (maxfreq + zeros - 1)) / 2) + residue;
        curr -= (freq[kiskimaxfreq] * (freq[kiskimaxfreq] - 1)) / 2;

        cout << curr << " ";
    }

    cout << endl;
}

void sol3()
{
    int n, k;
    cin >> n >> k;

    string a, b;
    cin >> a >> b;

    vector<pair<int, char>> ans;

    for (int i = n - 1; i >= 0; i--)
    {
        if (a[i] == b[i])
            continue;
        else
        {
            int j = i - 1;

            while (j >= 0 and (b[j] == b[i]))
            {
                j--;
            }

            j++;

            int currlen = i - j + 1;
            int remlen = k - currlen;
            if ((i + remlen) >= n)
            {
                cout << -1 << endl;
                return;
            }

            for (int p = i + 1; p <= (i + remlen); p++)
            {
                if (b[p] != b[i])
                {
                    cout << -1 << endl;
                    return;
                }
            }

            ans.push_back({j + 1, b[i]});
            i = j;
        }
    }

    cout << ans.size() << endl;
    for (auto i : ans)
    {
        cout << i.first << " " << i.second << endl;
    }
}

void solve()
{
    int n, k;
    cin >> n >> k;
    string f, s;
    cin >> f >> s;
    vector<int> prev(n);
    for (int i = 0; i < n; i++)
    {
        prev[i] = i;
        if (i > 0 and s[i] == s[i - 1])
            prev[i] = prev[i - 1];
    }

    vector<pair<int, char>> changes;
    int j = n;
    int pos_ = n;
    char c_;

    for (int i = 0; i < n; i++)
    {
        j--;
        if (j - k + 1 < 0)
        {
            j++;
            break;
        }
        if (j >= pos_)
            f[j] = c_;
        if (s[j] == f[j])
            continue;
        f[j] = s[j];
        pos_ = j - k + 1, c_ = f[j];
        changes.push_back({pos_, c_});
    }

    while (--j >= pos_)
        f[j] = c_;

    bool change[n] = {false};
    char c;
    int pos = -1;
    for (int i = 0; i < n; i++)
    {
        char &curr = f[i];
        if (pos >= i)
            curr = c;
        if (curr == s[i])
            continue;
        int p = prev[i];
        p = max(p, i - k + 1);
        if (p + k - 1 >= n)
            continue;
        if (!change[p])
            changes.push_back({p, s[i]});
        change[p] = true;
        pos = p + k - 1, c = s[i];
        f[i] = s[i];
    }

    if (f != s)
        cout << -1 << endl;
    else
    {
        cout << changes.size() << endl;
        for (auto t : changes)
            cout << t.first + 1 << " " << t.second << endl;
    }
}

void sol4()
{
    int n;
    cin >> n;
    vector<int> v(n);
    fl(i, n)
    {
        cin >> v[i];
    }

    ll res = 0ll;

    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            int zeros = 0;
            for (int p = i; p <= j; p++)
            {
                if (v[p] == 0)
                    zeros++;
            }
            res += (j - i + 1) + zeros;
        }
    }

    cout << res << endl;
}

// https://codeforces.com/contest/1637/problem/C
void sol5()
{
    int n;
    cin >> n;
    vector<ll> v(n);

    ll odds = 0, evens = 0;
    bool numGreaterThan1 = false;
    fl(i, n)
    {
        cin >> v[i];
        if ((i == 0) || (i == n - 1))
        {
            continue;
        }
        if (v[i] > 1)
        {
            numGreaterThan1 = true;
        }
        if (v[i] % 2 == 0)
        {
            evens++;
        }
        else
        {
            odds++;
        }
    }

    v[0] = 0;
    v[n - 1] = 0;

    if (odds == 0)
    {
        ll sum = accumulate(all(v), 0ll);
        cout << (ll)(sum / 2) << endl;
    }
    else
    {
        if (evens || (numGreaterThan1 and odds > 1))
        {
            ll cost = 0ll;

            for (int i = 1; i < n - 1; i++)
            {
                cost += (1ll * v[i] + 1) / 2;
            }

            cout << cost << endl;
        }
        else
        {
            cout << -1 << endl;
        }
    }
}

void sol6()
{
    int n;
    cin >> n;

    vector<int> a(n), b(n);
    ll constantTerm = 0;

    fl(i, n)
    {
        cin >> a[i];
        constantTerm += (a[i] * a[i]);
    }

    fl(i, n)
    {
        cin >> b[i];
        constantTerm += (b[i] * b[i]);
    }

    constantTerm = (n - 2) * 1ll * (constantTerm);

    // approach 1 using dp[i,w]

    // vector<vector<bool>> dp(n, vector<bool>(10001, 0));

    // dp[0][a[0]] = 1;
    // dp[0][b[0]] = 1;

    // for (int i = 1; i < n; i++)
    // {
    //     for (int j = 0; j <= 10000; j++)
    //     {
    //         dp[i][j] = ((j - a[i - 1]) >= 0 ? dp[i - 1][j - a[i - 1]] : 0) ||
    //                    ((j - b[i - 1]) >= 0
    //                         ? dp[i - 1][j - b[i - 1]]
    //                         : 0);
    //     }
    // }

    // ll total = accumulate(all(a), 0ll) + accumulate(all(b), 0ll);
    // ll res = LLONG_MAX;

    // for (int i = 0; i < 10001; i++)
    // {
    //     if (dp[n - 1][i])
    //     {
    //         res = min(res, (i * i) + (total - i) * (total - i));
    //     }
    // }

    ll res = LLONG_MAX;

    // approach-2 using bitset

    ll suma = 0, sumb = 0;

    for (int i = 0; i < n; i++)
    {
        if (a[i] > b[i])
        {
            swap(a[i], b[i]);
        }
        suma += a[i];
        sumb += b[i];
    }

    bitset<10004> dp;
    dp[0] = 1;

    for (int i = 0; i < n; i++)
    {
        dp |= (1 << (b[i] - a[i]));
    }

    for (int i = 0; i <= sumb - suma; i++)
    {
        if (dp[i])
        {
            res = min(res, (suma + i) * (suma + i) + (sumb - i) * (sumb - i));
        }
    }

    cout << res + constantTerm << endl;
}

// https://codeforces.com/contest/1637/problem/E

void sol7()
{
    int n, m;
    cin >> n >> m;

    vector<int> a(n);
    map<int, int> cnt;

    for (auto &x : a)
    {
        cin >> x;
        cnt[x]++;
    }

    vector<pair<int, int>> bad_pairs;
    bad_pairs.reserve(2 * m);

    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        bad_pairs.emplace_back(x, y);
        bad_pairs.emplace_back(y, x);
    }

    sort(all(bad_pairs));

    vector<vector<int>> occ(n);
    for (auto &val : cnt)
        occ[val.second].push_back(val.first);

    for (auto &v : occ)
        reverse(v.begin(), v.end());

    long long answer = 0;

    // Iterating over all x
    // and cnty ≤ cntx
    //     works in O(∑cntx) = O(n)
    //                             .And finding maximum y
    //                                 such that x≠y and
    //                         the pair(x, y)
    //                             is not bad.

    for (int cnt_x = 1; cnt_x < n; cnt_x++)
    {
        for (int x : occ[cnt_x])
        {
            for (int cnt_y = 1; cnt_y <= cnt_x; cnt_y++)
            {
                for (int y : occ[cnt_y])
                {
                    if (x != y and !binary_search(bad_pairs.begin(), bad_pairs.end(), make_pair(x, y)))
                    {
                        answer = max(answer, 1ll * (cnt_x + cnt_y) * (x + y));
                        break;
                    }
                }
            }
        }
    }

    cout << answer << '\n';
}

void sol8()
{
    int n, q;
    cin >> n >> q;

    string s;
    cin >> s;

    ll ans = 0;

    for (int i = 0; i < n - 1; i++)
    {
        if (s[i] == s[i + 1])
        {
            ans += 2;
        }
        else
        {
            ans++;
        }
    }

    fl(i, q)
    {
        int ind;
        cin >> ind;
        --ind;

        if (ind != 0)
        {
            ans = ans - ((s[ind] == s[ind - 1]) ? 2 : 1);
        }
        if (ind != (n - 1))
        {
            ans = ans - ((s[ind] == s[ind + 1]) ? 2 : 1);
        }

        int newval = s[ind] - '0';
        newval = !newval;
        s[ind] = newval + '0';

        if (ind != 0)
        {
            ans = ans + ((s[ind] == s[ind - 1]) ? 2 : 1);
        }
        if (ind != (n - 1))
        {
            ans = ans + ((s[ind] == s[ind + 1]) ? 2 : 1);
        }

        cout << ans << endl;
    }
}

void h1()
{
    int n;
    cin >> n;

    vector<int> v(n);
    fl(i, n)
    {
        cin >> v[i];
    }

    if (v[0] == v[n - 1])
    {
        py;
        return;
    }

    for (int i = 0; i < n - 1; i++)
    {
        if (v[i] == v[0] and v[i + 1] == v[n - 1])
        {
            py;
            return;
        }
    }

    pn;
}

void h2()
{
    int n;
    cin >> n;
    vector<ll> v(n);
    inputvector(v);

    ll my = v[0];
    vector<ll> sm, lg;

    for (int i = 1; i < n; i++)
    {
        if (v[i] < my)
        {
            sm.push_back(v[i]);
        }
        else
        {
            lg.push_back(v[i]);
        }
    }

    ll ans = 1;
    if (sm.size() == 0)
    {
        ans += my - 1;
    }
    else
    {
        ll t = *max_element(all(sm));
        ll gap = abs(t - my);
        ans += gap / 2;
    }

    if (lg.size() == 0)
    {
        ans += (1e6 - my);
    }
    else
    {
        ll t = *min_element(all(lg));
        ll gap = abs(t - my);
        ans += gap / 2;
    }

    if (lg.size() == 0 and sm.size() == 0)
    {
        ans--;
    }

    cout << ans << endl;
}

void h3()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    int ans = n;

    // string t = s;

    bool one = false, z = false;
    for (int i = 0; i < n; i++)
    {
        if (s[i] == '1')
            one = true;
        else
            z = true;
    }

    if (one and z)
    {
        cout << 1 << endl;
    }
    else
    {
        cout << n << endl;
    }
}

void h4()
{
    int n;
    cin >> n;

    vector<vector<int>> ans(n, vector<int>(n, 0));

    deque<int> dq;

    dq.push_back((n + 1) / 2);
    for (int i = 1; i <= n; i++)
    {
        if (i != (n + 1) / 2)
            dq.push_back(i);
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            ans[i][j] = dq[j];
        }
        int fr = dq.back();
        dq.pop_back();
        dq.push_front(fr);
    }

    for (auto i : ans)
    {
        for (auto k : i)
        {
            cout << k << " ";
        }
        cout << endl;
    }
}

void braces()
{
    int n;
    cin >> n;
    string s;
    cin >> s;

    stack<int> st;
    unordered_map<int, int> mp;
    // {start -> end}

    for (int i = 0; i < n; i++)
    {
        if (s[i] == '(')
        {
            st.push(i);
        }
        else if (s[i] == ')')
        {
            if (!st.empty())
            {
                mp[st.top()] = i + 1;
                st.pop();
            }
        }
    }

    string ans = "";
    for (int i = 0; i < n; i++)
    {
        if (s[i] == '(')
        {
            if (mp.count(i))
            {
                i = mp[i] - 1;
            }
            else
            {
                ans += s[i];
            }
        }
        else
        {
            ans += s[i];
        }
    }
    cout << ans << endl;
}

void h5()
{
    ll n, m;
    cin >> n >> m;

    ll res = 0;

    if (n > 3)
    {
        res += multiply(m, power(m - 1, n - 2ll, new_mod), new_mod);
    }
    if (m > 2)
    {
        res += multiply(m - 2, multiply(m, power(m - 1, n - 2ll, new_mod), new_mod), new_mod);
    }

    cout << res << endl;
}

void h6()
{
    ll k, n;
    cin >> k >> n;
    ll ans = 1;
    set<char> st;

    string s = to_string(k);

    for (auto i : s)
    {
        st.insert(i);
    }

    for (int i = 1; i <= 3; i++)
    {
        ans *= (int)st.size();
    }

    cout << ans << endl;
}

// https://www.codechef.com/practice/course/4-star-difficulty-problems/DIFF1900/problems/BLIMP?tab=statement
void h7()
{
    ll n, x, y;
    cin >> n >> x >> y;
    vector<ll> v(n);
    inputvector(v);
    ll ans = 0;
    if (x <= y)
    {
        for (auto &a : v)
        {
            ans = max(ans, (a + y - 1) / y);
        }
    }
    else
    {
        ll total_used = 0;
        for (int i = n - 1; i >= 0; i--)
        {
            v[i] = max(0ll, v[i] - (total_used * y));
            ans += (v[i] + x - 1) / x;
            total_used += (v[i] + x - 1) / x;
        }
    }
    cout << ans << endl;
}

void h8()
{
    int n, x;
    cin >> n >> x;
    if (x >= n)
    {
        vector<int> marked(n + 1, false);
        int curr = x - n + 1;
        cout << curr << " ";
        marked[curr] = true;
        fl(i, n)
        {
            if (marked[i + 1] == false)
            {
                cout << i + 1 << " ";
            }
        }
        cout << endl;
    }
    else
    {
        cout << -1 << endl;
    }
}

// https://www.codechef.com/problems/AVGPERM?tab=statement
void h9()
{
    int n;
    cin >> n;

    vector<int> perm(n, 0);
    int itr = 1;

    perm[0] = n;
    perm[n - 1] = n - 1;
    perm[1] = n - 2;

    if (n != 3)
    {
        perm[n - 2] = n - 3;
    }

    for (int i = 2; i <= (n - 3); i++)
    {
        perm[i] = itr++;
    }

    for (int i = 1; i <= n; i++)
    {
        cout << perm[i - 1] << " ";
    }

    cout << endl;
}

void h10()
{
    int n, k;
    cin >> n >> k;

    vector<int> v(n);
    inputvector(v);

    ll rem = 0;
    vector<int> diff;
    ll ans = 0;

    for (auto i : v)
    {
        if (i >= k)
        {
            rem += (i - k);
            ans++;
        }
        else if (i < k)
        {
            diff.push_back(k - i);
        }
    }

    sort(all(diff));

    for (auto i : diff)
    {
        if (rem >= i)
        {
            ans++;
            rem -= i;
        }
        else
        {
            break;
        }
    }

    cout << ans << endl;
}

// https://www.codechef.com/problems/MINIMISEINV

ll flipBits(string s, int front1s, int back0s)
{
    for (auto &ch : s)
    {
        if (ch == '1')
        {
            if (front1s > 0)
            {
                ch = '0';
                front1s--;
            }
            else
            {
                break;
            }
        }
    }
    for (int i = s.size() - 1; i >= 0; i--)
    {
        if (s[i] == '0')
        {
            if (back0s > 0)
            {
                s[i] = '1';
                back0s--;
            }
            else
            {
                break;
            }
        }
    }

    ll ans = 0;
    ll zeros = 0;

    for (int i = (int)s.size() - 1; i >= 0; i--)
    {
        if (s[i] == '0')
        {
            zeros++;
        }
        else
        {
            ans += zeros;
        }
    }

    return ans;
}

void h11()
{
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;

    ll ans = INT_MAX;

    for (int i = 0; i <= k; i++)
    {
        ans = min(ans, flipBits(s, i, k - i));
    }

    cout << ans << endl;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    ll t = 1;
    cin >> t;

    while (t--)
        h11();

    // precomputeFactorials(factSize, mod);
    // primes.clear();
    // generatePrimes(1e5);
    // precomputePalindromes();

    return 0;
}