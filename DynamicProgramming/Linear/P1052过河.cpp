#include <bits/stdc++.h>
using namespace std;

int l, s, t, m;
int a[105], d[105], stone[10000], f[10000];

int main()
{
    scanf("%d%d%d%d", &l, &s, &t, &m);
    for (int i = 1; i <= m; i++)
        scanf("%d", &a[i]);
    sort(a + 1, a + m + 1);
    if (s == t)
    {
        int ans = 0;
        for (int i = 1; i <= m; i++)
            if (a[i] % s == 0)
                ans++;
        printf("%d", ans);
        return 0;
    }
    for (int i = 1; i <= m; i++)
    {
        a[i] = a[i - 1] + (a[i] - a[i - 1]) % 90;
        stone[a[i]] = true;
    }
    l = a[m];
    for (int i = 0; i < l + t; i++)
        f[i] = m;
    f[0] = 0;
    for (int i = 1; i < l + t; i++)
        for (int j = s; j <= t; j++)
        {
            if (i >= j)
                f[i] = min(f[i], f[i - j]);
            f[i] += stone[i];
        }
    int ans = m;
    for (int i = l; i < l + t; i++)
        ans = min(ans, f[i]);
    printf("%d", ans);
    return 0;
}