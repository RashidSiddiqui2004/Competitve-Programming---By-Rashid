
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

const int N = 1e7 + 1;
vector<bool> isPrime;
vector<ll> sprime;

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

void generatePrimeNumbers(int n)
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

void sol2()
{
    ll n, x, k;
    cin >> n >> x >> k;
    string s;
    cin >> s;

    ll zeros = 0, inv = 0;

    for (int i = n - 1; i >= 0; i--)
    {
        if (s[i] == '0')
        {
            zeros++;
        }
        else
        {
            inv += zeros;
        }
    }

    int ans = 2;

    if ((inv % k == 0) and inv <= x)
    {
        ans = 1;
    }

    cout << ans << endl;
}

void sol1()
{
    int n;
    cin >> n;

    string a, b;
    cin >> a >> b;

    int ans = 0, ch = 0;

    fl(i, n)
    {
        if (a[i] == '1' and b[i] == '1')
        {
            ans++;
        }
        else if (a[i] == '1' || b[i] == '1')
        {
            ch++;
        }
    }

    if (ans % 2 != 0)
    {
        cout << "YES\n";
    }
    else
    {
        if (ch > 0)
        {
            cout << "YES\n";
        }
        else
        {
            cout << "NO\n";
        }
    }
}

void sol3()
{
    ll n;
    cin >> n;

    vector<ll> v(n);

    vector<vector<ll>> pos(n + 2);

    fl(i, n)
    {
        cin >> v[i];
        pos[v[i]].push_back(i);
    }

    ll ans = 0;

    fl(i, n)
    {
        int sz = pos[v[i]].size();

        if (sz == 1)
        {
            continue;
        }

        ll st = pos[v[i]][0], en = pos[v[i]][sz - 1];

        unordered_set<ll> seti;
        for (int j = st; j <= en; j++)
        {
            sz = pos[v[j]].size();
            if (sz != 1)
            {
                en = max(en, pos[v[j]][sz - 1]);
            }
            seti.insert(v[j]);
        }
        i = en;
        ans += (ll)seti.size();
    }

    cout << ans << endl;
}

vector<pii> helper(const vector<ll> &array)
{
    unordered_map<int, vector<int>> temp;
    temp[0].push_back(0);

    ll prefixXor = 0;
    vector<pair<int, int>> result;

    for (int j = 0; j < array.size(); ++j)
    {
        prefixXor ^= array[j];
        auto it = temp.find(prefixXor);
        if (it != temp.end())
        {
            for (int i : it->second)
            {
                result.push_back({i, j + 1});
            }
        }

        temp[prefixXor].push_back(j + 1);
    }

    return result;
}

vector<pii> helper2(const vector<ll> &array)
{
    unordered_map<int, int> mp;
    mp[0] = 0;

    ll prefixXor = 0;
    vector<pii> result;

    for (int j = 0; j < array.size(); ++j)
    {
        prefixXor ^= array[j];

        auto it = mp.find(prefixXor);
        if (it != mp.end())
        {
            result.push_back({it->second, j + 1});
        }

        mp[prefixXor] = j + 1;
    }

    return result;
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

    ll ans = 0;
    vector<ll> score(n, -1);

    auto temp = helper2(v);

    unordered_map<int, int> mp;

    for (auto i : temp)
    {
        // cout << i.first << " " << i.second << endl;
        if (mp.count(i.first))
            mp[i.first] = min(mp[i.first], i.second - 1);
        else
            mp[i.first] = i.second - 1;
    }

    for (int i = n - 1; i >= 0; i--)
    {
        ll curr = v[i], currxor = v[i];

        if (mp.count(i))
        {
            curr += score[mp[i]];
            ans = max(ans, curr);
            score[i] = curr;
        }
        else
        {
            ans = max(ans, curr);
            score[i] = curr;
        }
    }

    cout << ans << endl;
}

