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
const int MOD_ATCODERS = 998244353;

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

void movement()
{
    int n;
    cin >> n;
    vector<ll> v(n);
    input_vector(v);
    int i = 0;

    vector<ll> freq;

    while (i < n)
    {
        ll curr = v[i], len = 0;
        while (i < n and v[i] == curr)
        {
            len++;
            i++;
        }
        freq.push_back(len);
    }

    ll ans = n;

    for (auto i : freq)
    {
        ans = min(ans, n - i);
    }

    cout << ans << endl;
}

void sorting()
{
    int n;
    cin >> n;
    vector<ll> v(n);
    input_vector(v);

    int prev = -1;
    while (true)
    {
        int curr = 0;
        for (int i = 0; i < n - 1; i++)
        {
            if ((i + 1) < n and (v[i] - v[i + 1]) == 1)
            {
                swap(v[i], v[i + 1]);
                curr++;
            }
        }
        if (curr == prev)
        {
            break;
        }
        prev = curr;
    }

    vector<ll> ans(n);

    for (int i = 0; i < n; i++)
    {
        if (v[i] != (i + 1))
        {
            cout << "NO\n";
            return;
        }
    }

    cout << "YES\n";
}

void bbq()
{
    int n;
    cin >> n;

    if ((n % 2) == 0)
    {
        int ptr = 1;
        for (int i = 0; i < n; i += 2)
        {
            cout << ptr << " " << ptr << " ";
            ptr++;
        }
        cout << endl;
    }
    else
    {
        cout << -1 << endl;
    }
}

ll rabbithelper(vector<ll> &v, int pos, vector<ll> &dp, vector<bool> &vis,
                ll prevHeight = 0)
{
    ll maxHeight = max(v[pos], prevHeight);

    int n = v.size();
    vis[pos] = true;

    // piche => bada
    for (int i = pos - 1; i >= 0; i--)
    {
        if (v[i] > v[pos] and !vis[i])
        {
            maxHeight = max(maxHeight, rabbithelper(v, i, dp, vis, maxHeight));
        }
    }

    // aage => chota
    for (int i = pos + 1; i < n; i++)
    {
        if (v[i] < v[pos] and !vis[i])
        {
            maxHeight = max(maxHeight, rabbithelper(v, i, dp, vis, maxHeight));
        }
    }

    return dp[pos] = maxHeight;
}

void rabbithops()
{
    int n;
    cin >> n;
    vector<ll> v(n);
    input_vector(v);

    vector<ll> dp(n, -1);
    vector<bool> vis(n, false);

    fl(i, n)
    {
        if (dp[i] == -1)
        {
            rabbithelper(v, i, dp, vis);
        }
    }

    for (auto i : dp)
    {
        cout << i << " ";
    }

    cout << endl;
}

void d1()
{
    int l, r;
    cin >> l >> r;

    unordered_set<int> st;

    for (int i = l; i <= r; i++)
    {
        st.insert(i);
    }

    int oper = 0;
    int a = 0, b = 0, c = 0;

    while (true)
    {
        a = 0, b = 0, c = 0;
        bool f = false;

        for (auto i : st)
        {
            if (f)
            {
                break;
            }
            for (auto j : st)
            {
                if (i == j)
                {
                    continue;
                }
                if (__gcd(i, j) == 1)
                {
                    a = i, b = j;
                    f = true;
                    break;
                }
            }
        }

        if (f)
        {
            st.erase(a);
            st.erase(b);

            for (auto i : st)
            {
                if (__gcd(i, a) == 1 and __gcd(i, b) == 1)
                {
                    c = i;
                    break;
                }
            }

            if ((c != 0))
            {
                st.erase(c);
                oper++;
            }
            else
            {
                break;
            }
        }
        else
        {
            break;
        }
    }

    cout << oper << endl;
}

void rash1()
{
    int n;
    cin >> n;
    string s;
    cin >> s;

    // finally s = 000...00 , t = 111.1..1

    int grps = 0;
    int i = 0;

    while (i < n)
    {
        while (i < n and s[i] == '0')
        {
            i++;
        }

        if (i < n)
        {
            grps++;
            while (i < n and s[i] == '1')
            {
                i++;
            }
        }
    }

    int ans = grps;

    if (grps != 0)
    {
        ans += (grps - 1);
        ans += (s[n - 1] == '0');
    }

    cout << ans << endl;
}

void rash2()
{
    int n;
    cin >> n;
    vector<ll> v(n);
    input_vector(v);

    vector<ll> freq(n + 1, 0);

    for (auto i : v)
    {
        freq[i]++;
    }

    ll maxlen = 0;
    int l = -1, r = -1;

    int i = 0;

    while (i < n)
    {
        while (i < n and freq[v[i]] != 1)
        {
            i++;
        }

        ll len = 0;
        ll currl = i;

        while (i < n and freq[v[i]] == 1)
        {
            i++;
            len++;
        }

        if (len > maxlen)
        {
            l = currl, r = i - 1;
            maxlen = len;
        }
    }

    if (l != -1)
    {
        cout << l + 1 << " " << r + 1 << endl;
    }
    else
    {
        cout << 0 << endl;
    }
}

