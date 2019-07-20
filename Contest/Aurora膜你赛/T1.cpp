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
