#include <queue>
#include <cstdio>
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;
ll n, m, q, u, v, t, a[7500000], ans[7500000], s, y, tot;
queue<ll> q1, q2, q3;

ll getmax()
{
    int x1 = -(1 << 30), x2 = -(1 << 30), x3 = -(1 << 30);
    if (!q1.empty())
        x1 = q1.front();
    if (!q2.empty())
        x2 = q2.front();
    if (!q3.empty())
        x3 = q3.front();
    if (x1 > x2 && x1 > x3)
    {
        q1.pop();
        return x1;
    }
    else if (x2 > x1 && x2 > x3)
    {
        q2.pop();
        return x2;
    }
    q3.pop();
    return x3;
}

bool cmp(ll x, ll y)
{
    return x > y;
}
inline ll read()
{
    char ch = getchar();
    ll j = 0;
    while (ch < '0' || ch > '9')
        ch = getchar();
    while (ch >= '0' && ch <= '9')
        j = j * 10 + ch - '0', ch = getchar();
    return j;
}
inline void write(ll x)
{
    if (x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
}

int main()
{
    freopen("in.in", "r", stdin);
    n = read(), m = read(), q = read(), u = read(), v = read(), t = read();
    double p = (double)u / v;
    bool flag = p < 0.5;
    for (int i = 1; i <= n; i++)
        a[i] = read();
    sort(a + 1, a + n + 1, cmp);
    for (int i = 1; i <= n; i++)
        q1.push(a[i]);
    
    for (int i = 1; i <= m; i++)
    {
        ans[i] = getmax() + y;
        int j = ans[i] * p, k = ans[i] - j;
        y += q;
        if (flag)
            swap(j, k);
        q2.push(j - y), q3.push(k - y);
    }
    
    for (int i = t; i <= m; i += t)
        write(ans[i]), putchar(' ');
    putchar('\n');
    
    for (int i = 1; i <= m + n; i++)
    {
        tot = getmax();
        if (i % t == 0)
            printf("%d ", tot + y);
    }
    
    putchar('\n');
    return 0;
}