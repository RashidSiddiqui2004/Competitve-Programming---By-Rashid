
class DSU
{
    int n;
    vector<int> parent, rank;

public:
    DSU(int _n) : n(_n)
    {
        parent.resize(n);
        rank.assign(n, 1);
        for (int i = 0; i < n; i++)
        {
            parent[i] = i; // Initialize each node as its own parent
        }
    }

    int find(int u)
    {
        // Path compression: make the parent of all nodes in the path point to the root
        if (parent[u] != u)
        {
            parent[u] = find(parent[u]);
        }
        return parent[u];
    }

    void unionSets(int u, int v)
    {
        int rootU = find(u);
        int rootV = find(v);

        if (rootU != rootV)
        {
            // Union by rank
            if (rank[rootU] < rank[rootV])
            {
                parent[rootU] = rootV;
                rank[rootV] += rank[rootU];
            }
            else if (rank[rootU] > rank[rootV])
            {
                parent[rootV] = rootU;
                rank[rootU] += rank[rootV];
            }
            else
            {
                parent[rootU] = rootV;
                rank[rootV]++;
            }
        }
    }

    void makeDSU(set<pair<int, int>> &edges)
    {
        for (auto i : edges)
        {
            unionSets(i.first, i.second);
        }
    }

    bool isConnected(int u, int v)
    {
        return find(u) == find(v);
    }

    int getNumberOfComponents()
    {
        unordered_set<int> uniqparents;
        for (auto i : parent)
        {
            uniqparents.insert(find(i));
        }
        return (int)uniqparents.size();
    }
};

void graphDecomposition()
{
    int n, m1, m2;
    cin >> n >> m1 >> m2;

    DSU objF(n), objG(n);

    set<pair<int, int>> edgesF, edgesG;
    set<pair<int, int>> newfedges;
    int u, v;

    for (int i = 0; i < m1; i++)
    {
        cin >> u >> v;
        edgesF.insert({u - 1, v - 1});
    }
    for (int i = 0; i < m2; i++)
    {
        cin >> u >> v;
        edgesG.insert({u - 1, v - 1});
    }

    objG.makeDSU(edgesG);

    // find operations of removing edges from graph F

    long oper1 = 0;

    for (auto it = edgesF.begin(); it != edgesF.end(); ++it)
    {
        int u = it->first, v = it->second;
        if (!objG.isConnected(u, v))
        {
            // Remove this edge from F
            oper1++;
        }
        else
        {
            newfedges.insert({u, v});
        }
    }

    objF.makeDSU(newfedges);

    int s1 = objF.getNumberOfComponents(), s2 = objG.getNumberOfComponents();

    long oper2 = abs(s1 - s2);

    long ans = oper1 + oper2;

    cout << ans << endl;
}
