
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using lld = long double;
using ull = unsigned long long;

// Constants
const ll INF = LONG_LONG_MAX;
const ll mod = 1e9 + 7;

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
#define loop(i, n) for (int i = 0; i < n; i++)
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

template <class T>
void print(const T &t)
{
    print_single(t);
}

template <class T, class... Args>
void print(const T &t, const Args &...args)
{
    print_single(t, 2);
    print(args...);
}

string readString()
{
    string s;
    cin >> s;
    return s;
}

void printarr(vector<int> &a)
{
    for (auto i : a)
    {
        cout << i << " ";
    }
    cout << endl;
}

// read unweighted undirected/directed graph
vector<vector<ll>>
readUnWeightedGraph(int n, int m, bool isDirected = true)
{
    vector<vector<ll>> g(n);
    fl(i, m)
    {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        g[a].pb(b);
        if (isDirected == false)
            g[b].pb(a);
    }
    return g;
}
// read weighted undirected/directed graph
vector<vector<pll>> readWeightedGraph(int n, int m, bool isDirected = true)
{
    vector<vector<pll>> g(n);
    fl(i, m)
    {
        ll a, b, w;
        cin >> a >> b >> w;
        a--;
        b--;
        g[a].pb({b, w});
        if (isDirected == false)
            g[b].pb({a, w});
    }
    return g;
}

#define khalaas return 0;
#define in1(t) \
    int t;     \
    cin >> t;
#define in2(a, b) \
    int a, b;     \
    cin >> a >> b
#define in3(a, b, c) \
    int a, b, c;     \
    cin >> a >> b >> c
#define in4(a, b, c, d) \
    int a, b, c, d;     \
    cin >> a >> b >> c >> d
#define in5(a, b, c, d, e) \
    ll a, b, c, d, e;      \
    cin >> a >> b >> c >> d >> e
#define in6(a, b, c, d, e, f) \
    ll a, b, c, d, e, f;      \
    cin >> a >> b >> c >> d >> e >> f

#define vecin(v, n) \
    vector<ll> v;   \
    loop(i, 0, n)   \
    {               \
        in1(x);     \
        v.pb(x);    \
    }

typedef priority_queue<int> pq;

typedef unordered_map<char, int> ump;

typedef unordered_set<ll> ust;

typedef priority_queue<int, vector<int>, greater<int>> minh;

typedef priority_queue<int> maxh;

#define TEST   \
    int t = 1; \
    cin >> t;  \
    while (t--)

#define QUERY \
    int q;    \
    cin >> q; \
    while (q--)

#define prec(n) fixed << setprecision(n)

int mod_add(int a, int b, int m)
{
    a %= m;
    b %= m;
    return ((a + b) % m);
}
int mod_sub(int a, int b, int m)
{
    a %= m;
    b %= m;
    return ((a - b) % m);
}
int mod_mul(int a, int b, int m)
{
    a %= m;
    b %= m;
    return ((a * b) % m);
}

// it returns the logarithm of n to the base k
// @param(long long n) the value
// @param(long long k) the base for the logarithm
int lognk(ll n, ll k)
{
    int ans = 0;
    if (k == 1)
    {
        // Logarithm base 1 is undefined, return special value
        return n - 1; // Subtracting one repeatedly in this case
    }

    int currnum = 1;
    while ((currnum * k) <= n)
    {
        if (currnum > n / k) // Prevent multiplication overflow
            break;
        currnum *= k;
        ans++;
    }
    return ans;
}

const ll M = mod;

unsigned long long powerOptimum(unsigned long long x,
                                int y, int p = M)
{
    unsigned long long res = 1;

    x = x % p; // Update x if it is more than or
    // equal to p

    while (y > 0)
    {

        // If y is odd, multiply x with result
        if (y & 1)
            res = (res * x) % p;

        // y must be even now
        y = y >> 1; // y = y/2
        x = (x * x) % p;
    }
    return res;
}

ll modInverse(ll A)
{
    return (powerOptimum(A, M - 2));
}

unsigned long long factdp[200000 + 1];

ll nCr(ll n, ll r)
{
    ll x = factdp[n - r];
    x = modInverse(x);

    n = factdp[n];
    r = factdp[r];
    r = modInverse(r);

    ll ans = (n * r) % M;
    ans *= x;
    ans %= M;

    return ans;
}

void factorialCalculation()
{
    memset(factdp, -1, sizeof(factdp));
    factdp[0] = 1;
    for (int i = 1; i <= 200000; i++)
        factdp[i] = (factdp[i - 1] * i) % mod;
}

void frogs()
{
    int n, a, b;
    cin >> n >> a >> b;

    int diff = abs(a - b);

    if (diff % 2 == 0)
    {
        cout << "YES\n";
    }
    else
    {
        cout << "NO\n";
    }
}

