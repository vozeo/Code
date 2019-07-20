#include <cstdio>
#include <iostream>
typedef long long ll;
const int N = 100005;

int n, m;
ll a[N], ret;

struct Node {
    int len;
    Node *lc, *rc;
    ll sum, tag;

    Node() {}
    Node(ll val) : len(1), lc(NULL), rc(NULL), sum(val), tag(0) {}
    Node(Node *lc, Node *rc, int l) : len(l), lc(lc), rc(rc), tag(0) {
        sum = lc->sum + rc->sum;
    }

    void add(ll d) {
        sum += len * d;
        tag += d;
    }

    void pushdown() {
        if (tag) {
            lc->add(tag);
            rc->add(tag);
            tag = 0;
        }
    }

    void modify(int l, int r, int nl, int nr, ll d) {
        if (nr < l || r < nl)
            return;
        if (l <= nl && nr <= r) {
            add(d);
            return;
        }
        pushdown();
        int mid = (nl + nr) >> 1;
        lc->modify(l, r, nl, mid, d);
        rc->modify(l, r, mid + 1, nr, d);
        sum = lc->sum + rc->sum;
    }

    void query(int l, int r, int nl, int nr) {
        if (nr < l || r < nl)
            return;
        if (l <= nl && nr <= r) {
            ret += sum;
            return;
        }
        pushdown();
        int mid = (nl + nr) >> 1;
        lc->query(l, r, nl, mid);
        rc->query(l, r, mid + 1, nr);
    }
} *segt, tpool[N << 1], *tcur = tpool;

Node *build (int l, int r) {
    if (l == r)
        return new(tcur++) Node(a[l]);
    int mid = (l + r) >> 1;
    return new(tcur++) Node(build(l, mid), build(mid + 1, r), r - l + 1);
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        scanf("%lld", &a[i]);
    segt = build(1, n);
    int s, x, y;
    ll k;
    for (int i = 1; i <= m; ++i) {
        scanf("%d%d%d", &s, &x, &y);
        if (s == 1) {
            scanf("%lld", &k);
            segt->modify(x, y, 1, n, k);
        } else {
            ret = 0;
            segt->query(x, y, 1, n);
            printf("%lld\n", ret);
        }
    }
    return 0;
}
