#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e8;
int m, n, f[13][1 << 12], g[13];
bool h[1 << 12];

int main()
{
    scanf("%d%d", &m, &n);
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
        {
            int x;
            scanf("%d", &x);
            g[i] = (g[i] << 1) + x;
        }
    const int max_state = 1 << n;
    for (int i = 0; i < max_state; i++)
        h[i] = !((i << 1) & i) && !((i >> 1) & i);
    f[0][0] = 1;
    for (int i = 1; i <= m; i++)
        for (int j = 0; j < max_state; j++)
            if ((j & g[i]) == j && h[j])
                for (int k = 0; k < max_state; k++)
                    if (!(k & j))
                        f[i][j] = (f[i][j] + f[i - 1][k]) % MOD;
    int ans = 0;
    for (int i = 0; i < max_state; i++)
        ans = (ans + f[m][i]) % MOD;
    printf("%d", ans);
    return 0;
}