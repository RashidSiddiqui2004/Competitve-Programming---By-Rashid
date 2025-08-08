#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXN = 1e5 + 5;
vector<int> spf(MAXN); // Smallest Prime Factor for sieve
 
void sieve()
{
    iota(spf.begin(), spf.end(), 0); // spf[i] = i initially
    for (int i = 2; i * i < MAXN; i++)
    {
        if (spf[i] == i)
        { // Prime number
            for (int j = i * i; j < MAXN; j += i)
            {
                if (spf[j] == j)
                    spf[j] = i; 
            }
        }
    }
}

// Segment tree node: stores a frequency map of prime factors
struct Node
{
    unordered_map<int, int> freq; // {prime_factor -> exponent count}
};

vector<ll> v;
vector<Node> segTree;

// Function to factorize a number and get prime factor frequencies
unordered_map<int, int> getPrimeFactors(int num)
{
    unordered_map<int, int> factors;
    while (num > 1)
    {
        int prime = spf[num], exp = 0;
        while (num % prime == 0)
        {
            exp++;
            num /= prime;
        }
        factors[prime] += exp;
    }
    return factors;
}

// Build the segment tree
void build(int idx, int low, int high)
{
    if (low == high)
    {
        segTree[idx].freq = getPrimeFactors(v[low]);
        return;
    }

    int mid = (low + high) / 2;
    build(2 * idx + 1, low, mid);
    build(2 * idx + 2, mid + 1, high);

    // Merge operation: Combine frequency maps
    segTree[idx].freq = segTree[2 * idx + 1].freq;
    for (auto &p : segTree[2 * idx + 2].freq)
    {
        segTree[idx].freq[p.first] += p.second;
    }
}

// Query to get exponent sum of primes in range [x, y]
ll query(int idx, int low, int high, int l, int r, int x, int y)
{
    if (low > r || high < l)
        return 0; // Completely outside
    if (low >= l && high <= r)
    { // Completely inside
        ll res = 0;
        for (auto &p : segTree[idx].freq)
        {
            if (p.first >= x && p.first <= y)
            {
                res += p.second;
            }
        }
        return res;
    }

    // Partial overlap
    int mid = (low + high) / 2;
    return query(2 * idx + 1, low, mid, l, r, x, y) +
           query(2 * idx + 2, mid + 1, high, l, r, x, y);
}

 
void s3()
{
    int n;
    cin >> n;
    v.resize(n);
    for (int i = 0; i < n; i++)
        cin >> v[i];
 
    segTree.resize(4 * n);
    build(0, 0, n - 1);

    int q;
    cin >> q;
    while (q--)
    {
        int l, r, x, y;
        cin >> l >> r >> x >> y;
        --l, --r;

        cout << query(0, 0, n - 1, l, r, x, y) << endl;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    sieve();  
    s3();     

    return 0;
}
