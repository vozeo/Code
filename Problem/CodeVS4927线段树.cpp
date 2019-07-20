#include <climits>
#include <cstdio>
#include <iostream>
using namespace std;

typedef long long ll;
const int N = 100005;
const long long INF = LLONG_MAX;
ll a[N];

struct Node {
    Node *lc, *rc;
    ll sum, mx, mn, atag, stag;

    Node() {}
    Node(int pos, ll val) : lc(NULL), rc(NULL), sum(val), mx(val), mn(val), atag(0), stag(-INF) {}
    Node(Node *lc, Node *rc) : lc(lc), rc(rc), atag(0), stag(-INF) {
        maintain();
    }

    inline void maintain() {
        sum = lc->sum + rc->sum;
        mx = max(lc->mx, rc->mx);
        mn = min(lc->mn, rc->mn);
    }

    void tagadd(int l, int r, ll d) {
        sum += (r - l + 1) * d;
        mx += d;
        mn += d;
        atag += d;
    }

    void tagset(int l, int r, ll d) {
        sum = (r - l + 1) * d;
        mx = mn = stag = d;
        atag = 0;
    }

    void pushdown(int l, int r) {
        int mid = (l + r) >> 1;
        if (stag != -INF) {
            lc->tagset(l, mid, stag);
            rc->tagset(mid + 1, r, stag);
            stag = -INF;
        }
        if (atag) {
            lc->tagadd(l, mid, atag);
            rc->tagadd(mid + 1, r, atag);
            atag = 0;
        }
    }

    void modify(int s, int l, int r, int nl, int nr, ll d) {
        if (nr < l || r < nl)
            return;
        if (l <= nl && nr <= r) {
            if (s == 1)
                tagadd(nl, nr, d);
            else
                tagset(nl, nr, d);
            return;
        }
        pushdown(nl, nr);
        int mid = (nl + nr) >> 1;
        lc->modify(s, l, r, nl, mid, d);
        rc->modify(s, l, r, mid + 1, nr, d);
        maintain();
    }

    ll query(int s, int l, int r, int nl, int nr) {
        if (nr < l || r < nl)
            return s == 1 ? 0 : (s == 2 ? -INF : INF);
        if (l <= nl && nr <= r)
            return s == 1 ? sum : (s == 2 ? mx : mn);
        pushdown(nl, nr);
        int mid = (nl + nr) >> 1;
        if (s == 1)
            return lc->query(s, l, r, nl, mid) + rc->query(s, l, r, mid + 1, nr);
        else if (s == 2)
            return max(lc->query(s, l, r, nl, mid), rc->query(s, l, r, mid + 1, nr));
        else
            return min(lc->query(s, l, r, nl, mid), rc->query(s, l, r, mid + 1, nr));
    }
} *root = NULL, tpool[N << 1], *tcur = tpool;

Node *build(int l, int r) {
    if (l == r)
        return new (tcur++) Node(l, a[l]);
    int mid = (l + r) >> 1;
    return new (tcur++) Node(build(l, mid), build(mid + 1, r));
}

int main() {
    freopen("data.in", "r", stdin);
    freopen("seg.out", "w", stdout);
    int n, m, x, y;
    string p;
    ll d;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        scanf("%lld", &a[i]);
    root = build(1, n);
    for (int i = 1; i <= m; ++i) {
        cin >> p;
        scanf("%d%d", &x, &y);
        if (p == "add") {
            scanf("%lld", &d);
            root->modify(1, x, y, 1, n, d);
        } else if (p == "set") {
            scanf("%lld", &d);
            root->modify(2, x, y, 1, n, d);
        } else if (p == "sum")
            printf("%lld\n", root->query(1, x, y, 1, n));
        else if (p == "max")
            printf("%lld\n", root->query(2, x, y, 1, n));
        else
            printf("%lld\n", root->query(3, x, y, 1, n));
    }
    return 0;
}