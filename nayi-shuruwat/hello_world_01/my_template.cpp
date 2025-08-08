
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

void sol10()
{
    int n;
    cin >> n;

    ll elem;
    ll even = 0;
    fl(i, n)
    {
        cin >> elem;
        if (elem % 2 == 0)
            even++;
    }

    ll res = power(2, even, mod);

    // if all numbers are even => all elements will remain in 1 case
    // => subtract this case

    if (even == n)
    {
        res--;
    }
    cout << res << endl;
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

void sol11()
{
    int n;
    cin >> n;
    vector<int> v(n);
    vector<int> fr(32770, 0);

    fl(i, n)
    {
        cin >> v[i];
        fr[v[i]]++;
    }

    ll res = 0;

    fl(i, n)
    {
        fl(j, (int)palindromicNos.size())
        {
            int vj = v[i] ^ palindromicNos[j];
            if (fr[vj])
            {
                res += fr[vj];
            }
        }
        fr[v[i]]--;
    }

    cout << res << endl;
}

int dp2[2001][2];

bool helper1(int n, string &s, int pos, int prev = -1, int balance = 0)
{
    if (pos == n)
    {
        return balance == 0;
    }

    if (balance < 0)
    {
        return false;
    }

    if (dp2[pos][prev + 1] != -1)
    {
        return dp2[pos][prev + 1];
    }

    bool ans = 0;

    if (pos == 0)
    {
        ans = helper1(n, s, pos + 1, 1, balance + 1) || helper1(n, s, pos + 1, 0, balance - 1);
    }
    else
    {
        if (s[pos] == s[pos - 1])
        {
            ans = helper1(n, s, pos + 1, prev, balance + (prev == 0 ? -1 : 1));
        }
        else
        {
            ans = helper1(n, s, pos + 1, 1, balance + 1) || helper1(n, s, pos + 1, 0, balance - 1);
        }
    }
    return dp2[pos][prev + 1];
}

void sol12()
{
    int n;
    cin >> n;
    string s, ans = "";
    cin >> s;

    if (n % 2 != 0)
    {
        cout << "NO\n";
    }
    else
    {
        // dp[index][balance] = possible or not?
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, -1));
        function<int(int, int)> dfs = [&](int index, int balance) -> int
        {
            if (index >= n)
            {
                return (balance == 0 ? 1 : 0);
            }
            if (balance < 0)
            {
                return 0;
            }
            if (dp[index][balance] != -1)
            {
                return dp[index][balance];
            }
            int pick_open = 0, pick_closed = 0;
            int p = index;
            while (p + 1 < n && s[p] == s[p + 1])
            {
                p++;
            }
            p++;

            pick_open = dfs(p, balance + p - index);
            if (pick_open)
            {
                for (int j = 0; j < p - index; j++)
                    ans += "(";
                dp[index][balance] = 1;
                return 1;
            }

            pick_closed = dfs(p, balance - (p - index));
            if (pick_closed)
            {
                for (int j = 0; j < p - index; j++)
                    ans += ")";
                dp[index][balance] = 1;
                return 1;
            }

            dp[index][balance] = 0;
            return 0;
        };

        int res = dfs(0, 0);
        reverse(ans.begin(), ans.end());

        if (res > 0)
        {
            py;
            cout << ans << endl;
        }
        else
        {
            pn
        }
    }
}

void sol13()
{
    int n;
    cin >> n;
    vector<ll> freq(n + 1, 0);

    fl(i, n)
    {
        ll elem;
        cin >> elem;
        freq[elem]++;
    }

    // to store minimum till ith location
    vector<ll> minitill(n + 1);
    ll mini = freq[0];

    fl(i, n + 1)
    {
        mini = min(freq[i], mini);
        minitill[i] = mini;
    }

    int pos = n + 1;

    // find the first element with 0 frequency
    fl(i, n + 1)
    {
        if (freq[i] == 0)
        {
            pos = i;
            break;
        }
    }

    pos--;

    vector<ll> b;
    ll used = 0;

    while (pos >= 0)
    {
        int mini = minitill[pos] - used;
        for (int t = 0; t < mini; t++)
        {
            b.push_back(pos + 1);
        }
        used += mini;
        freq[pos] -= used;
        pos--;
        while (pos >= 0 and minitill[pos] == used)
        {
            freq[pos] -= used;
            pos--;
        }
    }

    // fill 0 for alll remaining elements
    for (auto i : freq)
    {
        int mini = i;
        for (int t = 0; t < mini; t++)
        {
            b.push_back(0);
        }
    }

    cout << b.size() << endl;

    for (auto i : b)
    {
        cout << i << " ";
    }

    cout << endl;
}

