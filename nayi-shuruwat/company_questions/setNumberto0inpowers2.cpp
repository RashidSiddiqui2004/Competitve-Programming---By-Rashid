
#include <bits/stdc++.h>
#include <cassert>
using namespace std;

int main(int argc, char const *argv[])
{
    int n = 16;
    // cin >> n;

    bitset<sizeof(long) * 32> bits(n);

    int ans = 0;

    int ptr = 0;

    while (ptr < 32)
    {
        while (ptr < 32 and bits[ptr] == 0)
        {
            ptr++;
        }

        int len = 0;

        while (ptr < 32 and bits[ptr] == 1)
        {
            ptr++;
            len++;
        }

        if (len == 1)
        {
            ans++;
            bits[ptr - 1] = 0;
        }
        else if (len > 1)
        {
            ans++;
            for (int i = ptr - 1; i >= 0 and bits[i] == 1; i--)
            {
                bits[i] = 0;
            }
            bits[ptr] = 1;
        }
    }

    cout << ans << "\n";
    assert((ans == 1));
    return 0;
}
