#include <iostream>
#include <cstdio>
//using namespace std;

typedef long long ll;
const int N = 100005;
int n, m;
ll MOD, a[N];

struct Node {
    //int l, r;
    Node *lc, *rc;
    ll sum, k, b;
    Node() {}
    Node(int pos, ll val) : /*l(pos), r(pos), */lc(NULL), rc(NULL), sum(val), k(1), b(0) {}
    Node(Node *lc, Node *rc) : /*l(lc->l), r(rc->r), */lc(lc), rc(rc), k(1), b(0) {
        sum = (lc->sum + rc->sum) % MOD;
    }

    void addk(ll d) {
        sum = sum * d % MOD;
        k = k * d % MOD;
        b = b * d % MOD;
    }

    void addb(int nl, int nr, ll d) {
        sum = (sum + (nr - nl + 1) * d) % MOD;
        b = (b + d) % MOD;
    }

    void pushdown(int nl, int nr) {
        int mid = (nl + nr) >> 1;
        if (k != 1) {
            lc->addk(k);
            rc->addk(k);
            k = 1;
        }
        if (b) {
            lc->addb(nl, mid, b);
            rc->addb(mid + 1, nr, b);
            b = 0;
        }
    }

    void modify(int s, int l, int r, int nl, int nr, ll d) {
        if (r < nl || nr < l)
            return;
        if (nl != nr)
            pushdown(nl, nr);
        if (l <= nl && nr <= r) {
            if (s == 1)
                addk(d);
            else
                addb(nl, nr , d);
            return;
        }
        int mid = (nl + nr) >> 1;
        //lc->modify(s, l, mid, d);
        //rc->modify(s, mid + 1, r, d);
        //pushdown();
        lc->modify(s, l, r, nl, mid, d);
        rc->modify(s, l, r, mid + 1, nr, d);
        sum = (lc->sum + rc->sum) % MOD;
    }

    ll query(int l, int r, int nl, int nr) {
        if (r < nl || nr < l)
            return 0;
        if (nl != nr)
            pushdown(nl, nr);
        if (l <= nl && nr <= r)
            return sum;
        int mid = (nl + nr) >> 1;
        //return lc->query(l, mid) + rc->query(mid + 1, r);
        //pushdown();
        return (lc->query(l, r, nl, mid) + rc->query(l, r, mid + 1, nr)) % MOD;
    }
} *root, tpool[N << 1], *tcur = tpool;

Node *build(int l, int r) {
    if (l == r)
        return new (tcur++) Node(l, a[l]);
    int mid = (l + r) >> 1;
    return new (tcur++) Node(build(l, mid), build(mid + 1, r));
}

int main() {
    scanf("%d%lld", &n, &MOD);
    for (int i = 1; i <= n; ++i)
        scanf("%lld", &a[i]);
    scanf("%d", &m);
    root = build(1, n);
    int p, x, y;
    ll d;
    for (int i = 1; i <= m; ++i) {
        scanf("%d%d%d", &p, &x, &y);
        if (p == 3)
            printf("%lld\n", root->query(x, y, 1, n));
        else {
            scanf("%lld", &d);
            root->modify(p, x, y, 1, n, d);
        }
    }
    return 0;
}