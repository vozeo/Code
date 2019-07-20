#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

typedef long long ll;
const int N = 1e7 + 5;

ll mu[N], pri[N], f[N];
bool vis[N];
int n, cnt;

void prework() {
    mu[1] = 1;
    ll to;
    rep (i, 2, n) {
        if (!vis[i]) {
            pri[++cnt] = i;
            mu[i] = -1;
        }
        rep (j, 1, cnt) {
            to = i * pri[j];
            if (to > n) break;
            vis[to] = true;
            if (i % pri[j] == 0) {
                mu[to] = 0;
                break;
            }
            mu[to] = -mu[i];
        }
    }

    rep (j, 1, cnt)
        for (int i = 1; i * pri[j] <= n; ++i)
            f[i * pri[j]] += mu[i];
    rep (i, 1, n)
        f[i] += f[i - 1];
}

int main() {
    scanf("%d", &n);
    prework();
    ll ans = 0;
    for (int l = 1, r; l <= n; l = r + 1) {
        r = n / (n / l);
        ans += (f[r] - f[l - 1]) * (n / l) * (n / l);
    }
    rep (i, 1, n)
        cout << mu[i] << " " ;
    cout << endl;
    printf("%lld\n", ans);
}
