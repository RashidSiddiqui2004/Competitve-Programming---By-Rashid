#include <bits/stdc++.h>
using namespace std;

// Macros
#define fast_io                  \
    ios::sync_with_stdio(false); \
    cin.tie(nullptr);            \
    cout.tie(nullptr);
#define pb push_back
#define mp make_pair
#define all(v) (v).begin(), (v).end()
#define rall(v) (v).rbegin(), (v).rend()
#define fi first
#define se second
#define sz(x) (int)((x).size())
#define endl '\n'
#define fl(i, n) for (int i = 0; i < n; i++)
#define fr(i, n) for (int i = n - 1; i >= 0; i--)
#define ha           \
    cout << "YES\n"; \
    return;
#define na          \
    cout << "NO\n"; \
    return;

// Typedefs
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pii> vpii;
typedef vector<pll> vpll;

// Constants
const int MOD = 1e9 + 7;
const ll INF = 1e18;
const double EPS = 1e-9;

// Debugging
#ifndef ONLINE_JUDGE
#define debug(x) cerr << #x << " = " << (x) << endl;
#else
#define debug(x)
#endif

// Utility Functions
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
ll lcm(ll a, ll b) { return a / gcd(a, b) * b; }

ll mod_add(ll a, ll b, ll m = MOD)
{
    return (a + b) % m;
}

ll mod_sub(ll a, ll b, ll m = MOD)
{
    return (a - b + m) % m;
}

ll mod_mul(ll a, ll b, ll m = MOD)
{
    return (a * b) % m;
}

ll mod_pow(ll a, ll b, ll m = MOD)
{
    ll res = 1;
    while (b > 0)
    {
        if (b & 1)
            res = mod_mul(res, a, m);
        a = mod_mul(a, a, m);
        b >>= 1;
    }
    return res;
}

ll mod_inv(ll a, ll m = MOD)
{
    // Modular inverse using Fermat's Little Theorem: a^(m-2) % m
    return mod_pow(a, m - 2, m);
}

vector<ll> factorial, inv_factorial;

void precompute_factorials(int maxN, ll m = MOD)
{
    factorial.resize(maxN + 1);
    inv_factorial.resize(maxN + 1);

    factorial[0] = 1;
    for (int i = 1; i <= maxN; ++i)
    {
        factorial[i] = mod_mul(factorial[i - 1], i, m);
    }

    inv_factorial[maxN] = mod_inv(factorial[maxN], m);

    // (n)^-1 = ((n+1)^-1) * (n+1)
    for (int i = maxN - 1; i >= 0; --i)
    {
        inv_factorial[i] = mod_mul(inv_factorial[i + 1], i + 1, m);
    }
}

ll ncr(ll n, ll r, ll m = MOD)
{
    if (r > n || r < 0)
        return 0;
    return mod_mul(factorial[n], mod_mul(inv_factorial[r], inv_factorial[n - r], m), m);
}

template <typename T>
void input_vector(vector<T> &v)
{
    for (auto &x : v)
        cin >> x;
}

template <typename T>
void print_vector(const vector<T> &v)
{
    for (const auto &x : v)
        cout << x << " ";
    cout << endl;
}

void sol1()
{
    int n, m;
    cin >> n >> m;
    unordered_set<ll> v(m);

    for (int i = 0; i < m; i++)
    {
        int e;
        cin >> e;
        v.insert(e);
    }

    vector<int> ans;

    for (int i = 1; i <= n; i++)
    {
        if (!v.count(i))
        {
            ans.push_back(i);
        }
    }
    cout << ans.size() << endl;

    for (auto i : ans)
    {
        cout << i << " ";
    }
}

void sol3()
{
    int a1, a2, a3;
    cin >> a1 >> a2 >> a3;

    bool b1 = (a1 * a2) == a3;
    bool b2 = (a2 * a3) == a1;
    bool b3 = (a1 * a3) == a2;

    if (b1 || b2 || b3)
    {
        cout << "Yes\n";
    }
    else
    {
        cout << "No\n";
    }
}

void heko()
{
    int n;
    cin >> n;
    vector<pair<int, unordered_map<int, int>>> freq(n);

    fl(i, n)
    {
        int sz;
        cin >> sz;

        freq[i].first = sz;

        fl(j, sz)
        {
            int e;
            cin >> e;
            freq[i].second[e]++;
        }
    }
    double maxp = 0.0;

    fl(i, n)
    {
        for (int j = i + 1; j < n; j++)
        {
            double currprob = 0.0;
            int s1 = freq[i].first, s2 = freq[j].first;

            for (auto e1 : freq[i].second)
            {
                int num = e1.first;
                int fr = 0;
                if (freq[j].second.count(num))
                {
                    fr = freq[j].second[num];
                    double t = (num / s1) * (fr / s2);

                    currprob += t;
                }
            }

            maxp = max(maxp, currprob);
        }
    }

    cout << maxp << endl;
}

