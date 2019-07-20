#include <bits/stdc++.h>
using namespace std;

double f[55][2505][2];
int n, m, v, sum;

int main()
{
    scanf("%d%d%d%d", &n, &m, &v, &sum);
    f[0][0][0] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m * n; j++)
        {
            for (int k = 1; k <= m; k++)
            {
                if (k != v)
                {
                    f[i][j][1] += f[i - 1][j - k][1];
                    f[i][j][0] += f[i - 1][j - k][0];
                }
                else
                    f[i][j][1] += f[i - 1][j - k][1] + f[i - 1][j - k][0];
            }
            f[i][j][1] *= 1.0 / m;
            f[i][j][0] *= 1.0 / m;
        }
    double s = 0;
    for (int i = 1; i <= n * m; i++)
        s += f[n][i][1];
    printf("%.8f ", f[n][sum][1] / s);
    return 0;
}