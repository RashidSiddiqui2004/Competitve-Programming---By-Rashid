
#include <bits/stdc++.h>
using namespace std;

void sol8()
{
    int n;
    cin >> n;

    vector<int> v(n + 1, 0), prefsum(n + 1, 0);

    fl(i, n)
    {
        cin >> v[i + 1];
    }

    for (int i = 1; i <= n; i++)
    {
        prefsum[i] = prefsum[i - 1] + v[i];
    }

    int l = 1, r = n, mid, ans;

    while (l <= r)
    {
        mid = (l + r) / 2;

        int queriedWt;

        int len = (r - mid + 1);
        cout << "? " << len << " ";

        for (int i = mid; i <= r; i++)
        {
            cout << i << " ";
        }

        cout << endl
             << flush;

        cin >> queriedWt;

        int calcWt = prefsum[r] - prefsum[mid - 1];

        if (calcWt == queriedWt)
        {
            r = mid - 1;
        }
        else
        {
            ans = mid;
            l = mid + 1;
        }
    }

    cout << "! " << ans << endl
         << flush;
}