void helper()
{
    int n;
    cin >> n;
    vector<pair<int, unordered_map<int, int>>> freq(n);

    for (int i = 0; i < n; i++)
    {
        int sz;
        cin >> sz;

        freq[i].first = sz;

        for (int j = 0; j < sz; j++)
        {
            int e;
            cin >> e;
            freq[i].second[e]++;
        }
    }

    double maxp = 0.0;

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            double currprob = 0.0;

            int s1 = freq[i].first, s2 = freq[j].first;

            for (auto &e1 : freq[i].second)
            {
                int num = e1.first, fr1 = e1.second;
                if (freq[j].second.count(num))
                {
                    int fr = freq[j].second[num];
                    double t = (double(fr1) / s1) * (double(fr) / s2);
                    currprob += t;
                }
            }

            maxp = max(maxp, currprob);
        }
    }

    cout << fixed << setprecision(8) << maxp << endl;
}

class DSU
{
    vector<int> parent, size;

public:
    DSU(int n)
    {
        parent.resize(n);
        size.resize(n, 1);
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int find(int x)
    {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    void unionSets(int x, int y)
    {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX != rootY)
        {
            if (size[rootX] < size[rootY])
                swap(rootX, rootY);
            parent[rootY] = rootX;
            size[rootX] += size[rootY];
        }
    }
};

void sol5()
{
    int n, m;
    cin >> n >> m;

    vector<pll> extras;
    DSU dsu(n);
    int root = 0;

    fl(i, m)
    {
        int u, v;
        cin >> u >> v;
        --u, --v;

        if (i == 0)
        {
            root = u;
        }

        if (dsu.find(u) == dsu.find(v))
        {
            extras.push_back({i + 1, v});
        }

        dsu.unionSets(u, v);
    }

    bool isConnected = true;
    for (int i = 0; i < n; i++)
    {
        if (dsu.find(i) != dsu.find(root))
        {
            isConnected = false;
            break;
        }
    }

    if (isConnected)
    {
        cout << "0\n";
        return;
    }

    vector<vector<ll>> oper;
    int ptr = 0;

    fl(i, n)
    {
        if (dsu.find(i) != dsu.find(root))
        {
            oper.push_back({extras[ptr].first, extras[ptr].second, i});
            dsu.unionSets(root, i);
            ptr++;
        }
    }

    cout << oper.size() << endl;

    for (auto i : oper)
    {
        cout << i[0] << " " << i[1] + 1 << " " << i[2] + 1 << endl;
    }
}

void sol6()
{
    int n;
    cin >> n;

    vector<pll> vp(n);

    fl(i, n)
    {
        cin >> vp[i].first;
    }

    fl(i, n)
    {
        cin >> vp[i].second;
    }

    ll maxcost = 0;

    fl(i, n)
    {
        maxcost += max(vp[i].first, vp[i].second);
    }

    ll res = maxcost + min(vp[0].first, vp[0].second);

    fl(i, n)
    {
        res = max(res, maxcost + min(vp[i].first, vp[i].second));
    }

    cout << res << endl;
}

void sol7()
{
    int n;
    cin >> n;
    vector<ll> v(n);
    input_vector(v);

    vector<ll> ans(n);

    int p1 = 0, p2 = n - 1;
    int ptr = 0;

    while (p1 <= p2)
    {
        ans[ptr++] = v[p1++];
        if (ptr < n)
            ans[ptr++] = v[p2--];
    }

    print_vector(ans);
}

void r1()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    string req = "2020";

    int p1 = 0, fr = 0;

    while (p1 < 4 and req[p1] == s[fr])
    {
        fr++;
        p1++;
    }

    int p2 = 3, back = n - 1;
    while (p2 >= 0 and req[p2] == s[back])
    {
        p2--;
        back--;
    }

    int sum = (p1 + (4 - p2 - 1));

    if (sum >= 4)
    {
        cout << "YES" << endl;
    }
    else
    {
        cout << "NO\n";
    }
}

vector<string> uniqNums;