void rash3()
{
    int n;
    cin >> n;
    vector<ll> v(n);
    input_vector(v);

    int i = 0;
    ll maxsum = 0, currsum = 0;

    while (i < n and (v[i] < 0))
    {
        currsum += abs(v[i]);
        i++;
    }

    maxsum = max(currsum, maxsum);

    vector<ll> posSum, negSum;

    while (i < n)
    {
        ll sum1 = 0, sum2 = 0;

        while (i < n and v[i] >= 0)
        {
            sum1 += v[i];
            i++;
        }
        posSum.push_back(sum1);

        while (i < n and v[i] < 0)
        {
            sum2 += abs(v[i]);
            i++;
        }
        negSum.push_back(sum2);

        maxsum = max(maxsum, sum1 + sum2);
    }

    int negptr = 0;

    ll possum = 0;

    for (auto i : posSum)
    {
        possum += i;
        maxsum = max(maxsum, possum + negSum[negptr++]);
    }

    negptr = 0;

    ll sum = 0;
    reverse(all(negSum));
    reverse(all(posSum));

    for (auto i : negSum)
    {
        sum += i;
        maxsum = max(maxsum, sum + posSum[negptr++]);
    }

    cout << maxsum << endl;
}

void sol1()
{
    int n;
    cin >> n;
    vector<ll> v(n - 2);
    input_vector(v);

    vector<ll> a(n);
    vector<bool> marked(n, false);
    a[0] = 1;

    for (int i = 1; i < n - 1; i++)
    {
        if (v[i - 1] == 1)
        {
            if (i != 1 and marked[i] and a[i] != a[i - 1])
            {
                na
            }
            a[i] = a[i - 1];
            if (i != 1 and marked[i + 1] and a[i + 1] != a[i])
            {
                na
            }
            a[i + 1] = a[i];
            marked[i + 1] = true;
        }
        else
        {
            if (i != 1 and marked[i] and a[i] == a[i - 1])
            {
                if (i != 1 and marked[i + 1] and a[i + 1] == a[i])
                {
                    na
                }
                else
                {
                    a[i + 1] = !a[i];
                    marked[i + 1] = true;
                }
            }
            else
            {
                a[i] = !a[i - 1];
            }
        }
        marked[i] = true;
    }

    ha
}

vector<int> dx = {0, 0, 1, -1};
vector<int> dy = {1, -1, 0, 0};

int getsize(int n, int m, vector<vector<int>> &grid, int x, int y, vector<vector<bool>> &vis)
{
    int sz = 0;
    queue<pair<int, int>> q;
    int currcolor = grid[x][y];

    q.push({x, y});
    vis[x][y] = true;

    while (!q.empty())
    {
        auto fr = q.front();
        int cx = fr.first, cy = fr.second;
        q.pop();

        sz++;

        for (int i = 0; i < 4; i++)
        {
            int newx = cx + dx[i], newy = cy + dy[i];
            if (newx >= 0 && newx < n && newy >= 0 && newy < m &&
                grid[newx][newy] == currcolor && !vis[newx][newy])
            {
                vis[newx][newy] = true;
                q.push({newx, newy});
            }
        }
    }

    return sz;
}

void sol2()
{
    int n, m;
    cin >> n >> m;

    if (n == 0 || m == 0)
    {
        cout << 0 << endl;
        return;
    }

    vector<vector<int>> grid(n, vector<int>(m));
    unordered_map<int, long long> mp;
    vector<vector<bool>> vis(n, vector<bool>(m, false));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> grid[i][j];
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (!vis[i][j])
            {
                long long val = getsize(n, m, grid, i, j, vis);
                val = min(2ll, val);
                mp[grid[i][j]] = max(mp[grid[i][j]], val);
            }
        }
    }

    vector<long long> comp;
    for (auto &i : mp)
    {
        comp.push_back(i.second);
    }

    long long minoper = LLONG_MAX;
    long long total = accumulate(comp.begin(), comp.end(), 0LL);

    for (auto i : comp)
    {
        minoper = min(minoper, total - i);
    }

    cout << minoper << endl;
}

void sol3()
{
    int n;
    cin >> n;

    vector<ll> v(n);
    input_vector(v);

    ll ans = 0;
    ll waitingCount = 0;
    ll waitingSum = 0;

    for (int i = 0; i < n; i++)
    {
        if (v[i] == 1)
        {
            waitingCount = (waitingCount + 1) % MOD_ATCODERS;
            waitingSum = (waitingSum + 1) % MOD_ATCODERS;
        }
        else if (v[i] == 2)
        {
            waitingSum = (waitingSum * 2) % MOD_ATCODERS;
        }
        else if (v[i] == 3)
        {
            ans = (ans + (waitingSum - waitingCount + MOD_ATCODERS) % MOD_ATCODERS) % MOD_ATCODERS;
        }
    }

    cout << ans << endl;
}

