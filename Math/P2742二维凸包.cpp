#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define per(i_, s_, t_) for (int i_ = (s_); i_ >= (t_); --i_)

const int N = 1e4 + 5;

struct Pot {
    double x, y;
    Pot() {}
    Pot(const Pot &a, const Pot &b) : x(b.x - a.x), y(b.y - a.y) {}
    bool operator < (const Pot &a) const {
        return x < a.x || (x == a.x && y < a.y);
    }
    double operator * (const Pot &a) const {
        return x * a.y - y * a.x;
    }
    double dis() const {
        return x * x + y * y;
    }
} p[N], t[N];

typedef Pot Vec;

int main() {
    freopen("P2742.in", "r", stdin);
    int n, c = 0, r;
    scanf("%d", &n);
    rep (i, 1, n)
        scanf("%lf%lf", &p[i].x, &p[i].y);
    sort(p + 1, p + n + 1);
    rep (i, 1, n) {
        while (c > 1 && Vec(t[c - 1], t[c]) * Vec(t[c - 1], p[i]) < 0)
            --c;
        t[++c] = p[i];
    }
    r = c;
    per (i, n, 1) {
        while (c > r && Vec(t[c - 1], t[c]) * Vec(t[c - 1], p[i]) < 0)
            --c;
        t[++c] = p[i];
    }
    double ans = 0;
    rep (i, 2, c)
        ans += sqrt(Vec(t[i - 1], t[i]).dis());
    ans += sqrt(Vec(t[c], t[1]).dis());
    printf("%.2f\n", ans);
}
