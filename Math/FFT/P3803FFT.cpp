#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define re(i_, s_, t_) for (int i_ = (s_); i_ < (t_); ++i_)

const int N = 1e6 + 5;
const double PI = acos(-1.0);
int lim, r[N << 2];

struct com {
    double x, y;
    com() {}
    com(double s, double t) : x(s), y(t) {}
    com operator * (const com &rhs) const {
        return com(x * rhs.x - y * rhs.y, x * rhs.y + y * rhs.x);
    }
    com operator + (const com &rhs) const {
        return com(x + rhs.x, y + rhs.y);
    }
    com operator - (const com &rhs) const {
        return com(x - rhs.x, y - rhs.y);
    }
} a[N << 2], b[N << 2];

void fft(com f[], int op) {
    re (i, 0, lim)
        if (i < r[i])
            swap(f[i], f[r[i]]);
    for (int i = 1; i < lim; i <<= 1) {
        com wn(cos(PI / i), op * sin(PI / i));
        for (int j = 0; j < lim; j += (i << 1)) {
            com w(1, 0);
            re (k, j, j + i) {
                com tp = w * f[k + i];
                f[k + i] = f[k] - tp;
                f[k] = f[k] + tp;
                w = w * wn;
            }
        }
    }
}
template<typename T>
void read(T &x) {
    char ch = 0;
    while (!isdigit(ch = getchar()));
    for (x = ch - '0'; isdigit(ch = getchar()); x = x * 10 + ch - '0');
}

int main() {
    int n, m, l = 0;
    read(n), read(m);
    rep (i, 0, n)
        read(a[i].x);
    rep (i, 0, m)
        read(b[i].x);
    lim = 1;
    while (lim <= n + m)
        lim <<= 1, ++l;
    rep (i, 0, lim)
        r[i] = (r[i >> 1] >> 1) | ((i & 1) << (l - 1)); // ***
    fft(a, 1), fft(b, 1);
    rep (i, 0, lim)
        a[i] = a[i] * b[i];
    fft(a, -1);
    rep (i, 0, n + m)
        printf("%d ", (int)(a[i].x / lim + 0.5));
    puts("");
}
