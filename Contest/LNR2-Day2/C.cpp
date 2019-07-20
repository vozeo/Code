#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define per(i_, s_, t_) for (int i_ = (s_); i_ >= (t_); --i_)

const int N = 2e5 + 5;
typedef long long ll;

template <typename T>
void read(T &x) {
    char ch;
    while (!isdigit(ch = getchar()));
    for (x = ch - '0'; isdigit(ch = getchar()); x = x * 10 + ch - '0');
}

int n, m;
int vis[N], a[N], b[N], c[N], t[N];

void upd(int x, int y) {
    for (; x <= (n << 1); x += x & -x)
        t[x] += y;
}

int qry(int x) {
    int ans = 0;
    for (; x; x -= x & -x)
        ans += t[x];
    return ans;
}

int cal(int x) {
    int s = qry(a[x]), l = 1, r = a[x], p = a[x];
    while (l < r) {
        int mid = (l + r + 1) >> 1;
        if (p + qry(mid - 1) + 1 > s + mid)
            l = mid;
        else r = mid - 1;
    }
    return l;
}

void add(int x, int p) {
    vis[p] = 1, upd(p, 1), b[x] = p;
}

bool comp(int x, int y) {
    return a[x] < a[y] || (a[x] == a[y] && x < y);
}

void srt() {
    sort(c + 1, c + n + 1, comp);
    memset(t, 0, sizeof t);
    memset(vis, 0, sizeof vis);
    rep (i, 1, n) {
        if (vis[a[c[i]]])
            add(c[i], cal(c[i]));
        else add(c[i], a[c[i]]);
    }
}

int main() {
    freopen("s2.in", "r", stdin);
    freopen("s2.out", "w", stdout);
    read(n), read(m);
    rep (i, 1, n)
        read(a[i]), c[i] = i;
    int op, x, y;
    srt();
    while (m--) {
        read(op), read(x), read(y);
        if (op == 1)
            a[x] = y, srt();
        else {
            int ans = 0;
            rep (i, 1, n)
                if (b[i] <= x && a[i] >= y)
                    ans += a[i] + b[i];
            printf("%d\n", ans);
        }
    }
}
