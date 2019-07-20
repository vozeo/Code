#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

int x, n, mx, ans, c[15], cnt;
bool vis[15];

int main() {
    scanf("%d", &n);
    rep (i, 1, n) {
        scanf("%d", &x);
        vis[x] = true, ++c[x];
        rep (j, 1, 10)
            if (vis[j])
                mx = max(mx, c[j]);
        --mx, cnt = 0;
        rep (j, 1, 10)
            if (vis[j])
                cnt += c[j] - mx;
        if (cnt == 1)
            ans = max(ans, i);
    }
    cout << ans << endl;
}
