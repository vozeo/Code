#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

const int N = 2e5 + 5, M = 2e6 + 5, C = 26;

struct Node {
    Node *ch[C], *fail;
    struct Edge *head;
    int cnt, pos;
    Node() {}
} tpool[N], *pos[N], *tcur = tpool, *root = tpool;

struct Edge {
    Node *v;
    Edge *nxt;
    Edge() {}
    Edge(Edge *&p, Node *y) : v(y), nxt(p) {
        p = this;
    }
} epool[N], *ecur = epool;

void add(Node *x, Node *y) {
    new (++ecur) Edge(x->head, y);
}

void build(char *s, int p) {
    Node *o = root;
    int len = strlen(s) - 1;
    rep (i, 0, len) {
        Node *&v = o->ch[s[i] - 'a'];
        if (!v) v = new (++tcur) Node();
        o = v;
    }
    pos[p] = o, o->pos = p;
}

void getfail() {
    queue<Node*> q;
    rep (i, 0, C - 1) {
        Node *&v = root->ch[i];
        if (v) v->fail = root, q.push(v);
        else v = root;
    }
    Node *o;
    while (!q.empty()) {
        o = q.front(), q.pop();
        rep (i, 0, C - 1) {
            Node *&v = o->ch[i];
            if (v)
                q.push(v), v->fail = o->fail->ch[i];
            else v = o->fail->ch[i];
        }
    }
}

void query(char *s) {
    int len = strlen(s) - 1, c;
    Node *o = root;
    rep (i, 0, len) {
        c = s[i] - 'a';
        while (!o->ch[c] && o != root)
            o = o->fail;
        o = o->ch[c], ++o->cnt;
    }
}

void dfs(Node *u) {
    for (Edge *e = u->head; e; e = e->nxt)
        dfs(e->v), u->cnt += e->v->cnt;
}

int n;
char s[N], t[M];

int main() {
    freopen("P3796.in", "r", stdin);
    scanf("%d", &n);
    rep (i, 1, n)
        scanf("%s", s), build(s, i);
    getfail();
    scanf("%s", t), query(t);
    for (Node *p = tpool + 1; p <= tcur; ++p)
        add(p->fail, p);
    dfs(root);
    rep (i, 1, n)
        printf("%d\n", pos[i]->cnt);
}
