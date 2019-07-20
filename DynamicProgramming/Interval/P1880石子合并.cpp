#include <bits/stdc++.h>
using namespace std;
int n, mx, mn = 2e9, a[205], fx[205][205], fn[205][205], s[205];
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        a[i + n] = a[i];
    }
    for (int i = 1; i <= (n << 1); i++)
        s[i] = s[i - 1] + a[i];
    for (int j = 2; j <= n; j++)
        for (int l = 1; l <= (n << 1); l++)
        {
            int r = l + j - 1;
            if (r > (n << 1))
            break;
            fn[l][r] = 2e9;
            for (int k = l; k < r; k++)
            {
                fx[l][r] = max(fx[l][r], fx[l][k] + fx[k + 1][r]);
                fn[l][r] = min(fn[l][r], fn[l][k] + fn[k + 1][r]);
            }
            fx[l][r] += s[r] - s[l - 1];
            fn[l][r] += s[r] - s[l - 1];
        }
    for (int i = 1; i <= n; i++)
    {
        mx = max(mx, fx[i][i + n - 1]);
        mn = min(mn, fn[i][i + n - 1]);
    }
    printf("%d\n%d", mn, mx);
    return 0;
}