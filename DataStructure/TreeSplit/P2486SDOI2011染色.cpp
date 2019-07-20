#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

const int N = 2e5 + 5, M = 2e5 + 5;
int n, m, Num, c[N], a[N];

template<typename T>
void read(T &x) {
    char ch;
    while (!isdigit(ch = getchar()));
    for (x = ch - '0'; isdigit(ch = getchar()); x = x * 10 + ch - '0');
}

struct Edge {
    struct Node *v;
    Edge *nxt;
    Edge() {}
    Edge(Edge *&p, Node *y) : v(y), nxt(p) {
        p = this;
    }
} epool[N << 1], *ecur = epool;


struct Node {
    Edge *head;
    Node *fa, *son, *top;
    int dep, siz, dfn;
    void dfs1() {
        siz = 1;
        Node *v;
        for (Edge *e = head; e; e = e->nxt)
            if ((v = e->v) != fa) {
                v->dep = dep + 1, v->fa = this;
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
} g[N];

void add(Node *x, Node *y) {
    new (++ecur) Edge(x->head, y);
    new (++ecur) Edge(y->head, x);
}

struct Tree {
    Tree *lc, *rc;
    int vl, vr, v, tag;
    Tree() {}
    Tree(Tree *l, Tree *r) : lc(l), rc(r) {
        maintain();
    }
    Tree(int x) : vl(x), vr(x), v(1), tag(x) {}
    void maintain() {
        vl = lc->vl, vr = rc->vr;
        v = lc->v + rc->v - (lc->vr == rc->vl);
    }

    void cover(int x) {
        tag = vl = vr = x, v = 1;
    }

    void pushdown() {
        if (tag) {
            lc->cover(tag);
            rc->cover(tag);
            tag = 0;
        }
    }

    void modify(int l, int r, int nl, int nr, int x) {
        //cout << nl << " " << nr << endl;
        if (l <= nl && nr <= r)
            return cover(x);
        pushdown();
        int mid = (nl + nr) >> 1;
        if (l <= mid)
            lc->modify(l, r, nl, mid, x);
        if (r > mid)
            rc->modify(l, r, mid + 1, nr, x);
        maintain();
    }

    int query(int l, int r, int nl, int nr) {
        if (l <= nl && nr <= r) return v;
        pushdown();
        int mid = (nl + nr) >> 1, ans = 0;
        if (l <= mid) ans += lc->query(l, r, nl, mid);
        if (r > mid) ans += rc->query(l, r, mid + 1, nr);
        if (l <= mid && r > mid) ans -= lc->vr == rc->vl;
        return ans;
    }

    int qrc(int l, int r, int x) {
        //printf("%d %d %d %d\n", l, r, vl, vr);
        if (l == r) return vr;
        pushdown();
        int mid = (l + r) >> 1;
        if (x <= mid) return lc->qrc(l, mid, x);
        else return rc->qrc(mid + 1, r, x);
    }
} tpool[N << 1], *tcur = tpool, *root = tpool;

Tree *build(int l, int r) {
    if (l == r) return new (++tcur) Tree(c[l]);
    int mid = (l + r) >> 1;
    return new (++tcur) Tree(build(l, mid), build(mid + 1, r));
}

int query(Node *x, Node *y) {
    int ans = 0;
    while (x->top != y->top) {
        if (x->top->dep < y->top->dep) swap(x, y);
        ans += root->query(x->top->dfn, x->dfn, 1, n) - (root->qrc(1, n, x->top->dfn) == root->qrc(1, n, x->top->fa->dfn));
        x = x->top->fa;
    }
    if (x->dep < y->dep) swap(x, y);
    ans += root->query(y->dfn, x->dfn, 1, n);
    return ans;
}

void modify(Node *x, Node *y, int w) {
    while (x->top != y->top) {
        if (x->top->dep < y->top->dep) swap(x, y);
        root->modify(x->top->dfn, x->dfn, 1, n, w);
        x = x->top->fa;
    }
    if (x->dep > y->dep) swap(x, y);
    //cout << x->dfn << " " << y->dfn << endl;
    root->modify(x->dfn, y->dfn, 1, n, w);
}

int main() {
    freopen("P2486.in", "r", stdin);
    int x, y, w;
    char op[3];
    read(n), read(m);
    rep (i, 1, n)
        read(a[i]);
    rep (i, 2, n)
        read(x), read(y), add(g + x, g + y);
    g[1].dep = 1, g[1].dfs1(), g[1].dfs2();
    rep (i, 1, n)
        c[g[i].dfn] = a[i];
    root = build(1, n);
    rep (i, 1, m) {
        scanf("%s", op), read(x), read(y);
        if (op[0] == 'C')
            read(w), modify(g + x, g + y, w);
        else printf("%d\n", query(g + x, g + y));
        //cout << i << endl;
        //root->qrc(1, n, g[1].dfn);
        //cout << endl;
    }
}
