
// https://www.codechef.com/problems/REIGN
void s5()
{
    ll n, k;
    cin >> n >> k;

    vector<ll> a(n);
    for (ll &x : a)
        cin >> x;

    vector<ll> prefixMax(n, LLONG_MIN), suffixMax(n, LLONG_MIN);

    // Compute prefix max subarray sum using kadane's algorithm

    ll maxsum = LLONG_MIN, currsum = 0;

    for (int i = 0; i < n; i++)
    {
        currsum += a[i];
        maxsum = max(maxsum, currsum);

        prefixMax[i] = maxsum;
        if (currsum < 0)
        {
            currsum = 0;
        }
    }

    maxsum = LLONG_MIN, currsum = 0;
    for (int i = n - 1; i >= 0; i--)
    {
        currsum += a[i];
        maxsum = max(maxsum, currsum);
        if (currsum < 0)
            currsum = 0;
        suffixMax[i] = maxsum;
    }

    ll ans = LLONG_MIN;

    // Iterate over blocked intervals
    for (int i = 1; i <= n - k - 1; i++)
    {
        ll leftMax = (i > 0) ? prefixMax[i - 1] : LLONG_MIN;
        ll rightMax = (i + k < n) ? suffixMax[i + k] : LLONG_MIN;
        ans = max(ans, leftMax + rightMax);
    }

    cout << ans << endl;
}
