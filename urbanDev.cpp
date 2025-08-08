#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

#define ll long long
#define int long long
#define endl '\n'
#define sp ' '
#define pii pair<int, int>
#define pb push_back
#define vi vector<int>
#define vll vector<ll>
#define vvi vector<vi>
#define all(c) c.begin(), c.end()

const int mod = 1e9 + 7;
ll i, j, k;

template <typename T>
using pbds = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// one Data structure for verticals and other for horizontals
unordered_map<int, pbds<pii>> horizontal, verticals;

void solve()
{
    int n;
    cin >> n;

    vector<vector<ll>> roads;

    ll x1, y1, x2, y2;

    for (int i = 0; i < n; i++)
    {
        cin >> x1 >> y1 >> x2 >> y2;
        roads.push_back({x1, y1, x2, y2});

        if (x1 == x2)
        {
            verticals[x1].insert({y1, y2});
        }
        else
        {
            horizontal[y1].insert({x1, x2});
        }
    }

    vector<ll> trafficLights(n);

    for (int i = 0; i < n; i++)
    {
        auto v = roads[i];
        ll x1 = v[0], y1 = v[1], x2 = v[2], y2 = v[3];

        ll currLights = 0;

        if (x1 == x2)
        {
            for (int j = y1; j <= y2; j++)
            {
                if (horizontal[j].empty())
                {
                    continue; // Skip if no points exist in this x-coordinate
                }

                auto it = horizontal[j].upper_bound({-1, x1});

                if (it == horizontal[j].end() || it->second < x1)
                    continue;

                ll p1 = horizontal[j].order_of_key({-1, x1});
                ll p2 = horizontal[j].order_of_key({x1 + 1, -1});

                currLights += (p2 - p1);
            }
        }
        else
        {
            for (int j = x1; j <= x2; j++)
            {
                if (verticals[j].empty())
                {
                    continue; // Skip if no points exist in this y-coordinate
                }

                auto it = verticals[j].upper_bound({-1, y1});

                if (it == verticals[j].end() || it->second < y1)
                    continue;

                ll p1 = verticals[j].order_of_key({-1, y1}); // Count elements strictly < x1

                ll p2 = verticals[j].order_of_key({y1 + 1, -1}); // Count elements < (x2+1)

                currLights += (p2 - p1);
            }
        }

        trafficLights[i] = currLights;
    }

    ll ans = accumulate(all(trafficLights), 0);

    ans /= 2;

    cout << ans << endl;

    for (auto i : trafficLights)
    {
        cout << i << " ";
    }

    cout << endl;
}

int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t = 1;
    // cin >> t;

    while (t--)
    {
        solve();
    }

    return 0;
}