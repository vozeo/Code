#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define per(i_, s_, t_) for (int i_ = (s_); i_ >= (t_); --i_)

typedef long long ll;
const int N = 1e5 + 5;
int fa[N][18], dep[N];
int s, n, m;

template<typename T>
void read(T &x) {
    char ch;
    while (!isdigit(ch = getchar()));
    for (x = ch - '0'; isdigit(ch = getchar()); x = x * 10 + ch - '0');
}

struct Edge *head[N];
struct Edge {
    int v;
    Edge *nxt;
    Edge() {}
    Edge(int x, int y) : v(y), nxt(head[x]) {
        head[x] = this;
    }
} epool[N << 1], *ecur = epool;

void add(int x, int y) {
    new (++ecur) Edge(x, y);
    new (++ecur) Edge(y, x);
}

struct Node {
    Node *lc, *rc;
    int v;
    Node() {}
    Node(Node *p) { *this = *p; };
    Node(Node *l, Node *r) : lc(l), rc(r) {}

    void dfs(int l, int r) {
        if (l == r) {
            if (v) cout << v << " ";
            return;
        }
        int mid = (l + r) >> 1;
        lc->dfs(l, mid), rc->dfs(mid + 1, r);
    }
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

int query(Node *a, Node *b, Node *c, Node *d, int l, int r, int k) {
    if (l == r) return l;
    int mid = (l + r) >> 1, val = a->lc->v + b->lc->v - c->lc->v - d->lc->v;
    if (k <= val)
        return query(a->lc, b->lc, c->lc, d->lc, l, mid, k);
    else return query(a->rc, b->rc, c->rc, d->rc, mid + 1, r, k - val);
}

int a[N], b[N];

void dfs(int u, int f) {
    modify(root[f], root[u], 1, n, a[u]);
    fa[u][0] = f, dep[u] = dep[f] + 1;
    rep (i, 1, 17) {
        fa[u][i] = fa[fa[u][i - 1]][i - 1];
        if (!fa[u][i]) break;
    }
    for (Edge *e = head[u]; e; e = e->nxt)
        if (e->v != f)
            dfs(e->v, u);
}

int lca(int x, int y) {
    if (dep[x] < dep[y])
        swap(x, y);
    per (i, 17, 0)
        if (dep[fa[x][i]] >= dep[y])
            x = fa[x][i];
    if (x == y) return x;
    per (i, 17, 0)
        if (fa[x][i] != fa[y][i])
            x = fa[x][i], y = fa[y][i];
    return fa[x][0];
}

int main() {
    freopen("P2633-1.in", "r", stdin);
    freopen("P.out", "w", stdout);
    read(s), read(m);
    rep (i, 1, s)
        read(a[i]), b[i] = a[i];
    sort(b + 1, b + s + 1);
    n = unique(b + 1, b + s + 1) - b - 1;
    rep (i, 1, s)
        a[i] = lower_bound(b + 1, b + n + 1, a[i]) - b;
    int x, y, k, p, las = 0;
    rep (i, 2, s)
        read(x), read(y), add(x, y);
    root[0] = build(1, n), dfs(1, 0);
    rep (i, 1, m) {
        read(x), read(y), read(k); 
        x ^= las, p = lca(x, y);
        printf("%d\n", las = b[query(root[x], root[y], root[p], root[fa[p][0]], 1, n, k)]);
    }
}