void sol5()
{
    int n;
    cin >> n;

    string s;
    cin >> s;

    int ones = 0;
    for (auto i : s)
    {
        if (i == '1')
            ones++;
    }

    if (ones == 0)
    {
        cout << n << endl;
        return;
    }
    if (ones % 2 == 0)
    {
        cout << 0 << endl;
    }

    else
    {
        cout << 1 << endl;
    }
}

void sol6()
{
    int n;
    cin >> n;

    vector<ll> v(n);

    fl(i, n)
    {
        cin >> v[i];
    }

    ll result = 0;

    vector<ll> t;

    fl(j, n)
    {
        for (int k = j; k < n; k++)
        {
            t = vector<ll>(v.begin() + j, v.begin() + k + 1);

            bool ans = true;

            ll ch1 = t[0], ch2 = t[0] ^ 1;

            for (int i = 1; i < (int)t.size(); i++)
            {
                if (ch1 != -1)
                {
                    int pos1 = t[i] ^ ch1;
                    if (pos1 > (i + 1))
                    {
                        ch1 = -1;
                    }
                }
                if (ch2 != -1)
                {
                    int pos2 = t[i] ^ ch2;
                    if (pos2 > (i + 1))
                    {
                        ch2 = -1;
                    }
                }
                if (ch1 == -1 and ch2 == -1)
                {
                    ans = false;
                    break;
                }
            }

            if (ans)
            {
                result++;
            }
        }
    }

    cout << result << endl;
}

bool ispossible(vector<ll> &v, ll l, double mid)
{
    double lastCovered = -1;
    int lasttaken = -1; // Initialize to -1 to indicate no lanterns taken.

    while (lastCovered < l)
    {
        auto it = upper_bound(all(v), lastCovered);

        if (it == v.end())
        {
            return false;
        }

        if (it != v.begin() && (double)(*it - mid) > lastCovered)
        {
            --it;
        }

        int i = it - v.begin();

        if (i == lasttaken) // Prevent reselecting the same lantern.
        {
            return false;
        }

        double prevCovered = *it - mid;
        if (prevCovered > lastCovered)
        {
            return false;
        }

        lastCovered = *it + mid;
        lasttaken = i;
    }

    return true;
}

void sol7()
{
    ll n, l;
    cin >> n >> l;

    vector<ll> v(n);
    inputvector(v);
    sort(all(v));

    double low = 1.0, high = 1e9, mid, ans = 0.0;

    while (high - low > 1e-7) // Use a precision threshold.
    {
        mid = (low + high) / 2.0;
        if (ispossible(v, l, mid))
        {
            ans = mid;
            high = mid;
        }
        else
        {
            low = mid;
        }
    }

    cout << fixed << setprecision(11) << ans << endl;
}

void sol8()
{
    int n;
    cin >> n;

    vector<ll> v(n);
    inputvector(v);
    unordered_map<ll, ll> freq;

    for (auto i : v)
    {
        unordered_map<ll, ll> mp;
        getFactorization(i, mp);
        for (auto j : mp)
        {
            freq[j.first]++;
        }
    }

    ll ans = INT_MAX;

    // all 1s
    if (freq.size() == 1 and freq.count(1))
    {
        cout << -1 << " ";
        return;
    }
    // cout << freq.size() << endl;

    for (auto i : freq)
    {
        ans = min(ans, n - i.second);
    }

    cout << ans << " ";
}

void rearrange(vector<int> &temp)
{
    vector<int> curr;
    for (int i = 0; i < temp.size(); i += 2)
    {
        curr.push_back(temp[i]);
    }
    for (int i = 1; i < temp.size(); i += 2)
    {
        curr.push_back(temp[i]);
    }
    temp = curr;
}

