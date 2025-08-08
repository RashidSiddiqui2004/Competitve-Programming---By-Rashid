#include <algorithm>
#include <iostream>
#include <set>
using namespace std;

// https://cses.fi/problemset/result/12072482/

using ll = long long;
long N, M;
long arr[200010];
multiset<long> up;
multiset<long> low;

ll lowSum = 0, highSum = 0;

void ins(long val)
{                           // insert val into sets
    long a = *low.rbegin(); // current median
    if (a < val)
    {
        up.insert(val);
        highSum += val;
        if (up.size() > M / 2)
        {
            low.insert(*up.begin());
            highSum -= *up.begin();
            lowSum += *up.begin();
            up.erase(up.begin());
        }
    }
    else
    {
        low.insert(val);
        lowSum += val;
        if (low.size() > (M + 1) / 2)
        {
            up.insert(*low.rbegin());
            lowSum -= *low.rbegin();
            highSum += *low.rbegin();
            low.erase(--low.end());
        }
    }
}

void er(long val)
{ // erase from sets
    if (up.find(val) != up.end())
    {
        highSum -= val;
        up.erase(up.find(val));
    }

    else
    {
        lowSum -= val;
        low.erase(low.find(val));
    }

    if (low.empty())
    {
        lowSum += *up.begin();
        highSum -= *up.begin();
        low.insert(*up.begin());
        up.erase(up.begin());
    }
}

int main()
{
    cin >> N >> M;
    for (int i = 0; i < N; i++)
        cin >> arr[i];
    low.insert(arr[0]);
    lowSum += arr[0];

    for (int i = 1; i < M; i++)
        ins(arr[i]);

    ll median = *low.rbegin();

    ll prevCost = ((low.size()) * median) - lowSum;
    ll nextCost = highSum - (up.size() * median);

    cout << prevCost + nextCost << " ";

    for (long i = M; i < N; i++)
    {
        if (M == 1)
        {
            ins(arr[i]);
            er(arr[i - M]);
        }
        else
        {
            er(arr[i - M]);
            ins(arr[i]);
        }

        ll median = *low.rbegin();

        ll prevCost = ((low.size()) * median) - lowSum;
        ll nextCost = highSum - (up.size() * median);

        cout << prevCost + nextCost << " ";
    }
    cout << endl;
}