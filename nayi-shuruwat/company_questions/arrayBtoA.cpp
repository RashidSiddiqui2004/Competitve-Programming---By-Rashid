// Given 2 arrays A and B. Make B equal to A in minimum no. of operations. In each operation, you can
// remove any element from array B and put that element in front or end of array B. We need to output the
// number of operations.

// A = [1,4,5,4,5]
// B = [5,4,5,1,4]

// Steps
// 1. remove 4 from B and put it at the front of B => [4,5,4,5,1]
// 2. remove 1 from B and put it at the front of B => [1,4,5,4,5]
// 2 steps are required.
// it can be proven that minimum 2 steps are required to make B equal to A.

void solve7()
{
    int n;
    cin >> n;

    vector<int> a(n), b(n);

    fl(i, n)
    {
        cin >> a[i];
    }

    fl(i, n)
    {
        cin >> b[i];
    }

    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (a[i] == b[j])
            {
                dp[i + 1][j + 1] = dp[i][j] + 1;
            }
            else
            {
                dp[i + 1][j + 1] = dp[i + 1][j];
            }
        }
    }

    int ans = 0;
    for (auto i : dp)
    {
        for (auto j : i)
        {
            ans = max(ans, j);
        }
    }

    cout << "Max length of common subsequence is " << ans << endl;
    cout << "Required number of operations is/are : " << n - ans << endl;
}
