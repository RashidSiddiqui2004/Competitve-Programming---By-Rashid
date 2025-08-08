#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll mod = 1e9 + 7;
vector<int> primes;

void generatePrimes(int limit)
{
    vector<bool> isPrime(limit + 1, true);
    for (int i = 2; i * i <= limit; i++)
    {
        if (isPrime[i])
        {
            for (int j = i * i; j <= limit; j += i)
            {
                isPrime[j] = false;
            }
        }
    }
    for (int i = 2; i <= limit; i++)
    {
        if (isPrime[i])
        {
            primes.push_back(i);
        }
    }
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
    ll maxi = *max_element(v.begin(), v.end());
    primes.clear();

    ll prsz = max(m, maxi) + 1;

    generatePrimes(prsz);

    ll sz = primes.size();
    vector<ll> pows(sz, 0);

    unordered_map<ll, ll> memo;
    unordered_map<ll, vector<ll>> dp;
    vector<ll> temp_pows(sz, 0);

    for (int i = 2; i <= m; i++)
    {
        temp_pows.assign(sz, 0);
        ll temp = i;
        for (int j = 0; j < sz && (primes[j] * 1ll * primes[j]) <= temp; j++)
        {
            while (temp % primes[j] == 0)
            {
                pows[j]++;
                temp_pows[j]++;
                temp /= primes[j];
            }
        }
        if (temp > 1)
        {
            int idx = lower_bound(primes.begin(), primes.end(), temp) - primes.begin();
            if (idx < sz && primes[idx] == temp)
            {
                pows[idx]++;
                temp_pows[idx]++;
            }
        }
    }

    for (auto num : v)
    {
        if (memo.count(num))
        {
            cout << memo[num] << " ";
            continue;
        }

        temp_pows = pows;
        ll res = 1;

        ll temp = num;
        for (int i = 0; i < sz && primes[i] * primes[i] <= temp; i++)
        {
            while (temp % primes[i] == 0)
            {
                temp_pows[i]++;
                temp /= primes[i];
            }
        }

        if (temp > 1)
        {
            int idx = lower_bound(primes.begin(), primes.end(), temp) - primes.begin();
            if (idx < sz && primes[idx] == temp)
            {
                temp_pows[idx]++;
            }
        }

        for (int i = 0; i < sz; i++)
        {
            if (temp_pows[i] > 0)
            {
                res = (res * (temp_pows[i] + 1)) % mod;
            }
        }

        cout << res << " ";
        memo[num] = res;
    }

    return 0;
}
