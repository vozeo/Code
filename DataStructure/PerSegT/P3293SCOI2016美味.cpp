#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define per(i_, s_, t_) for (int i_ = (s_); i_ >= (t_); --i_)

const int N = 8e5 + 5;

template<typename T>
void read(T &x) {
    char ch;
    while (!isdigit(ch = getchar()));
    for (x = ch - '0'; isdigit(ch = getchar()); x = x * 10 + ch - '0');
}

struct Node {
    Node *lc, *rc;
    int v;
    Node() {}
    Node(Node *l, Node *r) : lc(l), rc(r) {}
    Node(Node *p) { *this = *p; }

} tpool[N * 30], *tcur = tpool, *root[N];

Node *build(int l, int r) {
    if (l == r) return new (++tcur) Node();
    int mid = (l + r) >> 1;
    return new (++tcur) Node(build(l, mid), build(mid + 1, r));
}

void modify(Node *p, Node *&o, int l, int r, int x) {
    o = new (++tcur) Node(p), ++o->v;
    if (l == r) return;
    int mid = (l + r) >> 1;
    if (x <= mid) modify(p->lc, o->lc, l, mid, x);
    else modify(p->rc, o->rc, mid + 1, r, x);
}

int query(Node *p, Node *o, int l, int r, int nl, int nr) {
    if (l <= nl && nr <= r) return o->v - p->v;
    if (l > nr || nl > r) return 0;
    int mid = (nl + nr) >> 1;
    return query(p->lc, o->lc, l, r, nl, mid) + query(p->rc, o->rc, l, r, mid + 1, nr);
}

int a[N];

int main() {
    freopen("1.in", "r", stdin);
    int n, m, tot = 0, b, x, l, r, v, ql, qr, ans, p;
    read(n), read(m);
    tot = 100000, root[0] = build(1, tot);
    rep (i, 1, n)
        read(a[i]), modify(root[i - 1], root[i], 1, tot, a[i]);
    while (m--) {
        read(b), read(x), read(l), read(r);
        ans = p = 0;
        per (i, 17, 0) {
            v = !((b >> i) & 1);
            ql = max(0, p + (v << i) - x);
            qr = min(tot - 1, p + (v << i) + (1 << i) - 1 - x);
            if (query(root[l - 1], root[r], ql, qr, 1, tot))
                ans += 1 << i, p += v << i;
            else p += (v ^ 1) << i;
        }
        printf("%d\n", ans);
    }
}

