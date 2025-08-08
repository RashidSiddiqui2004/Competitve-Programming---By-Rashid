#include <bits/stdc++.h>
using namespace std;
#define fastio() ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)

#define ceil(x, y) (x + y - 1) / y // least integer function
#define sz(x) (int)(x).size()
#define PI 3.141592653589793238
#define ull unsigned long long
#define ll long long
#define pb push_back
#define pp pop_back
#define IM INT_MAX
#define IN INT_MIN
#define lb lower_bound
#define ub upper_bound

// const int M = 1e9+7;
// const int N = 1e5+5;

/* Things get better by time, hope for the best ..........
-------------- GO THROUGH CODE ONCE BEFORE SUBMITTING ------------------*/

int binExp(int a, int b, int M)
{
    a %= M;
    int ans = 1;
    while (b)
    {
        if (b & 1)
            ans = (ans * 1ll * a) % M;
        a = (a * 1ll * a) % M;
        b >>= 1;
    }
    return ans;
}

int main()
{

    fastio();

    int n, x, q;
    cin >> n;

    int primes[25] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
    vector<vector<int>> pf_cnt(n + 1, vector<int>(25, 0));

    for (int i = 1; i <= n; i++)
    {
        cin >> x;
        for (int j = 0; j < 25; j++)
        {
            while (x % primes[j] == 0)
            {
                pf_cnt[i][j]++;
                x /= primes[j];
            }
            pf_cnt[i][j] += pf_cnt[i - 1][j];
        }
    }

    cin >> q;
    while (q--)
    {
        int l, r, M;
        cin >> l >> r >> M;
        int res = 1;
        for (int i = 0; i < 25; i++)
        {
            res = (res * 1ll * binExp(primes[i], pf_cnt[r][i] - pf_cnt[l - 1][i], M)) % M;
        }
        cout << res << endl;
    }
}