void sol9()
{
    int n;
    cin >> n;
    int ans[n][n] = {0};
    int curr = 1;

    vector<int> temp;

    fl(i, n)
    {
        temp.push_back(curr++);
    }

    rearrange(temp);

    fl(i, n)
    {
        ans[i][i] = temp[i];
    }

    int startx = 0, starty = 1;
    int startx2 = 1, starty2 = 0;

    for (int i = 1; i < n; i++)
    {
        int j = 0;
        vector<int> temp;

        for (int j = 0; j < n; j++)
        {
            if ((startx + j) >= n || (starty + j) >= n)
            {
                break;
            }
            temp.push_back(curr++);
        }

        rearrange(temp);

        for (int j = 0; j < n; j++)
        {
            if ((startx + j) >= n || (starty + j) >= n)
            {
                break;
            }
            ans[startx + j][starty + j] = temp[j];
        }

        temp.clear();

        for (int j = 0; j < n; j++)
        {
            if ((startx2 + j) >= n || (starty2 + j) >= n)
            {
                break;
            }
            temp.push_back(curr++);
        }

        rearrange(temp);

        for (int j = 0; j < n; j++)
        {
            if ((startx2 + j) >= n || (starty2 + j) >= n)
            {
                break;
            }
            ans[startx2 + j][starty2 + j] = temp[j];
        }

        starty++;
        startx2++;
    }

    fl(i, n)
    {
        fl(j, n)
        {
            cout << ans[i][j] << " ";
        }
        cout << endl;
    }
}

void sol10()
{
    int n, m;
    cin >> n >> m;

    vector<int> a(n);
    map<int, int> freq;

    inputvector(a);

    fl(i, m)
    {
        int e;
        cin >> e;
        freq[e]++;
    }

    int i = 0;

    for (; i < n; i++)
    {
        auto it = freq.lower_bound(a[i] + 1);

        int num = it->first;
        if (num < a[i])
        {
            break;
        }
        freq[num]--;
        if (freq[num] == 0)
        {
            freq.erase(num);
        }
    }

    int ans = n - i;
    cout << ans << endl;
}

void jumptoend()
{
    // {0,_,_,_,_} -: -1
    // {1,1,3,2,1} -: 4
    // {2,0,1,1,0} -: 3

    // a[x] ->  y = min(n-1, x + a[x]);
    // 2 choices to move forward by 1 to y

    int n;
    cin >> n;
    vector<int> v(n);
    inputvector(v);

    vector<int> maxsteps(n, -1);
    maxsteps[n - 1] = 0;

    int maxtillnow = 0;
    int maxkiloc = n - 1;

    for (int i = n - 2; i >= 0; i--)
    {
        int y = min(i + v[i], n - 1);
        int currmax = -1;

        // yadi currloc se next possible step pe pahuch skte hai to ++, o/w -1
        if (y >= maxkiloc)
        {
            maxtillnow++;
            maxkiloc = i;
            currmax = maxtillnow;
        }
        maxsteps[i] = currmax;
    }

    int ans = maxsteps[0];

    cout << ans << endl;
}

void aliceX()
{
    ll n, x;
    cin >> n >> x;

    priority_queue<ll> pq;

    while (n--)
    {
        ll x;
        cin >> x;
        pq.push(x);
    }
    int ans = 0;
    while (!pq.empty() and x > 0)
    {
        ll top = pq.top();
        pq.pop();
        x -= top;
        ans++;
    }
    if (x > 0)
    {
        ans = -1;
    }
    cout << ans << endl;
}

// https://www.codechef.com/practice/course/adobe-interview-questions/ADOBEPREP/problems/PREP36?tab=statement

void wordLadder()
{
    string a, b;
    cin >> a >> b;
    int m;
    cin >> m;
    unordered_set<string> dixt;

    while (m--)
    {
        string s;
        cin >> s;
        dixt.insert(s);
    }
    dixt.insert(b);

    int len = a.size();

    if (a == b)
    {
        cout << 1 << endl;
        return;
    }

    unordered_set<string> vis;
    queue<string> q;

    q.push(a);
    vis.insert(a);
    string s, temp;

    int steps = 1;

    while (!q.empty())
    {
        int sz = q.size();

        // perform 1-layer search for all frontier nodes
        while (sz--)
        {
            s = q.front();
            q.pop();

            if (s == b)
            {
                cout << steps << endl;
                return;
            }

            for (int i = 0; i < len; i++)
            {
                char ch = s[i];
                for (int j = 0; j < 26; j++)
                {
                    char curr = 'a' + j;
                    if (ch != curr)
                    {
                        temp = s;
                        temp[i] = curr;
                        if (!vis.count(temp) and dixt.count(temp))
                        {
                            q.push(temp);
                            vis.insert(temp);
                        }
                    }
                }
            }
        }

        steps++;
    }

    cout << -1 << endl;
}

