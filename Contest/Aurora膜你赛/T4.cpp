#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define per(i_, s_, t_) for (int i_ = (s_); i_ >= (t_); --i_)

const int N = 6e6 + 5, P = 998244353;

template <typename T>
void read(T &x) {
    char ch = 0;
    while (!isdigit(ch = getchar()));
    for (x = ch - '0'; isdigit(ch = getchar()); x = x * 10 + ch - '0');
}

int fac[N], inv[N], tot;

int C(int n, int m) {
    if (n < m)
        return 0;
    return 1ll * fac[n] * inv[m] % P * inv[n - m] % P;
}

int qpow(int x, int b = P - 2) {
    int ans = 1;
    for (; b; b >>= 1, x = 1ll * x * x % P)
        if (b & 1)
            ans = 1ll * ans * x % P;
    return ans;
}

void prework() {
    fac[1] = inv[1] = fac[0] = inv[0] = 1;
    rep (i, 2, tot)
        fac[i] = 1ll * fac[i - 1] * i % P;
    inv[tot] = qpow(fac[tot]);
    per (i, tot - 1, 2)
        inv[i] = 1ll * inv[i + 1] * (i + 1) % P;
}

int y[N], f[105][6005];

void work() {

}

int main() {
    freopen("restrict1.in", "r", stdin);
    /* freopen("a4.out", "w", stdout); */



    int n, S, Q, mc = INT_MAX;
    read(n), read(S), read(Q);
    tot = n + S;
    rep (i, 1, n)
        scanf("%d", &y[i]), mc = min(mc, y[i]);
    /* rep (i, 1, n) */
        /* cout << inv[i] << " " << fac[i] << endl; */
    /*
    if (mc == 1) {
   work1();
        return 0;
    }
    */
    if (S <= mc) {
        prework();
        printf("%d\n", C(S + n - 1, n - 1));
        return 0;
    }
    f[0][0] = 1;
    rep (i, 1, n)
        rep (j, 0, S)
            rep (k, 0, y[i])
            f[i + 1][j + k] = 
            if (j >= k)
                f[i][j] = f[i][j] + f[i - 1][j - k] % P;
    printf("%d\n", f[n][S]);
}
