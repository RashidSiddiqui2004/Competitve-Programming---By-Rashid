#include <bits/stdc++.h>
using namespace std;

// We'll use a large INF value.
const int INF = 1e9;

// Dimensions for corridor BFS; chosen sufficiently large.
const int MAXC = 2103; // maximum coordinate in corridors.

// Function to check if (x,y) is within our precomputed grid.
inline bool inGrid(int x, int y)
{
    return (x >= 0 && x <= MAXC && y >= 0 && y <= MAXC);
}

// Check if a cell (x,y) is a corridor cell.
// A cell is a corridor if either x mod 3 == 0 or y mod 3 == 0.
inline bool isCorridor(int x, int y)
{
    return (x % 3 == 0 || y % 3 == 0);
}

// Precompute corridor distances from (0,0) in the grid [0, MAXC]x[0, MAXC].
vector<vector<int>> computeCorridorDistances()
{
    vector<vector<int>> dist(MAXC + 1, vector<int>(MAXC + 1, INF));
    deque<pair<int, int>> dq;
    if (isCorridor(0, 0))
    {
        dist[0][0] = 0;
        dq.push_back({0, 0});
    }
    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};
    while (!dq.empty())
    {
        auto tp = dq.front();
        auto x = tp.first, y = tp.second;
        dq.pop_front();
        int d = dist[x][y];
        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i], ny = y + dy[i];
            if (inGrid(nx, ny) && isCorridor(nx, ny) && d + 1 < dist[nx][ny])
            {
                dist[nx][ny] = d + 1;
                dq.push_back({nx, ny});
            }
        }
    }
    return dist;
}

// Structure for a table.
// Each table is determined by two non-negative integers (i,j)
// and its four cells are:
//   A: (3*i+1, 3*j+1)
//   B: (3*i+1, 3*j+2)
//   C: (3*i+2, 3*j+1)
//   D: (3*i+2, 3*j+2)
struct Table
{
    int i, j;           // table indices
    int base_x, base_y; // base coordinates (smallest x and y: (3*i+1,3*j+1))
    int occupancy;      // number of seats occupied (0 to 4)
    // Precomputed distance for each seat (if free).
    // For a seat, its distance is defined as the corridor distance from (0,0) to a neighboring corridor cell plus 1.
    int seat[4];
    // Current effective distance: min_{free seat} seat[k]
    int eff;
    int ver; // version for lazy-updates in PQ
};

// Global vector of candidate tables.
vector<Table> tables;

// PQ entry for a table.
struct PQEntry
{
    int eff, base_x, base_y; // keys: effective distance, then tie-break by base_x then base_y
    int tid;                 // table id (index in tables)
    int ver;                 // version of the table when entry was pushed.
};

// Comparator for PQ: smallest effective distance first; tie-break with base_x then base_y.
struct PQComp
{
    bool operator()(const PQEntry &a, const PQEntry &b) const
    {
        if (a.eff != b.eff)
            return a.eff > b.eff;
        if (a.base_x != b.base_x)
            return a.base_x > b.base_x;
        return a.base_y > b.base_y;
    }
};

// We will maintain two PQs:
// - pq_empty: only for tables with occupancy==0 (for guests with t==0).
// - pq_all: for tables that are not full (occupancy < 4) (for guests with t==1).
priority_queue<PQEntry, vector<PQEntry>, PQComp> pq_empty, pq_all;

// Push table tid into pq_all (always) and into pq_empty if table is empty.
void pushTable(int tid)
{
    PQEntry e{tables[tid].eff, tables[tid].base_x, tables[tid].base_y, tid, tables[tid].ver};
    if (tables[tid].occupancy == 0)
        pq_empty.push(e);
    if (tables[tid].occupancy < 4)
        pq_all.push(e);
}