int nodeincycle = -1;

void findNodeinCycle(int node, vector<vector<int>> &adj, int par, vector<int> &vis)
{
    vis[node] = true;
    for (auto i : adj[node])
    {
        if (i != par and vis[i])
        {
            nodeincycle = i;
            return;
        }
        else if (!vis[i])
        {
            vis[i] = true;
            findNodeinCycle(i, adj, node, vis);
        }
    }
}

bool findIfCycle(int node, vector<vector<int>> &adj, int par, vector<int> &vis)
{
    vis[node] = true;
    bool ans = false;
    for (auto i : adj[node])
    {
        if (i != par and vis[i])
        {
            return true;
        }
        else if (i == nodeincycle)
        {
            continue;
        }
        else if (!vis[i])
        {
            vis[i] = true;
            ans |= findIfCycle(i, adj, node, vis);
        }
    }

    return ans;
}

void findCycle(int node, vector<vector<int>> &adj, int par, vector<int> &visited, vector<int> &path, unordered_set<int> &cycleNodes)
{
    visited[node] = 1;
    path.push_back(node);

    for (int neighbor : adj[node])
    {
        if (neighbor == par)
            continue; // Skip parent node
        if (visited[neighbor] == 0)
        { // If neighbor is not visited
            findCycle(neighbor, adj, node, visited, path, cycleNodes);
            if (!cycleNodes.empty())
                return; // Stop further traversal if cycle is found
        }
        else if (visited[neighbor] == 1)
        { // Cycle detected
            // Backtrack to reconstruct the cycle
            auto it = find(path.begin(), path.end(), neighbor);
            while (it != path.end())
            {
                cycleNodes.insert(*it);
                ++it;
            }
            return;
        }
    }
    path.pop_back();   // Remove the current node from the path
    visited[node] = 2; // Mark as completely processed
}

unordered_set<int> nodesIncycles(int node, vector<vector<int>> &adj)
{
    int n = adj.size();
    vector<int> visited(n, 0); // 0 = unvisited, 1 = visited, 2 = processed
    vector<int> path;
    unordered_set<int> cycleNodes;
    findCycle(node, adj, -1, visited, path, cycleNodes);
    return cycleNodes;
}

void sol14()
{
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n);
    vector<pair<int, int>> edges(m);
    vector<bool> edgestaken(m, false);

    fl(i, m)
    {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        edges.push_back({u, v});
    }

    // find a node in cycle
    vector<int> vis(n, false);
    findNodeinCycle(0, adj, -1, vis);

    if (nodeincycle == -1)
    {
        // any order works
        for (int i = 1; i <= m; i++)
        {
            cout << i << " ";
        }
        cout << endl;
    }
    else
    {
        cout << "Nodein cycle: " << nodeincycle << "\n";
        // now find if cycle exists after removing this node
        vector<int> vis(n, false);
        if (findIfCycle(nodeincycle != 0 ? 0 : 1, adj, -1, vis))
        {
            cout << -1 << endl;
        }
        else
        {
            // find all edges in cycle
            auto nodesincycle = nodesIncycles(0, adj);
            fl(i, m)
            {
                if (nodesincycle.count(edges[i].first) || nodesincycle.count(edges[i].second))
                {
                    continue;
                }
                cout << i + 1 << " ";
                edgestaken[i] = true;
            }
            fl(i, m)
            {
                if (edgestaken[i] == false)
                {
                    cout << i + 1 << " ";
                }
            }
            cout << endl;
        }
    }
}

