#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

typedef long long ll;


ll qpow(ll x, ll b, int P) {
    ll ans = 1;
    for (; b; b >>= 1, x = x * x % P)
        if (b & 1)
            ans = ans * x % P;
    return ans;
}

ll hs(int l, int r) {
    return 
}

void work() {
    scanf("%s", a + 1);
    int len = strlen(a + 1);
    rep (i, 1, n) {
        f[i] = (f[i - 1] * bs + (ll)a[i]) % P1;
        g[i] = (g[i - 1] * bs + (ll)a[i]) % P2;
    }

}

int main() {
    scanf("%d", &T);
    p1[0] = p2[0] = 1;
    rep (i, 1, 2000)
        p1[i] = p1[i - 1] * bs % P1, p2[i] = p2[i - 1] * bs % P2;
    while (T--)
        work();


}
