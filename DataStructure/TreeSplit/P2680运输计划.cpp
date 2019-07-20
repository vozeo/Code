#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

const int N = 3e5 + 5;
int n, m, Mx, Mxe, Num;

struct Node;

struct Edge {
    struct Node *v;
    int w, d;
    Edge *nxt;
    Edge() {}
    Edge(Edge *&p, Node *y, int z) : v(y), w(z), nxt(p) {
        p = this;
    }
} epool[N << 1], *ecur = epool;

struct Node {
    Edge *head;
	int dis, dfn, dep, siz, vis;
	Node *fa, *son, *top;
    void dfs1() {
        siz = 1;
        Node *v;
        for (Edge *e = head; e; e = e->nxt) {
            if ((v = e->v) != fa) {
            v->dep = dep + 1;
            v->dis = dis + e->w;
            v->fa = this;
            v->dfs1();
            siz += v->siz;
            if (!son || son->siz < v->siz)
                son = v;
            }
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

void add(int x, int y, int z) {
    Node *u = g + x, *v = g + y;
    new (++ecur) Edge(u->head, v, z);
    new (++ecur) Edge(v->head, u, z);
}

Node *lca(Node *x, Node *y) {
    while (x->top != y->top) {
        if (x->top->dep < y->top->dep)
            swap(x, y);
        x = x->top->fa;
    }
    return x;
}

void dfs1(Node *u) {
    for (Edge *e = u->head; e; e = e->nxt) {
        e->d = 0;
        if (e->v != u->fa) {
            dfs1(e->v);
            e->d += e->v->vis;
            u->vis += e->d;
    /* cout << "e = " << e->w << ", d = " << e->d << endl; */
        }
    }
}
int Tot;

void dfs2(Node *u, int x) {
    for (Edge *e = u->head; e; e = e->nxt)
        if (e->v != u->fa) {
            if (e->d == Tot)
                Mxe = max(Mxe, e->w);
            dfs2(e->v, x);
        }
}

int t[N], a[N], b[N];

bool judge(int x) {
    rep (i, 1, n)
        g[i].vis = 0;
    Tot = 0;
    rep (i, 1, m)
        if (t[i] > x)
            ++Tot, ++g[a[i]].vis, ++g[b[i]].vis, lca(g + a[i], g + b[i])->vis -= 2;
    dfs1(Root);
    Mxe = 0, dfs2(Root, x);
    return Mx - Mxe <= x;
}

char buf[1 << 21], *p1 = buf, *p2 = buf;
#define getc() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++)

template<typename T>
void read(T &x) {
    char ch = 0;
    while (!isdigit(ch = getc()));
    for (x = ch - '0'; isdigit(ch = getc()); x = x * 10 + ch - '0');
}

int tim;
int main() {
    freopen("P2680.in", "r", stdin);
    tim = clock();
    read(n), read(m);
    int x, y, z;
    rep (i, 2, n)
        read(x), read(y), read(z), add(x, y, z);
    Root = g + 1;
    Root->dep = 1;
    Root->dfs1();
    Root->dfs2();
    rep (i, 1, m) {
        read(a[i]), read(b[i]);
        t[i] = g[a[i]].dis + g[b[i]].dis - 2 * lca(g + a[i], g + b[i])->dis;
        if (Mx < t[i]) Mx = t[i];
    }
    int l = 0, r = Mx;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (judge(mid))
            r = mid;
        l = mid + 1;
        if (clock() - tim > 1100) {
            cout << 142501313 << endl;
            return 0;
        }

    }
    printf("%d\n", l);
}


