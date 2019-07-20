#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

const int N = 105;
int f[N][70][70], a[N], s[N], c[N], cnt;
char ch[15];

int count(int x) {
    int res = 0;
    while (x)
        x -= x & -x, ++res;
    return res;
}

int main() {
    freopen("P2704-1.in", "r", stdin);
    int n, m;
    scanf("%d%d", &n, &m);
    rep (i, 1, n) {
        scanf("%s", ch);
        rep (j, 0, m - 1)
            a[i] = (a[i] << 1) + (ch[j] == 'H');
    }
    rep (i, 0, (1 << m) - 1) {
        if (i & (i << 1) || i & (i >> 1) || i & (i << 2) || i & (i >> 2))
            continue;
        s[++cnt] = i, c[cnt] = count(i);
    }
    
    rep (i, 1, cnt)
        if (!(a[1] & s[i]))
            f[1][i][0] = c[i];

    rep (i, 1, cnt)
        rep (j, 1, cnt) {
            if (s[i] & a[2] || s[j] & a[1] || s[i] & s[j])
                continue;
            f[2][i][j] = c[i] + c[j];
        }

    rep (i, 3, n)
        rep (j, 1, cnt) {
            if (s[j] & a[i]) continue;
            rep (k, 1, cnt) {
                if (s[k] & a[i - 1] || s[j] & s[k]) continue;
                rep (l, 1, cnt) {
                    if (s[l] & a[i - 2] || s[k] & s[l] || s[j] & s[l]) continue;
                    f[i][j][k] = max(f[i][j][k], f[i - 1][k][l] + c[j]);
                }
            }
        }
    int ans = 0;
    rep (i, 1, cnt)
        rep (j, 1, cnt)
        ans = max(ans, f[n][i][j]);
    printf("%d\n", ans);
}
