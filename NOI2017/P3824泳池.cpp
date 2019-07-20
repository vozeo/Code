#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define per(i_, s_, t_) for (int i_ = (s_); i_ >= (t_); --i_)

typedef long long ll;
const int N = 1005, P = 998244353;
ll f[N];

ll qpow(ll x, ll b = P - 2) {
    ll ans = 1;
    for (; b; b >>= 1, x = x * x % P)
        if (b & 1)
            ans = ans * x % P;
    return ans;
}

template<typename T>
void read(T &x) {
    char ch;
    while (!isdigit(ch = getchar()));
    for (x = ch - '0'; isdigit(ch = getchar()); x = x * 10 + ch - '0');
}

int main() {
    ll n, m, x, y;
    freopen("P3824-1.in", "r", stdin);
    scanf("%lld%lld%lld%lld", &n, &m, &x, &y);
    printf("%lld\n", qpow(x * qpow(y) % P, m) * (y - x) % P * qpow(y) % P);
}
