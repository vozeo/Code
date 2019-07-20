#include <iostream>
#include <cstdio>
using namespace std;

int m, n, a[55][55], f[105][55][55];
int ax[4] = {0, 1, 0, 1}, ay[4] = {0, 0, 1, 1};

int main()
{
    scanf("%d%d", &m, &n);
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            scanf("%d", &a[i][j]);
    //memset(f, -1, sizeof(f));
    //f[0][1][1] = 0;

    for (int i = 3; i <= m + n - 1; i++)
        for (int j = 1; j <= n; j++)
            for (int k = 1; k <= n; k++)
                for (int l = 0; l <= 3; l++)
                {
                    //j += ax[l], k += ay[l];
                    if (j == k && i - j > 0)
                        f[i][j][k] = max(f[i][j][k], f[i - 1][j - ax[l]][k - ay[l]] + a[i - j][j]);
                    else if (i - j > 0 && i - k > 0)
                        f[i][j][k] = max(f[i][j][k], f[i - 1][j - ax[l]][k - ay[l]] + a[i - j][j] + a[i - k][k]);
                    //j -= ax[l], k -= ay[l];
                }
    printf("%d", f[m + n - 1][n - 1][n]);
    return 0;
}