#include <bits/stdc++.h>
using namespace std;
#define int long long
using ll = int;

ll fastPow(ll base, int exp)
{
    ll result = 1;
    while (exp > 0)
    {
        if (exp & 1)
            result *= base;
        base *= base;
        exp >>= 1;
    }
    return result;
}

ll maxProductSplit(int n)
{
    if (n < 4)
        return n;

    int count3 = n / 3;
    int remainder = n % 3;

    if (remainder == 1)
    {
        count3 -= 1;
        remainder += 3;
    }

    ll product = fastPow(3, count3) * (remainder > 0 ? remainder : 1);
    return product;
}

void sol1()
{
    int n;
    cin >> n;

    vector<int> v(n);

    for (int i = 0; i < n; i++)
    {
        cin >> v[i];
    }

    vector<int> pref(n);
    pref[0] = v[0];

    for (int i = 1; i < n; i++)
    {
        pref[i] = pref[i - 1] + v[i];
    }

    sort(v.begin(), v.end());

    vector<int> prefsorted(n);
    prefsorted[0] = v[0];

    for (int i = 1; i < n; i++)
    {
        prefsorted[i] = prefsorted[i - 1] + v[i];
    }

    int m;
    cin >> m;

    while (m--)
    {
        int type;
        cin >> type;
        int l, r;
        cin >> l >> r;
        l--;
        r--;
        int ans;
        if (type == 1)
        {
            ans = pref[r] - (l > 0 ? pref[l - 1] : 0);
        }
        else
        {
            ans = prefsorted[r] - (l > 0 ? prefsorted[l - 1] : 0);
        }
        cout << ans << endl;
    }
}

void sol2()
{
    int n;
    cin >> n;

    vector<int> v(n);

    for (int i = 0; i < n; i++)
    {
        cin >> v[i];
    }

    sort(v.begin(), v.end());

    int ans = 0;

    int i = 0;

    while (i < n)
    {
        int curr = v[i];
        int len = 0;

        while (i < n and (2 * curr) >= v[i])
        {
            curr = v[i++];
            len++;
        }

        ans = max(ans, len);
    }

    cout << ans << endl;
}

void sol3()
{
    int n;
    cin >> n;

    vector<int> v(n);

    for (int i = 0; i < n; i++)
    {
        cin >> v[i];
    }

    sort(v.begin(), v.end());

    int ans = 0, i = 0;

    while (i < n)
    {
        int maxInexp = v[i];
        int currCnt = 1;
        i++;

        if (maxInexp <= currCnt)
        {
            ans++;
            continue;
        }

        while (i < n)
        {
            maxInexp = max(maxInexp, v[i++]);
            currCnt++;
            if (maxInexp <= currCnt)
            {
                ans++;
                break;
            }
        }
    }

    cout << ans << endl;
}

void sol4()
{
    int n;
    cin >> n;

    vector<int> v(n);

    for (int i = 0; i < n; i++)
    {
        cin >> v[i];
    }

    int maxsum = 0;

    int i = 0;

    while (i < n)
    {
        bool ispos = v[i] >= 0;
        int currval = v[i];

        while (i < n and ((v[i] >= 0) ^ ispos) == 0)
        {
            currval = max(currval, v[i++]);
        }

        maxsum += currval;
    }

    cout << maxsum << endl;
}

int maxProd;

void helper(vector<int> &v1, vector<int> &v2, int p1, int p2, int currProd, int taken = 0)
{
    if (taken == 5)
    {
        maxProd = max(maxProd, currProd);
        return;
    }

    if (p1 < (int)v1.size())
    {
        helper(v1, v2, p1 + 1, p2, currProd * v1[p1], taken + 1);
    }

    if (p2 < (int)v2.size())
    {
        helper(v1, v2, p1, p2 + 1, currProd * v2[p2], taken + 1);
    }
}

void sol5()
{
    maxProd = LLONG_MIN;

    int n;
    cin >> n;

    vector<int> v(n);
    vector<int> pos, neg;
    for (int i = 0; i < n; i++)
    {
        cin >> v[i];
    }

    sort(v.begin(), v.end());

    for (int i = 0; i < n; i++)
    {
        if (v[i] >= 0)
        {
            pos.push_back(v[i]);
        }
        else
        {
            neg.push_back(v[i]);
        }
    }

    reverse(pos.begin(), pos.end());

    vector<int> v1, v2;

    for (int i = 0; i < min(5ll, (int)pos.size()); i++)
    {
        v1.push_back(pos[i]);
    }

    for (int i = 0; i < min(5ll, (int)neg.size()); i++)
    {
        v2.push_back(neg[i]);
    }

    helper(v1, v2, 0, 0, 1);

    cout << maxProd << endl;
}

int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;

    while (t--)
    {
        sol5();
    }

    return 0;
}