void rhelp(string &curr)
{
    uniqNums.push_back(curr);

    for (int i = 0; i < 10; i++)
    {
        char ch = '0' + i;
        if (curr.find(ch) == string::npos)
        {
            curr += ch;
            rhelp(curr);
            curr.pop_back();
        }
    }
}

void r2()
{
    int n, w;
    cin >> n >> w;

    vector<list<int>> coord(w);

    for (int i = 0; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        coord[y - 1].push_back(x);
    }

    for (int i = 0; i < w; i++)
    {
        int sz = coord[i].size();
        if (sz > 0)
        {
            sort(all(coord));
        }
    }

    int q;
    cin >> q;

    vector<vector<int>> queries(q);

    for (int i = 0; i < q; i++)
    {
        cin >> queries[i][0] >> queries[i][1];
        queries[i][2] = i;
    }

    sort(all(queries)); // according to time queried about

    vector<bool> ans(n);

    int currtime = 0;

    for (auto i : queries)
    {
        int askedtime = i[0], id = i[1], qid = i[2];

        while (currtime < askedtime)
        {
            int maxTime = 0;
            bool isposs = true;
            // check if all cols have atleast 1 block
            for (int j = 0; j < w; j++)
            {
                if (coord[j].empty())
                {
                    isposs = false;
                    break;
                }
                maxTime = max(maxTime, coord[j].front());
                coord[j].pop_front();
            }
            if (!isposs)
            {
                break;
            }
            currtime = maxTime;
        }
    }

    for (auto i : ans)
    {
        cout << i << " ";
    }
    cout << endl;
}

void r3()
{
    int n;
    cin >> n;
    vector<ll> v(n);

    input_vector(v);
    sort(all(v));

    ll minb = LLONG_MAX;

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            ll a2 = (v[i] + v[j]) / 2;
            auto itr = lower_bound(v.begin() + i, v.begin() + j, a2);

            --itr;

            int ptr = itr - v.begin();
            ptr = max(ptr, i + 1);

            for (int k = 0; k < 10 and ptr < j and ptr >= 0; k++)
            {
                ll ans = abs(v[i] + v[j] - 2 * v[ptr++]);
                minb = min(minb, ans);
            }
        }
    }

    cout << minb << endl;
}

int isposs(vector<pll> &v, ll n, ll k)
{
    int i = 0;
    int maxprob = 0;

    ll maxWaitime = 0;

    for (; i < n; i++)
    {
        if (v[i].second <= k)
        {
            k -= v[i].second;
            maxWaitime = max(maxWaitime, v[i].second - v[i].first);
            maxprob++;
        }
        else
        {
            break;
        }
    }

    // 2 options

    ll remk = k;

    for (; i < n; i++)
    {
        if (v[i].first <= remk)
        {
            maxprob++;
            break;
        }
        else
        {
            long long sum = remk - v[i].second;
            sum += maxWaitime;

            if (sum >= 0)
            {
                maxprob++;
                break;
            }
        }
    }

    return maxprob;
}

bool comp(pair<long long, long long> &P, pair<long long, long long> &Q)
{
    if (P.second == Q.second)
        return P.first < Q.first;
    return P.second < Q.second;
}

void r4()
{
    ll n, k;
    cin >> n >> k;

    vector<pll> v(n);

    fl(i, n)
    {
        cin >> v[i].first;
    }
    fl(i, n)
    {
        cin >> v[i].second;
        v[i].second += v[i].first;
    }

    sort(all(v), comp);

    int ans = isposs(v, n, k);

    cout << ans << endl;
}

void r5()
{
    int n;
    cin >> n;
    vector<ll> v(n);

    fl(i, n)
    {
        cin >> v[i];
    }

    ll q;
    cin >> q;

    bool changed = false;

    while (q--)
    {
        int type;
        cin >> type;

        if (type == 1)
        {
            int x, y;
            cin >> x >> y;
            v[x - 1] = y;
            changed = true;
        }
        else
        {
            ll l, r, g;
            cin >> l >> r >> g;
            --l;

            int ans = 0;

            for (int i = l; i < r; i++)
            {
                int gcd = __gcd(g, v[i]);
                if (gcd == 1)
                    ans++;
            }

            changed = false;

            cout << ans << "\n";
        }
    }
}

