#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define per(i_, s_, t_) for (int i_ = (s_); i_ >= (t_); --i_)

const int N = 1001000, C = 36;

int sa[N], rnk[N], Num;

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
    Node *ch[C], *nxt;
    int len, pos;
    bool vis;
    Node() {}
    Node(Node *p, int l) {
        *this = *p, len = l, vis = true;
    }
    Node(int l, int x) : len(l), pos(x) {}
    void dfs() {
        if (!vis) sa[rnk[pos] = ++Num] = pos;
        for (Edge *e = head; e; e = e->nxt)
            e->v->dfs();
    }
} tpool[N << 1], *root, *last, *tcur;

void add(Node *x, Node *y) {
    new (++ecur) Edge(x->head, y);
}

void init() {
    root = last = tcur = tpool;
}

void extend(int c, int p) {
    Node *u = new (++tcur) Node(last->len + 1, p), *v = last;
    for (; v && !v->ch[c]; v = v->nxt)
        v->ch[c] = u;
    if (!v) u->nxt = root;
    else if (v->ch[c]->len == v->len + 1)
        u->nxt = v->ch[c];
    else {
        Node *n = new (++tcur) Node(v, v->len + 1), *o = v;
        u->nxt = o->nxt = n;
        for (; v && v->ch[c] == o; v = v->nxt)
            v->ch[c] = n;
    }
    add(u->nxt, u), last = u;
}

char s[N];
int pm[200], cnt;

int main() {
    rep (i, '0', '9') pm[i] = cnt++;
    rep (i, 'a', 'z') pm[i] = cnt++;
    init();
    scanf("%s", s);
    int len = strlen(s) - 1;
    per (i, len, 0)
        extend(pm[(int)s[i]], i);
    root->dfs();
    rep (i, 0, len)
        printf("%d ", sa[i]);
    puts("");
}
