#include <bits/stdc++.h>
using namespace std;

#define all(i) i.begin(), i.end()

void solve1()
{
    vector<int> v(6);
    cin >> v[1] >> v[2] >> v[4] >> v[5];

    unordered_map<int, int> fr;
    fr[(v[1] + v[2])]++;
    fr[(v[4] - v[2])]++;
    fr[(v[5] - v[4])]++;

    int maxi = 0;
    for (auto i : fr)
    {
        maxi = max(maxi, i.second);
    }

    cout << maxi << endl;
}

void solve2()
{
    int n, m;
    cin >> n >> m;

    vector<unordered_set<int>> cards(n);
    vector<int> fixorder(n);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            int curr;
            cin >> curr;
            cards[i].insert(curr);
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (cards[j].count(i))
            {
                fixorder[i] = j;
                break;
            }
        }
    }

    for (int i = 1; i < m; i++)
    {
        int hist = n;
        for (int j = 0; j < n; j++)
        {
            if (cards[fixorder[j]].count(hist + j))
            {
                continue;
            }
            else
            {
                cout << -1 << " \n";
                return;
            }
        }
        hist += n;
    }

    for (auto i : fixorder)
    {
        cout << i + 1 << " ";
    }

    cout << endl;
}

void solve3()
{
    int n, m;
    cin >> n >> m;

    unordered_map<int, int> freq;
    vector<int> v(n);
    for (int i = 0; i < n; i++)
    {
        int curr;
        cin >> curr;
        freq[curr]++;
        v[i] = curr;
    }

    int ans = 0;

    for (auto i : v)
    {
        if (!freq.count(i))
        {
            continue;
        }
        int rem = m - i;
        if (rem != i)
        {
            if (freq.count(rem))
            {
                ans++;
                freq[i]--;
                freq[rem]--;
                if (freq[i] == 0)
                {
                    freq.erase(i);
                }
                if (freq[rem] == 0)
                {
                    freq.erase(rem);
                }
            }
        }
        else
        {
            if (freq.count(rem) and freq[rem] > 1)
            {
                ans++;
                freq[i] -= 2;
                if (freq[i] == 0)
                {
                    freq.erase(i);
                }
            }
        }
    }

    cout << ans << endl;
}

// https://codeforces.com/contest/2060/problem/D
void solve4()
{
    int n;
    cin >> n;
    vector<long long> v(n);

    for (int i = 0; i < n; i++)
    {
        cin >> v[i];
    }

    if (v[0] <= v[1])
    {
        v[1] -= v[0];
        v[0] = 0;
    }
    else
    {
        cout << "NO\n";
        return;
    }

    for (int i = 1; i < n - 1; i++)
    {
        if (v[i] <= v[i + 1] && v[i - 1] == 0)
        {
            v[i + 1] -= v[i];
            v[i] = 0;
        }
        if (v[i] > v[i + 1])
        {
            cout << "NO\n";
            return;
        }
    }

    cout << "YES\n";
}

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

    vector<int> getparent()
    {
        for (int i = 0; i < n; i++)
        {
            this->find(i);
        }
        return this->parent;
    }

    unordered_map<int, vector<int>> getComponents()
    {
        getparent();
        unordered_map<int, vector<int>> mp;

        for (int i = 0; i < n; i++)
        {
            mp[parent[i]].push_back(i);
        }

        return mp;
    }
};

// https://codeforces.com/contest/2060/problem/E

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

// https://codeforces.com/problemset/problem/1490/D

void gettree(vector<pair<int, int>> &v, int l, int r, vector<int> &parent, int par = -1)
{
    if (r < l)
    {
        return;
    }
    if ((r - l) < 1)
    {
        if (l >= 0 and l < parent.size())
            parent[l] = par;
        return;
    }

    int ind = -1, currmax = -1;

    for (int i = l; i <= r; i++)
    {
        if (v[i].first > currmax)
        {
            ind = v[i].second;
            currmax = v[i].first;
        }
    }

    parent[ind] = par;

    gettree(v, l, ind - 1, parent, ind);
    gettree(v, ind + 1, r, parent, ind);
}

void getdepth(vector<vector<int>> &adj, vector<int> &ans, int node, int depth = 0)
{
    ans[node] = depth;

    if (adj[node].empty())
    {
        return;
    }

    for (auto i : adj[node])
    {
        getdepth(adj, ans, i, depth + 1);
    }
}

