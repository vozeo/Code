#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

const int N = 205;
int a[N][N], b[N][N], c[N][N], x[3], y[3], z[3], ans;

int main() {
    freopen("6.in", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n = 1;
    cin >> n;
    rep (i, 1, n) {
        cin >> x[1] >> y[1] >> z[1] >> x[2] >> y[2] >> z[2];
        rep (j, x[1], x[2] - 1)
            rep (k, y[1], y[2] - 1)
                ++a[j][k];
        rep (j, x[1], x[2] - 1)
            rep (k, z[1], z[2] - 1)
                ++b[j][k];
        rep (j, y[1], y[2] - 1)
            rep (k, z[1], z[2] - 1)
                ++c[j][k];
    }
    rep (i, 0, 199)
        rep (j, 0, 199) {
            if (a[i][j]) ++ans;
            if (b[i][j]) ++ans;
            if (c[i][j]) ++ans;
        }
    cout << ans * 2 << endl;
    

}
