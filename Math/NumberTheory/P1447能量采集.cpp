#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

const int N = 1e5 + 5;
int n, m, t, cnt, pri[N], phi[N];
bool vis[N];
long long s[N];

void prework() {
    phi[1] = s[1] = 1;
    rep (i, 2, n) {
        if (!vis[i])
            pri[++cnt] = i, phi[i] = i - 1;
        rep (j, 1, cnt) {
            if ((t = pri[j] * i) > n) break;
            vis[t] = true, phi[t] = phi[i] * phi[pri[j]];
            if (i % pri[j] == 0) { 
                phi[t] = phi[i] * pri[j];
                break;
            }
        }
        s[i] = s[i - 1] + phi[i];
    }
}

long long ans;

int main() {
    scanf("%d%d", &n, &m);
    if (n > m) swap(n, m);
    prework();
    for (int l = 1, r = 0; l <= n; l = r + 1) {
        r = min(n / (n / l), m / (m / l));
        ans += 1ll * (n / l) * (m / l) * (s[r] - s[l - 1]);
    }
    printf("%lld\n", ans * 2 - 1ll * n * m);
}
