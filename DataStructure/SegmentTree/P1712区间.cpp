#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

const int N = 5e5 + 5;

template<typename T>
void read(T &x) {
    char ch;
    while (!isdigit(ch = getchar()));
    for (x = ch - '0'; isdigit(ch = getchar()); x = x * 10 + ch - '0');
}

struct Node {
    Node *lc, *rc;
    int val, tag;
    Node() : lc(NULL), rc(NULL), val(0), tag(0) {}
    Node(Node *l, Node *r) : lc(l), rc(r), val(0), tag(0) {}
    void maintain() {
        val = max(lc->val, rc->val);
    }
    void cover(int w) {
        tag += w, val += w;
    }
    void pushdown() {
        if (tag) {
            lc->cover(tag);
            rc->cover(tag);
            tag = 0;
        }
    }
    void modify(int l, int r, int nl, int nr, int w) {
        if (l <= nl && nr <= r)
            return cover(w);
        pushdown();
        int mid = (nl + nr) >> 1;
        if (l <= mid)
            lc->modify(l, r, nl, mid, w);
        if (r > mid)
            rc->modify(l, r, mid + 1, nr, w);
        maintain();
    }
} tpool[N << 1], *tcur = tpool, *segt;

Node *build(int l, int r) {
    if (l == r)
        return new (++tcur) Node();
    int mid = (l + r) >> 1;
    return new (++tcur) Node(build(l, mid), build(mid + 1, r));
}

struct Invt {
    int l, r;
    long long len;
    bool operator < (const Invt rhs) const {
        return len < rhs.len;
    }
} t[N];

int cnt, tot, b[N];

int main() {
    freopen("P1712.in", "r", stdin);
    int n, m;
    read(n), read(m);
    rep (i, 1, n) {
        read(t[i].l), read(t[i].r);
        b[++cnt] = t[i].l, b[++cnt] = t[i].r;
    }
    sort(b + 1, b + cnt + 1);
    tot = unique(b + 1, b + cnt + 1) - b - 1;
    rep (i, 1, n) {
        t[i].len = t[i].r - t[i].l;
        t[i].l = lower_bound(b + 1, b + tot + 1, t[i].l) - b;
        t[i].r = lower_bound(b + 1, b + tot + 1, t[i].r) - b;
    }
    segt = build(1, tot);
    sort(t + 1, t + n + 1);
    int l = 0, r = 0;
    long long ans = INT_MAX;
    while (true) {
        while (segt->val < m && r < n)
            ++r, segt->modify(t[r].l, t[r].r, 1, tot, 1);
        if (segt->val < m) break;
        while (segt->val >= m && l < n)
            ++l, segt->modify(t[l].l, t[l].r, 1, tot, -1);
        ans = min(t[r].len - t[l].len, ans);
    }
    if (ans == INT_MAX) puts("-1");
    else printf("%lld\n", ans);
}