bool ispal(vector<ll> arr, ll i, ll j)
{
    while (i <= j)
    {
        if (arr[i] != arr[j])
            return 0;
        ++i, --j;
    }
    return 1;
}

void palindromeseq()
{
    //  {34, 45, 34, 56, 34} -> min seq. possible is 3

    ll n;
    cin >> n;
    vector<ll> dp(n);
    vector<ll> arr(n);

    for (ll i = 0; i < n; ++i)
    {
        cin >> arr[i];
        dp[i] = i + 1; // because for n integers, no. of sequences is atmax n (O based indexing hoti hai isliye i+1 :))
    }
    // find c for each idx
    for (ll i = 1; i < n; ++i)
    {
        for (ll j = 0; j <= i; ++j) // iterate till i
        {
            if (ispal(arr, j, i)) // if palindrome between i and j
            {
                if (j == 0) // if palindrome betwen start and i
                {
                    dp[i] = 1; // 1 palindrome till i
                    break;     // smallest value possible, no need to go further
                }
                else
                {
                    dp[i] = min(dp[i], dp[j - 1] + 1);
                    // we already computed c for j - 1
                    // c from j to i is 1 so we update
                    // c of i to the min of c of i and (c of j - 1) + 1
                }
            }
        }
    }
    // finnaly we print c of last idx
    cout << dp[n - 1] << endl;
}

void preprocess(vector<int> &cost)
{
    queue<int> q;

    int steps = 1;
    for (int i = 1; i <= 12; i++)
    {
        int curr = pow(2, i - 1);
        q.push(curr);
        cost[curr] = steps;
    }
    steps++;

    while (!q.empty())
    {
        int sz = q.size();
        while (sz--)
        {
            int front = q.front();
            q.pop();
            for (int i = 1; i <= 12; i++)
            {
                int curr = front + pow(2, i - 1);
                if (curr > 1e5)
                {
                    continue;
                }
                if (cost[curr] > (steps))
                {
                    q.push(curr);
                    cost[curr] = steps;
                }
            }
        }
        steps++;
    }
}

void restaurant()
{
    int t;
    cin >> t;
    vector<int> cost(1e5 + 2, 1e5);
    preprocess(cost);
    while (t--)
    {
        int n;
        cin >> n;
        cout << cost[n] << endl;
    }
}

void ortuples()
{
    int p, q, r;
    cin >> p >> q >> r;

    ll ans = 1;

    for (int i = 20; i >= 0; i--)
    {
        int s1 = (p & (1 << i)) != 0, s2 = (q & (1 << i)) != 0, s3 = (r & (1 << i)) != 0;
        int count = s1 + s2 + s3;
        if (count == 0 || count == 2)
        {
            continue;
        }
        else if (count == 1)
        {
            cout << 0 << endl;
            return;
        }
        else
        {
            ans *= 4;
        }
    }
    cout << ans << endl;
}

// https://www.codechef.com/problems/CHRL1
// bitmasking
void oranges()
{
    ll n, k;
    cin >> n >> k;

    vector<ll> cost(n), wt(n);

    fl(i, n)
    {
        cin >> cost[i] >> wt[i];
    }

    ll maxwt = 0;

    for (ll i = 0; i <= (1 << n) - 1; i++)
    {
        ll currwt = 0, remMoney = k;
        bool poss = true;
        for (int j = 0; j < n; j++)
        {
            if (((1 << j) & i) != 0)
            {
                if (remMoney >= cost[j])
                {
                    remMoney -= cost[j];
                    currwt += wt[j];
                }
                else
                {
                    poss = false;
                    break;
                }
            }
        }
        if (poss)
        {
            maxwt = max(maxwt, currwt);
        }
    }

    cout << maxwt << endl;
}