void r6()
{
    string s;
    cin >> s;

    int n = s.size();

    // finding LNDS => longest non-decreasing subsequence

    vector<pii> lis(n);
    int lndslen = 0;
    // also mark used indices

    vector<int> usedIndices(n, 0);

    int i = 0;
    for (auto ch : s)
    {
        int asciicode = ch - 'a';
        if (lndslen == 0 || (lis[lndslen - 1].first <= asciicode))
        {
            lis[lndslen++] = {asciicode, i};
            usedIndices[i] = 1;
        }
        else
        {
            int lb = upper_bound(lis.begin(), lis.begin() + lndslen, make_pair(asciicode, n)) - lis.begin();
            int prevInd = lis[lb].second;
            usedIndices[prevInd] = 0;
            usedIndices[i] = 1;
            lis[lb] = {asciicode, i};
        }
        i++;
    }

    unordered_set<int> used;

    for (int i = 0; i < n; i++)
    {
        if (usedIndices[i])
        {
            used.insert(i);
        }
    }

    usedIndices.assign(n, 0);

    vector<pii> lds(n);
    int lnislen = 0;

    i = 0;
    for (auto ch : s)
    {
        int asciicode = ch - 'a';
        if (lnislen == 0 || (lds[lnislen - 1].first >= asciicode))
        {
            lds[lnislen++] = {asciicode, i};
            usedIndices[i] = 1;
        }
        else
        {
            int lb = upper_bound(lds.begin(), lds.begin() + lnislen, make_pair(asciicode, i),
                                 [](const pii &p1, const pii &p2)
                                 {
                                     return p1.first > p2.first;
                                 }) -
                     lds.begin();

            if (lb > 0)
            {
                lb--;
                int prevInd = lds[lb].second;
                usedIndices[prevInd] = 0;
                usedIndices[i] = 1;
                lds[lb] = {asciicode, i};
            }
        }
        i++;
    }

    for (int i = 0; i < n; i++)
    {
        if (usedIndices[i])
        {
            cout << i << " ";
            used.insert(i);
        }
    }

    cout << (int)used.size() << endl;
}

void r7()
{
    int n;
    cin >> n;
    vector<ll> v(n);
    input_vector(v);

    sort(all(v));

    unordered_map<ll, ll> st;

    for (int i = 0; i < n; i += 2)
    {
        if (v[i] == v[i + 1])
        {
            st[v[i]]++;
            st[v[i] + st[v[i]]]++;
        }
        else
        {
            if (st.count(v[i]))
            {
                int diff = v[i + 1] - v[i];
                if (diff <= st[v[i]])
                {
                    st[v[i + 1]]++;
                }
                else
                {
                    cout << "No\n";
                    return;
                }
            }
            else
            {
                cout << "No\n";
                return;
            }
        }
    }

    cout << "Yes\n";
    return;
}

// stemming
void r8()
{
    int n;
    cin >> n;

    vector<string> v(n);
    input_vector(v);

    string ans = "";
    int max_size = 0;

    sort(all(v), [](string &s1, string &s2)
         {
        int n1=s1.size(), n2=s2.size();
        if(n1!=n2){
            return n1<n2;
        } 
        return s1<s2; });

    string smallest = v[0];

    int len = smallest.size();

    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j <= len - i; j++)
        {
            string curr = smallest.substr(i, j + 1);

            bool ispres = true;

            for (int t = 0; t < n; t++)
            {
                if (v[t].find(curr) == string::npos)
                {
                    ispres = false;
                    break;
                }
            }

            if (ispres)
            {
                int sz = curr.size();
                if (sz == max_size)
                {
                    ans = min(ans, curr);
                }
                else if (sz > max_size)
                {
                    max_size = sz;
                    ans = curr;
                }
            }
        }
    }

    cout << ans << endl;
}

void r9()
{
}

void s1()
{
    int n;
    cin >> n;

    vector<string> blocked, unblocked;

    fl(i, n)
    {
        char t;
        cin >> t;
        string name;
        cin >> name;

        if (t == '+')
        {
            unblocked.push_back(name);
        }
        else
        {
            blocked.push_back(name);
        }
    }

    sort(all(blocked));

    unordered_set<string> blst(all(blocked));

    // -1 if a prefix of unblocked site is blocked
    for (auto i : unblocked)
    {
        int len = i.size();
        string curr = "";

        for (int j = 0; j < len; j++)
        {
            curr += i[j];
            if (blst.count(curr))
            {
                cout << -1 << endl;
                return;
            }
        }
    }

    // now find filters
    unordered_set<string> filters;

    unordered_map<char, vector<string>> mp;

    for (auto i : unblocked)
    {
        mp[i[0]].push_back(i);
    }

    for (auto i : blst)
    {
        int maxDiff = 1;

        for (auto j : mp[i[0]])
        {
            bool ch = false;
            for (int t = 0; t < i.size() and t < j.size(); t++)
            {
                if (i[t] != j[t])
                {
                    ch = true;
                    maxDiff = max(maxDiff, t + 1);
                    break;
                }
            }
            if (!ch)
            {
                maxDiff = (int)j.size() + 1;
            }
        }
        filters.insert(i.substr(0, maxDiff));
    }

    cout << filters.size() << endl;

    vector<string> temp(all(filters));

    sort(all(temp));

    for (auto i : temp)
    {
        cout << i << "\n";
    }
}