bool isposs(const string &s, int mid)
{
    int n = s.size();
    if (mid > n)
        return false;

    // 1. Precompute prefix frequency table for s.
    //    pref[i][c] = count of letter c in s[0..i-1]
    vector<vector<int>> pref(n + 1, vector<int>(26, 0));

    for (int i = 0; i < n; i++)
    {
        pref[i + 1] = pref[i];
        pref[i + 1][s[i] - 'a']++;
    }

    // 2. Precompute prefix maximum for mismatched pairs in the first half.
    // For each i in [0, floor((n-1)/2)], if s[i]!=s[n-i-1] then note req = n-i-1.
    int half = n / 2;                         // floor(n/2)
    vector<int> prefixMismatch(half + 1, -1); // prefixMismatch[k] = max { n-i-1 for i in [0, k-1] with mismatch }
    for (int i = 0; i < half; i++)
    {
        int req = (s[i] != s[n - i - 1]) ? (n - i - 1) : -1;
        prefixMismatch[i + 1] = max(prefixMismatch[i], req);
    }

    // 3. We now try every window [L, R] of length mid (with R = L+mid-1).
    // For a window to be valid, two conditions must hold:
    // (A) For every i with i < L and s[i] != s[n-i-1], we must have n-i-1 <= R.
    //     In other words, prefixMismatch[min(L, half)] <= R.
    // (B) For every index j outside [L,R] whose mirror falls inside [L,R],
    //     the letter s[j] must be available in the window.
    //
    //     These “crossing” positions occur in two parts:
    //       - Left part: indices j in [X, L-1] where the mirror index = n-j-1 lies in [L,R].
    //         Since n-j-1 ∈ [L,R] is equivalent to j ∈ [n-R-1, n-L-1],
    //         the effective interval is I1 = [max(0, n-R-1), L-1].
    //       - Right part: indices j in [R+1, Y] where n-j-1 ∈ [L,R].
    //         This is j ∈ [max(R+1, n-R-1), min(n-1, n-L-1)].

    for (int L = 0; L <= n - mid; L++)
    {
        int R = L + mid - 1;

        // Condition (A):
        int mm = (L <= half ? prefixMismatch[L] : prefixMismatch[half]);
        if (mm > R)
            continue; // found a mismatched pair completely outside the window

        // Condition (B): Compute required letter counts from positions outside [L,R] whose mirror is inside.
        vector<int> reqCount(26, 0);
        // Left side: j in I1 = [max(0, n-R-1), L-1]
        int L1 = max(0, n - R - 1);
        int R1 = L - 1;
        if (L1 <= R1)
        {
            for (int c = 0; c < 26; c++)
            {
                reqCount[c] += pref[R1 + 1][c] - pref[L1][c];
            }
        }
        // Right side: j in I2 = [max(R+1, n-R-1), min(n-1, n-L-1)]
        int L2 = max(R + 1, n - R - 1);
        int R2 = min(n - 1, n - L - 1);
        if (L2 <= R2)
        {
            for (int c = 0; c < 26; c++)
            {
                reqCount[c] += pref[R2 + 1][c] - pref[L2][c];
            }
        }

        // Get window frequency (letters available to “fix” crossing pairs).
        bool ok = true;
        for (int c = 0; c < 26; c++)
        {
            int windowFreq = pref[R + 1][c] - pref[L][c];
            if (windowFreq < reqCount[c])
            {
                ok = false;
                break;
            }
        }
        if (ok)
            return true;
    }

    return false;
}

void sol4()
{
    string s;
    cin >> s;
    int n = s.size();
    int l = 0, r = n, mid, ans = -1;

    // always even ans possible

    while (l <= r)
    {
        mid = (l + r) / 2;
        if (isposs(s, mid))
        {
            ans = mid;
            r = mid - 1;
        }
        else
        {
            l = mid + 1;
        }
    }

    cout << ans << endl;
}

void help1()
{
    ll n, x, y;
    cin >> n >> x >> y;

    vector<ll> a(n), b(n);

    input_vector(a);
    input_vector(b);

    vector<pll> diffab;

    fl(i, n)
    {
        diffab.push_back({a[i] - b[i], i});
    }

    sort(all(diffab), greater<>());

    ll maxi = 0ll;

    int i = 0;

    for (; i < min(x, n); i++)
    {
        ll val = a[diffab[i].second];
        if (val <= 0)
        {
            i--;
            break;
        }
        maxi += val;
    }

    for (; i < n; i++)
    {
        maxi += b[diffab[i].second];
    }

    sort(all(diffab));

    ll maxi2 = 0ll;

    // i = 0;

    // for (; i < min(y, n); i++)
    // {
    //     ll val = b[diffab[i].second];
    //     if (val >= 0)
    //     {
    //         i--;
    //         break;
    //     }
    //     maxi2 += val;
    // }

    // for (; i < n; i++)
    // {
    //     maxi2 += a[diffab[i].second];
    // }

    ll ans = max(maxi, maxi2);

    cout << ans << endl;
}

void sol5()
{
}

int main()
{
    fast_io;

    int t = 1;
    // cin >> t;

    while (t--)
    {
        help1();
    }

    return 0;
}