// Update table tid after seating a guest.
void updateTable(int tid)
{
    tables[tid].ver++;
    int new_eff = INF;
    for (int k = 0; k < 4; k++)
    {
        new_eff = min(new_eff, tables[tid].seat[k]);
    }
    tables[tid].eff = new_eff;
    pushTable(tid);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        vector<int> guestType(n);
        for (int i = 0; i < n; i++)
        {
            cin >> guestType[i];
        }

        // Clear global data for each test case.
        tables.clear();
        while (!pq_empty.empty())
            pq_empty.pop();
        while (!pq_all.empty())
            pq_all.pop();

        // Precompute corridor distances.
        auto corridorDist = computeCorridorDistances();

        // Bound for table indices. (Assume tables with i,j in [0, M) are enough.)
        int M = 700; // Adjust M if necessary.
        tables.reserve(M * M);

        // Build candidate tables.
        for (int i = 0; i < M; i++)
        {
            for (int j = 0; j < M; j++)
            {
                Table table;
                table.i = i;
                table.j = j;
                table.base_x = 3 * i + 1;
                table.base_y = 3 * j + 1;
                table.occupancy = 0;
                table.ver = 0;

                // Seat A: (3*i+1, 3*j+1)
                int dA = INF;
                if (inGrid(3 * i, 3 * j + 1) && isCorridor(3 * i, 3 * j + 1))
                    dA = min(dA, corridorDist[3 * i][3 * j + 1]);
                if (inGrid(3 * i + 1, 3 * j) && isCorridor(3 * i + 1, 3 * j))
                    dA = min(dA, corridorDist[3 * i + 1][3 * j]);
                if (dA < INF)
                    dA++;
                table.seat[0] = dA;

                // Seat B: (3*i+1, 3*j+2)
                int dB = INF;
                if (inGrid(3 * i, 3 * j + 2) && isCorridor(3 * i, 3 * j + 2))
                    dB = min(dB, corridorDist[3 * i][3 * j + 2]);
                if (inGrid(3 * i + 1, 3 * j + 3) && isCorridor(3 * i + 1, 3 * j + 3))
                    dB = min(dB, corridorDist[3 * i + 1][3 * j + 3]);
                if (dB < INF)
                    dB++;
                table.seat[1] = dB;

                // Seat C: (3*i+2, 3*j+1)
                int dC = INF;
                if (inGrid(3 * i + 2, 3 * j) && isCorridor(3 * i + 2, 3 * j))
                    dC = min(dC, corridorDist[3 * i + 2][3 * j]);
                if (inGrid(3 * i + 3, 3 * j + 1) && isCorridor(3 * i + 3, 3 * j + 1))
                    dC = min(dC, corridorDist[3 * i + 3][3 * j + 1]);
                if (dC < INF)
                    dC++;
                table.seat[2] = dC;

                // Seat D: (3*i+2, 3*j+2)
                int dD = INF;
                if (inGrid(3 * i + 3, 3 * j + 2) && isCorridor(3 * i + 3, 3 * j + 2))
                    dD = min(dD, corridorDist[3 * i + 3][3 * j + 2]);
                if (inGrid(3 * i + 2, 3 * j + 3) && isCorridor(3 * i + 2, 3 * j + 3))
                    dD = min(dD, corridorDist[3 * i + 2][3 * j + 3]);
                if (dD < INF)
                    dD++;
                table.seat[3] = dD;

                table.eff = min({table.seat[0], table.seat[1], table.seat[2], table.seat[3]});

                tables.push_back(table);
            }
        }

        // Initialize priority queues with candidate tables.
        for (int tid = 0; tid < (int)tables.size(); tid++)
        {
            if (tables[tid].eff < INF)
                pushTable(tid);
        }

        // We'll store for each guest the traveled distance and the seat coordinates.
        vector<int> travel(n);
        vector<pair<int, int>> guestCoord(n);

        // Process guests in order.
        for (int idx = 0; idx < n; idx++)
        {
            int type = guestType[idx];
            PQEntry chosen;
            bool found = false;
            if (type == 0)
            {
                // Find a table that is completely unoccupied.
                while (!pq_empty.empty())
                {
                    PQEntry top = pq_empty.top();
                    pq_empty.pop();
                    Table &t = tables[top.tid];
                    if (t.ver != top.ver || t.occupancy != 0 || t.eff != top.eff)
                        continue; // outdated
                    chosen = top;
                    found = true;
                    break;
                }
            }
            else
            {
                // type == 1: choose table with occupancy < 4.
                while (!pq_all.empty())
                {
                    PQEntry top = pq_all.top();
                    pq_all.pop();
                    Table &t = tables[top.tid];
                    if (t.ver != top.ver || t.occupancy >= 4 || t.eff != top.eff)
                        continue; // outdated
                    chosen = top;
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                // Should not happen given enough candidate tables.
                cout << "Error: no available table found for guest " << idx << "\n";
                return 1;
            }

            int tid = chosen.tid;
            travel[idx] = tables[tid].eff;

            // Determine which seat is taken.
            int chosenSeat = -1;
            for (int k = 0; k < 4; k++)
            {
                if (tables[tid].seat[k] == tables[tid].eff)
                {
                    chosenSeat = k;
                    break;
                }
            }
            // Compute the coordinate of the chosen seat.
            int guest_x, guest_y;
            // Table's base coordinates correspond to seat A.
            // Seat A: (3*i+1, 3*j+1)
            // Seat B: (3*i+1, 3*j+2)
            // Seat C: (3*i+2, 3*j+1)
            // Seat D: (3*i+2, 3*j+2)
            int i_val = tables[tid].i;
            int j_val = tables[tid].j;
            if (chosenSeat == 0)
            {
                guest_x = 3 * i_val + 1;
                guest_y = 3 * j_val + 1;
            }
            else if (chosenSeat == 1)
            {
                guest_x = 3 * i_val + 1;
                guest_y = 3 * j_val + 2;
            }
            else if (chosenSeat == 2)
            {
                guest_x = 3 * i_val + 2;
                guest_y = 3 * j_val + 1;
            }
            else
            { // chosenSeat == 3
                guest_x = 3 * i_val + 2;
                guest_y = 3 * j_val + 2;
            }
            guestCoord[idx] = {guest_x, guest_y};

            // Mark the chosen seat as taken.
            tables[tid].seat[chosenSeat] = INF;
            tables[tid].occupancy++;

            // Update table if not full.
            if (tables[tid].occupancy < 4)
                updateTable(tid);
        }

        // Output for each guest: the traveled distance and the coordinate.
        // Format: distance x y
        for (int i = 0; i < n; i++)
        {
            cout << guestCoord[i].first << " " << guestCoord[i].second << "\n";
        }
    }
    return 0;
}
