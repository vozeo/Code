#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

typedef long long ll;
const int N = 3e4 + 5;

/* void solve1() { */
/*     for (int i = 4; i <= len; i += 2) */
/*         ans += 1ll * (len - i + 1) * (((i - 4) >> 1) + 1); */
/* } */

ll hs(int l, int r, ll h[], ll c[], int P) {
    return h[r] - h[l - 1] * c[r - l + 1] % P;
}

const long long bs = 131, P1 = 1e9 + 7, P2 = 1e9 + 9;
ll f[N], g[N], p1[N], p2[N];

bool cal(int l, int r) {
    if (l >= r) return false;
    int w = (l + r) >> 1;
    ll a = hs(l - 1, w, f, p1, P1), b = hs(w, r, f, p1, P1);
    ll c = hs(l - 1, w, g, p2, P2), d = hs(w, r, g, p2, P2);
    return a == b && c == d;
}

ll a[N], b[N], ans;
char s[N];

int main() {
    freopen("P1117.in", "r", stdin);
    p1[0] = p2[0] = 1;
    rep (i, 1, 2000)
        p1[i] = p1[i - 1] * bs % P1, p2[i] = p2[i - 1] * bs % P2;
    int T, n;
    scanf("%d\n", &T);
    while (T--) {
        scanf("%s", s + 1);
        n = strlen(s + 1), ans = 0;
        rep (i, 1, n) {
            f[i] = (f[i - 1] * bs + (ll)s[i]) % P1;
            g[i] = (g[i - 1] * bs + (ll)s[i]) % P2;
        }
        rep (i, 1, n)
            cout << f[i] << " ";
        for (int i = 1; i <= n; i += 2)
            for (int j = i + 2; j <= n; j += 2)
                if (cal(i, j - 1))
                    ++a[i], ++b[j - 1];
        ans = 0;
        rep (i, 1, n)
            ans += a[i] * b[i - 1];
        printf("%lld\n", ans);
    }
}
