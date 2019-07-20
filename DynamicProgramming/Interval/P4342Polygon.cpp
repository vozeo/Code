#include <bits/stdc++.h>
using namespace std;
int n, mx, mn = 2e9, a[105], fx[105][105], fn[105][105];
char p[105];
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%c", &p[i]);
        scanf("%d", &a[i]);
        a[i + n] = a[i];
        p[i + n] = p[i];
        fx[i][i] = fn[i][i] = fx[i + n][i + n] = fn[i + n][i + n] = a[i][i];
    }
    for (int i = 2; i <= n; i++)
        for (int l = 1; l <= n * 2; l++)
        {
            int r = l + i - 1;
            if (r > n * 2)
                break;
            fn[l][r] = 2e9;
            for (int j = l; j < r; j++)
            {
                fx[l][r] = max(fx[l][r], fx[l][k] + fx[l + 1][r]);
                if (p[k] == 'x')
                {
                    fx[l][r] = max(fx[l][r], fx[l][k] * fx[l + 1][r]);
                    fn[l][r] = max(fn[l][r], fn[l][k] * fn[l + 1][r]);
                }
                fn[l][r] = max(fn[l][r], fn[l][k] + fn[l + 1][r]);
                if (p[k] == 'x')
                {
                    fn[l][r] = min(fn[l][r], fx[l][k] * fx[l + 1][r]);
                    fn[l][r] = min(fn[l][r], fn[l][k] * fn[l + 1][r]);
                    fn[l][r] = min(fn[l][r], fx[l][k] * fn[l + 1][r]);
                    fn[l][r] = min(fn[l][r], fn[l][k] * fx[l + 1][r]);
                }
            }
        }
    for (int i = 1; i <= n; i++)
        mx = max(mx, fx[i][i + n - 1]);
    printf("%d\n", mx);
    return 0;
}