void hailxor()
{
    int n, x;
    cin >> n >> x;
    vector<ll> v(n);
    inputvector(v);
    vector<bool> toggled(32, 0);

    fl(i, n)
    {
        for (int j = 31; j >= 0; j--)
        {
            if ((v[i] & (1 << j)) != 0)
            {
                if (toggled[j])
                {
                    toggled[j] = 0;
                    v[i] ^= (1 << j);
                }
                else if (x > 0 and i != n - 1)
                {
                    toggled[j] = 1;
                    v[i] ^= (1 << j);
                    x--;
                }
            }
        }
    }

    fl(i, 32)
    {
        if (toggled[i])
        {
            v[n - 1] ^= (1 << i);
            toggled[i] = 0;
        }
    }

    if (x % 2 != 0 and n == 2)
    {
        v[n - 1] ^= 1;
        v[n - 2] ^= 1;
    }

    for (auto i : v)
    {
        cout << i << " ";
    }
    cout << endl;
}

void voting()
{
    int n;
    cin >> n;
    vector<ll> v(n);
    inputvector(v);

    vector<ll> ans(n, 0);
    fl(i, n)
    {
        ll sum = 0;
        for (int j = i + 1; j < n; j++)
        {
            if (v[i] >= sum)
            {
                ans[j]++;
            }
            else
            {
                break;
            }
            sum += v[j];
        }
    }

    for (int i = n - 1; i >= 0; i--)
    {
        ll sum = 0;
        for (int j = i - 1; j >= 0; j--)
        {
            if (v[i] >= sum)
            {
                ans[j]++;
            }
            else
            {
                break;
            }
            sum += v[j];
        }
    }

    for (auto i : ans)
    {
        cout << i << " ";
    }

    cout << endl;
}

