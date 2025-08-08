
const int SIZE = 11;
vector<long long> e(SIZE, 1), dp(SIZE, 0);

void precompute()
{
    for (int n = 1; n < SIZE; n++)
    {
        e[n] = n * e[n - 1];
    }

    for (int n = 1; n < SIZE; n++)
    {
        dp[n] = dp[n - 1] + 9 * e[9] / e[10 - n];
    }
}

long long calc(long long x)
{
    if (x > 9876543210)
    {
        return dp[10];
    }

    vector<int> digits(SIZE, 0);
    int n = 0;

    while (x)
    {
        digits[n++] = x % 10;
        x /= 10;
    }

    long long ans = dp[n - 1];
    vector<bool> mark(10, false);

    for (int i = n - 1; i >= 0; i--)
    {
        for (int d = (i == n - 1 ? 1 : 0); d < digits[i]; d++)
        {
            if (!mark[d])
            {
                ans += e[9 - (n - 1 - i)] / e[10 - n];
            }
        }
        if (mark[digits[i]])
            break;
        mark[digits[i]] = true;
    }
    return ans;
}

void solve100()
{
    int t;
    cin >> t;
    while (t--)
    {
        long long l, r;
        cin >> l >> r;
        long long resL = calc(l);
        long long resR = calc(r + 1);
        cout << resR - resL << endl;
    }
}