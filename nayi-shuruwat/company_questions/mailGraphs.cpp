// https://www.codechef.com/problems/MAIL_DELIVER
// updated djikstra's

void sol12()
{
    int n, m, k;
    cin >> n >> m >> k;

    vector<int> x(k), d(k);

    fl(i, k)
    {
        cin >> x[i];
        x[i]--;
    }

    fl(i, k)
    {
        cin >> d[i];
    }

    vector<vector<int>> adj(n);

    fl(i, m)
    {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<bool> vis(n, false);

    priority_queue<pll> pq;

    fl(i, k)
    {
        pq.push({d[i], x[i]});
    }

    // vector<ll> dist(n, INT_MAX);
    // dist[pq.top().second] = pq.top().first;

    while (!pq.empty())
    {
        auto fr = pq.top();
        pq.pop();

        auto strength = fr.first, node = fr.second;
        vis[node] = true;

        if (strength == 1)
        {
            continue;
        }

        for (auto neighbor : adj[node])
        {
            if (!vis[neighbor])
            {
                vis[neighbor] = true;
                pq.push({strength - 1, neighbor});
            }
        }
    }

    for (auto i : vis)
    {
        if (i == false)
        {
            cout << "NO\n";
            return;
        }
    }

    cout << "YES\n";
}