string craftingDebug(std::ifstream &inFile, std::ofstream &outFile)
{
    int n;
    inFile >> n;

    vector<ll> a(n), b(n);

    fl(i, n)
    {
        inFile >> a[i];
    }

    fl(j, n)
    {
        inFile >> b[j];
    }

    bool found = false;

    for (int i = 0; i < n; i++)
    {
        if (a[i] < b[i])
        {
            if (found)
            {
                return "NO";
            }
            else
            {
                found = true;
            }
        }
    }

    if (found == false)
    {
        return "YES";
    }
    else
    {
        bool used = false;
        ll diff = 0;
        for (int i = 0; i < n; i++)
        {
            a[i] -= diff;
            if (a[i] < b[i])
            {
                if (used)
                {
                    return "NO";
                }
                else
                {
                    used = true;
                    a[i] = b[i];
                    diff += abs(b[i] - a[i]);
                }
            }
        }
        return "YES";
    }
}

void crafting()
{
    int n;
    cin >> n;

    vector<ll> a(n), b(n);

    fl(i, n)
    {
        cin >> a[i];
    }

    fl(j, n)
    {
        cin >> b[j];
    }

    bool found = false;
    ll diff = 0;

    for (int i = 0; i < n; i++)
    {
        if (a[i] < b[i])
        {
            if (found)
            {
                cout << "NO\n";
                return;
            }
            else
            {
                found = true;
                diff = b[i] - a[i];
            }
        }
    }

    if (found == false)
    {
        cout << "YES\n";
        return;
    }
    else
    {
        bool used = false;

        for (int i = 0; i < n; i++)
        {
            a[i] -= diff;
            if (a[i] < b[i])
            {
                if (used)
                {
                    cout << "NO\n";
                    return;
                }
                else
                {
                    used = true;
                    a[i] = b[i];
                }
            }
        }
        cout << "YES\n";
        return;
    }
}

// for debugging with input use file input
// infile, outfile
// then check result with a result file

void trailing()
{
    ll n, k;
    cin >> n >> k;

    ll q = n / k;
    ll given = q * 1ll * k;

    ll rem = n - given;
    ll maxgive = min(k / 2, rem);

    given += maxgive;
    cout << given << endl;
}

void gifts()
{
    int n;
    cin >> n;

    vector<int> arr(n);
    vector<bool> mark(n, false);

    fl(i, n)
    {
        cin >> arr[i];
        if (arr[i] != 0)
            mark[arr[i] - 1] = true;
    }

    deque<int> rem;

    fl(i, n)
    {
        if (mark[i] == 0)
        {
            rem.push_back(i + 1);
        }
    }

    deque<int> temp;
    vector<int> temparr;

    do
    {
        temp = rem;
        temparr.clear();
        temparr.assign(arr.begin(), arr.end());

        int first = temp.front();
        temp.pop_front();
        temp.push_back(first);

        bool isposs = true;

        fl(i, n)
        {
            if (temparr[i] == 0)
            {
                if ((i + 1) == temp.front())
                {
                    isposs = false;
                    break;
                }
                temparr[i] = temp.front();
                temp.pop_front();
            }
        }

        if (isposs)
        {
            break;
        }

    } while ((next_permutation(rem.begin(), rem.end())));

    for (auto i : temparr)
    {
        cout << i << " ";
    }

    cout << endl;
}

signed main()
{
    bool debugMode = false;

    if (debugMode)
    {
        // File paths
        std::string inputFilePath = "input.txt";
        std::string outputFilePath = "output.txt";
        std::string answerFilePath = "answer.txt";

        // Open file streams
        std::ifstream inFile(inputFilePath);
        std::ofstream outFile(outputFilePath);
        std::ifstream ansFile(answerFilePath);

        if (!inFile.is_open() || !outFile.is_open() || !ansFile.is_open())
        {
            cerr << "Error: Failed to open one or more files.\n";
            return 1;
        }

        ll t;
        inFile >> t;
        for (int i = 1; i <= t; i++)
        {
            auto result = craftingDebug(inFile, outFile);
            string ans;
            ansFile >> ans;
            if (result != ans)
            {
                cout << ans << result << endl;
                outFile << "Test failed on test case - " << i << endl;
                return 0;
            }
            else
            {
                outFile << "Test case " << i << " passed " << endl;
            }
        }

        cout << "Success:) All test cases passed..\n\n";

        inFile.close();
        outFile.close();
        ansFile.close();

        cout << "Processing complete. Results written to: " << outputFilePath << endl;
    }
    else
    {
        // ll t;
        // cin >> t;
        // while (t--)
        gifts();
    }

    khalaas
}