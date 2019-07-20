#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

const int N = 505, P = 1024523;

void add(int &a, int b) {
    if ((a += b) >= P) a -= P;
}

int f[2][N][N];
char a[N], b[N];

int main() {
    freopen("P1758.in", "r", stdin);
    int n, m, p, cur;
    scanf("%d%d", &n, &m);
    scanf("%s%s", a + 1, b + 1);
    f[0][0][0] = 1;
    rep (i, 0, n)
        rep (j, 0, m)
            rep (k, 0, n) {
                cur = i & 1, p = f[cur][j][k];
                if (a[i + 1] == a[k + 1])
                    add(f[cur ^ 1][j][k + 1], p);
                if (a[i + 1] == b[i + j - k + 1])
                    add(f[cur ^ 1][j][k], p);
                if (b[j + 1] == b[i + j - k + 1])
                    add(f[cur][j + 1][k], p);
                if (b[j + 1] == a[k + 1])
                    add(f[cur][j + 1][k + 1], p);
                f[cur][j][k] = 0;
            }
    printf("%d\n", f[!(n & 1)][m][n]);
}
