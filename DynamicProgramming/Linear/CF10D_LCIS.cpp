#include <bits/stdc++.h>
using namespace std;

int n, m, cnt, a[505], b[505], f[505][505], num[505][505], pri[505];
bool sa[505][505];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    scanf("%d", &m);
    for (int i = 1; i <= m; i++)
        scanf("%d", &b[i]);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            if (a[i] == b[j])
            {
                for (int k = 0; k < j; k++)
                    if (b[k] < b[j] && f[i - 1][k] + 1 > f[i][j])
                    {
                        f[i][j] = f[i - 1][k] + 1;
                        num[i][j] = k;
                    }
            }
            else
            {
                f[i][j] = f[i - 1][j];
                num[i][j] = num[i - 1][j];
                sa[i][j] = true;
            }
        }
    printf("%d\n", f[n][m]);
    int j = m;
    for (int i = n; i >= 1; i--)
    {
        if (sa[i][j] == false)
            pri[++cnt] = num[i][j];
        j = num[i][j];
    }
    while(cnt--)
    {
        printf("%d ", b[pri[cnt+1]]);
    }
    return 0;
}