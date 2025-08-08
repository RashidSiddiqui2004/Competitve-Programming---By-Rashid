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
const ll MOD_UNCONVENTIONAL = 998244353;

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

vector<int> sieve(int n)
{
    vector<int> primes;
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

#define yes cout << "YES\n";
#define no cout << "NO\n";

struct myComp
{
    bool operator()(const pair<int, pii> &a, const pair<int, pii> &b)
    {
        // Sort by first value in descending order
        if (a.first != b.first)
            return a.first < b.first;
        // If first values are equal, sort by first value of second element in ascending order priority_queue<pair<int, pii>, vector<pair<int, pii>>, myComp> pq;
        return a.second.first > b.second.first;
    }
};

void sol1()
{
    int s;
    cin >> s;
    if (s >= 200 and s <= 299)
    {
        cout << "Success";
    }
    else
    {
        cout << "Failure";
    }
}

void sol2()
{
    int n;
    cin >> n;
    string s;
    int ans = 0;
    bool login = false;
    while (n--)
    {
        cin >> s;
        if (s == "login")
        {
            login = true;
        }
        else if (s == "logout")
        {
            login = false;
        }
        else if (s == "public")
        {
        }
        else
        {
            if (!login)
            {
                ans++;
            }
        }
    }

    cout << ans << endl;
}

void sol3()
{
    int n, k;
    cin >> n >> k;

    vector<ll> A(n + 1, 0);

    for (int i = 0; i < min(n + 1, k); i++)
    {
        A[i] = 1;
    }

    ll prevsum = 0ll;

    for (int i = 0; i < k; i++)
    {
        prevsum = (prevsum + A[i]) % MOD;
    }

    for (int i = k; i <= n; i++)
    {
        A[i] = prevsum % MOD;
        prevsum = (prevsum + A[i] - A[i - k] + MOD) % MOD;
    }

    cout << A[n] << "\n";
}

const int NEG_INF = -1000000000;

void sol4()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    string s;
    cin >> s;
 
    int fixed_o = 0;
    for (char c : s)
        if (c == 'o')
            fixed_o++;
 
    int rem = k - fixed_o;

    // Precompute dp0 and dp1 arrays.
    // dp0[i]: maximum additional o's we can place from i to n-1 if the previous cell is NOT an o.
    // dp1[i]: same if the previous cell IS an o (in which case we are forced to place '.').
    vector<int> dp0(n + 1, 0), dp1(n + 1, 0);
    // Base case:
    dp0[n] = 0;
    dp1[n] = 0;

    for (int i = n - 1; i >= 0; i--)
    {
        char c = s[i];
        if (c == 'o')
        {
            // Fixed 'o' is allowed only if the previous cell was not an o.
            dp0[i] = 1 + dp1[i + 1];
            dp1[i] = NEG_INF; // if previous was o, a fixed 'o' makes it invalid.
        }
        else if (c == '.')
        {
            // Fixed dot: just continue.
            dp0[i] = dp0[i + 1];
            dp1[i] = dp0[i + 1];
        }
        else
        { // c == '?'
            // When free, we choose the maximum option (and here we don’t force a particular number, just the maximum possible)
            dp0[i] = max(dp0[i + 1], 1 + dp1[i + 1]);
            // If previous was o then we cannot choose an 'o', so only dot is allowed.
            dp1[i] = dp0[i + 1];
        }
    }

    // --- Greedy construction of lexicographically smallest completion (A) ---
    string A = s;
    int currR = rem; // o's still needed to assign.
    int state = 0;   // 0 => last output was not an o; 1 => last output was an o.
    // We'll simulate the assignment in a left-to-right pass.
    for (int i = 0; i < n; i++)
    {
        if (s[i] == 'o' || s[i] == '.')
        {
            // Fixed letters; update state accordingly.
            A[i] = s[i];
            state = (s[i] == 'o' ? 1 : 0);
        }
        else
        { // s[i] == '?'
            if (state == 1)
            {
                // We cannot place an o because the previous character is 'o'.
                A[i] = '.';
                state = 0;
            }
            else
            {
                // state==0 => we are allowed to place an o.
                // For lexicographically smallest solution we try dot first.
                // We check if it is possible to complete the rest with currR o's if we place a dot here.
                // (The dp array is computed assuming the state is 0.)
                if (currR == 0)
                {
                    // No more o's needed.
                    A[i] = '.';
                    state = 0;
                }
                else
                {
                    // If leaving a dot is sufficient, i.e. if currR <= dp0[i+1] then we choose dot.
                    if (currR <= dp0[i + 1])
                    {
                        A[i] = '.';
                        state = 0;
                    }
                    else
                    {
                        // Otherwise we must put an o.
                        A[i] = 'o';
                        currR--;
                        state = 1;
                    }
                }
            }
        }
    }

    // --- Greedy construction of lexicographically largest completion (B) ---
    string B = s;
    currR = rem;
    state = 0;
    // For lex largest, we try to use an o (the larger letter) whenever it is “safely” feasible.
    for (int i = 0; i < n; i++)
    {
        if (s[i] == 'o' || s[i] == '.')
        {
            B[i] = s[i];
            state = (s[i] == 'o' ? 1 : 0);
        }
        else
        { // s[i] == '?'
            if (state == 1)
            {
                B[i] = '.';
                state = 0;
            }
            else
            {
                if (currR == 0)
                {
                    B[i] = '.';
                    state = 0;
                }
                else
                {
                    // Here, try to assign an o if it is safe.
                    // When we assign an o in state 0, the new state becomes 1.
                    // We can assign an o if the remainder (currR - 1) can be placed from i+1 assuming state = 1.
                    if (currR > 0 && (currR - 1) <= dp1[i + 1])
                    {
                        B[i] = 'o';
                        currR--;
                        state = 1;
                    }
                    else
                    {
                        B[i] = '.';
                        state = 0;
                    }
                }
            }
        }
    }

    // --- Combine A and B into final answer T ---
    // For every position, if both completions agree then that letter is forced; if not, output '?'.
    string T;
    T.resize(n);
    for (int i = 0; i < n; i++)
    {
        if (A[i] == B[i])
            T[i] = A[i];
        else
            T[i] = '?';
    }

    cout << T << "\n";
}

int main()
{
    fast_io;
    int t = 1;
    // cin >> t;

    while (t--)
    {
        sol4();
    }

    return 0;
}