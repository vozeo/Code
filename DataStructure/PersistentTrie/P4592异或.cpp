#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define per(i_, s_, t_) for (int i_ = (s_); i_ >= (t_); --i_)

const int N = 2e5 + 5, W = 30;
int Num, fa[N][20], dep[N], siz[N], dfn[N];

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
    Node *ch[2];
    int v;
    Node() {}
    Node(Node *p) {
        if (p) *this = *p;
    }
} tpool[N * 30], *tcur = tpool, *rt[N];

int val(Node *o) {
    return o ? o->v : 0;
}

void insert(Node *&o, int x, int d = W) {
    o = new (++tcur) Node(o), ++o->v;
    if (d < 0) return;
    insert(o->ch[(x >> d) & 1], x, d - 1);
}

int query1(Node *a, Node *b, int x, int d = W) {
    if (d < 0) return 0;
    if (!a || !b) return x & ((1 << d) - 1);
    int c = (x >> 1) & 1, s = val(b->ch[c ^ 1]) - val(a->ch[c ^ 1]);
    if (s) return query1(a->ch[c ^ 1], b->ch[c ^ 1], x, d - 1) + (1 << d);
    else return query1(a->ch[c], b->ch[c], x, d - 1);
}

int query2(Node *a, Node *b, Node *c, Node *d, int x, int t = W) {
    if (t < 0) return 0;
    if (!a || !b || !c || !d) return x & ((1 << t) - 1);
    int w = (x >> 1) & 1, s = val(a->ch[w ^ 1]) + val(b->ch[w ^ 1]) - val(c->ch[w ^ 1]) - val(d->ch[w ^ 1]);
    if (s) return query2(a->ch[w ^ 1], b->ch[w ^ 1], c->ch[w ^ 1], d->ch[w ^ 1], x, t - 1) + (1 << t);
    else return query2(a->ch[w], b->ch[w], c->ch[w], d->ch[w], x, t - 1);
}

int a[N];

void dfs(int x, int f) {
    per (i, 18, 1)
        fa[x][i] = fa[fa[x][i - 1]][i - 1];
    dfn[x] = ++Num, siz[x] = 1;
    insert(rt[dfn[x]] = rt[dfn[fa[x][0]]], a[x]);
    for (Edge *e = head[x]; e; e = e->nxt)
        if (e->v != f) {
            fa[e->v][0] = x, dep[e->v] = dep[x] + 1;
            dfs(e->v, x), siz[x] += siz[e->v];
        }
}

int lca(int x, int y) {
    if (dep[x] < dep[y])
        swap(x, y);
    per (i, 18, 0)
        if (dep[fa[x][i]] >= dep[y])
            x = fa[x][i];
    if (x == y) return x;
    per (i, 18, 0)
        if (fa[x][i] != fa[y][i])
            x = fa[x][i], y = fa[y][i];
    return fa[x][0];
}

int main() {
    freopen("P4592.in", "r", stdin);
    int n, m, op, x, y, z;
    read(n), read(m);
    rep (i, 1, n)
        read(a[i]);
    rep (i, 2, n)
        read(x), read(y), add(x, y);
    insert(rt[0], 0);
    dfs(1, 1);
    rep (i, 1, m) {
        read(op), read(x), read(y);
        if (op == 1)
            printf("%d\n", query1(rt[dfn[x]], rt[dfn[x] + siz[x] - 1], y));
        else read(z), printf("%d\n", query2(rt[dfn[x]], rt[dfn[y]], rt[dfn[lca(x, y)]], rt[dfn[fa[lca(x, y)][0]]], z));
    }
    rep (i, 1, n)
        cout << rt[dfn[i]] << endl;
}
