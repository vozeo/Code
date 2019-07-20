#include <iostream>
#include <cstdio>
#define rep(i_, s_, t_) for(int i = (s_); i_ <= (t_); ++i_)
int n, m, a[500005];

void add(int x, int k)
{
    for (; x <= n; x += (x & -x))
        a[x] += k;
}

int query(int x)
{
    int ans = 0;
    for(; x; x -= (x & -x))
        ans += a[x];
    return ans;
}

int main()
{
    scanf("%d%d", &n, &m);
    int c, x, y, k = 0;
    rep (i, 1 ,n)
    {
        scanf("%d", &c);
        add(i, c - k);
        k = c;
    }
    rep (i, 1, m)
    {
        scanf("%d", &c);
        if (c == 1)
        {
            scanf("%d%d%d", &x, &y, &k);
            add(x, k);
            add(y + 1, -k);
        }
        else
        {
            scanf("%d", &x);
            printf("%d\n", query(x));
        }
    }
    return 0;
}