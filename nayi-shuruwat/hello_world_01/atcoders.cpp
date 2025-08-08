
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

bool check1(int num)
{
    bool check = true;
    string rs = to_string(num);
    for (int i = 1; i < rs.size(); i++)
    {
        if (rs[i] >= rs[0])
        {
            check = false;
            break;
        }
    }

    return check;
}

void sol1()
{
    ll ans = 0;

    ll x;
    cin >> x;

    for (int i = 1; i <= 9; i++)
    {
        for (int j = 1; j <= 9; j++)
        {
            ll sum = i * j;
            if (sum != x)
            {
                ans += sum;
            }
        }
    }
    cout << ans << endl;
}

ll solve(int len)
{
    ll sum = 0;

    for (int i = 1; i <= 9; i++)
    {
        sum += 1ll * pow(i, len - 1);
    }

    return sum;
}

ll solve2gr(string curr)
{
    ll res = 0;
    int len = curr.size();
    int rem = curr[0] - '0';

    for (int i = rem + 1; i < 10; i++)
    {
        res += pow(i, len - 1);
    }

    for (int i = 1; i < len; i++)
    {
        int currdig = curr[i] - '0';
        int remlen = len - i - 1;
        for (int j = currdig + 1; j < rem; j++)
        {
            res += pow(rem, remlen);
        }
        if (currdig >= rem)
        {
            break;
        }
    }

    return res;
}

ll solve2ls(string curr)
{
    ll res = 0;

    int len = curr.size();
    int rem = curr[0] - '0';

    for (int i = 1; i < rem; i++)
    {
        res += pow(i, len - 1);
    }

    for (int i = 1; i < len - 1; i++)
    {
        int currdig = curr[i] - '0';
        int remlen = len - i - 1;
        for (int j = 0; j < min(currdig, rem); j++)
        {
            res += pow(rem, remlen);
        }
        if (currdig >= rem)
        {
            return res;
        }
    }

    int currdig = curr[len - 1] - '0';
    int remlen = 0;
    for (int j = 0; j <= min(currdig, rem); j++)
    {
        res += pow(rem, remlen);
    }

    return res;
}

void sol2()
{
    ll l, r;
    cin >> l >> r;

    string ls = to_string(l), rs = to_string(r);
    ll res = 0;
    int sz = ls.size();

    for (int len = sz + 1; len <= (int)rs.size() - 1; len++)
    {
        res += solve(len);
    }

    if ((int)ls.size() == (int)rs.size())
    {
        ll x = solve2gr(ls);
        ll y = solve2ls(rs);

        ll total = solve(sz);

        ll p = x + y - total;
        res += p;

        cout << y << endl;

        bool check = true;
        for (int i = 1; i < rs.size(); i++)
        {
            if (rs[i] >= rs[0])
            {
                check = false;
                break;
            }
        }
        if (check)
        {
            res++;
        }

        check = true;
        for (int i = 1; i < ls.size(); i++)
        {
            if (ls[i] >= ls[0])
            {
                check = false;
                break;
            }
        }
        if (check)
        {
            res++;
        }
    }

    else
    {
        res += solve2gr(ls);
        ll total = solve((int)rs.size());

        res += total - solve2gr(rs);

        bool check = true;
        for (int i = 1; i < rs.size(); i++)
        {
            if (rs[i] >= rs[0])
            {
                check = false;
            }
        }

        if (check)
        {
            res++;
        }
    }

    cout << res;
}

void h4()
{
    int n, m;
    cin >> n >> m;

    vector<string> grid(n);

    fl(i, n)
    {
        cin >> grid[i];
    }

    int startx, starty, endx, endy;

    fl(i, n)
    {
        fl(j, m)
        {
            if (grid[i][j] == 'S')
            {
                startx = i;
                starty = j;
            }
            else if (grid[i][j] == 'G')
            {
                endx = i;
                endy = j;
            }
        }
    }

    bool vis[n][m][2];
    memset(vis, false, sizeof(vis));

    vis[startx][starty][0] = 1;
    vis[startx][starty][1] = 1;

    queue<pair<pair<int, int>, int>> q;

    // 0 -> hor, 1-> vert
    if ((starty + 1) < m and grid[startx][starty + 1] != '#')
        q.push({{startx, starty + 1}, 0});
    if ((starty - 1) >= 0 and grid[startx][starty - 1] != '#')
        q.push({{startx, starty - 1}, 0});
    if ((startx + 1) < n and grid[startx + 1][starty] != '#')
        q.push({{startx + 1, starty}, 1});
    if ((startx - 1) >= 0 and grid[startx - 1][starty] != '#')
        q.push({{startx - 1, starty}, 1});

    int dist = 1;

    while (!q.empty())
    {
        int sz = q.size();

        while (sz--)
        {
            auto fr = q.front();
            q.pop();

            int x = fr.first.first, y = fr.first.second, dir = fr.second;

            vis[x][y][dir] = 1;

            if (x == endx and y == endy)
            {
                cout << dist << endl;
                return;
            }

            else
            {
                if (dir == 0)
                {
                    if ((x + 1) < n and grid[x + 1][y] != '#' and !vis[x + 1][y][1])
                    {
                        vis[x + 1][y][1] = 1;
                        q.push({{x + 1, y}, 1});
                    }

                    if ((x - 1) >= 0 and grid[x - 1][y] != '#' and !vis[x - 1][y][1])
                    {
                        vis[x - 1][y][1] = 1;
                        q.push({{x - 1, y}, 1});
                    }
                }
                else
                {
                    if ((y + 1) < m and grid[x][y + 1] != '#' and !vis[x][y + 1][0])
                    {
                        vis[x][y + 1][0] = 1;
                        q.push({{x, y + 1}, 0});
                    }

                    if ((y - 1) >= 0 and grid[x][y - 1] != '#' and !vis[x][y - 1][0])
                    {
                        vis[x][y - 1][0] = 1;
                        q.push({{x, y - 1}, 0});
                    }
                }
            }
        }

        dist++;
    }

    cout << -1 << endl;
}

int goodArray(vector<int> &arr, int k)
{
    unordered_map<int, int> fr;

    for (auto i : arr)
    {
        fr[i]++;
    }

    int ans = 0;

    for (auto i : arr)
    {
        int req = i ^ k;
        fr[i]--;
        if (fr[i] == 0)
        {
            fr.erase(i);
        }

        if (fr.count(req))
        {
            fr[req]--;
            if (fr[req] == 0)
            {
                fr.erase(req);
            }
        }
        else
        {
            ans++;
        }
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    // precomputeFactorials(factSize, mod);
    // primes.clear();
    // generatePrimes(1e5);
    // precomputePalindromes();

    return 0;
}