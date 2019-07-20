#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define per(i_, s_, t_) for (int i_ = (s_); i_ >= (t_); --i_)

typedef long long ll;
const int N = 3e6 + 5;
int n, m, K;
ll ans[N], tot, now;

template<typename T>
void read(T &x) {
    char ch;
    while (!isdigit(ch = getchar()));
    for (x = ch - '0'; isdigit(ch = getchar()); x = x * 10 + ch - '0');
}

struct Veg {
    ll a, s, c, x;
    Veg() {}
    Veg(ll da, ll ds, ll dc, ll dx) : a(da), s(ds), c(dc), x(dx) {}
    bool operator < (const Veg &rhs) const {
        return a > rhs.a;
    }
} g[N << 1];

void solve1() {
    tot = n;
    rep (i, 1, n)
        if (g[i].c > 1)
            --g[i].c, g[++tot] = Veg(g[i].s + g[i].a, 0, 1, 0);
    sort(g + 1, g + tot + 1);
    rep (i, 1, tot) {
        rep (j, now + 1, now + g[i].c)
            ans[(j - 1) / m + 1] += g[i].a;
        now += g[i].c;
    }
    now = (now - 1) / m + 1;
    rep (i, 1, now)
        ans[i] += ans[i - 1];
    int p;
    rep (i, 1, K)
        read(p), printf("%lld\n", ans[p]);
}

int main() {
    freopen("P3826.in", "r", stdin);
    read(n), read(m), read(K);
    rep (i, 1, n)
        read(g[i].a), read(g[i].s), read(g[i].c), read(g[i].x);
    solve1();
}
