
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

// TypeDEf
typedef pair<ll, ll> pll;
typedef vector<ll> vll;
typedef vector<pll> vpll;
typedef vector<string> vs;
typedef unordered_map<ll, ll> umll;
typedef map<ll, ll> mll;

vector<int> primes;
const long long int MOD = 1e9 + 7;

void generatePrimes(int n)
{
    vector<bool> isPrime(n + 1, true);
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

    for (int i = 2; i <= n; ++i)
    {
        if (isPrime[i])
        {
            primes.push_back(i);
        }
    }
}

void h1()
{
    int sz = primes.size();
    vector<ll> pows(sz);

    int n, m;
    cin >> n >> m;

    vector<ll> v(n);

    for (int i = 0; i < n; ++i)
    {
        cin >> v[i];
    }

    for (int i = 1; i <= m; i++)
    {
        for (int j = 0; j < sz; j++)
        {
            int pw = 0;
            while ((i != 0) and (i % primes[j]) == 0)
            {
                i /= primes[j];
                pw++;
            }
            pows[j] += pw;
        }
    }

    for (auto num : v)
    {
        vector<ll> pws = pows;
        for (int i = 0; i < primes.size(); i++)
        {
            int pw = 0;
            while ((num != 0) and (num % primes[i]) == 0)
            {
                num /= primes[i];
                pw++;
            }
            pows[i] += pw;
        }
        ll res = 1;
        for (int i = 0; i < sz; i++)
        {
            res = (res * 1ll * (pows[i])) % mod;
        }

        cout << res << " ";
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, m;
    cin >> n >> m;

    primes.clear();
    generatePrimes(1e5 + 3);

    int sz = primes.size();
    vector<ll> pows(sz, 0);
    vector<ll> v(n);

    for (int i = 0; i < n; ++i)
    {
        cin >> v[i];
    }

    int maxpos = 0;
    for (int i = 2; i <= m; i++)
    {
        ll temp = i;
        int ub = upper_bound(primes.begin(), primes.end(), sqrt(i)) - primes.begin();
        maxpos = max(maxpos, ub);
        for (int j = 0; j < min((int)(ub + 20), (int)sz); j++)
        {
            ll pw = 0;
            while ((temp != 0) && (temp % primes[j]) == 0)
            {
                temp /= primes[j];
                pw++;
            }
            pows[j] += pw;
        }
    }

    for (auto num : v)
    {
        vector<ll> temp_pows = pows;
        ll res = 1ll;

        ll temp = num;

        int ub = upper_bound(primes.begin(), primes.end(), sqrt(temp)) - primes.begin();

        for (int i = 0; i < min((int)sz, max((int)maxpos, (int)(ub + 20))); i++)
        {
            ll pw = 0;
            while ((temp != 0) && (temp % primes[i]) == 0)
            {
                temp /= primes[i];
                pw++;
            }
            temp_pows[i] += pw;
            res = (res * 1ll * (temp_pows[i] + 1)) % mod;
        }

        res = res % mod;

        cout << res << " ";
    }

    return 0;
}