#include <bits/stdc++.h>

int n, m, dp[35][35];

int main()
{
    dp[0][1] = 1;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i)
    {
        dp[i][1] = dp[i - 1][n] + dp[i - 1][2];
        dp[i][n] = dp[i - 1][n - 1] + dp[i - 1][1];
        for (int j = 2; j < n; ++j)
            dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j + 1];
    }
    printf("%d", dp[m][1]);
    return 0;
}