void trailing()
{
    int n;
    cin >> n;

    vector<ll> x(n), p(n);

    inputvector(x);
    inputvector(p);

    int p1 = 0, p2 = n - 1;

    while (p1 < p2)
    {
        ll p1next = x[p1 + 1] - p[p1 + 1];
        int t1 = 0;
        if (p1next <= x[p1])
        {
            t1++;
            p1++;
        }

        ll p2prev = x[p2 - 1] + p[p2 - 1];
        if (p2prev >= x[p2])
        {
            t1++;
            p2--;
        }
        if (t1 == 0)
        {
            break;
        }
    }

    if ((p2 - p1) <= 1)
    {
        cout << "YES\n";
    }
    else
    {
        p1 = 0;

        while (p1 < (n - 1))
        {
            ll p1next = x[p1] + p[p1];

            if (p1next >= x[p1 + 1])
            {
                p1++;
            }
            else
            {
                break;
            }
        }

        p1++;

        while (p1 < (n - 1))
        {
            ll p1next = x[p1] + p[p1];

            if (p1next >= x[p1 + 1])
            {
                p1++;
            }
            else
            {
                break;
            }
        }
        if (p1 >= (n - 1))
        {
            cout << "YES\n";
        }
        else
        {
            p1 = n - 1;

            while (p1 > 0)
            {
                ll p1next = x[p1] - p[p1];

                if (p1next <= x[p1 - 1])
                {
                    p1--;
                }
                else
                {
                    break;
                }
            }

            p1--;

            while (p1 > 0)
            {
                ll p1next = x[p1] - p[p1];

                if (p1next <= x[p1 - 1])
                {
                    p1--;
                }
                else
                {
                    break;
                }
            }

            // cout << p1 << " ";

            if (p1 <= 0)
            {
                cout << "YES\n";
            }
            else
            {
                p1 = 0, p2 = n - 1;

                while (p1 < p2)
                {
                    ll p1next = x[p1] + p[p1];
                    int t1 = 0;
                    if (p1next >= x[p1 + 1])
                    {
                        t1++;
                        p1++;
                    }

                    ll p2prev = x[p2] - p[p2];
                    if (p2prev <= x[p2 - 1])
                    {
                        t1++;
                        p2--;
                    }
                    if (t1 == 0)
                    {
                        break;
                    }
                }

                if ((p2 - p1) <= 1)
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
}

// https://www.codechef.com/problems/DDISH?tab=statement

vector<ll> delicCount(10, 0);

ll numDoflenn(int n)
{
    int temp = n;
    ll ans = 9;
    n--;
    int curr = 9;
    while (n-- > 0)
    {
        ans *= curr;
        curr--;
    }
    delicCount[temp] = ans;
    return ans;
}

ll atmostR(ll r)
{
    string s = to_string(r);
    int len = s.size();
    ll ans = 0;

    for (int i = 1; i < len; i++)
    {
        ans += delicCount[i];
    }

    for (int i = 0; i < len - 1; i++)
    {
        int curdig = s[i] - '0';
        int remlen = len - i - 1;
        if (curdig > 1)
            ans += (curdig - 1) * delicCount[remlen];
    }

    int curdig = s[len - 1] - '0';
    if (curdig > 1)
        ans += curdig * delicCount[0];

    return ans;
}

void deliciosNumbers()
{
    ll l, r;
    cin >> l >> r;

    l = min((ll)1e10, l);
    r = min((ll)1e10, r);

    if (l == 1e10)
    {
        cout << 0 << endl;
    }
    else
    {
        ll ans = atmostR(r) - atmostR(l - 1);
        cout << ans << endl;
    }
}

ll maxprofit = INT_MIN;
vector<int> optimalcount;
vector<vector<int>> optimalsteps;

void cheftraverse(int n,
                  vector<int> &chefcount, vector<vector<int>> &adj,
                  vector<bool> &vis, int d, vector<ll> &s, int node,
                  vector<vector<int>> stepsTransfer)
{
    ll currprofit = 0;
    for (int i = 0; i < n; i++)
    {
        if (chefcount[i] > 0)
        {
            currprofit += s[i];
        }
    }

    if (currprofit > maxprofit)
    {
        maxprofit = max(maxprofit, currprofit);
        optimalsteps = stepsTransfer;
        optimalcount = chefcount;
    }

    if (d == 0)
    {
        return;
    }

    else
    {
        vis[node] = true;
        int currchefs = chefcount[node];
        for (auto i : adj[node])
        {
            if (vis[i])
            {
                continue;
            }
            for (int j = 1; j <= currchefs; j++)
            {
                chefcount[node] -= j;
                chefcount[i] += j;
                // if (j != 0)
                stepsTransfer.push_back({node + 1, i + 1, j});
                cheftraverse(n, chefcount, adj, vis, d - 1, s, i, stepsTransfer);
                stepsTransfer.pop_back();
                chefcount[node] += j;
                chefcount[i] -= j;
            }
        }
        vis[node] = false;
    }
}

void chefcity()
{
    int n, c, d;
    cin >> n >> c >> d;
    vector<ll> s(n);
    inputvector(s);

    vector<vector<int>> adj(n);
    fl(i, n - 1)
    {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<bool> vis(n, false);
    vector<int> chefcount(n, 0);
    chefcount[0] = c;

    vector<vector<int>> stepsTransfer;

    cheftraverse(n, chefcount, adj, vis, d, s, 0, stepsTransfer);

    cout << maxprofit << endl;

    for (auto i : optimalsteps)
    {
        d--;
        cout << "transfer " << i[0] << " " << i[1] << " " << i[2] << endl;
    }
    for (int i = 0; i < n; i++)
    {
        if (optimalcount[i] != 0)
        {
            d--;
            cout << "build " << i + 1 << endl;
        }
    }
    while (d--)
    {
        cout << "nothing\n";
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    // primes.clear();
    // generatePrimes();

    chefcity();

    // precomputeFactorials(factSize, mod);
    // primes.clear();
    // generatePrimes(1e5);
    // precomputePalindromes();

    return 0;
}