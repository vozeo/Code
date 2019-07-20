#include <cstdio>
#define go(i, j, n, k) for (int i = j; i <= n; i += k)
#define fo(i, j, n, k) for (int i = j; i >= n; i -= k)
#define mn 500010
#define ll long long
inline ll read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (ch > '9' || ch < '0')
    {
        if (ch == '-')
            f = -f;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
ll z[mn << 2], M, n, m;
inline void update(int rt) { z[rt] = z[rt << 1] + z[rt << 1 | 1]; }
inline void build()
{
    for (M = 1; M < n + 2; M <<= 1)
        ;
    go(i, M + 1, M + n, 1) z[i] = read();
    fo(i, M, 1, 1) update(i);
}
inline void modify(int now, ll v)
{
    for (z[now += M] += v, now >>= 1; now; now >>= 1)
        update(now);
}
inline ll query(int l, int r)
{
    int ans = 0;
    for (--l += M, ++r += M; l ^ r ^ 1; l >>= 1, r >>= 1)
    {
        if (~l & 1)
            ans += z[l ^ 1];
        if (r & 1)
            ans += z[r ^ 1];
    }
    return ans;
}
int main()
{
    n = read(), m = read();
    build();
    go(i, 1, m, 1)
    {
        int s = read(), x = read(), y = read();
        if (s == 1)
            modify(x, y);
        else
            printf("%lld\n", query(x, y));
    }
}