#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (ll i_ = (s_); i_ <= (t_); ++i_)

typedef long long ll;

ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (!b)
        return x = 1, y = 0, a;
    ll d = exgcd(b, a % b, y, x);
    y -= (a / b) * x;
    return d;
}

void end() {
    printf("-1\n");
    exit(0);
}

int main() {
    freopen("CF982E.in", "r", stdin);
    ll n, m, a, b, p, q, d, x, y, g, vx, vy;
    scanf("%lld%lld%lld%lld%lld%lld", &n, &m, &a, &b, &p, &q);
    if (!p) {
        if (a && a != n) end();
        else printf("%lld %lld\n", a, q > 0 ? m : 0);
        return 0;
    }
    if (!q) {
        if (b && b != m) end();
        else printf("%lld %lld\n", p > 0 ? n : 0, b);
        return 0;
    }
    if (p < 0) a = n - a;
    if (q < 0) b = m - b;

    d = exgcd(n, m, x, y), g = (a - b) / d;
    if ((a - b) % d) end();

    x *= g, y *= g;
    ll dm = m / d;
    vx = (x % dm + dm - 1) % dm + 1, vy = (vx * n + b - a) / m;

    ll an = n, am = m;
    if ((vx & 1) == 0) an = n - an;
    if ((vy & 1) == 0) am = m - am;
    printf("%lld %lld\n", p == -1 ? n - an : an, q == -1 ? m - am : am);
}
