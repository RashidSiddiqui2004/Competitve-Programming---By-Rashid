
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define fl(i, n) for (int i = 0; i < n; i++)
#define fl1(i, n) for (int i = 1; i <= n; i++)
#define flm(i, m, n) for (int i = m; i < n; i++)
#define fl1m(i, m, n) for (int i = m; i <= n; i++)
#define pb push_back
#define all(x) x.begin(), x.end()
#define one(x) memset(x, -1, sizeof(x))
#define zero(x) memset(x, 0, sizeof(x))
#define sort(x) sort(all(x))
#define sortallr(x) sort(x.rbegin(), x.rend())
typedef pair<int, int> pii;

int main()
{
    int n, d;
    cin >> n >> d;
    vector<pii> v(n);
    vector<int> tempv(n);

    // index stores the index of the occurences of an element 'x' in the original array
    //  for each x belonging to the array v

    unordered_map<int, vector<int>> index;

    fl(i, n)
    {
        cin >> v[i].first;
        v[i].second = i;
        tempv[i] = v[i].first;
        index[v[i].first].push_back(i);
    }

    sort(v);

    vector<vector<int>> aps;
    unordered_map<int, unordered_set<int>> mp;

    fl(i, n)
    {
        flm(j, i + 1, n)
        {
            int diff = v[j].first - v[i].first;
            int diffIndex = v[j].second - v[i].second;

            if ((!mp.count(v[i].first) || !mp[v[i].first].count(diff)) and diffIndex <= d)
            {
                vector<int> tempAP = {v[i].first, v[j].first};
                int cd = diff;
                int lastIndex = v[j].second;

                mp[v[i].first].insert(cd);
                mp[v[j].first].insert(cd);

                while (lastIndex < n)
                {
                    int next = tempAP.back() + cd;

                    if (index.find(next) == index.end())
                    {
                        break;
                    }
                    else
                    {
                        auto indices = index[next];
                        auto ub = upper_bound(all(indices), lastIndex - d - 1);

                        if (ub == indices.end())
                        {
                            break;
                        }
                        else
                        {
                            if (*ub <= (lastIndex + d))
                            {
                                lastIndex = *ub;
                                tempAP.push_back(tempv[lastIndex]);
                                mp[next].insert(cd);
                            }
                            else
                            {
                                break;
                            }
                        }
                    }
                }
                if (tempAP.size() > 2)
                {
                    aps.push_back(tempAP);
                }
            }
        }
    }

    int apcount = 1;

    for (auto i : aps)
    {
        cout << "AP " << apcount << ": ";
        for (auto j : i)
        {
            cout << j << " ";
        }
        cout << endl;

        apcount++;
    }
}