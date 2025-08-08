#include <bits/stdc++.h>
using namespace std;

#define int long long int

using ll = long long;
using lld = long double;
using ull = unsigned long long;

// Constants
const ll INF = LONG_LONG_MAX;
const ll mod = 1e9 + 7;

typedef map<ll, ll> mll;

// Macros
#define ff first
#define ss second
#define pb push_back
#define pii pair<int, int>
#define fl(i, n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define one(x) memset(x, -1, sizeof(x))
#define zero(x) memset(x, 0, sizeof(x))

// Segment tree template
struct node
{
    int gcd_value;

    node()
    {
        gcd_value = 0; // Default value for GCD
    }
};

node merge(node a, node b)
{
    node ans;
    ans.gcd_value = __gcd(a.gcd_value, b.gcd_value);
    return ans;
}

node t[4 * 200200];

void build(int id, int l, int r)
{
    if (l == r)
    {
        t[id].gcd_value = 0;
        return;
    }

    int mid = (l + r) / 2;
    build(2 * id, l, mid);
    build(2 * id + 1, mid + 1, r);
    t[id] = merge(t[2 * id], t[2 * id + 1]);
}

void update(int id, int l, int r, int pos, int val)
{
    if (pos < l || pos > r)
    {
        return;
    }

    if (l == r)
    {
        t[id].gcd_value = val;
        return;
    }
    int mid = (l + r) / 2;
    update(2 * id, l, mid, pos, val);
    update(2 * id + 1, mid + 1, r, pos, val);
    t[id] = merge(t[2 * id], t[2 * id + 1]);
}

node query(int id, int l, int r, int lo, int hi)
{
    if (l > hi || lo > r)
    {
        return node(); // Return a default node
    }
    if (lo <= l && r <= hi)
    {
        return t[id];
    }

    int mid = (l + r) / 2;
    return merge(query(2 * id, l, mid, lo, hi), query(2 * id + 1, mid + 1, r, lo, hi));
}

void s10()
{
    int n, q;
    cin >> n >> q;

    int arr[n];

    build(1, 0, n - 1);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    for (int i = 0; i < n - 1; i++)
    {
        update(1, 0, n - 1, i, abs(arr[i + 1] - arr[i]));
    }

    fl(i, q)
    {
        int l, r;
        cin >> l >> r;
        --l, --r;

        node result = query(1, 0, n - 1, l, r - 1);
        int value = result.gcd_value;

        if (value == arr[l])
        {
            value = 0;
        }

        cout << value << " ";
    }

    cout << endl;
}

signed main()
{
    ll t;
    cin >> t;
    while (t--)
    {
        s10();
    }
}
