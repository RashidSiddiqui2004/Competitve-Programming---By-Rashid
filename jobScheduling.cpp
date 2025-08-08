#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pli = pair<ll, int>;

// Global arrays to store profit and potential for each job.
vector<ll> profit;
vector<ll> pot; // potential value for each job
vector<vector<int>> children;

// We compute the potential for job "node" recursively.
// potential[node] = profit[node] + sum( max(0, potential[child]) ) over all children.
ll computePotential(int node)
{
    ll total = profit[node];
    for (int ch : children[node])
    {
        ll childPot = computePotential(ch);
        if (childPot > 0)
            total += childPot;
    }
    return pot[node] = total;
}

void solve()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    ll s;
    cin >> n >> s;
    ll startMoney = s;

    profit.resize(n);
    pot.resize(n, 0);
    children.assign(n, vector<int>());

    // To know which nodes are roots:
    vector<bool> isRoot(n, true);

    // Input: each job has profit and a dependency.
    // If dependency p != 0, then p-1 must come before job i.
    for (int i = 0; i < n; i++)
    {
        ll a;
        int p;
        cin >> a >> p;
        profit[i] = a;
        if (p != 0)
        {
            // p-1 is the parent of job i
            children[p - 1].push_back(i);
            isRoot[i] = false;
        }
    }

    // Compute potential for every node.
    // (Since each node has at most one parent, the graph is a forest.)
    for (int i = 0; i < n; i++)
    {
        if (isRoot[i])
        {
            computePotential(i);
        }
    }

    // We'll simulate our process using two priority queues.
    // The keys are the potential values.
    // (We always want to pick the unlocked job with highest potential that is feasible.)
    priority_queue<pli> feasible;    // jobs that are unlocked and currently feasible.
    priority_queue<pli> nonFeasible; // unlocked but not yet feasible.

    // Initially, add all roots.
    for (int i = 0; i < n; i++)
    {
        if (isRoot[i])
        {
            // A job is immediately executable if s + profit >= 0.
            if ((s + profit[i]) >= 0)
                feasible.push({pot[i], i});
            else
                nonFeasible.push({pot[i], i});
        }
    }

    ll maxProf = s;

    // Our simulation: we do not have to execute every available job.
    // In particular, if a job’s potential isn’t positive (i.e. it doesn’t lead to a net gain)
    // we skip it.
    while (!feasible.empty())
    {
        auto top = feasible.top();

        auto pVal = top.first;
        auto node = top.second;
        feasible.pop();

        // (Re-check feasibility; it might have become non-feasible due to earlier negative moves.)
        if (s + profit[node] < 0)
            continue;

        // If the total potential (i.e. net benefit from doing this branch) is not positive,
        // then skip it. (This avoids taking a negative task that does not unlock benefit.)

        // "Invest" in job "node"

        s += profit[node];
        maxProf = max(maxProf, s);

        // Unlock its children.
        for (int ch : children[node])
        {
            // When a child is unlocked, add it to the nonFeasible heap;
            // later we will check if it becomes feasible.
            if ((s + profit[ch]) >= 0)
                feasible.push({pot[ch], ch});
            else
                nonFeasible.push({pot[ch], ch});
        }

        // After s has increased, some jobs that were previously non-feasible may now be executable.
        while (!nonFeasible.empty() && (s + profit[nonFeasible.top().second] >= 0))
        {
            auto temp = nonFeasible.top();
            nonFeasible.pop();
            feasible.push(temp);
        }
    }

    cout << (maxProf - startMoney) << "\n";
}

int main()
{
    solve();
    return 0;
}