void s2()
{
    string s;
    cin >> s;

    int k;
    cin >> k;

    int n = s.size();
    ll ans = 0;

    for (int i = 0; i < n; i++)
    {
        unordered_map<char, int> fr;
        for (int j = i; j < n; j++)
        {
            fr[s[j]]++;
            if (fr.size() >= k)
            {
                int firstfr = fr.begin()->second;
                bool valid = true;
                for (auto p : fr)
                {
                    if (firstfr != p.second)
                    {
                        valid = false;
                        break;
                    }
                }
                if (valid)
                {
                    ans++;
                }
            }
        }
    }

    cout << ans << endl;
}

void s3()
{
    ll n, k;
    cin >> n >> k;

    map<ll, ll> fr;

    fl(i, n)
    {
        ll e;
        cin >> e;
        fr[e]++;
    }

    int numSubarrays = n / k; // each of size k

    for (auto i : fr)
    {
        if (i.second > (numSubarrays))
        {
            cout << -1 << endl;
            return;
        }
    }

    vector<vector<ll>> ans(numSubarrays, vector<ll>());

    for (auto i : fr)
    {
        ll e = i.first, freq = i.second;
        int p = 0;
        while (freq > 0)
        {
            if (p >= numSubarrays)
                p = 0;

            int sz = ans[p].size();
            if (sz < k)
            {
                ans[p].push_back(e);
                freq--;
            }
            p++;
        }
    }

    for (auto i : ans)
    {
        for (auto e : i)
        {
            cout << e << " ";
        }
    }

    cout << endl;
}

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

// https://www.codechef.com/problems/CHEFSOC2
void dpsolver(int n, int m, int currDog, vector<int> &a, vector<ll> &ans, int turn = 0)
{
    if (turn == m)
    {
        ans[currDog] += 1 % MOD;
        return;
    }

    int prev = currDog - a[turn], next = currDog + a[turn];

    if (prev >= 0)
    {
        dpsolver(n, m, prev, a, ans, turn + 1);
    }

    if (next < n)
    {
        dpsolver(n, m, next, a, ans, turn + 1);
    }
}

ll dp[1001][1001];

ll dpsolver2(int n, int m, int currDog, int reqDog, vector<int> &a, int turn)
{
    if (currDog < 0 || currDog >= n)
    {
        return 0ll;
    }

    if (turn == -1)
    {
        return (currDog == reqDog);
    }

    if (dp[currDog][turn] != -1)
    {
        return dp[currDog][turn];
    }

    ll ans = (dpsolver2(n, m, currDog + a[turn], reqDog, a, turn - 1) +
              dpsolver2(n, m, currDog - a[turn], reqDog, a, turn - 1)) %
             MOD;

    return dp[currDog][turn] = ans;
}

void s4()
{
    int n, m, x;
    cin >> n >> m >> x;
    x--;

    memset(dp, -1, sizeof(dp));

    vector<int> a(m);
    input_vector(a);

    vector<ll> ans(n, 0ll);

    for (int i = 0; i < n; i++)
    {
        ans[i] = dpsolver2(n, m, i, x, a, m - 1);
    }

    print_vector(ans);
}

// https://www.codechef.com/problems/REIGN
void s5()
{
    ll n, k;
    cin >> n >> k;

    vector<ll> a(n);
    for (ll &x : a)
        cin >> x;

    vector<ll> prefixMax(n, LLONG_MIN), suffixMax(n, LLONG_MIN);

    // Compute prefix max subarray sum using kadane's algorithm

    ll maxsum = LLONG_MIN, currsum = 0;

    for (int i = 0; i < n; i++)
    {
        currsum += a[i];
        maxsum = max(maxsum, currsum);

        prefixMax[i] = maxsum;
        if (currsum < 0)
        {
            currsum = 0;
        }
    }

    maxsum = LLONG_MIN, currsum = 0;
    for (int i = n - 1; i >= 0; i--)
    {
        currsum += a[i];
        maxsum = max(maxsum, currsum);
        if (currsum < 0)
            currsum = 0;
        suffixMax[i] = maxsum;
    }

    ll ans = LLONG_MIN;

    // Iterate over blocked intervals
    for (int i = 1; i <= n - k - 1; i++)
    {
        ll leftMax = (i > 0) ? prefixMax[i - 1] : LLONG_MIN;
        ll rightMax = (i + k < n) ? suffixMax[i + k] : LLONG_MIN;
        ans = max(ans, leftMax + rightMax);
    }

    cout << ans << endl;
}

