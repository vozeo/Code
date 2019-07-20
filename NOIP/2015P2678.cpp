#include <bits/stdc++.h>
using namespace std;

#define MAXN 50005

int a[MAXN], b[MAXN];
int l, n, m, le, ri, mid;

int read()
{
    int x = 0;
    char c = getchar();
    while (c < '0' || c > '9')
        c = getchar();
    while (c >= '0' && c <= '9')
    {
        x = x * 10 + c - '0';
        c = getchar();
    }
    return x;
}

bool ok(int dis)
{
    int sum = 0, x = 0;
    for (int i = 1; i <= n; i++)
    {
        if (a[i] - a[x] <= dis)
            sum++;
        else
            x = i;
    }
    return sum <= m;
}

int main()
{
    l = read(), n = read(), m = read();
    le = 1, ri = l;
    for (int i = 1; i <= n; i++)
        a[i] = read();
    while (le < ri)
    {
        mid = (le + ri) >> 1;
        if (ok(mid))
            le = mid + 1;
        else
            ri = mid;
    }
    if (n == 0)
        printf("%d", l);
    else
        printf("%d", le);
    return 0;
}