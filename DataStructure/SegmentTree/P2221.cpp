#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

typedef long long ll;
const int N = 2e5 + 5;
ll ans[5];

ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}

struct Node {
    Node *lc, *rc;
    ll sum[6], tag;
    int len;
    Node () {}
    Node (Node *l, Node *r, int p) : lc(l), rc(r), len(p) {
        maintain();
    }
    Node (ll x) : len(1) {
        sum[4] = x, sum[5] = x * x;
    }
    void update() {
        rep (i, 1, 3)
            sum[i] = lc->sum[i] + rc->sum[i];
    }
    void maintain() {
        sum[4] = lc->sum[4] + rc->sum[4];
        sum[5] = lc->sum[5] + rc->sum[5];
    }
    void cover(ll x) {
        sum[1] += x * len;
        sum[2] += x * sum[4];
        sum[3] += x * sum[5];
        tag += x;
    }
    void pushdown() {
        if (tag) {
            lc->cover(tag);
            rc->cover(tag);
            tag = 0;
        }
    }
    void modify(int l, int r, int nl, int nr, ll x) {
        if (l <= nl && nr <= r)
            return cover(x);
        pushdown();
        int mid = (nl + nr) >> 1;
        if (l <= mid) lc->modify(l, r, nl, mid, x);
        if (r > mid) rc->modify(l, r, mid + 1, nr, x);
        update();
    }
    void query(int l, int r, int nl, int nr) {
        if (l <= nl && nr <= r) {
            rep (i, 1, 3)
                ans[i] += sum[i];
            return;
        }
        pushdown();
        int mid = (nl + nr) >> 1;
        if (l <= mid) lc->query(l, r, nl, mid);
        if (r > mid) rc->query(l, r, mid + 1, nr);
    }
} tpool[N << 1], *tcur = tpool, *root;

Node *build(int l, int r) {
    if (l == r) return new (++tcur) Node(l);
    int mid = (l + r) >> 1;
    return new (++tcur) Node(build(l, mid), build(mid + 1, r), r - l + 1);
}

int main() {
    freopen("P2221.in", "r", stdin);
    int n, m;
    char c[3];
    ll a, b, g, l, r, x;
    scanf("%d%d", &n, &m);
    --n;
    root = build(1, n);
    rep (i, 1, m) {
        scanf("%s %lld %lld", c, &l, &r);
        --r;
        if (c[0] == 'C')
            scanf("%lld", &x), root->modify(l, r, 1, n, x);
        else {
            ans[1] = ans[2] = ans[3] = 0;
            root->query(l, r, 1, n);
            a = (r - l + 1 - l * r) * ans[1] + (l + r) * ans[2] - ans[3];
            b = (r - l + 2) * (r - l + 1) / 2;
            g = gcd(a, b);
            printf("%lld/%lld\n", a / g, b / g);
        }
    }
}