void s6()
{
    ll ones, zeros;
    cin >> ones >> zeros;

    ll res = 0ll;

    ll total = ones + zeros;

    // find all factors of total

    vector<ll> factors;

    for (ll i = 2; i <= sqrt(total); i++)
    {
        if ((total % i) == 0)
        {
            factors.push_back(i);
            ll rem = total / i;
            if (rem != i)
            {
                factors.push_back(rem);
            }
        }
    }

    ll totalWords = (factorial[total] / ((factorial[ones] * factorial[zeros]) % 531169)) % 531169;

    for (auto blockSize : factors)
    {
        int numBlocks = total / blockSize;
        for (ll i = 0; i <= blockSize; i++)
        {
            ll reqOnes = i * numBlocks, reqZeros = (blockSize - i) * numBlocks;

            if (reqOnes <= ones and reqZeros <= zeros)
            {
                totalWords = (totalWords - ((factorial[blockSize] / ((factorial[i] * factorial[blockSize - i]) % 531169))) + 531169) % 531169;
            }
        }
    }

    cout << totalWords << endl;
}

ll dp2[502][502];

ll helpers7(vector<vector<int>> &grid, int x, int y)
{
    int n = grid.size(), m = grid[0].size();

    if (x == (n - 1) and y == (m - 1))
    {
        return 0;
    }

    if (dp2[x][y] != -1)
    {
        return dp2[x][y];
    }

    ll ans = 1;

    int curr = grid[x][y];

    for (int j = x + 1; j < n; j++)
    {
        if (grid[j][y] <= curr)
        {
            ans = max(ans, 1 + helpers7(grid, j, y));
        }
    }

    for (int j = y + 1; j < m; j++)
    {
        if (grid[x][j] >= curr)
        {
            ans = max(ans, 1 + helpers7(grid, x, j));
        }
    }

    return dp2[x][y] = ans;
}

void smartFrog()
{
    int n, m;
    cin >> n >> m;

    memset(dp2, -1, sizeof(dp2));

    dp2[n - 1][m - 1] = 1;

    vector<vector<int>> grid(n, vector<int>(m));

    fl(i, n)
    {
        input_vector(grid[i]);
    }

    ll ans = 0;

    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = m - 1; j >= 0; j--)
        {
            ll curr = helpers7(grid, i, j);
            ans = max(ans, curr);
        }
    }

    cout << ans + 1 << endl;
}

void smartFrogOptimized()
{
    int n, m;
    cin >> n >> m;

    vector<vector<int>> grid(n, vector<int>(m));

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            cin >> grid[i - 1][j - 1];
            dp2[i][j] = 1;
        }
    }

    ll ans = 1;

    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = m - 1; j >= 0; j--)
        {
            int curr = grid[i][j];

            for (int p = i + 1; p < n; p++)
            {
                if (grid[p][j] <= curr)
                {
                    dp2[i][j] = max(dp2[i][j], 1 + dp2[p][j]);
                    ans = max(ans, dp2[i][j]);
                }
                if (grid[p][j] == grid[i][j])
                    break;
            }

            for (int p = j + 1; p < m; p++)
            {
                if (grid[i][p] >= curr)
                {
                    dp2[i][j] = max(dp2[i][j], 1 + dp2[i][p]);
                    ans = max(ans, dp2[i][j]);
                }
                if (grid[i][p] == grid[i][j])
                    break;
            }
        }
    }

    cout << ans << endl;
}

