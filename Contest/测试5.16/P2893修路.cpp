#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define per(i_, s_, t_) for (int i_ = (s_); i_ >= (t_); --i_)

const int N = 2005;

template <typename T>
void read(T &x) {
    char ch = 0;
    while (!isdigit(ch = getchar()));
    for (x = ch - '0'; isdigit(ch = getchar()); x = x * 10 + ch - '0');
}

int n, a[N], b[N], c[N], f[N][N];

int main() {
    freopen("P2114.in", "r", stdin);
    read(n);
    int mx = 0, mn, tot = 0;
    rep (i, 1, n)
        read(a[i]), b[i] = a[i], mx = max(mx, a[i]);
    sort(b + 1, b + n + 1);
    unique(b + 1, b + n + 1);
    rep (i, 1, n)
        if (b[i] == mx) {
            tot = i;
            break;
        }
    /* int tot = lower_bound(b + 1, b + n + 1, mx) - b; */
    /* rep (i, 1, n) */
    /*     c[i] = lower_bound(b + 1, b + tot + 1, a[i]) - b; */
    /* rep (i, 1, n) */
    /*     cout << c[i] << " "; */
    rep (i, 1, n) {
        mn = INT_MAX;
        rep (j, 1, tot) {
            mn = min(mn, f[i - 1][j]);
            f[i][j] = mn + abs(a[i] - b[j]);
        }
    }
    int ans = INT_MAX;
    rep (i, 1, tot)
        ans = min(ans, f[n][i]);
    
    rep (i, 1, n) {
        mn = INT_MAX;
        per (j, tot, 1) {
            mn = min(mn, f[i - 1][j]);
            f[i][j] = mn + abs(a[i] - b[j]);
        }
    }
    rep (i, 1, tot)
        ans = min(ans, f[n][i]);
    printf("%d\n", ans);
}
