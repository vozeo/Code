#include <bits/stdc++.h>
using namespace std;
int n, ans, a[100005], f[100005];
struct cmp
{
    bool operator()(int x, int y) { return x > y; }
};
int main()
{
    while (~scanf("%d", &a[++n]));
    n--;
    f[1] = a[1], ans = 1;
    for (int i = 2; i <= n; i++)
    {
        if (f[ans] >= a[i])
            f[++ans] = a[i];
        else
            f[upper_bound(f + 1, f + ans + 1, a[i], cmp()) - f] = a[i];
    }
    printf("%d\n", ans);
    f[1] = a[1], ans = 1;
    for (int i = 2; i <= n; i++)
    {
        if (f[ans] < a[i])
            f[++ans] = a[i];
        else
            f[lower_bound(f + 1, f + ans + 1, a[i]) - f] = a[i];
    }
    printf("%d", ans);
    return 0;
}