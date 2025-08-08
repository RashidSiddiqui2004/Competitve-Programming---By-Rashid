#include <bits/stdc++.h>
using namespace std;
static const int MOD = 998244353;

// fast exponentiation mod
long long modexp(long long a, long long e = MOD - 2)
{
    long long r = 1;
    while (e)
    {
        if (e & 1)
            r = r * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int A, B, C, D;
    cin >> A >> B >> C >> D;
    int N = A + B + C + D + 5;

    vector<long long> fact(N), invfact(N);
    fact[0] = 1;
    for (int i = 1; i < N; i++)
        fact[i] = fact[i - 1] * i % MOD;
    invfact[N - 1] = modexp(fact[N - 1]);
    for (int i = N - 1; i > 0; i--)
        invfact[i - 1] = invfact[i] * i % MOD;

    auto Cnk = [&](int n, int k) -> long long
    {
        if (k < 0 || k > n)
            return 0;
        return fact[n] * invfact[k] % MOD * invfact[n - k] % MOD;
    };

    long long ans = 0;
    for (int k = 0; k <= B; k++)
    {
        long long ways1 = Cnk(A + k, k);
        for (int x = 0; x <= C; x++)
        {
            long long ways2 = Cnk((B - k) + x, x);
            long long ways3 = Cnk((C - x) + D, D);
            ans = (ans + ways1 * ways2 % MOD * ways3) % MOD;
        }
    }

    cout << ans / 2 << "\n";
    return 0;
}
