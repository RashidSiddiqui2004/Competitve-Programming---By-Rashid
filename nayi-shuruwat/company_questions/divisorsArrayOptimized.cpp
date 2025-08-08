
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll mod = 1e9 + 7;
const int N = 1e7 + 1;
vector<bool> isPrime;
vector<ll> sprime;

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

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, m;
    cin >> n >> m;

    vector<ll> v(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> v[i];
    }

    generatePrimes();

    vector<ll> pows(N + 1, 0);

    unordered_map<ll, ll> memo;

    // to find the power of a in m!
    // sum = [a/n] + [a/n^2] + ..... (floor values)

    for (int i = 2; i <= N; i++)
    {
        if (isPrime[i])
        {
            ll curr = i;
            ll sum = 0;
            while (curr <= m)
            {
                sum += (m / curr);
                curr *= i;
            }
            pows[i] = sum;
        }
    }

    ll prod = 1;
    for (int i = 2; i <= m; i++)
    {
        prod = (prod % mod * (pows[i] + 1) % mod) % mod;
    }

    for (auto num : v)
    {
        if (memo.count(num))
        {
            cout << memo[num] << " ";
            continue;
        }

        ll res = prod;

        unordered_map<ll, ll> mpp;
        getFactorization(num, mpp);

        for (auto i : mpp)
        {
            if (i.first > 1)
            {
                ll ex = mul_inverse(pows[i.first] + 1);
                res = (res % mod * ex % mod) % mod;
                res = (res % mod * ((pows[i.first] + i.second) + 1) % mod) % mod;
            }
        }

        cout << res << " ";
        memo[num] = res;
    }

    return 0;
}
