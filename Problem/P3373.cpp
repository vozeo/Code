#include <iostream>
#include <cstdio>
typedef long long ll;
const int N = 100005;
int n, m;
ll MOD, a[N];

struct Node {
    int l, r;
    Node *lc, *rc;
    ll sum, k, b;
    Node() {}
    Node(int pos, ll val) : l(pos), r(pos), lc(NULL), rc(NULL), sum(val), k(1), b(0) {}
    Node(Node *lc, Node *rc) : l(lc->l), r(rc->r), lc(lc), rc(rc), k(1), b(0) {
        sum = (lc->sum + rc->sum) % MOD;
    }

    void addk(ll d) {
        sum = sum * d % MOD;
        k = k * d % MOD;
        b = b * d % MOD;
    }

    void addb(ll d) {
        sum = (sum + (r - l + 1) * d) % MOD;
        b = (b + d) % MOD;
    }

    void pushdown() {
        if (k != 1) {
            lc->addk(k);
            rc->addk(k);
            k = 1;
        }
        if (b) {
            lc->addb(b);
            rc->addb(b);
            b = 0;
        }
    }

    void modify(int s, int l, int r, ll d) {
        if (r < this->l || this->r < l)
            return;
        if (this->l != this->r)
            pushdown();
        if (l <= this->l && this->r <= r) {
            if (s == 1)
                addk(d);
            else
                addb(d);
            return;
        }
        lc->modify(s, l, r, d);
        rc->modify(s, l, r, d);
        sum = (lc->sum + rc->sum) % MOD;
    }

    ll query(int l, int r) {
        if (r < this->l || this->r < l)
            return 0;
        if (this->l != this->r)
            pushdown();
        if (l <= this->l && this->r <= r)
            return sum;
        return (lc->query(l, r) + rc->query(l, r)) % MOD;
    }
} *root, tpool[N << 1], *tcur = tpool;

Node *build(int l, int r) {
    if (l == r)
        return new (tcur++) Node(l, a[l]);
    int mid = (l + r) >> 1;
    return new (tcur++) Node(build(l, mid), build(mid + 1, r));
}

int main() {
    scanf("%d%d%lld", &n, &m, &MOD);
    for (int i = 1; i <= n; ++i)
        scanf("%lld", &a[i]);
    root = build(1, n);
    int p, x, y;
    ll d;
    for (int i = 1; i <= m; ++i) {
        scanf("%d%d%d", &p, &x, &y);
        if (p == 3)
            printf("%lld\n", root->query(x, y));
        else {
            scanf("%lld", &d);
            root->modify(p, x, y, d);
        }
    }
    return 0;
}