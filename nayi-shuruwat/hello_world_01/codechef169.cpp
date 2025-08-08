
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using lld = long double;
using ull = unsigned long long;

// Constants
const ll INF = LONG_LONG_MAX;
const ll mod = 1e9 + 7;
const ll MOD_FACT = 1e9 + 7;

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

void solut1()
{
    int n;
    cin >> n;

    vector<ll> v(n);
    ll negativescnt = 0;

    fl(i, n)
    {
        cin >> v[i];
        if (v[i] < 0)
            negativescnt++;
    }

    sort(all(v));

    if (negativescnt % 2 == 0)
    {
        ll sum = 0;
        for (auto i : v)
        {
            sum += abs(i);
        }
        cout << sum << endl;
    }
    else
    {

        ll sum = 0;
        ll maxneg = INT_MIN, minpos = INT_MAX;

        for (int i = 0; i < n; i++)
        {
            sum += abs(v[i]);
            if (v[i] < 0)
                maxneg = max(maxneg, v[i]);
            else
                minpos = min(minpos, v[i]);
        }

        if (minpos == INT_MAX)
        {
            sum += 2 * abs(v[n - 1]);
        }
        else
        {
            if (abs(maxneg) >= minpos)
            {
                sum -= 2 * abs(minpos);
            }
            else
            {
                sum += 2 * maxneg;
            }
        }

        cout << sum << endl;
    }
}

void sol2()
{
    ll n;
    cin >> n;
    vector<ll> v(n);

    fl(i, n)
    {
        cin >> v[i];
    }

    int p1 = 0, p2 = n - 1;
    while (p1 < n and v[p1] <= 0)
        p1++;
    while (p2 >= 0 and v[p2] <= 0)
        p2--;

    if (p1 > p2)
    {
        cout << 0 << endl;
    }
    else
    {
        int ans = 0;
        for (int i = p1; i <= p2; i++)
        {
            if (v[i] < 0)
                ans++;
        }
        cout << ans << endl;
    }
}

void sol3()
{
    int n;
    cin >> n;
    string s;
    cin >> s;

    vector<ll> ans(n, 0ll);
    ll x = 0;

    for (int i = 1; i < n; i++)
    {
        if (s[i] != s[i - 1])
        {
            ans[i] = add(ans[i - 1], (i * (i - 1) % mod) / 2);
            x += i;
        }
        else
        {
            ans[i] = add(ans[i - 1], x);
        }
        ans[i] %= mod;
    }

    ll res = 0;
    for (int i = 0; i < n; i++)
    {
        res = add(res, ans[i]);
    }
    cout << res << endl;
}

void sol4()
{
    ll n, x, k;
    cin >> n >> x >> k;

    vector<ll> v(n);

    fl(i, n)
    {
        cin >> v[i];
    }

    unordered_map<ll, ll> freq;

    for (auto i : v)
    {
        freq[i]++;
    }

    sort(all(v));
    vector<ll> temp2 = v;
    temp2.resize(distance(temp2.begin(), unique(temp2.begin(), temp2.end())));

    ll ans1 = 0ll, ans2 = 0ll;

    // using spell initially

    ll currx = x * 1ll * k;

    ans1 = lower_bound(all(temp2), currx) - temp2.begin();

    // without using spellll
    ll it = -1;

    // 2 maps because one a[i] can be destroyed initially
    // then again by renewing the health

    unordered_map<ll, ll> vis1, vis2;
    for (int i = n - 1; i >= 0; i--)
    {
        if (v[i] < x)
        {
            it = i;
            break;
        }
    }

    for (int i = it; i >= 0; i--)
    {
        if (freq[v[i]] and !vis1[v[i]])
        {
            vis1[v[i]] = 1;
            ans2++;
            freq[v[i]]--;
            if (freq[v[i]] == 0)
            {
                freq.erase(v[i]);
            }
        }
    }

    vector<ll> temp;

    // now use vis2 while re-filling values in temp
    fl(i, n)
    {
        if (freq[v[i]] and !vis2[v[i]])
        {
            temp.push_back(v[i]);
            vis2[v[i]] = 1;
        }
    }

    ll maxi = 0LL;

    if (ans2)
    {
        for (ll i = 0; i < temp.size(); i++)
        {
            // we can use this only if it was traversed before
            if (vis1[temp[i]])
            {
                auto it = lower_bound(temp.begin(), temp.end(), k * 1ll * temp[i]) - temp.begin();
                maxi = max((ll)maxi, (ll)it - i);
            }
        }
    }
    cout << max(ans1, ans2 + maxi) << endl;
}

