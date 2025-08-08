#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAX = 1000000;
vector<int> primes;

// Madeline Wuntch has been defeated, in a last ditch effort, she is trying to shut down precincts,
// but she has a very specific criterion—she will only close a precinct if its number of divisors is a
// prime number but the number itself should not be prime. These are known as Prime-Prime precincts.
// Given a range of precinct numbers from l to r, determine how many precincts Wuntch will shut down.

void sievePrimes()
{
    vector<bool> isPrime(MAX + 1, true);
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i <= MAX; i++)
    {
        if (isPrime[i])
        {
            primes.push_back(i);
            if ((ll)i * i <= MAX)
                for (ll j = (ll)i * i; j <= MAX; j += i)
                    isPrime[j] = false;
        }
    }
}

ll calc(ll x, int k)
{
    ll lo = 1, hi = MAX;
    while (lo < hi)
    {
        ll mid = lo + (hi - lo + 1) / 2;
        ll prod = 1;
        for (int i = 0; i < k; i++)
        {
            prod *= mid;
            if (prod > x)
                break;
        }
        if (prod <= x)
            lo = mid;
        else
            hi = mid - 1;
    }
    return lo;
}

ll calc2(ll x, int k)
{
    ll floorVal = calc(x, k);
    ll prod = 1;
    for (int i = 0; i < k; i++)
    {
        prod *= floorVal;
    }
    if (prod >= x)
        return floorVal;
    else
        return floorVal + 1;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    sievePrimes();

    vector<int> allowed = {2, 4, 6, 10, 12, 16, 18, 22, 28, 30, 36};

    int t;
    cin >> t;
    while (t--)
    {
        ll L, R;
        cin >> L >> R;
        ll ans = 0;
        for (int a : allowed)
        {
            ll lowP = calc2(L, a);
            ll highP = calc(R, a);
            if (lowP < 2)
                lowP = 2;
            if (lowP > highP)
                continue;
            auto lowerIt = lower_bound(primes.begin(), primes.end(), lowP);
            auto upperIt = upper_bound(primes.begin(), primes.end(), highP);
            ans += (upperIt - lowerIt);
        }
        cout << ans << "\n";
    }
    return 0;
}
