class Solution
{
public:
    long long mod_exp(long long x, long long y, long long mod)
    {
        long long res = 1;
        while (y > 0)
        {
            if (y & 1)
            {
                res = (res * x) % mod;
            }
            y = y >> 1;        // y = y / 2
            x = (x * x) % mod; // Change x to x^2
        }
        return res;
    }

    long long nCr(int n, int r)
    {
        r = min(r, n - r);
        long long mod = 1e9 + 7;
        long long nr = 1;
        long long dr = 1;

        for (int i = 1; i <= r; i++)
        {
            nr = (nr * (n - i + 1)) % mod;
            dr = (dr * i) % mod;
        }

        long long mod_inverse_dr = mod_exp(dr, mod - 2, mod);
        return (nr * mod_inverse_dr) % mod;
    }

    int houseRobWays(int n, int k)
    {
        if (k > (n + 1) / 2)
        { // base case
            return 0;
        }
        return (int)nCr(n - k + 1, k); // ways are (n-k+1) C (k)
    }
};
