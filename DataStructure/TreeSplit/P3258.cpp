#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

const int N = 3e5 + 5;
int n, Num, Ret;

struct Edge {
    struct Node *v;
    Edge *nxt;
    Edge() {}
    Edge(Edge *&p, Node *y) : v(y), nxt(p) {
        p = this;
    }
} epool[N << 1], *ecur = epool;

struct Node {
    int dep, dfn, siz;
    Edge *head;
    Node *fa, *son, *top;
    void dfs1() {
        siz = 1;
        Node *v;
        for (Edge *e = head; e; e = e->nxt)
            if ((v = e->v) != fa) {
                v->fa = this;
                v->dep = dep + 1;
                v->dfs1();
                siz += v->siz;
                if (!son || son->siz < v->siz)
                    son = v;
            }
    }
    void dfs2() {
        dfn = ++Num;
        if (!fa || fa->son != this)
            top = this;
        else top = fa->top;
        if (son) son->dfs2();
        for (Edge *e = head; e; e = e->nxt)
            if (e->v != fa && e->v != son)
                e->v->dfs2();
    }
} g[N];

void add(Node *x, Node *y) {
    new (++ecur) Edge(x->head, y);
    new (++ecur) Edge(y->head, x);
}

struct SegT {
    SegT *lc, *rc;
    int sum, tag, len;
    SegT() {}
    SegT(int x) : sum(x), len(1) {}
    SegT(SegT *l, SegT *r, int p) : lc(l), rc(r), len(p) {
        maintain();
    }

    void maintain() {
        sum = lc->sum + rc->sum;
    }

    void cover(int x) {
        sum += x * len;
        tag += x;
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

    void query(int l, int r, int nl, int nr) {
        if (l <= nl && nr <= r) {
            Ret += sum;
            return;
        }
        pushdown();
        int mid = (nl + nr) >> 1;
        if (l <= mid)
            lc->query(l, r, nl, mid);
        if (r > mid)
            rc->query(l, r, mid + 1, nr);
    }
} tpool[N << 1], *tcur = tpool, *segt;

SegT *build(int l, int r) {
    if (l == r)
        return new (++tcur) SegT(0);
    int mid = (l + r) >> 1;
    return new (++tcur) SegT(build(l, mid), build(mid + 1, r), r - l + 1);
}

int query(Node *x, Node *y) {
    int ans = 0;
    while (x->top != y->top) {
        if (x->top->dep < y->top->dep)
            swap(x, y);
        Ret = 0;
        segt->query(x->top->dfn, x->dfn, 1, n);
        ans += Ret;
        x = x->top->fa;
    }
    if (x->dep > y->dep)
        swap(x, y);
    Ret = 0;
    segt->query(x->dfn, y->dfn, 1, n);
    return ans + Ret;
}

void modify(Node *x, Node *y, int w) {
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

void init() {
    Node *Root = g + 1;
    Root->dep = 1;
    Root->dfs1();
    Root->dfs2();
    segt = build(1, n);
}

int a[N];

template<typename T>
void read(T &x) {
    char ch = 0;
    while (!isdigit(ch = getchar()));
    for (x = ch - '0'; isdigit(ch = getchar()); x = x * 10 + ch - '0');
}


int main() {
    freopen("P3258.in", "r", stdin);
    int x, y;
    read(n);
    rep (i, 1, n)
        read(a[i]);
    rep (i, 2, n)
        read(x), read(y),add(g + x, g + y);
    init();
    modify(g + a[1], g + a[1], 1);
    rep (i, 2, n) {
        modify(g + a[i - 1], g + a[i], 1);
        modify(g + a[i - 1], g + a[i - 1], -1);
    }
    modify(g + a[n], g + a[n], -1);
    rep (i, 1, n)
        printf("%d\n", query(g + i, g + i));
}