void sol15()
{
    int n, m;
    cin >> n >> m;

    vector<ll> a(n), b(m);

    fl(i, n)
    {
        cin >> a[i];
    }
    fl(i, m)
    {
        cin >> b[i];
    }

    sort(all(b));
    ll res = LLONG_MAX;

    fl(i, n)
    {
        auto it = upper_bound(all(b), a[i]);
        if (it == b.end())
        {
            --it;
        }
        res = min(res, abs(a[i] - *it));
        int dist = it - b.begin();
        if (dist != 0)
        {
            --it;
            res = min(res, abs(a[i] - *it));
        }
    }
    cout << res << endl;
}

void sol16()
{
    int n;
    cin >> n;

    vector<ll> v(n);
    ll maxi = INT_MIN, mini = INT_MAX;

    fl(i, n)
    {
        cin >> v[i];
    }

    vector<int> sizes;
    int currsize = 0;

    for (int i = 0; i < n; i++)
    {
        maxi = max(maxi, v[i]);
        mini = min(mini, v[i]);

        if ((2 * mini) <= maxi)
        {
            sizes.push_back(currsize);
            currsize = 1;
            mini = v[i];
            maxi = v[i];
        }
        else
        {
            currsize++;
        }
    }

    sizes.push_back(currsize);

    for (auto i : sizes)
    {
        if (i > 1)
        {
            py;
            return;
        }
    }

    pn;
}

void sol17()
{
    int n;
    cin >> n;

    vector<pll> v(n);
    ll maxi = 0;
    fl(i, n)
    {
        cin >> v[i].first >> v[i].second;
        maxi = max(maxi, v[i].second);
    }

    int len = maxi + 2;
    vector<int> freq(len, 0), prefsum(len, 0);

    fl(i, n)
    {
        ll diff = v[i].second - v[i].first + 1;
        if (diff == 1)
        {
            freq[v[i].first]++;
        }
    }

    for (int i = 1; i < len; i++)
    {
        prefsum[i] = (freq[i] >= 1) + prefsum[i - 1];
    }

    for (auto i : v)
    {
        ll diff = i.second - i.first + 1;
        if (diff == 1)
        {
            if (freq[i.first] == 1)
            {
                cout << 1;
            }
            else
            {
                cout << 0;
            }
        }
        else
        {
            ll l = i.first, r = i.second;
            bool p = false;
            ll sum = prefsum[r] - prefsum[l - 1];

            if (sum < (r - l + 1))
            {
                cout << 1;
            }
            else
            {
                cout << 0;
            }
        }
    }

    cout << endl;
}

ll recur(ll l, ll r, ll k)
{
    ll m = (l + r) / 2;
    ll length = (r - l + 1);

    if (length < k)
    {
        return 0ll;
    }

    ll res = 0ll;

    if (length % 2 == 0)
    {
        res += recur(l, m, k) + recur(m + 1, r, k);
    }
    else
    {
        res += m;
        if (l != r)
        {
            res += recur(l, m - 1, k) + recur(m + 1, r, k);
        }
    }

    return res;
}

void sol18()
{
    ll n, k;
    cin >> n >> k;
    ll mul = n + 1, sum = 0, cur = 1;
    while (n >= k)
    {
        if (n & 1)
            sum += cur;
        n >>= 1;
        cur <<= 1;
    }
    cout << mul * sum / 2 << endl;
}

