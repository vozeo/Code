#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

const int N = 1e5 + 5;

struct Peo {
    int l, r;
    bool operator < (const Peo &rhs) const {
        return r == rhs.r ? l < rhs.l : r < rhs.r;
    }
    bool operator != (const Peo &rhs) const {
        return l != rhs.l || r != rhs.r;
    }
} t[N];

int n, cnt, p, tot, w[N], l[N], r[N], f[N];

void read(int &x) {
    char ch;
    while (!isdigit(ch = getchar()));
    for (x = ch - '0'; isdigit(ch = getchar()); x = x * 10 + ch - '0');
}

int main() {
    freopen("P2519.in", "r", stdin);
    read(n);
    int x, y;
    rep (i, 1, n) {
        read(x), read(y);
        if (x + y >= n) continue;
        t[++tot].l = x + 1, t[tot].r = n - y;
    }
    sort(t + 1, t + tot + 1);
    rep (i, 1, tot) {
        if (t[i] != t[i - 1]) ++cnt;
        w[cnt] = min(w[cnt] + 1, t[i].r - t[i].l + 1);
        l[cnt] = t[i].l, r[cnt] = t[i].r;
    }
    p = 1;
    rep (i, 1, n) {
        f[i] = f[i - 1];
        while (p <= cnt && r[p] == i)
            f[i] = max(f[i], f[l[p] - 1] + w[p]), ++p;
    }
    printf("%d\n", n - f[n]);
}