// div 3
// https://codeforces.com/contest/1335

void sol5()
{
    int n;
    cin >> n;
    string s;
    cin >> s;

    vector<ll> tval(n - 1, 0);

    for (int i = 0; i < n - 1; i++)
    {
        if (s[i] != s[i + 1])
        {
            tval[i]++;
        }
    }

    for (int i = 1; i < n - 1; i++)
    {
        tval[i] += tval[i - 1];
    }

    ll total = 0LL;

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i; j < n; j++)
        {
            int len = j - i + 1;
            ll t =
                (j >= 1) ? ((i == 0) ? tval[j - 1] : (tval[j - 1] - tval[i - 1])) : 0;
            ll cntzero = len - 1 - t;
            ll ans = multiply(cntzero, t);
            ans = add(ans, multiply(t, t - 1) / 2);
            total = add(total, ans);
        }
    }

    cout << total << endl;
}

void sol6()
{
    int n, a, b;
    cin >> n >> a >> b;

    string s = "";
    int maxi = b, ptr = 0;
    for (int i = 0; i < a; i++)
    {
        s += ('a' + ptr);
        ptr = (ptr + 1) % maxi;
    }
    for (int i = a; i < n; i++)
    {
        s += s[i - a];
    }

    cout << s << endl;
}

void sol7()
{
    ll n;
    cin >> n;
    unordered_map<ll, ll> fr;

    fl(i, n)
    {
        ll e;
        cin >> e;
        fr[e]++;
    }

    ll ans = 0;

    for (auto i : fr)
    {
        ll currfreq = i.second, elem = i.first;
        ll f = fr.size() - 1, sec = currfreq;
        if (f >= sec)
        {
            ans = max(ans, sec);
        }
        else
        {
            ans = max(ans, min(sec - 1, f + 1));
        }
    }

    cout << ans << endl;
}

// https://codeforces.com/contest/1335/problem/E1
void sol8()
{
    int n;
    cin >> n;
    vector<int> v(n);
    vector<bool> mp(26, false);
    vector<vector<int>> freq(26, vector<int>(n, 0));

    fl(i, n)
    {
        cin >> v[i];
        v[i]--;
        mp[v[i]] = true;
        freq[v[i]][i]++;
    }

    fl(i, 26)
    {
        fl(j, n)
        {
            if (j == 0)
                continue;
            freq[i][j] += freq[i][j - 1];
        }
    }

    int ans = 0;

    fl(a, 26)
    {
        fl(b, 26)
        {
            if (a == b)
            {
                ans = max(ans, freq[a][n - 1]);
                continue;
            }
            if (ans >= (freq[a][n - 1] + freq[b][n - 1]))
            {
                continue;
            }
            if (mp[a] and mp[b])
            {
                vector<int> loc;

                for (int t = 0; t < n; t++)
                {
                    if (v[t] == b)
                    {
                        loc.push_back(t);
                    }
                }

                for (int t = 0; t < loc.size(); t++)
                {
                    for (int s = t; s < loc.size(); s++)
                    {
                        int f1 = (loc[t] == 0) ? 0 : freq[a][loc[t]], f2 = freq[a][n - 1] - freq[a][loc[s]];

                        int currlen = 2 * min(f1, f2) + (s - t + 1);
                        ans = max(ans, currlen);
                    }
                }
            }
        }
    }

    cout << ans << endl;
}

// build an integer which is maximum subsequnce from a subarray of size k.
// e.g Array is [4 , 9 , 0 , 2] and k = 2. asnwer 92 .

