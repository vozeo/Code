#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

const int N = 505;
int a[N][N], f[N][N], g[N][N];

int main() {
    ios::sync_with_stdio(false);
    int n, m, t;
    cin >> n >> m >> t;
    int p = min(m, n) - 1;
    rep (i, 1, n)
        rep (j, 1, m)
            cin >> a[i][j], g[i][j] = f[i][j] = a[i][j];
    rep (k, 1, p)
        rep (i, 1, n - k)
            rep (j, 1, m - k) {
                f[i][j] = max(max(f[i + 1][j], f[i][j + 1]), max(a[i][j], a[i + k][j + k]));
                g[i][j] = min(min(g[i + 1][j], g[i][j + 1]), min(a[i][j], a[i + k][j + k]));
                    if (f[i][j] - g[i][j] >= t) {
                        cout << k + 1 << endl;
                        return 0;
                    }
            }
            cout << -1 << endl;
}
