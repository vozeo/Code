#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

const int N = 2e5 + 5, M = 1e6 + 5;
int stk1[N], stk2[N], num[M];
int n, k, Mxr, Sum, Top, Ans;

struct Node {
    int siz, dis, d;
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

void getdis(Node *u, Node *fa, int d1, int d2) {
    if (d1 > k)
        return;
    stk1[++Top] = d1, stk2[Top] = d2;
    for (Edge *e = u->head; e; e = e->nxt) {
        if (e->v->vis || e->v == fa)
            continue;
        getdis(e->v, u, d1 + e->w, d2 + 1);
    }
}

void calc(Node *u) {
    Top = num[0] = 0;
    for (Edge *e = u->head; e; e = e->nxt) {
        if (e->v->vis)
            continue;
        int p = Top;
        getdis(e->v, u, e->w, 1);
        rep (i, p + 1, Top)
            Ans = min(Ans, num[k - stk1[i]] + stk2[i]);
        rep (i, p + 1, Top)
            num[stk1[i]] = min(num[stk1[i]], stk2[i]);
    }
    rep (i, 1, Top)
        num[stk1[i]] = 0x3f3f3f3f;
}

void dfs(Node *u) {
    u->vis = true;
    Node *v;
    calc(u);
    for (Edge *e = u->head; e; e = e->nxt) {
        if ((v = e->v)->vis)
            continue;
        Mxr = n, Sum = v->siz; 
        getrt(v, u);
        dfs(Root);
    }
}

template<typename T>
void read(T &x) {
    char ch = 0;
    while (!isdigit(ch = getchar()));
    for (x = ch - '0'; isdigit(ch = getchar()); x = x * 10 + ch - '0');
}

int main() {
    freopen("P4149.in", "r", stdin);
    read(n), read(k);
    int x, y, z;
    rep (i, 1, n - 1) {
        read(x), read(y), read(z);
        add(x + 1, y + 1, z), add(y + 1, x + 1, z);
    }
    Mxr = n, Sum = n, Ans = INT_MAX;
    getrt(g + 1, g + 1);
    memset(num, 0x3f, sizeof num);
    dfs(Root);
    printf("%d\n", Ans >= n ? -1 : Ans);
}
