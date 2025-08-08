//  https://www.codechef.com/problems/BINMIS

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
ll mod_add(ll a, ll b, ll m = MOD) { return (a + b) % m; }
ll mod_sub(ll a, ll b, ll m = MOD) { return (a - b + m) % m; }
ll mod_mul(ll a, ll b, ll m = MOD) { return (a * b) % m; }
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

// Main Solution Function
void solve()
{
    int n, k;
    cin >> n >> k;

    string s;
    cin >> s;

    // max consective 1s in string s

    int pizzatime = 0;
    string temp = s;

    int j = 0, currmax = 0;

    while (j < n)
    {
        while (j < n and temp[j] == '0')
        {
            j++;
        }
        int curr = 0;
        while (j < n and temp[j] == '1')
        {
            j++;
            curr++;
        }
        pizzatime = max(pizzatime, curr);
    }

    for (int i = 0; i <= n - k; i++)
    {
        int p1 = i - 1, p2 = i + k, currmax = k;

        while (p1 >= 0 and temp[p1] == '1')
        {
            p1--;
            currmax++;
        }
        while (p2 < n and temp[p2] == '1')
        {
            p2++;
            currmax++;
        }
        pizzatime = max(pizzatime, currmax);
    }

    cout << pizzatime << endl;
}

void solve2()
{
    int n;
    cin >> n;

    string s;
    cin >> s;

    if (n % 2 != 0)
    {
        cout << "NO\n";
    }
    else
    {
        int ones = 0, zeros = 0;

        for (auto i : s)
        {
            if (i == '1')
                ones++;
            else
                zeros++;
        }

        int diff = ones - zeros;

        // 1100001111
        // diff = ones - zeros = 6-4 = 2
        // so we need a subarray with n1s-n0s = diff (2)
        // 1100000111
        // diff += (s[i]=='1') ? 2 : -2;

        unordered_map<int, int> mp;
        // subarray with given sum chahiye

        int sum = 0;
        mp[sum] = -1;

        // diff=-2
        // sum = 0

        for (int i = 0; i < n; i++)
        {
            sum += (s[i] == '1') ? 2 : -2;

            int req = sum - diff;

            if (mp.count(req))
            {
                cout << "YES\n";
                cout << mp[req] + 2 << " " << i + 1 << endl;
                return;
            }

            mp[sum] = i;
        }

        cout << "NO\n";
    }
}

// Main Driver
int main()
{
    fast_io;
    int t = 1;
    cin >> t; // Uncomment if there are multiple test cases
    while (t--)
    {
        solve2();
    }
    return 0;
}
