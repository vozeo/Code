#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define per(i_, s_, t_) for (int i_ = (s_); i_ >= (t_); --i_)

typedef long long ll;
const int N = 1e5 + 5;
int n, m, top, stk[N];
bool vis[N];

template <typename T>
void read(T &x) {
    char ch;
    int f = 1;
    while (!isdigit(ch = getchar()))
        if (ch == '-') f = -1;
    for (x = ch - '0'; isdigit(ch = getchar()); x = x * 10 + ch - '0');
    x *= f;
}

struct Pot {
    ll x, y;
    int id;
    Pot() {}
    Pot(const Pot &a, const Pot &b) : x(b.x - a.x), y(b.y - a.y) {}
    bool operator < (const Pot &a) const {
        return x < a.x || (x == a.x && y < a.y);
    }
    ll operator * (const Pot &a) const {
        return x * a.y - y * a.x;
    }
    ll dis() const {
        return x * x + y * y;
    }
} p[N], t[N];

typedef Pot Vec;

ll cal() {
    int c = 0, r;
    rep (i, 1, n) {
        if (vis[p[i].id]) continue;
        while (c > 1 && Vec(t[c - 1], t[c]) * Vec(t[c - 1], p[i]) < 0)
            --c;
        t[++c] = p[i];
    }
    r = c;
    per (i, n, 1) {
        if (vis[p[i].id]) continue;
        while (c > r && Vec(t[c - 1], t[c]) * Vec(t[c - 1], p[i]) < 0)
            --c;
        t[++c] = p[i];
    }
    ll ans = 0;
    rep (i, 3, c)
        ans += Vec(t[1], t[i - 1]) * Vec(t[1], t[i]);
    return ans;
}

int main() {
    freopen("P3827-2.in", "r", stdin);
    read(n), read(m);
    rep (i, 1, n)
        read(p[i].x), read(p[i].y), p[i].id = i;
    ll lst = -1;
    int d, v, k;
    sort(p + 1, p + n + 1);
    while (m--) {
        read(k);
        rep (i, 1, k) {
            read(d), v = (lst + d) % n + 1;
            stk[++top] = v, vis[v] = true;
        }
        printf("%lld\n", lst = cal());
        while (top) vis[stk[top--]] = false;
    }
}