void permTranform()
{
    int n;
    cin >> n;

    vector<pair<int, int>> v(n);
    vector<int> par(n, -1);

    for (int i = 0; i < n; i++)
    {
        cin >> v[i].first;
        v[i].second = i;
    }

    vector<int> parent(n, -1);

    gettree(v, 0, n - 1, parent);

    vector<vector<int>> adj(n);
    int root = -1;

    for (int i = 0; i < n; i++)
    {
        if (parent[i] != -1)
        {
            adj[parent[i]].push_back(i);
        }
        else
        {
            root = i;
        }
    }

    vector<int> ans(n, -1);

    getdepth(adj, ans, root);

    for (auto i : ans)
    {
        cout << i << " ";
    }
    cout << endl;
}

// https://codeforces.com/problemset/problem/1592/B
void hemoseDsu()
{
    int n, x;
    cin >> n >> x;

    vector<long long> v(n);

    for (int i = 0; i < n; i++)
    {
        cin >> v[i];
    }
    vector<bool> mark(n, false);

    for (int i = 0; i < n; i++)
    {
        if ((i + x) < n)
        {
            mark[i + x] = true;
            mark[i] = true;
        }
    }
    vector<int> elems, posi;

    for (int i = 0; i < n; i++)
    {
        if (mark[i])
        {
            elems.push_back(v[i]);
            posi.push_back(i);
        }
        else
        {
            break;
        }
    }
    for (int i = x; i < n; i++)
    {
        elems.push_back(v[i]);
        posi.push_back(i);
    }

    sort(all(elems));
    int pos = 0;

    for (auto j : posi)
    {
        v[j] = elems[pos++];
    }

    // for (int i = 0; i < n; i++)
    // {
    //     for (int j = n - 1; (j - i) >= x; j--)
    //     {
    //         dsuObj.unionSets(i, j);
    //     }
    // }

    // auto comp = dsuObj.getComponents();

    // for (auto i : comp)
    // {
    //     vector<int> elems;
    //     for (auto j : i.second)
    //     {
    //         elems.push_back(v[j]);
    //     }

    //     sort(all(elems));
    //     int pos = 0;

    //     for (auto j : i.second)
    //     {
    //         v[j] = elems[pos++];
    //     }
    // }
    for (int i = 0; i < n - 1; i++)
    {
        if (v[i] > v[i + 1])
        {
            cout << "NO\n";
            return;
        }
    }

    cout << "YES\n";
    return;
}

void books()
{
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++)
    {
        cin >> v[i];
    }

    DSU obj = DSU(n);
    for (int i = 0; i < n; i++)
    {
        obj.unionSets(i, v[i] - 1);
    }

    vector<int> ans(n);
    auto t = obj.getComponents();

    for (auto i : t)
    {
        int ss = i.second.size();
        for (auto k : i.second)
        {
            ans[k] = ss;
        }
    }

    for (auto i : ans)
    {
        cout << i << " ";
    }
    cout << endl;
}

// https://codeforces.com/contest/1249/problem/C1

// use bitmask
void getnums(int curr, set<int> &v, int mask = 0)
{
    if (curr > 1e4)
    {
        return;
    }
    else
    {
        v.insert(curr);
    }
    for (int i = 0; i < 10; i++)
    {
        if ((mask & (1 << i)) == 0)
        {
            int newnum = curr + pow(3, i);
            if (newnum <= 1e4)
                getnums(newnum, v, mask | (1 << i));
        }
    }
}

void gooDNumbers()
{
    set<int> gennums;
    getnums(0, gennums);

    int q;
    cin >> q;
    while (q--)
    {
        int n;
        cin >> n;
        auto it = lower_bound(gennums.begin(), gennums.end(), n);
        if (it != gennums.end())
            cout << *it << endl;
        else
            cout << pow(3, 9) << endl;
    }
}

// https://codeforces.com/contest/1249/problem/C2

// optimized version of gooDNumbers

void gooDNumbersOptimized()
{
    long long n;
    cin >> n;
    long long temp = n;

    long long mask = 0;

    long long currnum = 0;

    // find highest set bit (base 3)
    int highestbit = static_cast<int>(log(n) / log(3));

    long long pot = pow(3, highestbit + 1);

    while (n > 0)
    {
        int currbit = static_cast<int>(log(n) / log(3));
        if (currbit == 0)
        {
            n -= 1;
            mask |= (1 << currbit);
            currnum += 1;
            break;
        }
        else
        {
            if ((mask & (1 << currbit)) != 0)
            {
                // for (int i = currbit - 1; i >= 0; i--)
                // {
                //     if ((mask & (1 << i)) != 0)
                //     {
                //         currnum += pow(3, i);
                //         n -= pow(3, i);
                //         mask |= (1 << i);
                //     }
                // }
            }
            else
            {
                n -= pow(3, currbit);
                currnum += pow(3, currbit);
                mask |= (1 << currbit);
            }
        }
    }

    int bit = 0;

    while (currnum < temp)
    {
        if ((mask & (1 << bit)) == 0)
        {
            currnum += pow(3, bit);
        }
        bit++;
    }

    long long res = min(currnum, pot);
    cout << res << endl;
}

