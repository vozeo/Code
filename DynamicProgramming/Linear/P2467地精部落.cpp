#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

int f[2][4205], ans;

int main() {
    int n, P;
    scanf("%d%d", &n, &P);
    f[0][2] = 1;
    rep (i, 3, n)
        rep (j, 1, i)
            f[i & 1][j] = (f[i & 1][j - 1] + f[(i - 1) & 1][i - j + 1]) % P;
    rep (i, 1, n)
        ans = (ans + f[n & 1][i]) % P;
    printf("%d\n", (ans << 1) % P);
}
