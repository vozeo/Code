#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define per(i_, s_, t_) for (int i_ = (s_); i_ >= (t_); --i_)

const int N = 105;
int a[N], t[20];
double f[N][1 << 16];

int main() {
    freopen("P2473.in", "r", stdin);
    int m, n, x;
    scanf("%d%d", &m, &n);
    rep (i, 1, n) {
        scanf("%d", &a[i]);
        while (scanf("%d", &x) && x)
            t[i] |= 1 << (x - 1);
    }
    per (i, m, 1)
        rep (j, 0, (1 << n) - 1) {
            rep (k, 1, n) {
                if ((t[k] | j) == j)
                    f[i][j] += max(f[i + 1][j], f[i + 1][j | (1 << (k - 1))] + a[k]);
                else f[i][j] += f[i + 1][j];
            }
            f[i][j] /= n;
        }
    printf("%.6f", f[1][0]);
}
