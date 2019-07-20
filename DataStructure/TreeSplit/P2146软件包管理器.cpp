#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

const int N = 1e5 + 5;
int n, Ret, Num;

struct Edge {
    struct Node *v;
    Edge *nxt;
    Edge() {}
    Edge(Edge *&x, Node *y) : v(y), nxt(x) {
        x = this;
    }
} epool[N << 1], *ecur = epool;

struct Node {
    Edge *head;
    int dfn, dep, siz;
    Node *fa, *son, *top;
    void dfs1() {
        siz = 1;
        Node *v;
        for (Edge *e = head; e; e = e->nxt)
            if ((v = e->v) != fa) { // ***
                v->dep = dep + 1;
                v->fa = this;
                v->dfs1();
                siz += v->siz;
                if (!son || v->siz > son->siz)
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
} g[N], *Root;

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
        sum = len * x;
        tag = x;
    }

    void pushdown() {
        if (tag != -1) {
            lc->cover(tag);
            rc->cover(tag);
            tag = -1;
        }
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
} *segt, tpool[N << 1], *tcur = tpool;

SegT *build(int l, int r) {
    if (l == r)
        return new (++tcur) SegT(0);
    int mid = (l + r) >> 1;
    return new (++tcur) SegT(build(l, mid), build(mid + 1, r), r - l + 1);
}

int ins(Node *x) {
    int ans = 0;
    while (x) {
        Ret = 0;
        segt->query(x->top->dfn, x->dfn, 1, n);
        ans += Ret;
        segt->modify(x->top->dfn, x->dfn, 1, n, 1);
        x = x->top->fa;
    }
    return ans;
}

int unins(Node *x) {
    Ret = 0;
    segt->query(x->dfn, x->dfn + x->siz - 1, 1, n);
    segt->modify(x->dfn, x->dfn + x->siz - 1, 1, n, 0);
    return Ret;
}

int read() {
    int x;
    char ch = 0;
    while (!isdigit(ch = getchar()));
    for (x = ch - '0'; isdigit(ch = getchar()); x = x * 10 + ch - '0');
    return x;
}

void init() {
    Root = g + 1;
    Root->dep = 1;
    Root->dfs1();
    Root->dfs2();
    segt = build(1, n);
}

int main() {
    freopen("P2146.in", "r", stdin);
    int x, q;
    char s[15];
    n = read();
    rep (i, 2, n)
        add(g + i, g + read() + 1);
    init();
    q = read();
    rep (i, 1, q) {
        scanf("%s", s);
        x = read() + 1;
        if (s[0] == 'i') {
            printf("%d\n", g[x].dep - ins(g + x));
        }
        else printf("%d\n", unins(g + x));
    }
}
