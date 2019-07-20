#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

const int P = 9999973;
int f[105][105][105], ans;

int main() {
    int n, m, p;
    scanf("%d%d", &n, &m);
    f[0][0][0] = 1;
    rep (i, 0, n - 1)
        rep (j, 0, m)
            rep (k, 0, m - j) {
                p = m - j - k;
                if (j > 1) f[i + 1][j - 2][k + 2] = (f[i + 1][j - 2][k + 2] + 1ll * f[i][j][k] * j * (j - 1) / 2) % P;
                if (p > 1) f[i + 1][j + 2][k] = (f[i + 1][j + 2][k] + 1ll * f[i][j][k] * p * (p - 1) / 2) % P;
                if (p) f[i + 1][j + 1][k] = (f[i + 1][j + 1][k] + f[i][j][k] * p) % P;
                if (j) f[i + 1][j - 1][k + 1] = (f[i + 1][j - 1][k + 1] + f[i][j][k] * j) % P;
                if (p && j) f[i + 1][j][k + 1] = (f[i + 1][j][k + 1] + 1ll * f[i][j][k] * j * p) % P;
                f[i + 1][j][k] = (f[i + 1][j][k] + f[i][j][k]) % P;
            }
    rep (j, 0, m)
        rep (k, 0, m - j)
            ans = (ans + f[n][j][k]) % P;
    printf("%d\n", ans);
}
