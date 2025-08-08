n, W, V = map(int, input().split())
items = []
for _ in range(n):
    w, v, p = map(int, input().split())
    items.append((w, v, p))

#Initialize DP array
dp = [[0] * (V + 1) for i in range(W + 1)]

#Process each item
for w_i, v_i, p_i in items:
    for w in range(W, w_i - 1, -1):
        for v in range(V, v_i - 1, -1):
            dp[w][v] = max(dp[w][v], dp[w - w_i][v - v_i] + p_i)

#The answer is the maximum value in the DP table
maximum_profit = max([max(row) for row in dp])

print(maximum_profit)
