#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

vector<int> masha_and_olya_game(const vector<int> &a)
{
    int n = a.size();
    // cout << a.size() << " ";
    vector<int> results;

    for (int k = 1; k <= n; ++k)
    {
        // Take the prefix of size k
        vector<int> prefix(a.begin(), a.begin() + k);
        priority_queue<int> max_heap(prefix.begin(), prefix.end());
        priority_queue<int, vector<int>, greater<int>> min_heap(prefix.begin(), prefix.end());

        while (max_heap.size() > 1)
        {
            if (max_heap.size() % 2 == 1)
            { // Masha's turn
                // Masha picks the two largest numbers
                int x = max_heap.top();
                max_heap.pop();
                int y = max_heap.top();
                max_heap.pop();
                int new_num = (x + y) / 2 * 2;
                max_heap.push(new_num);
            }
            else
            { // Olya's turn
                // Olya picks the two smallest numbers
                int x = min_heap.top();
                min_heap.pop();
                int y = min_heap.top();
                min_heap.pop();
                int new_num = (x + y) / 2 * 2;
                min_heap.push(new_num);
            }
        }

        // The final remaining number
        results.push_back(max_heap.empty() ? min_heap.top() : max_heap.top());
    }

    return results;
}

int main()
{
    int t;
    cin >> t;

    while (t--)
    {
        int n;
        cin >> n;

        vector<int> a(n);
        for (int i = 0; i < n; i++)
        {
            cin >> a[i];
        }

        vector<int> result = masha_and_olya_game(a);

        for (int num : result)
        {
            cout << num << " ";
        }
        cout << endl;
    }

    return 0;
}
