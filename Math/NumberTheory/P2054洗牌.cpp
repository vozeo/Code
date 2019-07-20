#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i)

typedef long long ll;
ll P;

void exgcd(ll a, ll b, ll &x, ll &y) {
    if (!b) {
        x = 1, y = 0;
        return;
    }
    exgcd(b, a % b, y, x);
    y -= (a / b) * x;
}

ll mul(ll &x, ll y) {
    ll ans = 0;
    for (; y; y >>= 1, x = (x << 1) % P)
        if (y & 1)
            ans = (ans + x) % P;
    return ans;
}

ll qpow(ll x, ll t) {
    ll ans = 1;
    for (; t; t >>= 1, x = mul(x, x))
        if (t & 1)
            ans = mul(ans, x);
    return ans;
}


int main() {
    ll n, m, l, x, y;
    scanf("%lld%lld%lld", &n, &m, &l);
    P = n + 1;
    exgcd(qpow(2, m), n + 1, x, y);
    printf("%lld\n", (mul(x, l) % (n + 1) + n + 1) % (n + 1));
}
