#include <bits/stdc++.h>

#define forn(i, n) for (int i = 0; i < int(n); i++)

using namespace std;

const int N = 300 * 1000 + 13;

int n;
int a[N];
vector<int> g[N];
int red, blue;
int ans;

pair<int, int> dfs(int v, int p = -1)
{
    int r = (a[v] == 1), b = (a[v] == 2);
    for (auto u : g[v])
    {
        if (u != p)
        {
            auto tmp = dfs(u, v);
            ans += (tmp.first == red && tmp.second == 0) + (tmp.first == 0 && tmp.second == blue);
            r += tmp.first;
            b += tmp.second;
        }
    }
    return {r, b};
}

int main()
{
    int n;
    scanf("%d", &n);

    forn(i, n)
    {
        scanf("%d", &a[i]);
        red += (a[i] == 1);
        blue += (a[i] == 2);
    }

    forn(i, n - 1)
    {
        int v, u;
        scanf("%d%d", &v, &u);
        --v, --u;
        g[v].push_back(u);
        g[u].push_back(v);
    }

    ans = 0;
    dfs(0);
    printf("%d\n", ans);
    return 0;
}