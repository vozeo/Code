#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define per(i_, s_, t_) for (int i_ = (s_); i_ >= (t_); --i_)

const int N = 1e5 + 5, P = 998244353;
typedef long long ll;

template <typename T>
void read(T &x) {
    char ch;
    while (!isdigit(ch = getchar()));
    for (x = ch - '0'; isdigit(ch = getchar()); x = x * 10 + ch - '0');
}

int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

int n, a[N];

void cal() {
    int mn = INT_MAX, p = 1, f;
    rep (i, 1, n - 1)
        if ((f = gcd(a[i], a[i + 1])) < mn)
            mn = f, p = i;
    int gl = a[1];
    rep (i, 1, p)
        gl = gcd(gl, a[i]);
    int gr = a[p + 1];
    rep (i, p + 1, n)
        gr = gcd(gr, a[i]);
    printf("%lld\n", 1ll * (n - 1) * mn + min(gl, gr));
}

int main() {
    freopen("A.in", "r", stdin);
    int x, y, m;
    read(n), read(m);
    rep (i, 1, n)
        read(a[i]);
    while (m--)
        read(x), read(y), a[x] = y, cal();
}