// use inverse multiplication => O(nlogn + qlogn)
void sol19()
{
    int n, q;
    cin >> n >> q;

    vector<pll> a(n), b(n);

    fl(i, n)
    {
        cin >> a[i].first;
        a[i].second = i;
    }
    fl(i, n)
    {
        cin >> b[i].first;
        b[i].second = i;
    }

    sort(all(a));
    sort(all(b));

    vector<int> posa(n), posb(n);

    for (int i = 0; i < n; i++)
    {
        posa[a[i].second] = i;
    }

    for (int i = 0; i < n; i++)
    {
        posb[b[i].second] = i;
    }

    vector<pll> queries;

    while (q--)
    {
        ll o, x;
        cin >> o >> x;
        queries.push_back({o, x});
    }

    ll ans = 1;

    for (int t = 0; t < n; t++)
    {
        ans = multiply(ans, min(a[t].first, b[t].first), new_mod);
    }

    cout << ans << " ";

    for (auto query : queries)
    {
        // increment ax by 1
        if (query.first == 1)
        {
            // index in posa
            int ind = posa[query.second - 1];

            int j = ind + 1;
            while (j < n and a[j].first == a[ind].first)
            {
                posa[a[j].second]--;
                j++;
            }

            a[j - 1].first = a[ind].first + 1;
            posa[query.second - 1] = j - 1;
            ll ans = 1;
            for (int t = 0; t < n; t++)
            {
                ans = multiply(ans, min(a[t].first, b[t].first), new_mod);
            }
            cout << ans << " ";
        }
        // increment bx by 1
        else
        {
            // index in posb
            int ind = posb[query.second - 1];
            int j = ind + 1;

            while (j < n and b[j].first == b[ind].first)
            {
                posb[b[j].second]--;
                j++;
            }

            b[j - 1].first = b[ind].first + 1;
            posb[query.second - 1] = j - 1;

            ll ans = 1;
            for (int t = 0; t < n; t++)
            {
                ans = multiply(ans, min(a[t].first, b[t].first), new_mod);
            }

            cout << ans << " ";
        }
        // cout << endl;
        // for (auto i : posa)
        // {
        //     cout << i << " ";
        // }
        // cout << endl;
        // for (auto i : posb)
        // {
        //     cout << i << " ";
        // }
        // cout << endl;
    }

    cout << endl;
}

// https://www.codechef.com/problems/MEXQUER

void sol20()
{
    int n;
    cin >> n;

    vector<ll> v(n);

    fl(i, n)
    {
        cin >> v[i];
    }

    ll required = 0ll;

    for (int i = 0; i < n; i++)
    {
        ll curr = v[i] + required;

        if (v[i] == 0)
        {
            ll val = 1;
            ll num = i;

            while (num >= 0)
            {
                num = (num % 2 == 0) ? num / 2 : (num - 1) / 2;
                if (v[num] > 1)
                {
                    v[num]--;
                    break;
                }
                else
                {
                    val++;
                }
                if (num == 0)
                {
                    val = INT_MAX;
                    break;
                }
            }

            if (val == INT_MAX)
            {
                cout << curr << " ";
                while (i < n)
                {
                    cout << -1 << " ";
                    i++;
                }
                cout << endl;
                return;
            }
            else
            {
                required += val;
            }
        }

        cout << curr << " ";
    }

    cout << required << endl;
}

void sol21()
{
    int n;
    cin >> n;
    vector<vector<ll>> v(n, vector<ll>(n));
}

long long maxAND(int k, vector<int> &arr)
{
    long long ans = 0;
    int n = arr.size();
    vector<ll> st;

    for (int i = 0; i < n; i++)
    {
        ll sum = 0;
        for (int j = i; j < n; j++)
        {
            sum += arr[j];
            st.push_back(sum);
        }
    }

    int sz = (int)st.size();
    vector<bool> vis(sz, false);
    vector<vector<int>> t(40);

    for (int j = 0; j < sz; j++)
    {
        for (int i = 39; i >= 0; i--)
        {
            if (((1LL << i) & st[j]) != 0)
            {
                t[i].push_back(j);
            }
        }
    }

    bool found = false;

    for (int i = 39; i >= 0; i--)
    {
        vector<int> validIndices;

        for (int idx : t[i])
        {
            validIndices.push_back(idx);
        }

        if ((int)validIndices.size() >= k)
        {

            for (int j = i - 1; j >= 0; j--)
            {
                vector<int> vt;

                for (ll idx : validIndices)
                {
                    if (((1LL << j) & st[idx]) != 0)
                    {
                        vt.push_back(idx);
                    }
                }

                if ((int)vt.size() >= k)
                {
                    validIndices = vt;
                }
            }

            int count = 0;
            for (int idx : validIndices)
            {
                if (count == 0)
                {
                    ans = st[idx];
                }
                else
                {
                    ans &= st[idx];
                }
                count++;
                if (count == k)
                    break;
            }

            break;
        }
    }

    return ans;
}

