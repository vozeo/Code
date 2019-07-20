#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define per(i_, s_, t_) for (int i_ = (s_); i_ >= (t_); --i_)

const int N = 1e5 + 5;
typedef long long ll;

template <typename T>
void read(T &x) {
    char ch;
    while (!isdigit(ch = getchar()));
    for (x = ch - '0'; isdigit(ch = getchar()); x = x * 10 + ch - '0');
}

ll n, P, Q, m, k, a[100];

ll qpow(ll x, ll b) {
    if (b < 0) return 0;
    ll ans = 1;
    for (; b; b >>= 1, x = x * x % P)
        if (b & 1)
            ans = ans * x % P;
    return ans;
}

int main() {
    //freopen("A.in", "r", stdin);
    read(n), read(P);
    rep (i, 0, n)
        read(a[i]);
    read(Q);
    rep (i, 1, Q) {
        read(m), read(k);
        printf("%lld\n", qpow(a[0], k) * qpow(a[1], m - k) % P);
    }
}
