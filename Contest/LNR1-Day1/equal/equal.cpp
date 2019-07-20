#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define per(i_, s_, t_) for (int i_ = (s_); i_ >= (t_); --i_)

const int N = 1e5 + 5, P = 998244353;
char s[N];
int n, ans, f[2][N], a[N];

void solve1() {
    rep (i, 1, n + 1)
        a[i] = i;
    do {
        rep (i, 1, n)
            if ((a[i] < a[i + 1]) != (s[i] == '<'))
                goto A;
        ++ans;
        if (ans > P) ans -= P;
A:;
    } while (next_permutation(a + 1, a + n + 2));
    printf("%d\n", ans);
}

void solve2() {
    int v;
    f[1][1] = 1;
    rep (i, 2, n) {
        v = i & 1;
        f[v][1] = f[v ^ 1][i - 1];
        rep (j, 2, i)
            f[v][j] = (f[v][j - 1] + f[v ^ 1][i - j]) % P;
    }
    printf("%d\n", f[n & 1][n]);
}

int main() {
    freopen("equal1.in", "r", stdin);
    //freopen("alone3.out", "w", stdout);
    scanf("%s", s + 1);
    n = strlen(s + 1);
    if (n <= 10)
        solve1();
    else ++n, solve2();
}
