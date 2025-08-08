#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>
using namespace std;

const int INF = 1e9;

int n;
vector<vector<int>> adf; // adjacency list (0-indexed)
vector<int> ansColor;    // answer colours for nodes (0 means unassigned)

// DFS used to obtain the connected component (ignoring blocked nodes).
void dfs_component(int u, int parent, vector<int> &comp, const vector<bool> &blocked)
{
    comp.push_back(u);
    for (int v : adj[u])
    {
        if (v == parent || blocked[v])
            continue;
        dfs_component(v, u, comp, blocked);
    }
}

// Use BFS to find the farthest node from start in the current component.
pair<int, vector<int>> find_farthest(int start, const vector<bool> &compMark)
{
    vector<int> dist(n, -1);
    queue<int> qu;
    qu.push(start);
    dist[start] = 0;
    while (!qu.empty())
    {
        int cur = qu.front();
        qu.pop();
        for (int nxt : adj[cur])
        {
            if (!compMark[nxt] || dist[nxt] != -1)
                continue;
            dist[nxt] = dist[cur] + 1;
            qu.push(nxt);
        }
    }
    int farthest = start;
    for (int i = 0; i < n; i++)
    {
        if (compMark[i] && dist[i] > dist[farthest])
            farthest = i;
    }
    return {farthest, dist};
}

// Given compMark (true if a node is in the current component),
// get a diameter (a vector of nodes along a longest path) using two BFS’s.
vector<int> get_diameter(const vector<bool> &compMark)
{
    int start = -1;
    for (int i = 0; i < n; i++)
    {
        if (compMark[i])
        {
            start = i;
            break;
        }
    }
    if (start == -1)
        return {};
    auto ret1 = find_farthest(start, compMark);
    int u = ret1.first;
    auto ret2 = find_farthest(u, compMark);
    int v = ret2.first;
    vector<int> parent(n, -1), dist(n, -1);
    queue<int> qu;
    qu.push(u);
    dist[u] = 0;
    while (!qu.empty())
    {
        int cur = qu.front();
        qu.pop();
        for (int nxt : adj[cur])
        {
            if (!compMark[nxt])
                continue;
            if (dist[nxt] == -1)
            {
                dist[nxt] = dist[cur] + 1;
                parent[nxt] = cur;
                qu.push(nxt);
            }
        }
    }
    vector<int> path;
    int cur = v;
    while (cur != -1)
    {
        path.push_back(cur);
        cur = parent[cur];
    }
    reverse(path.begin(), path.end());
    return path;
}

// The recursive procedure to assign colours in a component.
// (See the long explanation in the commentary.)
// This solution uses the “recursive diameter–based approach”.
// Note that there are several correct ways to assign colours,
// and if the tree is not good, the function returns false.
bool solve_component(const vector<int> &compNodes, vector<bool> &blocked, int &currentColor)
{
    if (compNodes.size() == 1)
        return false; // a single vertex cannot be paired

    vector<bool> compMark(n, false);
    for (int u : compNodes)
        compMark[u] = true;

    vector<int> diam = get_diameter(compMark);
    if (diam.size() < 2)
        return false;

    // Assign a new colour to the two endpoints of the diameter.
    int col = currentColor++;
    int uEndpoint = diam.front();
    int vEndpoint = diam.back();
    if (ansColor[uEndpoint] != 0 || ansColor[vEndpoint] != 0)
        return false;
    ansColor[uEndpoint] = col;
    ansColor[vEndpoint] = col;
    // Here we mark endpoints as processed.
    blocked[uEndpoint] = true;
    blocked[vEndpoint] = true;

    vector<bool> onDiam(n, false);
    for (int u : diam)
        onDiam[u] = true;

    // Process branches attached to the diameter.
    for (int u : diam)
    {
        for (int v : adj[u])
        {
            if (blocked[v] || onDiam[v])
                continue;
            vector<int> subComp;
            function<void(int, int)> dfsSub = [&](int cur, int par)
            {
                subComp.push_back(cur);
                for (int nxt : adj[cur])
                {
                    if (nxt == par || blocked[nxt] || onDiam[nxt])
                        continue;
                    dfsSub(nxt, cur);
                }
            };
            dfsSub(v, u);
            if (!solve_component(subComp, blocked, currentColor))
                return false;
        }
    }
    return true;
}

void sol4()
{

    cin >> n;
    vector<int> par(n, -1);
    par[0] = -1;

    adj.assign(n, vector<int>());
    for (int i = 0; i < n - 1; i++)
    {
        int e;
        cin >> e;
        e--;
        par[i + 1] = e;
        adj[e].push_back(i + 1);
        adj[i + 1].push_back(e);
    }

    ansColor.assign(n, 0);
    vector<bool> blocked(n, false);

    vector<int> comp;
    dfs_component(0, -1, comp, vector<bool>(n, false)); // full tree

    int currentColor = 1;
    bool ok = solve_component(comp, blocked, currentColor);
    if (!ok)
    {
        cout << -1 << "\n";
        return;
    }

    // Check that every node got a colour.
    for (int i = 0; i < n; i++)
    {
        if (ansColor[i] == 0)
        {
            cout << -1 << "\n";
            return;
        }
    }

    for (int i = 0; i < n; i++)
    {
        cout << ansColor[i] << " ";
    }
    cout << "\n";
}

int main()
{
    int t;
    cin >> t;

    while (t--)
    {
        sol4();
    }

    return 0;
}
