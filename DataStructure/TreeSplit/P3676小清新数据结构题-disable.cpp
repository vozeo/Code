#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

const int N = 2e5 + 5;

struct Edge {
    struct Node *v;
    Edge *nxt;
    Edge() {}
    Edge(Edge *&p, Node *y) : v(y), nxt(p) {
        p = this;
    }
};

struct Node {
    Edge *head;
    Node *fa, *son, *top;
    int dep, dfn, siz, sum, pw;
    void dfs1() {
        siz = 1;
        Node *v;
        for (Edge *e = head; e; e = e->nxt)
            if ((v = e->v) != fa) {
                v->fa = this, v->dep = dep + 1;
                v->dfs1();
                siz += v->siz, sum += v->sum, pw += v->pw;
                if (!son || son->siz < v->siz)
                    son = v;
            }
        pw += sum * sum;
    }
    void dfs2() {
        dfn = ++Num;
        if (!fa || fa->son != this)
            top = this;
        if (son) son->dfs2();
        for (Edge *e = head; e; e = e->nxt)
            if (e->v != fa && e->v != son)
                e->v->dfs2();
    }
} g[N];

struct Tree {
    Tree *lc, *rc;
    int sum, tag, len;
    Tree() {}
    Tree(Tree *l, Tree *r, int x) : lc(l), rc(r), len(x) {
        maintain();
    }
    Tree(int x) : sum(x) {}

    void maintain() {
        sum = lc->sum + rc->sum;
    }

    void cover(ll x) {
        sum += x, tag += x * len;
    }

    void pushdown() {
        if (tag) {
            lc->cover(tag);
            rc->cover(tag);
            tag = 0;
        }
    }

    void modify(int l, int r, int nl, int nr, int x) {
        if (l <= nl && nr <= r)
            return cover(x);
        int mid = (nl + nr) >> 1;
        pushdown();
        if (l <= mid)
            modify(l, r, nl, mid, x);
        if (r > mid)
            modify(l, r, mid + 1, nr, x);
         maintain();
    }

    void query(int l, int r, int nl, int nr) {
        if (l <= nl && nr <= r) {
            Ret += x;
            return;
        }
        int mid = (nl + nr) >> 1;
        pushdown();
        if (l <= mid)
            query(l, r, nl, mid);
        if (r > mid)
            query(l, r, mid + 1, nr);
    }
} tpool[N << 1], *tcur = tpool, *root = tpool;

Tree *build(int l, int r) {
    if (l == r)
        return Tree(a[b[l]]);
    int mid = (l + r) >> 1;
    return Tree(build(l, mid), build(mid + 1, r), r - l + 1);
}

void modify(Node *x, int w) {
    int cnt = 0;
    while (x != root)
        root->modify(x->top->dfn, x->dfn, 1, n, w);
}

int query(Node *x) {
    int ans = 0;
    while (x) {
        Ret = 0;
        root->query(x->top->dfn, x->dfn, 1, n);
        ans += Ret;
        x = x->top->fa;
    }
    return ans;
}

void upd(Node *x, int w) {
    Ans += 1ll * w * w * x->dep + 2 * w * query(x);
    modify(x, w);
}

int qry(Node *x) {
    Ans += S * (x->dep * S - (query(x) << 1));
}

void init() {
    root->dfs1(), root->dfs2();
}

int main() {
    read(n), read(m);
    rep (i, 2, n)
        read(x), read(y), add(g + x, g + y);
    init();
    rep (i, 1, n)
        read(a[i]);
    rep (i, 1, m) {
        read(op), read(x);
        if (op == 1)
            read(y), upd(g + x, y);
        else printf("%lld\n", qry(g + x));
    }
}
