#include <bits/stdc++.h>
using namespace std;
using ll = long long;
static const int MOD = 998244353;

// fast exponentiation mod
ll modpow(ll a, ll e = MOD - 2)
{
    ll r = 1;
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

    int t;
    cin >> t;

    while (t--)
    {

        int N;
        cin >> N;
        vector<int> A(N);
        for (int &x : A)
            cin >> x;
 
        vector<int> cnt(N + 2, 0);
        int largeCnt = 0;

        for (int x : A)
        {
            if (0 <= x && x <= N)
                cnt[x]++;
            else
                largeCnt++;
        } 
    
        vector<ll> p2(N + 1, 1);
        for (int i = 1; i <= N; i++)
        {
            p2[i] = p2[i - 1] * 2 % MOD;
        }
 
        vector<ll> Acoef(N + 2, 0), invA(N + 2, 0);
        
        for (int x = 0; x <= N + 1; x++)
        {
            if (cnt[x] > 0)
            {
                Acoef[x] = (p2[cnt[x]] + MOD - 1) % MOD;
                invA[x] = modpow(Acoef[x]);
            }
        }

        // 4) Build prefix arrays for k=0..N+1
        //    z[k] = # of i<k with cnt[i]==0
        //    Pnz[k] = ∏_{i<k, cnt[i]>0} Acoef[i]
        //    SumInv[k] = ∑_{i<k, cnt[i]>0} invA[i]
        vector<int> z(N + 2, 0);
        vector<ll> Pnz(N + 2, 1), SumInv(N + 2, 0);
        for (int k = 1; k <= N + 1; k++)
        {
            z[k] = z[k - 1] + (cnt[k - 1] == 0);
            if (cnt[k - 1] > 0)
            {
                Pnz[k] = Pnz[k - 1] * Acoef[k - 1] % MOD;
                SumInv[k] = (SumInv[k - 1] + invA[k - 1]) % MOD;
            }
            else
            {
                Pnz[k] = Pnz[k - 1];
                SumInv[k] = SumInv[k - 1];
            }
        }

        // 5) suffixCnt[k] = # of elements >k in A
        //    that's sum of cnt[j] for j>k plus largeCnt
        vector<int> suffixCnt(N + 3, largeCnt);
        for (int k = N; k >= 0; k--)
        {
            suffixCnt[k] = suffixCnt[k + 1] + cnt[k + 1];
        }

        // 6) Sum over k=1..N+1 the contributions for SMEX=k
        ll ans = 0;
        for (int k = 1; k <= N + 1; k++)
        {
            int zeros = z[k];
            if (zeros >= 2)
                continue;

            // count of ways to choose in [0..k-1] so exactly one value missing:
            ll waysBelow = 0;
            if (zeros == 1)
            {
                // the unique missing m1, and all others pick ≥1 copy:
                waysBelow = Pnz[k];
            }
            else
            {
                // zeros == 0: all present -> sum over which m1 we omit
                //   = Pnz[k] * SumInv[k]
                waysBelow = Pnz[k] * SumInv[k] % MOD;
            }

            // for all values > k, we can pick arbitrarily: 2^{suffixCnt[k]}
            ll waysAbove = p2[suffixCnt[k]];
            ll totalK = waysBelow * waysAbove % MOD;

            ans = (ans + (ll)k * totalK) % MOD;
        }

        cout << ans - 1 << "\n";
    }

    return 0;
}