void sol22()
{
    unsigned long long n;
    cin >> n;
    if (n == 1)
    {
        cout << 0 << endl;
        return;
    }

    n--;

    unsigned long long low = 0, high = 1e9, mid, ans;

    while (low <= high)
    {
        mid = (low + high) / 2;
        ll curr = (4 * mid) + (2 * mid * (mid - 1));
        if (curr > n)
        {
            ans = mid;
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
        // cout << mid << " " << curr << endl;
    }

    cout << ans << endl;
}

void sol23()
{
    int n;
    cin >> n;
    int ones = 0, zeros = 0;

    fl(i, n)
    {
        int e;
        cin >> e;
        if (e)
            ones++;
        else
            zeros++;
    }

    if (n % 2 != 0)
    {
        cout << -1 << endl;
        return;
    }
    int diff = abs(ones - zeros);
    if (diff == 0)
    {
        cout << 0 << endl;
    }
    else if (ones < zeros)
    {
        if (ones >= 1)
            cout << diff / 2 << endl;
        else
            cout << -1 << endl;
    }
    else
    {
        ll t = (diff + 3) / 4;
        zeros += t * 2;
        ones -= t * 2;
        if (ones >= 1)
        {
            cout << t + (ones != zeros) << endl;
        }
        else
            cout << -1 << endl;
    }
}

bool checkposs(vector<ll> v, vector<ll> &tocheck)
{
    int n = v.size();
    bool issortedasc = true, issorteddesc = true;

    fl(i, n)
    {
        if (tocheck[i] != v[i])
        {
            issortedasc = false;
            break;
        }
    }

    sort(all(v), greater<>());
    fl(i, n)
    {
        if (tocheck[i] != v[i])
        {
            issorteddesc = false;
            break;
        }
    }

    return (!issortedasc and !issorteddesc);
}

void sol24()
{
    int n;
    cin >> n;

    vector<ll> v(n);

    fl(i, n)
    {
        cin >> v[i];
    }

    sort(all(v));

    ll mindiff = LLONG_MAX;

    vector<ll> ans = {v[n - 1]};
    for (int i = 0; i < n - 1; i++)
    {
        ans.push_back(v[i]);
    }

    ll diff1 = LLONG_MAX, diff2 = LLONG_MAX;
    if (checkposs(v, ans))
    {
        for (int i = 0; i < n - 1; i++)
        {
            diff1 = min(diff1, abs(ans[i + 1] - ans[i]));
        }
    }

    vector<ll> ans2(n);

    for (int i = 0; i < n; i++)
    {
        ans2[i] = v[(i + 1) % n];
    }

    if (checkposs(v, ans2))
    {
        for (int i = 0; i < n - 1; i++)
        {
            diff2 = min(diff2, abs(ans2[i + 1] - ans2[i]));
        }
    }

    mindiff = min(diff1, diff2);

    if (mindiff != LLONG_MAX)
    {
        if (diff1 == mindiff)
            for (auto i : ans)
            {
                cout << i << " ";
            }
        else
            for (auto i : ans2)
            {
                cout << i << " ";
            }
        cout << endl;
    }

    else
    {
        cout << -1 << endl;
    }
}

// https://www.codechef.com/problems/BSTRING

void sol26()
{
    int n;
    cin >> n;

    // int z = 0, o = 0;
    vector<int> ones, zeros;
    string s;
    cin >> s;
    fl(i, n)
    {
        int e = s[i] - '0';

        if (e)
        {
            ones.push_back(i);
        }
        else
        {
            zeros.push_back(i);
        }
    }

    ll ans = (ll)ones.size() + (ll)zeros.size() % mod;

    int o = ones.size(), z = zeros.size();
    ll frontsum = 0ll;

    for (int i = 0; i < o; i++)
    {
        frontsum += power(2, ones[i], mod);
    }

    for (int i = 0; i < o; i++)
    {
        frontsum -= power(2, ones[i], mod);
        ans = add(ans, multiply(frontsum, mul_inverse(power(2, ones[i] + 1, mod)), mod));
    }

    frontsum = 0ll;

    for (int i = 0; i < z; i++)
    {
        frontsum += power(2, zeros[i], mod);
    }

    for (int i = 0; i < z; i++)
    {
        frontsum -= power(2, zeros[i], mod);
        ans = add(ans, multiply(frontsum, mul_inverse(power(2, zeros[i] + 1, mod)), mod));
    }

    cout << ans << endl;
}

void sol27()
{
    int n;
    cin >> n;
    vector<vector<int>> adj(n);

    fl(i, n - 1)
    {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    fl(i, n)
    {
        if (adj[i].size() != (n - 1))
        {
            cout << i + 1 << " ";
            vector<bool> vis(n, false);
            vis[i] = true;
            for (auto neigh : adj[i])
            {
                vis[neigh] = true;
            }
            for (int i = 0; i < n; i++)
            {
                if (!vis[i])
                {
                    cout << i + 1 << endl;
                    return;
                }
            }
        }
    }
}

void sol28()
{
    int n, s, d;
    cin >> n >> s >> d;

    vector<vector<int>> adj(n);

    fl(i, n - 1)
    {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    --s, --d;

    for (auto i : adj[s])
    {
        if (i == d)
        {
            py return;
        }
    }

    pn;
}

void dfs(vector<vector<int>> &adj, vector<int> &numChild, vector<int> &ans, int node = 0)
{
    for (auto i : adj[node])
    {
        ans[i] = numChild[node] > 1;
        dfs(adj, numChild, ans, i);
    }
}

void sol29()
{
    int n;
    cin >> n;
    vector<vector<int>> adj(n);
    vector<int> numChild(n, 0);

    fl(i, n - 1)
    {
        int e;
        cin >> e;
        adj[e - 1].push_back(i + 1);
        numChild[e - 1]++;
    }

    // do dfs traversal

    vector<int> ans(n, 0);
    ans[0] = 1;

    dfs(adj, numChild, ans);

    for (auto i : ans)
    {
        cout << i;
    }
}

int dfs2(vector<vector<int>> &adj, vector<int> &depth, int node, int par)
{
    int maxlen = 0;

    if (depth[node] != -1)
    {
        return depth[node];
    }

    for (auto i : adj[node])
    {
        if (i != par)
        {
            maxlen = max(maxlen, dfs2(adj, depth, i, node));
        }
    }

    return depth[node] = 1 + maxlen;
}

void sol30()
{
    int n;
    cin >> n;
    vector<vector<int>> adj(n);
    vector<int> degress(n, 0);
    vector<ll> values;

    fl(i, n - 1)
    {
        ll u, v, w;
        cin >> u >> v >> w;
        --u, --v;
        values.push_back(w);
        adj[u].push_back(v);
        adj[v].push_back(u);
        degress[u]++;
        degress[v]++;
    }

    vector<int> depth(n, -1);

    fl(i, n)
    {
        if (degress[i] == 1)
        {
            dfs2(adj, depth, i, -1);
        }
    }

    int diameter = *max_element(all(depth)) - 1;

    vector<ll> positives, negs;

    for (auto i : values)
    {
        if (i > 0)
            positives.push_back(i);
        else
            negs.push_back(i);
    }

    sort(all(positives), greater<>());
    sort(all(negs), greater<>());

    int p1 = 0, p2 = 0;
    ll sum = 0;

    int ptr = 0;
    ll maxsum = LLONG_MIN;

    while (ptr < diameter and p1 < positives.size())
    {
        sum += positives[p1++];
        maxsum = max(maxsum, sum);
        ptr++;
        if (ptr + 1 < diameter and p2 < negs.size())
        {
            sum += negs[p2++];
            maxsum = max(maxsum, sum);
        }

        ptr++;
    }

    cout << maxsum << endl;
}

void sol31()
{
    ll n, y;
    cin >> n >> y;
    ll val = 0;

    fl(i, n)
    {
        ll v;
        cin >> v;
        val |= v;
    }

    ll res = 0;

    if (val > y)
    {
        cout << -1 << endl;
        return;
    }

    else
    {
        for (int i = 40; i >= 0; i--)
        {
            bool b1 = ((1 << i) & val) != 0;
            bool b2 = ((1 << i) & y) != 0;

            if (b1 and !b2)
            {
                cout << -1 << endl;
                return;
            }
            else if (!b1 and b2)
            {
                res |= (1 << i);
            }
        }

        cout << res << endl;
    }
}

void sol32()
{
    ll x, y;
    cin >> x >> y;

    ll ans = x * 1ll * y;
    ans += (ll)(-x - y);
    if (ans == -1)
        ans = max(x, y) - 1;
    if (ans == 0)
        ans = 2;
    cout << ans << endl;
}

void sol33()
{
    int n;
    cin >> n;

    ll xori = 0;
    ll elem;

    fl(i, n)
    {
        cin >> elem;
        xori ^= elem;
    }

    if (xori == 0)
    {
        py;
    }

    else
    {
        if (n % 2 == 1)
        {
            cout << "YES\n";
        }
        else
        {
            cout << "NO\n";
        }
    }
}

const int szdp = 5 * 100004;
ll dp[szdp];

ll dpsolver(int n, vector<ll> &a, int pos)
{
    if (pos == n)
    {
        return 0;
    }
    if (dp[pos] != -1)
    {
        return dp[pos];
    }

    ll ans = INT_MAX;

    for (int i = 1; i <= a[pos]; i++)
    {
        if ((pos + i) > n)
        {
            break;
        }
        ans = min(ans, a[pos] | dpsolver(n, a, pos + i));
    }

    return dp[pos] = ans;
}

void minimumORpath()
{
    int n;
    cin >> n;

    vector<pii> a(n);

    fl(i, n)
    {
        cin >> a[i].first;
        a[i].second = i;
    }

    for (int i = 31; i >= 0; i--)
    {
        if (((1 << i) & a[0].first) != 0)
        {
            continue;
        }

        // take elements which have ith bit as unset
        int maxmove = 0, prev = 0;
        vector<pii> indices;
        bool poss = true;
        for (int j = 0; j < n; j++)
        {
            if (a[j].second > maxmove)
            {
                poss = false;
                break;
            }
            if (((1 << i) & a[j].first) == 0)
            {
                maxmove = max(maxmove, a[j].second + a[j].first);
                indices.push_back(a[j]);
            }
        }

        if (poss)
        {
            a = indices;
        }
        else
        {

            // for (auto q : a)
            // {
            //     cout << q.first << " ";
            // }
            // cout << endl;

            // check rem bits
            // for (int t = i - 1; t >= 0; t--)
            // {
            //     if (((1 << t) & indices[0].first) == 0)
            //     {
            //         continue;
            //     }

            //     int maxmove = 0, prev = 0;
            //     vector<pii> temp;
            //     bool poss = true;

            //     for (int j = 0; j < indices.size(); j++)
            //     {
            //         if (a[j].second > maxmove)
            //         {
            //             poss = false;
            //             break;
            //         }
            //         if (((1 << t) & indices[j].first) == 0)
            //         {
            //             maxmove = max(maxmove, indices[j].second + indices[j].first);
            //             temp.push_back(indices[j]);
            //         }
            //     }
            //     if (poss)
            //     {
            //         indices = temp;
            //     }
            // }

            // ll ans = 0ll;
            // for (auto i : indices)
            // {
            //     ans |= i.first;
            // }

            // cout << ans << endl;
            // return;
        }
    }

    int maxmove = 0, prev = 0;
    bool poss = true;

    ll orval = 0;

    for (int j = 0; j < n; j++)
    {
        if (a[j].second > maxmove)
        {
            cout << -1 << endl;
            return;
        }
        orval |= a[j].first;
        maxmove = max(maxmove, a[j].second + a[j].first);
    }

    cout << orval << endl;
}

void nextSmallerElement()
{
    int n;
    cin >> n;
    vector<int> v(n);
    fl(i, n)
    {
        cin >> v[i];
    }

    stack<pair<int, int>> st;
    st.push({v.back(), n - 1});

    vector<int> nextSmallerElement_index(n, n);

    for (int i = n - 2; i >= 0; i--)
    {
        while (!st.empty())
        {
            auto top = st.top();
            int val = top.first, index = top.second;
            if (v[i] <= val)
            {
                st.pop();
            }
            else
            {
                break;
            }
        }

        if (!st.empty())
        {
            nextSmallerElement_index[i] = st.top().second;
        }

        st.push({v[i], i});
    }

    ll ans = 0;

    int pos = 0;
    for (auto i : nextSmallerElement_index)
    {
        ans += (i - pos);
        pos++;
    }

    cout << ans << endl;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    // precomputeFactorials(factSize, MOD);
    // primes.clear();
    // generatePrimes(1e5);
    // precomputePalindromes();

    // ll t;
    // cin >> t;

    // while (t--)
    nextSmallerElement();

    return 0;
}