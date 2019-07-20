#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

bool judge(int x) {
    g.clear();
    rep (i, 1, n)
        rep (j, 1, m)
            g.insert(a[i][j]);
    rep (i, x, n)
        rep (j, x, m) {
            

        }
}

int main() {
    ios::sync_with_stdio(false);
    int n, m, k;
    cin >> n >> m >> k;
    rep (i, 1, n)
        rep (j, 1, m)
            cin >> a[i][j], s[i][j] = a[i][j] + s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1], mx = max(mx, a[i][j]);
    int l = -1, r = mx;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (judge(mid))
            r = mid;
        else l = mid + 1;
    }
}