void s8()
{
    int n;
    cin >> n;
    unordered_map<char, vector<pair<int, string>>> mp;

    string str = "";

    fl(i, n)
    {
        string s;
        cin >> s;
        if (str == "")
        {
            str = s;
        }
        else
        {
            str = min(str, s);
        }
        mp[s[0]].push_back({i, s});
    }

    int q;
    cin >> q;

    while (q--)
    {
        int r;
        string s;

        cin >> r;
        cin >> s;

        if (!mp.count(s[0]))
        {
            cout << str << "\n";
            continue;
        }

        string lexSmall = "";
        int maxCommon = -1;

        auto v = mp[s[0]];

        for (auto p : v)
        {
            int ind = p.first;

            if (ind >= r)
            {
                break;
            }
            int currCmn = 0;

            for (int j = 0; j < s.size() and j < p.second.size(); j++)
            {
                if (s[j] == p.second[j])
                {
                    currCmn++;
                }
                else
                {
                    break;
                }
            }

            if (currCmn > maxCommon)
            {
                maxCommon = currCmn;
                lexSmall = p.second;
            }
            else if (currCmn == maxCommon)
            {
                lexSmall = min(lexSmall, p.second);
            }
        }

        cout << lexSmall << endl;
    }
}

void s9()
{
    int n;
    cin >> n;
    string s;
    cin >> s;

    int ans = 0;

    for (int i = 0; i < n; i++)
    {
        if ((i + 1) < n and s[i] == s[i + 1])
        {
            ans++;
            i++;
        }
        else
        {
            ans++;
        }
    }

    cout << ans << endl;
}

void s10()
{
    string s;
    cin >> s;

    vector<int> freq(26, 0);

    for (auto i : s)
    {
        freq[i - 'a']++;
    }

    // abba => abab

    int n = s.size();
    string ans(n, '$');

    priority_queue<pair<int, char>> pq;

    for (int i = 0; i < 26; i++)
    {
        if (freq[i] > 0)
        {
            pq.push({freq[i], 'a' + i});
            if (freq[i] > ((s.length() + 1) / 2))
            {
                cout << -1 << endl;
                return;
            }
        }
    }

    while (!pq.empty())
    {
        auto top = pq.top();
        pq.pop();

        char ch = top.second, k = top.first;

        for (int i = 0; i < n and k > 0; i++)
        {
            if (ans[i] == '$')
            {
                ans[i] = ch;
                k--;
                i++;
            }
        }

        if (k > 0)
        {
            cout << -1 << endl;
            return;
        }
    }

    cout << ans << endl;
}

void s11()
{
    int n;
    cin >> n;
    vector<ll> v(n);
    input_vector(v);

    ll currxor = 0;
    ll ans = 0;

    unordered_map<ll, ll> mp;
    mp[0] = -1;

    for (int i = 0; i < n; i++)
    {
        currxor ^= v[i];
        if (mp.count(currxor))
        {
            ans++;
            mp.clear();
            mp[0] = -1;
            currxor = 0;
        }
        else
        {
            mp[currxor]++;
        }
    }

    cout << ans << endl;
}

void h1()
{
    string s1, s2;

    cin >> s1 >> s2;

    if (s1 == "sick" and s2 == "sick")
    {
        cout << 1;
    }

    else if (s1 == "fine" and s2 == "sick")
    {
        cout << 3;
    }
    else if (s1 == "sick" and s2 == "fine")
    {
        cout << 2;
    }
    else
    {
        cout << 4;
    }
}

void h2()
{
    string s;
    cin >> s;

    int ans = 0;

    int n = s.size();

    for (int i = 0; i < n; i++)
    {
        if (s[i] == 'B')
        {
            for (int j = i - 1; j >= 0; j--)
            {
                if (s[j] == 'A')
                {
                    int gap = i - j;

                    if ((i + gap) < n)
                    {
                        if (s[i + gap] == 'C')
                        {
                            ans++;
                        }
                    }
                }
            }
        }
    }

    cout << ans;
}

void h3()
{
    int n, m;
    cin >> n >> m;

    vector<unordered_set<int>> adj(n);
    ll ans = 0;
    fl(i, m)
    {
        int u, v;
        cin >> u >> v;
        --u, --v;
        if (adj[u].count(v) || u == v)
        {

            ans++;
        }
        adj[u].insert(v);
        adj[v].insert(u);
    }

    cout << ans << endl;
}

