#include <bits/stdc++.h>
using namespace std;

void solve()
{
    int r, c, x;
    cin >> r >> c >> x;

    vector<vector<int>> a(r, vector<int>(c));
    vector<vector<int>> b(r, vector<int>(c));
    vector<vector<int>> a1(x, vector<int>(x, 0));

    // Input matrices A and B
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            cin >> a[i][j];
        }
    }
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            cin >> b[i][j];
        }
    }

    // Construct a1 matrix by grouping elements by (i % x, j % x)
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            a1[i % x][j % x] += a[i][j] - b[i][j];
        }
    }

    // Check if the transformation is possible
    bool possible = true;
    for (int i = 1; i < x; i++)
    {
        int diff = a1[i][0] - a1[0][0]; // Difference should be constant
        for (int j = 1; j < x; j++)
        {
            if (a1[i][j] - a1[0][j] != diff)
            {
                possible = false;
                break;
            }
        }
        if (!possible)
            break;
    }

    cout << (possible ? "Yes" : "No") << endl;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }

    return 0;
}
