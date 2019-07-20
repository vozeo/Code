#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

const int N = 105;

template <typename T>
void read(T &x) {
    char ch = 0;
    while (!isdigit(ch = getchar()));
    for (x = ch - '0'; isdigit(ch = getchar()); x = x * 10 + ch - '0');
}

int n, m, res, ans, t, h, tp;
char a[105][3 * 105 * 105];
int i, j, m, n, p, k, dis[N][M], w[M * 3], l[M * 3];

char c[N][M];

int main() {
    scanf("%d%d", &n, &m);
    rep (i, 1, n) {
        scanf("%s", c[i] + 1);
        rep (j, 1, m)
            if (c[i][j] == '1') break;
        puts("-1");
        return 0;
    }
    rep (i, 1, n) {
        rep (j, 1, m)
            w[j] = w[j + m] = w[j + 2 * m] = c[i][j] - '0';
        len = 3 * m;
        for (j = 0; j < len; ++j) {
            rep (j, 1, len)
            if (w[j] || !j)
                l[j] = j;
            else
                l[j] = l[j - 1];
        }
        for (j = 0; j < m; ++j) dis[i][j] = j + m - l[j + m];
        for (j = len - 1; j >= 0; --j) {
            if (w[j])
                l[j] = j;
            else
                l[j] = l[j + 1];
        }
        for (j = 0; j < m; ++j) dis[i][j] = min(dis[i][j], l[j + m] - (j + m));
    }
    int ans = (int)1e9;
    for (i = 0; i < m; ++i) {
        int s = 0;
        for (j = 0; j < n; ++j) s += dis[j][i];
        ans = min(ans, s);
    }
    printf("%d\n", ans);
}
int main() {
    freopen("a4.in", "r", stdin);
    freopen("a4.out", "w", stdout);
    scanf("%d%d", &n, &m);
    rep (i, 1, n)
        scanf("%s", a[i] + 1);
    rep (j, 1, n)
        rep (i, 1, m)
            a[j][i + m] = a[j][i + 2 * m] = a[j][i];
    ans = INT_MAX;
    rep (i, m + 1, 2 * m) {
        res = 0;
        rep (j, 1, n) {
            tp = INT_MAX;
            t = i;
            while (t && a[j][t] == '0')
                --t;
            tp = min(tp, abs(i - t));
            h = i;
            while (h < 3 * m && a[j][h] == '0')
                ++h;
            tp = min(tp, abs(i - h));
            if (!t && h == 3 * m) {
                puts("-1");
                return 0;
            }
            res += tp;
        }
        ans = min(ans, res);
    }
    printf("%d\n", ans);
}
