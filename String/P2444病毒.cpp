#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

const int N = 2e4 + 5;

struct Node {
    Node *fail, *ch[2];
    bool dg, vis, in;
    Node() {}
} tpool[N], *tcur = tpool, *root = tpool;

void insert(char s[]) {
    Node *o = root;
    int len = strlen(s) - 1, p;
    rep (i, 0, len) {
        p = s[i] - '0';
        if (!o->ch[p])
            o->ch[p] = new (++tcur) Node();
        o = o->ch[p];
    }
    o->dg = true;
}

void build() {
    queue<Node*> q;
    rep (i, 0, 1)
        if (root->ch[i])
            root->ch[i]->fail = root, q.push(root->ch[i]);
    Node *o;
    while (!q.empty()) {
        o = q.front(), q.pop();
        rep (i, 0, 1) {
            if (o->ch[i]) {
                q.push(o->ch[i]);
                if (o->fail->ch[i])
                    o->ch[i]->fail = o->fail->ch[i], o->ch[i]->dg |= o->fail->ch[i]->dg;
                else o->ch[i]->fail = root;
            } else o->ch[i] = o->fail->ch[i] ? o->fail->ch[i] : root;
        }
    }
}

void dfs(Node *o) {
    if (o->in) {
        puts("TAK");
        exit(0);
    }
    if (o->vis || o->dg) return;
    o->vis = o->in = true;
    if (o->ch[0]) dfs(o->ch[0]);
    if (o->ch[1]) dfs(o->ch[1]);
    o->in = false;
}

char s[N];

int main() {
    int n;
    scanf("%d", &n);
    rep (i, 1, n)
        scanf("%s", s), insert(s);
    build(), dfs(root);
    puts("NIE");
}
