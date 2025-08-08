#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<ll> v;       // The input array (0-indexed)
vector<ll> segTree; // Segment tree; each node stores the maximum spf in that segment.
vector<int> lazy;   // Lazy propagation array (pending update count for each node)
vector<ll> spf;     // spf[x] will hold the smallest prime factor of x

// Sieve to compute smallest prime factors up to n.
// (After calling sieve(maxVal), spf[x] will equal the smallest prime factor of x.)
void sieve(ll n)
{
    spf.resize(n + 1);
    for (ll i = 0; i <= n; i++)
    {
        spf[i] = i;
    }
    for (ll i = 2; i * i <= n; i++)
    {
        if (spf[i] == i)
        { // i is prime
            for (ll j = i * i; j <= n; j += i)
            {
                if (spf[j] == j)
                    spf[j] = i;
            }
        }
    }
    // Define spf[1] = 1 so that when a value becomes 1, its spf remains 1.
    if (n >= 1)
        spf[1] = 1;
}

// Build the segment tree over indices [low, high] at tree index 'idx'.
// For each leaf, we store spf[v[i]]. For internal nodes we store the maximum of their children.
void build(int idx, int low, int high)
{
    if (low == high)
    {
        segTree[idx] = spf[v[low]];
        return;
    }
    int mid = (low + high) / 2;
    build(2 * idx + 1, low, mid);
    build(2 * idx + 2, mid + 1, high);
    segTree[idx] = max(segTree[2 * idx + 1], segTree[2 * idx + 2]);
}

// In this problem the update operation is: for each element in a range,
// if the element is not already 1, update it as: x -> x / spf[x].
// The lazy value (an integer) is meant to record how many pending update operations should be applied.
// Because f(x)=(x/spf[x]) is non‐linear, we must “push” the lazy value down to the leaves to recompute correct values.
//
// This push function will apply any pending updates for node idx. If idx covers a leaf, we update that leaf;
// if it covers an interval, we propagate the lazy value to its children and then update our node’s value.
void push(int idx, int low, int high)
{
    if (lazy[idx] == 0)
        return;

    // If this is a leaf, apply the pending updates directly.
    if (low == high)
    {
        int times = lazy[idx];
        lazy[idx] = 0;
        while (times-- && v[low] != 1)
        {
            v[low] = v[low] / spf[v[low]];
        }
        segTree[idx] = spf[v[low]];
        return;
    }

    // For an internal node, propagate the pending updates to its children.
    lazy[2 * idx + 1] += lazy[idx];
    lazy[2 * idx + 2] += lazy[idx];
    lazy[idx] = 0;

    // After propagation, force the children to “push” their lazy values
    // so that segTree values become up to date.
    int mid = (low + high) / 2;
    push(2 * idx + 1, low, mid);
    push(2 * idx + 2, mid + 1, high);

    // Recompute the current node’s value.
    segTree[idx] = max(segTree[2 * idx + 1], segTree[2 * idx + 2]);
}

void update(int idx, int low, int high, int l, int r)
{
    push(idx, low, high);

    if (high < l || low > r)
        return;

    if (low >= l && high <= r)
    {
        lazy[idx]++;
        push(idx, low, high);
        return;
    }
    
    int mid = (low + high) / 2;
    update(2 * idx + 1, low, mid, l, r);
    update(2 * idx + 2, mid + 1, high, l, r);

    segTree[idx] = max(segTree[2 * idx + 1], segTree[2 * idx + 2]);
}

// Range query: return the maximum spf in the range [l, r] (0-indexed).
ll query(int idx, int low, int high, int l, int r)
{
    // First, push down any pending lazy updates.
    push(idx, low, high);

    // No overlap.
    if (high < l || low > r)
        return 0; // For max query, 0 is a safe identity.

    // Total overlap.
    if (low >= l && high <= r)
        return segTree[idx];

    int mid = (low + high) / 2;
    return max(query(2 * idx + 1, low, mid, l, r),
               query(2 * idx + 2, mid + 1, high, l, r));
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    cin >> t;

    sieve(1e6 + 2);

    while (t--)
    {
        int n, q;
        cin >> n >> q;
        v.resize(n);
        ll max_val = 0;

        for (int i = 0; i < n; i++)
        {
            cin >> v[i];
            max_val = max(max_val, v[i]);
        }

        segTree.resize(4 * n);
        lazy.assign(4 * n, 0);

        build(0, 0, n - 1);

        while (q--)
        {
            int type, l, r;
            cin >> type >> l >> r;

            l--;
            r--;
            if (type == 0)
            {
                update(0, 0, n - 1, l, r);
            }
            else if (type == 1)
            {
                cout << query(0, 0, n - 1, l, r) << " ";
            }
        }

        cout << endl;
    }
    return 0;
}
