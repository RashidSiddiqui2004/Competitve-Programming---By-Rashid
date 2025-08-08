#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

using ll = long long;
using lld = long double;
using ull = unsigned long long;

// Constants
const ll INF = LONG_LONG_MAX;
const ll mod = 1e9 + 7;
const ll new_mod = 998244353;

// Typedefs
typedef pair<ll, ll> pll;
typedef vector<ll> vll;
typedef vector<pll> vpll;
typedef vector<string> vs;
typedef unordered_map<ll, ll> umll;
typedef map<ll, ll> mll;

ll maxprofit = LLONG_MIN;
vector<int> optimalcount;
vector<vector<int>> optimalsteps;

#define ff first
#define ss second
#define pb push_back
#define pii pair<int, int>
#define fl(i, n) for (int i = 0; i < n; i++)
#define rl(i, m, n) for (int i = n; i >= m; i--)
#define py cout << "YES\n";
#define pm cout << "-1\n";
#define pn cout << "NO\n";
#define pimp cout << "IMPOSSIBLE\n";
#define vr(v) v.begin(), v.end()
#define rv(v) v.end(), v.begin()
#define inputvector(v) \
    for (auto &x : v)  \
        cin >> x;
#define all(v) v.begin(), v.end()

void cheftraverse(int n, vector<int> &chefcount, vector<vector<int>> &adj,
                  vector<bool> &vis, int d, vector<pll> &s, int node,
                  vector<vector<int>> &stepsTransfer)
{
    ll currprofit = 0;
    int remdays = d;

    for (int i = 0; i < n; i++)
    {
        if (remdays == 0)
        {
            break;
        }
        if (chefcount[s[i].second] > 0)
        {
            currprofit += s[i].first;
            remdays--;
        }
    }

    if (currprofit > maxprofit)
    {
        maxprofit = currprofit;
        optimalsteps = stepsTransfer;
        optimalcount = chefcount;
    }

    if (d == 0)
    {
        return;
    }

    vis[node] = true;
    int currchefs = chefcount[node];
    for (auto i : adj[node])
    {
        if (vis[i])
        {
            continue;
        }
        for (int j = 1; j <= currchefs; j++)
        {
            chefcount[node] -= j;
            chefcount[i] += j;
            stepsTransfer.push_back({node + 1, i + 1, j});
            cheftraverse(n, chefcount, adj, vis, d - 1, s, i, stepsTransfer);
            stepsTransfer.pop_back();
            chefcount[node] += j;
            chefcount[i] -= j;
        }
    }
    vis[node] = false;
}

void chefcity()
{
    int n, c, d;
    cin >> n >> c >> d;

    vector<pll> s(n);

    fl(i, n)
    {
        cin >> s[i].first;
        s[i].second = i;
    }

    sort(all(s), [](pll &p1, pll &p2)
         {
    if(p1.first!=p2.first){
        return p1.first > p2.first;
    }else{
        return p1.second < p2.second;
    } });

    vector<vector<int>> adj(n);
    fl(i, n - 1)
    {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    if (n == 1)
    {
        cout << s[0].first << endl;
        return;
    }
    vector<bool> vis(n, false);
    vector<int> chefcount(n, 0);
    chefcount[0] = c;

    vector<vector<int>> stepsTransfer;
    maxprofit = LLONG_MIN;
    optimalcount.clear();
    optimalsteps.clear();

    cheftraverse(n, chefcount, adj, vis, d, s, 0, stepsTransfer);

    cout << maxprofit << endl;

    for (auto i : optimalsteps)
    {
        d--;
        cout << "transfer " << i[0] << " " << i[1] << " " << i[2] << endl;
    }
    for (int i = 0; i < n; i++)
    {
        if (optimalcount[i] != 0)
        {
            d--;
            cout << "build " << i + 1 << endl;
        }
    }
    while (d-- > 0)
    {
        cout << "nothing\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    chefcity();

    return 0;
}

// void cheftraverse(int n,
//                   vector<int> &chefcount, vector<vector<int>> &adj,
//                   vector<bool> &vis, int d, vector<ll> &s, int node,
//                   vector<vector<int>> stepsTransfer)
// {
//     ll currprofit = 0;
//     for (int i = 0; i < n; i++)
//     {
//         if (chefcount[i] > 0)
//         {
//             currprofit += s[i];
//         }
//     }

//     if (currprofit > maxprofit)
//     {
//         maxprofit = max(maxprofit, currprofit);
//         optimalsteps = stepsTransfer;
//         optimalcount = chefcount;
//     }

//     if (d == 0)
//     {
//         return;
//     }

//     else
//     {
//         vis[node] = true;
//         int currchefs = chefcount[node];
//         for (auto i : adj[node])
//         {
//             if (vis[i])
//             {
//                 continue;
//             }
//             for (int j = 1; j <= currchefs; j++)
//             {
//                 chefcount[node] -= j;
//                 chefcount[i] += j;
//                 // if (j != 0)
//                 stepsTransfer.push_back({node + 1, i + 1, j});
//                 cheftraverse(n, chefcount, adj, vis, d - 1, s, i, stepsTransfer);
//                 stepsTransfer.pop_back();
//                 chefcount[node] += j;
//                 chefcount[i] -= j;
//             }
//         }
//         vis[node] = false;
//     }
// }

// void chefcity()
// {
//     int n, c, d;
//     cin >> n >> c >> d;
//     vector<ll> s(n);
//     inputvector(s);

//     vector<vector<int>> adj(n);
//     fl(i, n - 1)
//     {
//         int u, v;
//         cin >> u >> v;
//         --u, --v;
//         adj[u].push_back(v);
//         adj[v].push_back(u);
//     }

//     if (n == 1)
//     {
//         cout << s[0] << endl;
//         return;
//     }

//     vector<bool> vis(n, false);
//     vector<int> chefcount(n, 0);
//     chefcount[0] = c;

//     vector<vector<int>> stepsTransfer;

//     cheftraverse(n, chefcount, adj, vis, d, s, 0, stepsTransfer);

//     cout << maxprofit << endl;

//     for (auto i : optimalsteps)
//     {
//         d--;
//         cout << "transfer " << i[0] << " " << i[1] << " " << i[2] << endl;
//     }
//     for (int i = 0; i < n; i++)
//     {
//         if (optimalcount[i] != 0)
//         {
//             d--;
//             cout << "build " << i + 1 << endl;
//         }
//     }
//     while (d--)
//     {
//         cout << "nothing\n";
//     }
// }
// int main()
// {
//     std::ios::sync_with_stdio(false);
//     std::cin.tie(nullptr);
//     std::cout.tie(nullptr);

//     chefcity();

//     return 0;
// }