#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define per(i_, s_, t_) for (int i_ = (s_); i_ >= (t_); --i_)

const int N = 2005;
int a[N][N], le[N][N], ri[N][N];

int sqr(int x) { return x * x; }

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    rep (i, 1, n)
        rep (j, 1, m)
            scanf("%d", &a[i][j]);
    rep (i, 1, n)
        le[i][1] = ri[i][m] = 1;
    rep (i, 1, n) {
        rep (j, 2, m)
            le[i][j] = (a[i][j] == a[i][j - 1]) ? 1 : le[i][j - 1] + 1;
        per (j, m - 1, 1)
            ri[i][j] = (a[i][j] == a[i][j + 1]) ? 1 : ri[i][j + 1] + 1;
    }
    int ans1 = 1, ans2 = 1;
    rep (j, 1, m) {
        int up, l, r;
        rep (i, 1, n) {
            if (i == 1 || a[i][j] == a[i - 1][j])
                up = 1, l = le[i][j], r = ri[i][j];
            else ++up, l = min(l, le[i][j]), r = min(r, ri[i][j]);
            ans1 = max(ans1, up * (r + l - 1));
            ans2 = max(ans2, sqr(min(up, r + l - 1)));
        }
    }
    printf("%d\n%d\n", ans2, ans1);
}
