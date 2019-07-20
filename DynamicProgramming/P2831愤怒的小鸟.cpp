#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define per(i_, s_, t_) for (int i_ = (s_); i_ >= (t_); --i_)

int n, cnt, t[500], f[1 << 19];
double x[20], y[20];
double a1, a2, b1, b2, c1, c2, p, q;

void cal(int i, int j) {
    a1 = x[i] * x[i], a2 = x[j] * x[j];
    b1 = x[i], b2 = x[j];
    c1 = y[i], c2 = y[j];
    p = (c1 * b2 - c2 * b1) / (a1 * b2 - a2 * b1);
    q = (c1 * a2 - c2 * a1) / (b1 * a2 - b2 * a1);
    rep (k, 1, n)
        if (p * x[k] * x[k] + q * x[k] == y[k])
            t[cnt] |= 1 << (k - 1);
}

void init() {

}

void work() {
    scanf("%d", &n);
    rep (i, 1, n)
        scanf("%lf%lf", &x[i], &y[i]);
    rep (i, 1, n)
        rep (j, i, n)
            ++cnt, cal(i, j);
    sort(t + 1, t + cnt + 1);
    cnt = unique(t + 1, t + cnt + 1) - t - 1;
    memset(f, 0x3f, sizeof f);

    f[0] = 0;
    rep (i, 1, cnt)
        per (j, (1 << n) - 1, 0)
            f[j | t[i]] = min(f[j | t[i]], f[j] + 1);
    printf("%d\n", f[(1 << n) - 1]);
}

int main() {
    freopen("P2831.in", "r", stdin);
    int T;
    scanf("%d", &T);
    while (T--)
        init(), work();
}
