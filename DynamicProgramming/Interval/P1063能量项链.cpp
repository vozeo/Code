#include <cstdio>
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

int n, ans, f[205][205], a[205];

inline int max(int a, int b)
{
    return a > b ? a : b;
}

int main()
{
    scanf("%d", &n);
    rep (i, 1, n)
    {
        scanf("%d", &a[i]);
        a[i + n] = a[i];
    }
    rep (l, 2, n)
        rep (i, 1, 2 * n - l)
        {
            int j = i + l;
            if (j > 2 * n)
                break;
            rep (k, i + 1, j - 1)
                f[i][j] = max(f[i][j], f[i][k] + f[k][j] + a[i] * a[k] * a[j]);
        }
    rep (i, 1, n)
        ans = max(ans, f[i][i + n]);
    printf("%d\n", ans);
    return 0;
}