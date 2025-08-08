#include "bits/stdc++.h"
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template <typename T = int>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

const int N = 100'005;
void solve()
{
    int n;
    cin >> n;
    vector<array<int, 4>> a;
    for (int i = 0; i < n; i++)
    {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        assert(x1 != x2 || y1 != y2);
        a.push_back({x1, y1, x2, y2});
    }

    long long res = 0;
    auto work = [&]()
    {
        vector<vector<int>> add(N), remove(N);
        vector<vector<int>> Q(N);
        vector<int> cnt(N, 0);
        vector<int> ans(n);
        int ptr = 0;

        // vertical segments are stored in Q

        for (auto &[x1, y1, x2, y2] : a)
        {
            if (y1 == y2)
            { // Horizontal Segment
                if (x1 > x2)
                    swap(x1, x2);
                add[x1].push_back(y1);    // Stores y-coordinates where horizontal lines starts at x
                remove[x2].push_back(y1); // Stores y-coordinates where horizontal lines ends at x
            }
            else
            { // Vertical Segment
                if (y1 > y2)
                    swap(y1, y2);
                Q[x1].push_back(ptr);
            }
            ptr++;
        }

        ordered_set<int> t;

        for (int i = 1; i < N; i++)
        {
            for (auto x : add[i])
            {
                ++cnt[x];
                t.insert(x);
            }
            for (int j : Q[i])
            {
                assert(a[j][3] > a[j][1]);
                int val = t.order_of_key(a[j][3]) - t.order_of_key(a[j][1] + 1);
                ans[j] += val;
                res += val;
            }
            for (auto x : remove[i])
            {
                --cnt[x];
                t.erase(x);
            }
            for (auto x : add[i])
            {
                --cnt[x];
            }
            for (int j : Q[i])
            {
                int val = cnt[a[j][3]] + cnt[a[j][1]];
                ans[j] += val;
                res += val;
            }
            for (auto x : add[i])
            {
                ++cnt[x];
            }
        }
        return ans;
    };

    auto L = work();
    for (auto &[x1, y1, x2, y2] : a)
    {
        swap(x1, y1), swap(x2, y2);
    }
    auto R = work();
    cout << res / 2 << endl;
    for (int i = 0; i < n; i++)
        cout << L[i] + R[i] << " ";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
    while (t--)
        solve();
}
