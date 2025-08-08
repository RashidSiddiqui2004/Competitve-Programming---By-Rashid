// https://www.codechef.com/problems/BSTRING

void sol26()
{
    int n;
    cin >> n;

    // int z = 0, o = 0;
    vector<int> ones, zeros;
    string s;
    cin >> s;
    fl(i, n)
    {
        int e = s[i] - '0';

        if (e)
        {
            ones.push_back(i);
        }
        else
        {
            zeros.push_back(i);
        }
    }

    ll ans = (ll)ones.size() + (ll)zeros.size() % mod;

    int o = ones.size(), z = zeros.size();
    ll frontsum = 0ll;

    for (int i = 0; i < o; i++)
    {
        frontsum += power(2, ones[i], mod);
    }

    for (int i = 0; i < o; i++)
    {
        frontsum -= power(2, ones[i], mod);
        ans = add(ans, multiply(frontsum, mul_inverse(power(2, ones[i] + 1, mod)), mod));
    }

    frontsum = 0ll;

    for (int i = 0; i < z; i++)
    {
        frontsum += power(2, zeros[i], mod);
    }

    for (int i = 0; i < z; i++)
    {
        frontsum -= power(2, zeros[i], mod);
        ans = add(ans, multiply(frontsum, mul_inverse(power(2, zeros[i] + 1, mod)), mod));
    }

    cout << ans << endl;
}
