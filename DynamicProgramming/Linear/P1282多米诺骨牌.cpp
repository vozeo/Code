#include <bits/stdc++.h>
using namespace std;
#define INF 0x3f3f3f3f

int n, a[1005], b[1005], f[1001][12005];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &a[i], &b[i]);
    memset(f, 0x3f, sizeof(f));
    f[0][6000] = 0;

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= 12000; j++)
        {
            f[i][j] = min(f[i][j], f[i - 1][j - a[i] + b[i]]);
            f[i][j] = min(f[i][j], f[i - 1][j + a[i] - b[i]] + 1);
        }

    for (int i = 0; i <= 6000; i++)
        if (f[n][6000 + i] < INF || f[n][6000 - i] < INF)
        {
            printf("%d", min(f[n][6000 + i], f[n][6000 - i]));
            return 0;
        }
}