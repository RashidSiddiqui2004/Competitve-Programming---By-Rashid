
#include <bits/stdc++.h>
using namespace std;

#include <iostream>
#include <bitset>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using lld = long double;
using ull = unsigned long long;

// Constants
const ll INF = LONG_LONG_MAX;
const ll mod = 1e9 + 7;

// TypeDEf
typedef pair<ll, ll> pll;
typedef vector<ll> vll;
typedef vector<pll> vpll;
typedef vector<string> vs;
typedef unordered_map<ll, ll> umll;
typedef map<ll, ll> mll;
// Macros
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
#define len(s) (int)s.size()
#define forn(i, n) for (int i = 0; i < int(n); i++)
#define all(v) v.begin(), v.end()
#define one(x) memset(x, -1, sizeof(x))
#define zero(x) memset(x, 0, sizeof(x))

// https://codeforces.com/contest/2000/problem/G

bool ispossible(int n, int m, ll to, ll t1, ll t2, vector<vector<vector<ll>>> &adj, ll mid)
{
    vector<ll> time(n, 1e16);
    priority_queue<ll, vector<pll>, greater<>> pq;
    time[0] = mid;
    pq.push({mid, 0});

    while (!pq.empty())
    {
        auto front = pq.top();
        pq.pop();
        auto currtime = front.first, node = front.second;

        if (currtime > to)
        {
            continue;
        }

        for (auto state : adj[node])
        {
            ll neighbour = state[0], bustime = state[1], walktime = state[2];
            if ((currtime + bustime) <= to)
            {
                if (((currtime + bustime) <= t1))
                {
                    if ((bustime + currtime) < time[neighbour])
                    {
                        time[neighbour] = (bustime + currtime);
                        pq.push({time[neighbour], neighbour});
                    }
                }
                if ((bustime + max(t2, currtime)) < time[neighbour])
                {
                    time[neighbour] = (bustime + max(t2, currtime));
                    pq.push({time[neighbour], neighbour});
                }
                if ((walktime + currtime) < time[neighbour])
                {
                    time[neighbour] = (walktime + currtime);
                    pq.push({time[neighbour], neighbour});
                }
            }
        }
    }

    return (time[n - 1] <= to);
}

// Binary search approach
void s15()
{
    int n, m;
    ll to, t1, t2;
    cin >> n >> m >> to >> t1 >> t2;

    vector<vector<vector<ll>>> adjlist(n);

    fl(i, m)
    {
        int u, v, l1, l2;
        cin >> u >> v >> l1 >> l2;
        --u, --v;
        adjlist[u].push_back({v, l1, l2});
        adjlist[v].push_back({u, l1, l2});
    }

    ll low = 0, high = to - 1;
    ll mid, ans = -1;

    while (low <= high)
    {
        mid = (low + high) / 2;
        if (ispossible(n, m, to, t1, t2, adjlist, mid))
        {
            ans = mid;
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    cout << ans << endl;
}

// new learning approach
// implementing Djikstra's using set method => slightly efficient
void efficientSol()
{
    int n, m;
    ll to, t1, t2;
    cin >> n >> m >> to >> t1 >> t2;

    vector<vector<vector<ll>>> adj(n);

    fl(i, m)
    {
        int u, v, l1, l2;
        cin >> u >> v >> l1 >> l2;
        --u, --v;
        adj[u].push_back({v, l1, l2});
        adj[v].push_back({u, l1, l2});
    }

    vector<ll> time(n, LLONG_MIN);

    set<pair<int, int>> pq;

    int target = n - 1;
    pq.insert({to, target});

    for (int i = 0; i + 1 < n; ++i)
    {
        pq.insert({-1e9, i});
    }

    while (!pq.empty())
    {
        auto front = *pq.rbegin();
        pq.erase(front);

        auto currtime = front.first, node = front.second;

        if (currtime < 0)
        {
            continue;
        }

        for (auto state : adj[node])
        {
            ll neighbour = state[0], bustime = state[1], walktime = state[2];
            ll d1 = ((currtime - bustime) >= t2 || currtime <= t1) ? (currtime - bustime) : (currtime - walktime);

            // (t1-bustime) implies stop at the node, and talk, then take bus
            if (d1 == (currtime - walktime))
                d1 = max(d1, t1 - bustime);

            if ((d1) > time[neighbour])
            {
                pq.erase({time[neighbour], neighbour});
                time[neighbour] = d1;
                pq.insert({d1, neighbour});
                // time[neighbour] = (d1);
                // pq.push({time[neighbour], neighbour});
            }
        }
    }

    int ans = time[0] >= 0 ? time[0] : -1;
    cout << ans << endl;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    ll t;
    cin >> t;

    while (t--)
    {
        efficientSol();
    }

    return 0;
}