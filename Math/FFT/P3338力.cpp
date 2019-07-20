#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define re(i_, s_, t_) for (int i_ = (s_); i_ < (t_); ++i_)

const int N = 4e6 + 5;
const double PI = acos(-1);

struct com {
    double x, y;
    com() {}
    com(double p, double q) : x(p), y(q) {}
    com operator * (const com &rhs) const {
        return com(x * rhs.x - y * rhs.y, x * rhs.y + y * rhs.x);
    }
    com operator + (const com &rhs) const {
        return com(x + rhs.x, y + rhs.y);
    }
    com operator - (const com &rhs) const {
        return com(x - rhs.x, y - rhs.y);
    }
} st[N], ed[N];


int n, lim, r[N << 2];

void fft(com f[], int op) {
    rep (i, 0, lim)
        if (i < r[i])
            swap(f[i], f[r[i]]);
    for (int i = 1; i < lim; i <<= 1) {
        com wn(cos(PI / i), op * sin(PI / i));
        for (int t = i << 1, j = 0; j < lim; j += t) {
            com w(1, 0);
            for (int k = j; k < j + i; ++k, w = w * wn) {
                com tp = w * f[k + i];
                f[k + i] = f[k] - tp;
                f[k] = f[k] + tp;
            }
        }
    }
}

double p[N], q[N], g[N], fa[N], fb[N];

void work(double a[], double b[], double res[]) {
    rep (i, 0, lim)
        st[i].x = a[i], ed[i].x = b[i], st[i].y = ed[i].y = 0;
    fft(st, 1), fft(ed, 1);
    rep (i, 0, lim)
        st[i] = st[i] * ed[i];
    fft(st, -1);
    rep (i, 1, n)
        res[i] = st[i].x / lim;
}

void init() {
    int len = 0;
    for (lim = 1; lim < (n << 1); lim <<= 1, ++len);
    re (i, 0, lim)
        r[i] = (r[i >> 1] >> 1) | ((i & 1) * (lim >> 1));
}

int main() {
    freopen("P3338.in", "r", stdin);
    scanf("%d", &n);
    init();
    rep (i, 1, n)
        scanf("%lf", &p[i]), q[i] = p[i], g[i] = 1.0 / i / i;
    reverse(q + 1, q + n + 1);
    work(p, g, fa);
    work(q, g, fb);
    rep (i, 1, n)
        printf("%.3f\n", fa[i] - fb[n - i + 1]);
}
