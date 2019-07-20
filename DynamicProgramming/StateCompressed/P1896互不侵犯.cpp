#include <bits/stdc++.h>
using namespace std;

int n, m, f[10][1 << 9], h[1 << 9], g[1 << 9], t[10][1 << 9];

int main()
{
    scanf("%d%d", &n, &m);
    const int max_state = 1 << n;
    for (int i = 0; i < max_state; i++)
    {
        h[i] = !((i << 1) & i) && !((i >> 1) & i);
        for (int j = 0; j <= 9; j++)
            g[i] += (1 << j) & i;
    }

    for (int i = 1; i <= n; i++)
        for (int j = 0; j < max_state; j++)
            if (h[j])
                for (int k = 0; k < max_state; k++)
                    if (!((k >> 1) & j) && !((k << 1) & j) && !(k & j) && g[k] + t[i][j] <= m)
                    {
                        t[i][j] += 
                    }
                        return 0;
}