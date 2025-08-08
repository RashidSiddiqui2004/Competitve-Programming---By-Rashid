#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

#define ll long long

int main()
{

    int t;
    cin >> t;
    while (t--)
    {

        int n;
        cin >> n;

        vector<ll> v(n);
        for (int i = 0; i < n; i++)
        {
            cin >> v[i];
        }

        ll ans = 0;
        vector<ll> score(n, -1);

        unordered_map<ll, ll> mp; // Map to store the last occurrence of the XOR prefix

        for (int i = n - 1; i >= 0; i--)
        {
            ll curr = v[i], currxor = v[i];

            // Check if the XOR prefix has been seen before in the map
            if (mp.find(currxor) != mp.end())
            {
                int j = mp[currxor]; // Get the index where the XOR prefix was seen
                curr += score[j];    // Add the score at that index
            }

            ans = max(ans, curr);
            score[i] = curr;

            // Update the map with the current XOR prefix and its index
            mp[currxor] = i;
        }

        cout << ans << endl;
    }
    return 0;
}
