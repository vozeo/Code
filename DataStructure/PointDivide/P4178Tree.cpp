#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

const int N = 4e4 + 5;
int Num, Mxr, Sum, Top, Ans, k, n;
int stk[N];

struct Node {
    int siz;
    bool vis;
    Node *fa;
    struct Edge *head;
} *Root, g[N];

struct Edge {
    Node *v;
    int w;
    Edge *nxt;
    Edge() {}
    Edge(Node *x, Node *y, int z) : v(y), w(z), nxt(x->head) {
        x->head = this;
    }
} epool[N << 1], *ecur = epool;

void add(int x, int y, int z) {
    new (++ecur) Edge(g + x, g + y, z);
    new (++ecur) Edge(g + y, g + x, z);
}

void getrt(Node *u, Node *fa) {
    u->siz = 1;
    int mp = 0;
    Node *v;
    for (Edge *e = u->head; e; e = e->nxt) {
        if ((v = e->v) == fa || v->vis)
            continue;
        getrt(v, u);
        u->siz += v->siz;
        mp = max(mp, v->siz);
    }
    mp = max(mp, Sum - u->siz);
    if (mp < Mxr)
        Mxr = mp, Root = u;
}

void getdis(Node *u, Node *fa, int d) {
    stk[++Top] = d;
    for (Edge *e = u->head; e; e = e->nxt) {
        if (e->v == fa || e->v->vis)
            continue;
        getdis(e->v, u, d + e->w);
    }
}

int calc(Node *u, int d) {
    Top = 0;
    int l, r, res = 0;
    getdis(u, u, d);
    sort(stk + 1, stk + Top + 1);
    l = 0, r = Top;
    while (l < r) {
        ++l;
        while (stk[r] + stk[l] > k && l < r) --r;
        res += r - l;
    }
    return res;
}

void dfs(Node *u) {
    u->vis = true;
    Node *v;
    Ans += calc(u, 0);
    for (Edge *e = u->head; e; e = e->nxt) {
        if ((v = e->v)->vis)
            continue;
        Ans -= calc(v, e->w);
        Mxr = n, Sum = v->siz; // ***
        getrt(v, u);
        dfs(Root);
    }
}

int main() {
    freopen("P4178.in", "r", stdin);
    int x, y, z;
    scanf("%d", &n);
    rep (i, 2, n)
        scanf("%d%d%d", &x, &y, &z), add(x, y, z);
    scanf("%d", &k);
    Mxr = Sum = n;
    getrt(g + 1, g + 1);
    dfs(Root);
    printf("%d\n", Ans);
}
