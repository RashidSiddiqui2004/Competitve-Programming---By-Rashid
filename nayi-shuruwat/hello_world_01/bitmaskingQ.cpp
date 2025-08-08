// https://www.codechef.com/problems/CHRL1
// bitmasking
void oranges()
{
    ll n, k;
    cin >> n >> k;

    vector<ll> cost(n), wt(n);

    fl(i, n)
    {
        cin >> cost[i] >> wt[i];
    }

    ll maxwt = 0;

    for (ll i = 0; i <= (1 << n) - 1; i++)
    {
        ll currwt = 0, remMoney = k;
        bool poss = true;
        for (int j = 0; j < n; j++)
        {
            if (((1 << j) & i) != 0)
            {
                if (remMoney >= cost[j])
                {
                    remMoney -= cost[j];
                    currwt += wt[j];
                }
                else
                {
                    poss = false;
                    break;
                }
            }
        }
        if (poss)
        {
            maxwt = max(maxwt, currwt);
        }
    }

    cout << maxwt << endl;
}
