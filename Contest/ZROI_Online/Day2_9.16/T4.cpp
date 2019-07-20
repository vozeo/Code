#include <cstdio>
const int MAXN = 305;
int n, m, k;
double f[MAXN], g[MAXN * MAXN], ans;
int main()
{
    scanf("%d%d%d", &n, &m, &k);
    f[0] = g[0] = 1;
    for (int i = 1; i <= n; i++)
        f[i] = f[i - 1] / i * (n - i + 1);
    for (int i = 1; i <= m; i++)
        g[i] = g[i - 1] / (m - i + 1) * (k - i + 1);
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= n; j++)
        {
            int t = (i + j) * n - i * j;
            if (t > k)
                continue;
            ans += f[i] * f[j] * g[t];
        }
    printf("%lf", ans > 1e99 ? 1e99 : ans);
    return 0;
}