class SparseTable
{
private:
    vector<vector<pair<int, int>>> table; // Sparse table to store {value, index}
    vector<int> logTable;                 // Log values for fast access

public:
    SparseTable(const vector<int> &arr)
    {
        int n = arr.size();
        int maxLog = log2(n) + 1;

        // Resize the table and initialize the first level
        table.resize(n, vector<pair<int, int>>(maxLog));
        logTable.resize(n + 1);

        // Fill log values
        logTable[1] = 0;
        for (int i = 2; i <= n; ++i)
        {
            logTable[i] = logTable[i / 2] + 1;
        }

        // Initialize table with array values for range length = 1
        for (int i = 0; i < n; ++i)
        {
            table[i][0] = {arr[i], i};
        }

        // Build Sparse Table
        for (int j = 1; (1 << j) <= n; ++j)
        {
            for (int i = 0; i + (1 << j) - 1 < n; ++i)
            {
                // Compare two intervals
                pair<int, int> left = table[i][j - 1];
                pair<int, int> right = table[i + (1 << (j - 1))][j - 1];

                // Take the maximum value and its first occurrence index
                if (left.first > right.first || (left.first == right.first && left.second < right.second))
                {
                    table[i][j] = left;
                }
                else
                {
                    table[i][j] = right;
                }
            }
        }
    }

    // Query the maximum and its first occurrence index in the range [L, R]
    pair<int, int> query(int L, int R)
    {
        int range = R - L + 1;
        int j = logTable[range]; // Get the largest power of 2 that fits in the range

        pair<int, int> left = table[L][j];
        pair<int, int> right = table[R - (1 << j) + 1][j];

        // Return the maximum value and its first occurrence index
        if (left.first > right.first || (left.first == right.first && left.second < right.second))
        {
            return left;
        }
        else
        {
            return right;
        }
    }
};

int segmentMain()
{
    vector<int> arr = {1, 3, 3, 8, 5, 8, 2, 4};
    SparseTable st(arr);

    auto result1 = st.query(0, 3);
    cout << "Maximum in range [0, 3]: Value = " << result1.first << ", Index = " << result1.second << endl;

    auto result2 = st.query(2, 5);
    cout << "Maximum in range [2, 5]: Value = " << result2.first << ", Index = " << result2.second << endl;

    auto result3 = st.query(4, 7);
    cout << "Maximum in range [4, 7]: Value = " << result3.first << ", Index = " << result3.second << endl;

    return 0;
}

void largestSubs()
{
    int n, k;
    cin >> n >> k;

    vector<int> v(n);

    fl(i, n)
    {
        cin >> v[i];
    }

    if (n < k)
    {
        cerr << "Invalid input: value of k should be less than or equal to n";
        return;
    }

    SparseTable st(v);

    vector<int> largestSubs(k);

    int pos = 0;
    for (int i = 0; i < k; i++)
    {
        // isko hatake, sparse table use kro
        // for (int j = pos; j <= (n - k + i); j++)
        // {
        //     if (v[j] > maxelem)
        //     {
        //         maxelem = v[j];
        //         pos = j;
        //     }
        // }
        auto result1 = st.query(pos, n - k + i);
        pos = result1.second + 1;
        largestSubs[i] = result1.first;
    }

    for (auto i : largestSubs)
    {
        cout << i;
    }
    cout << endl;
}

// You and your friends discuss a pattern of number your teacher has written on blackboard after class.
// Return false if there is any contradiction between you and your friends, in sequencing of numbers,
//  else return true.

// For e.g Suppose 4 friends write a sequence of numbers
// Friend 1: 1, 3, 4, 2
// Friend 2: 3, 4, 9, 10
// Friend 3: 11, 49, 13, 3
// Friend 4: 19, 3, 13, 4

// use topological sort => if cycle return false, else true.
// represent a graph from all sequences, then run a topological sort on this graph

void sol9()
{
    int n, k;
    cin >> n >> k;

    vector<ll> v(n);

    fl(i, n)
    {
        cin >> v[i];
    }

    vector<ll> swapelems;
    vector<bool> blocked(n, 0);
    fl(i, n)
    {
        if ((i + k) < n || (i - k) >= 0)
        {
            swapelems.push_back(v[i]);
            blocked[i] = 1;
        }
    }

    sort(all(swapelems));

    for (int i = 0, j = 0; i < n; i++)
    {
        if (blocked[i])
        {
            v[i] = swapelems[j++];
            blocked[i] = 0;
        }
    }

    for (auto i : v)
    {
        cout << i << " ";
    }
    cout << endl;
}