void equalornot()
{
    string s;
    cin >> s;
    int n = 0;
    for (auto i : s)
    {
        if (i == 'N')
        {
            n++;
        }
    }
    if (n == 1)
    {
        cout << "NO\n";
    }
    else
    {
        cout << "YES\n";
    }
}

int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

void tunnel()
{
    int n;
    cin >> n;
    int r1, c1, r2, c2;
    cin >> r1 >> c1 >> r2 >> c2;
    r1--;
    c1--;
    r2--;
    c2--;

    vector<string> grid(n);

    for (int i = 0; i < n; i++)
    {
        cin >> grid[i];
    }

    // first check if it's possible to reach the other end w/o a tunnel

    queue<pair<int, int>> q;
    q.push({r1, c1});

    vector<pair<int, int>> boundary1s;
    vector<vector<int>> vis(n, vector<int>(n, 0));
    vis[r1][c1] = 1;
    boundary1s.push_back({r1, c1});

    while (!q.empty())
    {
        auto fr = q.front();
        q.pop();

        int x = fr.first, y = fr.second;
        for (int i = 0; i < 4; i++)
        {
            int newx = x + dx[i], newy = y + dy[i];
            if (newx >= 0 and newx < n and newy >= 0 and newy < n and !vis[newx][newy])
            {
                if (grid[newx][newy] == '0')
                {
                    boundary1s.push_back({newx, newy});
                    if (newx == r2 and newy == c2)
                    {
                        cout << 0 << endl;
                        return;
                    }
                    q.push({newx, newy});
                }
                vis[newx][newy] = 1;
            }
        }
    }

    queue<pair<int, int>> q_2;
    q_2.push({r2, c2});

    vector<pair<int, int>> boundary1s_2;
    vector<vector<int>> vis_2(n, vector<int>(n, 0));
    vis_2[r2][c2] = 1;
    boundary1s_2.push_back({r2, c2});

    while (!q_2.empty())
    {
        auto fr = q_2.front();
        q_2.pop();

        int x = fr.first, y = fr.second;
        for (int i = 0; i < 4; i++)
        {
            int newx = x + dx[i], newy = y + dy[i];
            if (newx >= 0 and newx < n and newy >= 0 and newy < n and !vis_2[newx][newy])
            {
                if (grid[newx][newy] == '0')
                {
                    boundary1s_2.push_back({newx, newy});
                    q_2.push({newx, newy});
                }
                vis_2[newx][newy] = 1;
            }
        }
    }

    long long mindist = LLONG_MAX;

    for (auto i : boundary1s)
    {
        for (auto j : boundary1s_2)
        {
            long long x = abs(i.first - j.first), y = abs(i.second - j.second);
            long long curr = (x * x) + (y * y);
            mindist = min(mindist, curr);
        }
    }

    cout << mindist << endl;
}

// https://codeforces.com/problemset/problem/902/B

int dfs(int node, vector<vector<int>> &adj, int passedcolor, vector<int> &reqcolor)
{
    int ans = 0;
    if (reqcolor[node] != passedcolor)
    {
        ans++;
    }
    if (adj[node].empty())
    {
        return ans;
    }
    for (auto i : adj[node])
    {
        ans += dfs(i, adj, reqcolor[node], reqcolor);
    }
    return ans;
}

void coloringtree()
{
    int n;
    cin >> n;
    vector<vector<int>> adj(n);
    for (int i = 1; i < n; i++)
    {
        int par;
        cin >> par;
        adj[par - 1].push_back(i);
    }

    vector<int> reqcolor(n);
    for (int i = 0; i < n; i++)
    {
        cin >> reqcolor[i];
    }

    int ans = dfs(0, adj, 0, reqcolor);
    cout << ans << endl;
}

// 1 2 5 20
// 3 4 10 30
//  3 3 2 2
// 6 + 6 + 10 + 20

void heavyint()
{
    int n;
    cin >> n;
    vector<long> a(n), b(n), c(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++)
    {
        cin >> b[i];
    }
    for (int i = 0; i < n; i++)
    {
        cin >> c[i];
    }
    sort(all(a));
    sort(all(b));
    sort(all(c), greater<>());

    long res = 0;

    for (int i = 0; i < n; i++)
    {
        res += (b[i] - a[i]) * c[i];
    }

    cout << res << endl;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

    int t = 1;
    std::cin >> t;
    while (t--)
        heavyint();
    return 0;
}