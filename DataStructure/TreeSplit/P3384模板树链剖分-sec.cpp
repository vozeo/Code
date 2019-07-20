#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

const int N = 1e5 + 5, M = 1e5 + 5;
struct Node;
struct Edge;
int ret, num, n, m, P;
int s[N], a[N];

struct Node {
    Edge *e;
    Node *top, *son, *fa;
    int dfn, dep, siz, val;
} g[N];

struct Edge {
    Node *u, *v;
    Edge *nxt;
    Edge() {}
    Edge(Node *x, Node *y) : u(x), v(y), nxt(x->e) {}
} epool[M << 1], *ecur = epool;

void dfs1(Node *u) {
    u->siz = 1;
    Node *v;
    for (Edge *e = u->e; e; e = e->nxt)
        if ((v = e->v) != u->fa) {
            v->dep = u->dep + 1;
            v->fa = u;
            dfs1(v);
            u->siz += v->siz;
            if (!u->son || u->son->siz < v->siz)
                u->son = v;
        }
}

void dfs2(Node *u) {
    u->dfn = ++num;
    if (!u->fa || u->fa->son != u)
        u->top = u;
    else u->top = u->fa->top;
    if (u->son) dfs2(u->son);
    for (Edge *e = u->e; e; e = e->nxt)
        if (e->v != u->fa && e->v != u->son)
            dfs2(e->v);
}

void add(int x, int y) {
    g[x].e = new (++ecur) Edge(&g[x], &g[y]);
    g[y].e = new (++ecur) Edge(&g[y], &g[x]);
}

struct SegT {
    int sum, tag, len;
    SegT *lc, *rc;
    SegT() {}
    SegT(int v) : sum(v), len(1), lc(NULL), rc(NULL) {}
    SegT(SegT *l, SegT *r, int p) : len(p), lc(l), rc(r) {
        maintain();
    }

    void maintain() {
        sum = (lc->sum + rc->sum) % P;
    }

    void add(int v) {
        sum = (sum + v * len) % P;
        tag = (tag + v) % P;
    }

    void pushdown() {
        if (tag) {
            lc->add(tag);
            rc->add(tag);
            tag = 0;
        }
    }

    void modify(int l, int r, int nl, int nr, int v) {
        if (l <= nl && nr <= r)
            return add(v);
        pushdown();
        int mid = (nl + nr) >> 1;
        if (l <= mid)
            lc->modify(l, r, nl, mid, v);
        if (r > mid)
            rc->modify(l, r, mid + 1, nr, v);
        maintain();
    }

    void query(int l, int r, int nl, int nr) {
        if (l <= nl && nr <= r) {
            ret = (ret + sum) % P;
            return;
        }
        pushdown();
        int mid = (nl + nr) >> 1;
        if (l <= mid)
            lc->query(l, r, nl, mid);
        if (r > mid)
            rc->query(l, r, mid + 1, nr);
    }
} *segt, tpool[N << 1], *tcur = tpool;

SegT *build(int l, int r) {
    if (l == r)
        return new (++tcur) SegT(a[l]);
    int mid = (l + r) >> 1;
    return new (++tcur) SegT(build(l, mid), build(mid + 1, r), r - l + 1);
}

void modifyR(int l, int r, int w) {
    Node *x = &g[l], *y = &g[r];
    while (x->top != y->top) {
        if (x->top->dep < y->top->dep)
            swap(x, y);
        segt->modify(x->top->dfn, x->dfn, 1, n, w);
        x = x->top->fa;
    }
    if (x->dep > y->dep)
        swap(x, y);
    segt->modify(x->dfn, y->dfn, 1, n, w);
}

int queryR(int l, int r) {
    int ans = 0;
    Node *x = &g[l], *y = &g[r];
    while (x->top != y->top) {
        if (x->top->dep < y->top->dep)
            swap(x, y);
        ret = 0;
        segt->query(x->top->dfn, x->dfn, 1, n);
        ans = (ans + ret) % P;
        x = x->top->fa;
    }
    if (x->dep > y->dep)
        swap(x, y);
    ret = 0;
    segt->query(x->dfn, y->dfn, 1, n);
    return (ans + ret) % P;
}

void modifyS(int p, int w) {
    Node *x = &g[p];
    segt->modify(x->dfn, x->dfn + x->siz - 1, 1, n, w);
}

void queryS(int p) {
    Node *x = &g[p];
    ret = 0;
    segt->query(x->dfn, x->dfn + x->siz - 1, 1, n);
}

char buf[1 << 21], *p1 = buf, *p2 = buf;
#define getc() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++)

template<typename T>
void read(T &x) {
    char ch;
    while (!isdigit(ch = getchar()));
    for (x = ch - '0'; isdigit(ch = getchar()); x = x * 10 + ch - '0');
}

int main() {
    freopen("P3384.in", "r", stdin);
    int root;
    read(n), read(m), read(root), read(P);
    int op, x, y, z;
    rep (i, 1, n)
        read(g[i].val);
    rep (i, 1, n - 1)
        read(x), read(y), add(x, y);
    g[root].dep = 1;
    dfs1(&g[root]), dfs2(&g[root]);
    rep (i, 1, n)
        a[g[i].dfn] = g[i].val;
    segt = build(1, n);
    rep (i, 1, m) {
        read(op), read(x);
        if (op == 1)
            read(y), read(z), modifyR(x, y, z);
        else if (op == 2) {
            read(y), ret = 0;
            printf("%d\n", queryR(x, y));
        } else if (op == 3)
            read(z), modifyS(x, z);
        else if (op == 4) {
            ret = 0;
            queryS(x);
            printf("%d\n", ret);
        }
    }
}
