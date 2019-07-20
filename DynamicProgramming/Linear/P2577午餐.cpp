#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

const int N = 205;
int f[N][N * N], s[N];

struct buc {
    int a, b;
    bool operator < (const buc &rhs) {
        return b > rhs.b;
    }
} c[N];

int main() {
    int n, ans = INT_MAX;
    scanf("%d", &n);
    rep (i, 1, n)
        scanf("%d%d", &c[i].a, &c[i].b);
    sort(c + 1, c + n + 1);
    rep (i, 1, n)
        s[i] = s[i - 1] + c[i].a;
    memset(f, 0x3f, sizeof f);
    f[0][0] = 0;
    rep (i, 1, n)
        rep (j, 0, s[i]) {
            if (j >= c[i].a)
                f[i][j] = min(f[i][j], max(f[i - 1][j - c[i].a], j + c[i].b));
            f[i][j] = min(f[i][j], max(f[i - 1][j], s[i] - j + c[i].b));
        }
    rep (i, 1, s[n])
        ans = min(ans, f[n][i]);
    printf("%d\n", ans);
}
