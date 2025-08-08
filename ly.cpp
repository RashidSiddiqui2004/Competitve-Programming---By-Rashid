#include <bits/stdc++.h>
using namespace std;

using ll = long long;

bool ans(string s, int pos)
{
    if (pos < 0)
    {
        return true;
    }

    if (s[pos] == '1')
    {
        return true;
    }

    if (pos == 0)
    {
        return false;
    }

    if (s[pos - 1] == '0')
    {
        return false;
    }

    return ans(s, pos - 2);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--)
    {
        int n;
        cin >> n;
        string s;
        cin >> s;

        vector<int> v(n);
        for (int pos = 0; pos < n; pos++)
        {
            v[pos] = s[pos] - 'a' + 1;
        }

        vector<ll> prefixSum(n), prefixProd(n);
        ll curSum = 0, curProd = 1;
        ll res = LLONG_MAX;

        vector<vector<int>> temp(26);
        temp[0].push_back(-1);

        vector<ll> storedPrefixSum;
        storedPrefixSum.push_back(0);

        for (int i = 0; i < n; i++)
        {
            curSum += v[i];
            curProd *= v[i];
            prefixSum[i] = curSum;
            prefixProd[i] = curProd;

            int rem = curSum % 26;

            for (int cand : temp[rem])
            {
                ll candsum = (cand == -1) ? 0 : prefixSum[cand];

                if (curSum - candsum < 26)
                    continue;

                ll candprod = (cand == -1) ? 1 : prefixProd[cand];

                if (candprod != 0 && curProd % candprod == 0 &&
                    (curProd / candprod) % 26 == 0)
                {
                    res = min(res, (ll)(i - cand));
                }
            }

            temp[rem].push_back(i);
        }

        if (res == LLONG_MAX)
            res = -1;

        cout << res << "\n";
    }

    return 0;
}