void h4()
{
    int n;
    cin >> n;
    string s;
    cin >> s;

    ll ans = 0;

    vector<int> loc;
    for (int i = 0; i < n; i++)
    {
        if (s[i] == '1')
            loc.push_back(i);
    }

    int sz = loc.size();

    if ((sz % 2) != 0)
    {
        int pos = loc[sz / 2];
        int p1 = (sz / 2) - 1, p2 = (sz / 2) + 1;

        pos--;
        while (p1 >= 0)
        {
            ans += (pos - loc[p1]);
            p1--;
            pos--;
        }
        pos = loc[sz / 2];
        pos++;

        while (p2 < sz)
        {
            ans += (loc[p2] - pos);
            p2++;
            pos--;
        }
    }
    else
    {
        ll ans1 = 0ll;
        int pos = loc[sz / 2];

        int p1 = (sz / 2) - 1, p2 = (sz / 2) + 1;
        pos--;

        while (p1 >= 0)
        {
            ans1 += (pos - loc[p1]);
            p1--;
            pos--;
        }

        pos = loc[sz / 2];
        pos++;

        while (p2 < sz)
        {
            ans1 += (loc[p2] - pos);
            p2++;
            pos--;
        }

        ll ans2 = 0ll;

        int ind = (sz / 2) - 1;
        pos = loc[ind];

        p1 = ind - 1, p2 = ind + 1;

        pos--;

        while (p1 >= 0)
        {
            ans2 += (pos - loc[p1]);
            p1--;
            pos--;
        }

        pos = loc[ind];
        pos++;

        while (p2 < sz)
        {
            ans2 += (loc[p2] - pos);
            p2++;
            pos--;
        }

        ans = min(ans1, ans2);

        ll ans3 = 0ll;

        ind = (sz / 2) - 1;
        pos = (loc[ind] + loc[ind + 1]) / 2;

        p1 = ind, p2 = ind + 1;

        while (p1 >= 0)
        {
            ans3 += (pos - loc[p1]);
            p1--;
            pos--;
        }

        pos = (loc[ind] + loc[ind + 1]) / 2;
        pos++;

        while (p2 < sz)
        {
            ans3 += (loc[p2] - pos);
            p2++;
            pos--;
        }

        ans = min(ans, ans3);

        ll ans4 = 0ll;

        ind = (sz / 2) - 1;
        pos = (loc[ind] + loc[ind + 1]) / 2;

        p1 = ind, p2 = ind + 1;
        pos--;

        while (p1 >= 0)
        {
            ans4 += (pos - loc[p1]);
            p1--;
            pos--;
        }

        pos = (loc[ind] + loc[ind + 1]) / 2;

        while (p2 < sz)
        {
            ans4 += (loc[p2] - pos);
            p2++;
            pos--;
        }

        ans = min(ans, ans4);
    }

    cout << ans << endl;
}

void h5()
{
    int n;
    cin >> n;
    string s;
    cin >> s;

    ll ans = LLONG_MAX;

    vector<int> loc;

    for (int i = 0; i < n; i++)
    {
        if (s[i] == '1')
            loc.push_back(i);
    }

    int ones = loc.size();

    ll currOper = 0;

    for (int i = 0; i < ones; i++)
    {
        currOper += abs(loc[i] - i);
    }

    ans = min(ans, currOper);

    for (int i = ones; i < ones; i++)
    {
        currOper -= abs(loc[i] - i);
    }
}

// while (x > 1)
// {
//     ll prime_factor = spf[x];
//     multiples[prime_factor] += freq[i];
//     while ((x % prime_factor) == 0)
//     {
//         x /= prime_factor;
//     }
// }

// const int maxn = (1.2 * 1e6) + 2;
// int spf[maxn];

void h6()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, k;
    cin >> n >> k;
    const int MAX = 1200002;

    vector<ll> freq(MAX, 0);
    vector<ll> ans(MAX, 0);
    vector<ll> multiples(MAX, 0);

    vector<int> arr(n);
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        arr[i] = x;
        freq[x]++;
    }

    for (int d = 1; d < MAX; d++)
    {
        for (int m = d; m < MAX; m += d)
        {
            multiples[d] += freq[m];
        }
    }

    for (int d = MAX - 1; d >= 1; d--)
    {
        if (multiples[d] >= k)
        {
            for (int m = d; m < MAX; m += d)
            {
                if (freq[m] > 0 && ans[m] == 0)
                {
                    ans[m] = d;
                }
            }
        }
    }

    for (int x : arr)
    {
        cout << ans[x] << "\n";
    }
}

ll maxn = 1e6 + 5;

int main()
{
    fast_io;

    // for (ll i = 2; i < maxn; i++)
    // {
    //     if (spf[i])
    //         continue;
    //     spf[i] = i;
    //     for (ll j = i * i; j < maxn; j += i)
    //     {
    //         if (!spf[j])
    //             spf[j] = i;
    //     }
    // }

    int t = 1;

    while (t--)
    {
    }

    return 0;
}