void h1()
{
    int n, k;
    cin >> n >> k;

    vector<ll> v(n);
    vector<ll> fr(21, 0);

    int ans = 2;

    for (int i = 0; i < n; i++)
    {
        cin >> v[i];
        fr[v[i]]++;
    }

    vector<ll> temp(fr.begin(), fr.end());

    ll maxfreq = 0;
    for (int j = 1; j <= 20; j++)
    {
        maxfreq = max(maxfreq, temp[j]);
    }

    ll curr = temp[k];

    if (curr == maxfreq)
    {
        ans = 0;
        cout << ans << endl;
        return;
    }

    bool isposs = false;
    for (int i = 0; i < n - 1; i++)
    {
        temp[v[i]]--;
        ll maxfreq = 0;
        for (int j = 1; j <= 20; j++)
        {
            maxfreq = max(maxfreq, temp[j]);
        }
        int curr = temp[k];
        if (curr == maxfreq)
        {
            isposs = true;
            break;
        }
    }
    if (isposs)
    {
        ans = 1;
    }
    temp.assign(fr.begin(), fr.end());

    isposs = false;
    for (int i = n - 1; i > 0; i--)
    {
        temp[v[i]]--;
        ll maxfreq = 0;
        for (int j = 1; j <= 20; j++)
        {
            maxfreq = max(maxfreq, temp[j]);
        }
        int curr = temp[k];
        if (curr == maxfreq)
        {
            isposs = true;
            break;
        }
    }
    if (isposs)
    {
        ans = 1;
    }

    cout << ans << endl;
    return;
}

void h2()
{
    int n;
    cin >> n;

    vector<ll> v(n);
    fl(i, n)
    {
        cin >> v[i];
    }

    vector<vector<pll>> t(32);

    fl(i, n)
    {
        int b = __builtin_popcount(v[i]);
        // cout << b << " ";
        t[b].push_back({v[i], i});
    }

    for (auto &i : t)
    {
        vector<int> loc;
        for (auto k : i)
        {
            loc.push_back(k.second);
        }
        sort(all(i));

        int ptr = 0;
        for (auto k : i)
        {
            v[loc[ptr++]] = k.first;
        }
    }

    for (int i = 0; i < n - 1; i++)
    {
        if (v[i] > v[i + 1])
        {
            cout << "No\n";
            return;
        }
    }

    cout << "Yes\n";
}

bool isposs2(vector<ll> &pos, vector<ll> &neg, ll mid)
{
    int p1 = 0, p2 = 0;
    int n = pos.size(), m = neg.size();

    ll currsum = 0;

    while (p1 < n && p2 < m)
    {
        currsum = max(0ll, currsum);
        while (p1 < n && ((currsum + pos[p1]) <= mid))
        {
            currsum += pos[p1++];
        }
        if (p2 < m)
        {
            currsum += neg[p2++];
        }
    }

    if (p2 == m && currsum < mid)
    {
        currsum = max(0ll, currsum);
        while (p1 < n && ((currsum + pos[p1]) <= mid))
        {
            currsum += pos[p1++];
        }
    }

    return (p1 == n);
}

