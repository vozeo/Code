#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

const int N = 1005;
int a[N], b[N][N], f[N];

int main() {
    int n, m, p, sum, t;
    scanf("%d%d%d", &n, &m, &p);
    rep (i, 1, n)
        rep (j, 1, m)
            scanf("%d", &b[i][j]);
    rep (i, 1, n)
        scanf("%d", &a[i]);
    memset(f, -0x3f, sizeof f);
    f[0] = 0;
    rep (i, 1, m)
        rep (j, 1, n) {
            sum = -a[j] + f[i - 1];
            for (int k = 0; k < p && i + k <= m; ++k) {
                t = j + k;
                t = t > n ? t - n : t;
                sum += b[t][i + k];
                f[i + k] = f[i + k] > sum ? f[i + k] : sum;
            }
        }
    printf("%d\n", f[m]);
}
