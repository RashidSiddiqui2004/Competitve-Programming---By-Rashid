// https://www.codechef.com/problems/kUNIQUE?tab=statement
void s3Greedy()
{
    int n, k;
    cin >> n >> k;
    vi arr(n);
    input_vector(arr);

    map<int, int> mp;
    int seg = n / k;

    for (auto &it : arr)
    {
        if (++mp[it] > seg)
        {
            cout << -1 << endl;
            return;
        }
    }

    // instead of priority queue, because elements are also placed in sorted order in set
    // so we can use set as well =: remember djikstra's algo using set by striver

    set<pair<int, int>> s;

    for (auto &it : mp)
    {
        s.insert({it.second, it.first});
    }

    vector<vector<int>> block(seg);

    for (int i = 0; i < seg; i++)
    {
        if (block[i].size() == k)
            continue;
        while (!s.empty() && s.rbegin()->first == seg - i)
        {
            auto x = prev(s.end());
            for (int j = i; j < seg; j++)
            {
                block[j].pb(x->second);
            }
            mp.erase(x->second);
            s.erase(x);
        }
        for (auto it = begin(mp); it != end(mp) && block[i].size() < k;)
        {
            block[i].pb(it->first);
            s.erase(s.find({it->second, it->first}));
            if (--it->second == 0)
            {
                it = mp.erase(it);
            }
            else
            {
                s.insert({it->second, it->first});
                it++;
            }
        }
    }
    for (auto &it : block)
    {
        sort(all(it));
        for (auto &i : it)
            cout << i << " ";
    }
    cout << endl;
}