#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 1LL << 60;

void sol1()
{
    int n, m, x;
    cin >> n >> m >> x;

    // Build the graph (0-indexed) and also store reverse edges.
    vector<vector<int>> adj(n), rev(n);
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].push_back(v);
        rev[v].push_back(u); // reverse edge for state 1
    }

    // dist[state][vertex]: state 0 => original, state 1 => reversed.
    vector<vector<ll>> dist(2, vector<ll>(n, INF));
    dist[0][0] = 0; // start at vertex 0 in state 0

    // Priority queue: (current_cost, vertex, state)
    using T = tuple<ll, int, int>;
    priority_queue<T, vector<T>, greater<T>> pq;
    pq.push({0, 0, 0});

    while (!pq.empty())
    {
        auto [d, v, st] = pq.top();
        pq.pop();
        if (d != dist[st][v])
            continue;

        // Option 1: Reverse the direction (flip state) at vertex v at cost x.
        int nst = 1 - st;
        if (dist[nst][v] > d + x)
        {
            dist[nst][v] = d + x;
            pq.push({dist[nst][v], v, nst});
        }

        // Option 2: Move along an edge (cost 1)
        if (st == 0)
        {
            // In state 0, we can only go along edges as given.
            for (auto nxt : adj[v])
            {
                if (dist[st][nxt] > d + 1)
                {
                    dist[st][nxt] = d + 1;
                    pq.push({dist[st][nxt], nxt, st});
                }
            }
        }
        else
        {
            // In state 1, we can only move along edges in the reversed graph.
            for (auto nxt : rev[v])
            {
                if (dist[st][nxt] > d + 1)
                {
                    dist[st][nxt] = d + 1;
                    pq.push({dist[st][nxt], nxt, st});
                }
            }
        }
    }

    // The answer is the minimum cost to reach vertex n-1 in either state.
    ll ans = min(dist[0][n - 1], dist[1][n - 1]);
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    sol1();
    return 0;
}
