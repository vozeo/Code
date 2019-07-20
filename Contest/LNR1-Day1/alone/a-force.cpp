#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define per(i_, s_, t_) for (int i_ = (s_); i_ >= (t_); --i_)

const int N = 1e5 + 5, P = 998244353;
typedef long long ll;
int type, tot;
ll las, a[N];

template <typename T>
void read(T &x) {
    char ch;
    while (!isdigit(ch = getchar()));
    for (x = ch - '0'; isdigit(ch = getchar()); x = x * 10 + ch - '0');
}

void cal(ll l, ll r) {
    if (type) l ^= las, r ^= las;
    ll x = a[r], y = 1, p;
    per (i, r - 1, l)
        p = y, y = x, x = (p + a[i] * x) % P;
    //x %= P, y %= P;
    printf("%lld %lld\n", x, y);
    las = x ^ y;
}

int main() {
    freopen("alone3.in", "r", stdin);
    freopen("alone3.out", "w", stdout);
    int n, m, op, x, y;
    read(n), read(m), read(type);
    tot = n;
    rep (i, 1, n)
        read(a[i]);
    rep (i, 1, m) {
        read(op), read(x);
        if (op == 1) {
            if (type) x ^= las;
            a[++tot] = x;
        }
        else read(y), cal(x, y);
    }
}