void h3()
{
    int n;
    cin >> n;

    vector<ll> v(n);
    fl(i, n)
    {
        cin >> v[i];
    }

    vector<ll> pos, neg;

    for (auto i : v)
    {
        if (i >= 0)
        {
            pos.push_back(i);
        }
        else
        {
            neg.push_back(i);
        }
    }

    // ll abhi = 0;
    // ll currsum = 0, currmax = 0;

    // for (int i = 0; i < n; i++)
    // {
    //     currsum = max(0ll, currsum);
    //     currsum += v[i];
    //     currmax = max(currmax, currsum);
    // }

    ll low = 0, high = LLONG_MAX, mid, ans = -1;

    while (low <= high)
    {
        mid = (low + high) / 2;
        if (isposs2(pos, neg, mid))
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

void h4()
{
    int n;
    cin >> n;
    string s;
    cin >> s;

    vector<ll> fr(26, 0);
    for (auto i : s)
    {
        fr[i - 'a']++;
    }

    int countod = 0;

    for (auto i : fr)
    {
        if (i % 2 != 0)
        {
            countod++;
        }
    }

    if (countod > 1)
    {
        cout << 0 << endl;
        return;
    }

    bool found = false, isonly = true;
    for (auto i : fr)
    {
        if (i > 0)
        {
            if (found)
            {
                isonly = false;
            }
            else
            {
                found = true;
            }
        }
    }

    if (isonly)
    {
        cout << -1 << endl;
        return;
    }

    if (countod == 0)
    {
        // 2 odd chahiye
        string ans = "zz";
        unordered_set<char> uniq;

        vector<char> up(n, 'z');
        char curr = s[n - 1];

        for (int i = n - 2; i >= 0; i--)
        {
            up[i] = curr;
            curr = min(curr, s[i]);
        }

        for (int i = 0; i < 26; i++)
        {
            if (fr[i])
            {
                char ch = 'a' + i;

                string temp = "";
                temp += ch;

                for (int j = 0; j < n; j++)
                {
                    if (s[j] == ch)
                    {
                        bool found2 = false;
                        j++;

                        char upch = up[j];

                        if (upch < ch)
                        {
                            temp += upch;
                            ans = min(ans, temp);
                            break;
                        }

                        char minigrg;

                        for (; j < n; j++)
                        {
                            if (s[j] == ch)
                            {
                                temp += s[j];
                            }
                            else if (!found2 || (s[j] < minigrg))
                            {
                                string hell = temp;

                                int currlen = hell.size();
                                if ((currlen % 2) == 0)
                                {
                                    hell.pop_back();
                                }

                                hell += s[j];
                                ans = min(ans, hell);

                                if (!found2)
                                {
                                    minigrg = s[j];
                                    found2 = true;
                                }

                                minigrg = min(minigrg, s[j]);
                            }
                        }
                    }
                }
            }
        }

        cout << 2 << endl;
        cout << ans << endl;
    }
    else
    {
        // 1 odd chahiye
        string ans = "z";
        int len;

        for (int i = 0; i < 26; i++)
        {
            if (((fr[i] % 2) == 0) and fr[i] > 0)
            {
                string curr = "";
                curr += 'a' + i;
                ans = min(ans, curr);
            }
            if ((fr[i] % 2) != 0)
            {
                fr[i]--;
                len = fr[i];
            }
        }

        if (len == 0)
        {
            bool found = false, isonly = true;
            for (auto i : fr)
            {
                if (i > 0)
                {
                    if (found)
                    {
                        isonly = false;
                    }
                    else
                    {
                        found = true;
                    }
                }
            }

            if (isonly)
            {
                cout << -1 << endl;
                return;
            }
        }

        cout << 1 << endl;
        cout << ans << endl;
        return;
    }
}

void h8()
{
    ll n;
    cin >> n;
    string s;
    cin >> s;
    set<char> uniq;
    ll cnt[n + 1][26];
    ll next[n + 1][26];
    for (int i = 0; i < 26; i++)
    {
        next[n][i] = n;
        cnt[n][i] = 0;
    }
    for (int i = n - 1; i >= 0; i--)
    {
        uniq.insert(s[i]);
        for (int j = 0; j < 26; j++)
        {
            cnt[i][j] = cnt[i + 1][j];
            next[i][j] = next[i + 1][j];
        }
        cnt[i][s[i] - 'a']++;
        if ((i + 1) < n)
        {
            next[i][s[i + 1] - 'a'] = i + 1;
        }
    }
    ll parity[26] = {};
    for (int i = 0; i < 26; i++)
    {
        if (cnt[0][i] % 2 == 0)
        {
            parity[i] = 1;
        }
    }
    ll curr[26];
    ll pos;
    for (int i = 0; i < 26; i++)
    {
        curr[i] = next[0][i];
    }
    curr[s[0] - 'a'] = 0;
    if (uniq.size() == 1)
    {
        cout << "-1\n";
        return;
    }
    string ans = "";
    ll total[26] = {};
    ll flag = 0;
    while (true)
    {
        flag = 0;
        for (int i = 0; i < 26; i++)
        {
            if ((cnt[0][i] - total[i]) % 2)
            {
                flag++;
            }
        }
        if (flag >= 2)
        {
            break;
        }
        for (int i = 0; i < 26; i++)
        {
            if (curr[i] != n)
            {
                flag = 0;
                pos = curr[i];
                total[s[pos] - 'a']++;
                for (int j = 0; j < 26; j++)
                {
                    if (cnt[pos + 1][j] == 0 && parity[j] == (total[j] % 2))
                    {
                        flag++;
                        continue;
                    }
                    if (cnt[pos + 1][j])
                    {
                        flag++;
                    }
                }
                total[s[pos] - 'a']--;
                if (flag >= 2)
                {
                    for (int j = 0; j < 26; j++)
                    {
                        curr[j] = next[pos][j];
                    }
                    ans += s[pos];
                    total[s[pos] - 'a']++;
                    break;
                }
            }
        }
    }
    cout << ans.size() << "\n";
    for (auto it : ans)
    {
        cout << it;
    }
    cout << "\n";
}

ll new_mod = 1000000080798150871;

long long mod_exp(long long x, long long y, long long mod)
{
    long long res = 1;
    while (y > 0)
    {
        if (y & 1)
        {
            res = (res * x) % mod;
        }
        y = y >> 1;        // y = y / 2
        x = (x * x) % mod; // Change x to x^2
    }
    return res;
}

long long nCr(int n, int r)
{
    r = min(r, n - r);
    long long nr = 1;
    long long dr = 1;

    for (int i = 1; i <= r; i++)
    {
        nr = (nr * (n - i + 1)) % new_mod;
        dr = (dr * i) % new_mod;
    }

    long long mod_inverse_dr = mod_exp(dr, new_mod - 2, new_mod);
    return (nr * mod_inverse_dr) % new_mod;
}

void t1()
{
    int n, m, l, k;
    cin >> n >> m >> l >> k;
    vector<vector<int>> grid(n, vector<int>(m, 0));
    string s;
    fl(i, n)
    {
        cin >> s;
        fl(j, m)
        {
            grid[i][j] = (s[j] == '1');
        }
    }

    vector<int> t(3, 0);

    fl(i, m)
    {
        int cnt = 0;
        fl(j, n)
        {
            cnt += grid[j][i];
        }
        t[i] = cnt;
    }

    ll ans = 0;

    if (k == 1)
    {
        for (int i = 0; i < m; i++)
        {
            if (t[i] >= l)
                ans = add(ans, nCr(t[i], l), new_mod);
        }
    }
    else if (k == 2)
    {
        for (int i = 0; i < m; i++)
        {
            if (t[i] >= l)
            {
                for (int j = i + 1; j < m; j++)
                {
                    if (t[j] >= l)
                    {
                        ll common = 0;
                        for (int p = 0; p < n; p++)
                        {
                            if (grid[p][i] && grid[p][j])
                            {
                                common++;
                            }
                        }
                        if (common >= l)
                        {
                            ans = add(ans, nCr(common, l), new_mod);
                        }
                    }
                }
            }
        }
    }
    else
    {
        if (m < 3)
        {
            cout << ans << endl;
            return;
        }

        ll common = 0;
        for (int p = 0; p < n; p++)
        {
            if (grid[p][0] && grid[p][1] && grid[p][2])
            {
                common++;
            }
        }
        if (common >= l)
        {
            ans = nCr(common, l);
        }
    }

    cout << ans << endl;
}

void t2()
{
    int n;
    cin >> n;
    ll pw = pow(2, 32);
    for (int i = 0; i < n; i++)
    {
        cout << pw << " ";
    }
    cout << endl;
}

void t3()
{
    int n;
    cin >> n;
    vector<ll> v(n);

    unordered_map<ll, vector<int>> pos;

    fl(i, n)
    {
        cin >> v[i];
        pos[v[i]].push_back(i + 1);
    }

    ll ans = n + (n - 1);

    for (int i = 1; i <= n; i++)
    {
        if (i > v[i - 1])
        {
            int a = (i - v[i - 1] - 1), b;
            if (!pos.count(i))
            {
                b = n - i;
                ans += (a * b);
            }
            else
            {
                auto t = pos[i];
                auto it = upper_bound(all(t), i);
                b = *it - i - 1;
                ans += (a * b);
            }
        }
        else if (i < v[i - 1])
        {
            int a = (v[i - 1] - i - 1), b;
            if (!pos.count(i))
            {
                b = i - 1;
                ans += (a * b);
            }
            else
            {
                auto t = pos[i];
                auto it = lower_bound(all(t), i);
                if (it == t.end())
                {
                    b = i - 1;
                    ans += (a * b);
                }
                else
                {
                    --it;
                    b = *it - i - 1;
                    ans += (a * b);
                }
            }
        }
    }

    cout << ans << endl;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    ll t;
    cin >> t;

    while (t--)
        t3();

    // precomputeFactorials(factSize, MOD);
    // primes.clear();
    // generatePrimes(1e5);
    // precomputePalindromes();

    return 0;
}