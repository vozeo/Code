#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

const int N = 3e4 + 5;
int Num, Ret, Mxr;

struct Node;
struct Edge {
    Node *v;
    Edge *nxt;
    Edge() {}
    Edge(Edge *&p, Node *y) : v(y), nxt(p) {
        p = this;
    }
} epool[N << 1], *ecur = epool;

struct Node {
    Edge *head;
    int dfn, siz, dep;
    Node *top, *fa, *son;
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
} g[N], *Root;

void add(Node *x, Node *y) {
    new (++ecur) Edge(x->head, y);
    new (++ecur) Edge(y->head, x);
}

struct SegT {
    SegT *lc, *rc;
    int mx, sum, len;
    SegT() {}
    SegT(SegT *l, SegT *r, int w) : lc(l), rc(r), len(w) {
        maintain();
    }
    SegT(int p) : mx(p), sum(p), len(1) {}
    void maintain() {
        mx = max(lc->mx, rc->mx);
        sum = lc->sum + rc->sum;
    }
    void modify(int p, int nl, int nr, int w) {
        if (nl == nr) {
            mx = sum = w;
            return;
        }
        int mid = (nl + nr) >> 1;
        if (p <= mid)
            lc->modify(p, nl, mid, w);
        else rc->modify(p, mid + 1, nr, w);
        maintain();
    }
    void query(int l, int r, int nl, int nr) {
        if (l <= nl && nr <= r) {
            Ret += sum, Mxr = max(Mxr, mx);
            return;
        }
        int mid = (nl + nr) >> 1;
        if (l <= mid)
            lc->query(l, r, nl, mid);
        if (r > mid)
            rc->query(l, r, mid + 1, nr);
    }
} tpool[N << 1], *tcur = tpool, *segt;

int a[N], f[N], n, Q;

SegT *build(int l, int r) {
    if (l == r)
        return new (++tcur) SegT(a[l]);
    int mid = (l + r) >> 1;
    return new (++tcur) SegT(build(l, mid), build(mid + 1, r), r - l + 1);
}

void modify(Node *x, int w) {
    segt->modify(x->dfn, 1, n, w);
}

int querySum(Node *x, Node *y) {
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
    ans += Ret;
    return ans;
}

int queryMx(Node *x, Node *y) {
    int ans = INT_MIN;
    while (x->top != y->top) {
        if (x->top->dep < y->top->dep)
            swap(x, y);
        Mxr = INT_MIN;
        segt->query(x->top->dfn, x->dfn, 1, n);
        ans = max(ans, Mxr);
        x = x->top->fa;
    }
    if (x->dep > y->dep)
        swap(x, y);
    Mxr = INT_MIN;
    segt->query(x->dfn, y->dfn, 1, n);
    ans = max(ans, Mxr);
    return ans;
}

void init() {
    Root = g + 1;
    Root->dep = 1;
    Root->dfs1();
    Root->dfs2();
}

template<typename T>
void read(T &x) {
    char ch = 0;
    int ff = 1;
    while (!isdigit(ch = getchar()))
        if (ch == '-')
            ff = -1;
    for (x = ch - '0'; isdigit(ch = getchar()); x = x * 10 + ch - '0');
    x *= ff;
}

int main() {
    freopen("P2590.in", "r", stdin);
    int x, y;
    read(n);
    rep (i, 2, n)
        read(x), read(y), add(g + x, g + y);
    init();
    rep (i, 1, n)
        read(a[g[i].dfn]);
    segt = build(1, n);
    read(Q);
    char s[10];
    rep (i, 1, Q) {
        scanf("%s", s);
        read(x), read(y);
        if (s[0] == 'C')
            modify(g + x, y);
        else if (s[1] == 'M')
            printf("%d\n", queryMx(g + x, g + y));
        else printf("%d\n", querySum(g + x, g + y));
    }
}
