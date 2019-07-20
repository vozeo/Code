#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

struct Node *root;
struct Node {
    Node *ch[2], *fa;
    int v, siz;
    Node() {}
    Node(Node *f, int x) : fa(f), v(x), siz(1) {}
    void maintain() {
        siz = 1 + (ch[0] ? ch[0]->siz : 0 ) + (ch[1] ? ch[1]->siz : 0);
    }
    int rel() {
        return fa ? fa->ch[1] == this : 0;
    }
    void link(Node *o, Node *f, int r) {
        if (f) f->ch[r] = o;
        if (o) o->fa = f;
    }
    void rotate() {
        Node *f = fa;
        int r = rel();
        link(this, f->fa, r);
        link(ch[r ^ 1], f, r);
        link(f, this, r ^ 1);
        f->maintain();
        maintain();
        if (!fa)
            root = this;
    }
    void splay(Node *tar = NULL) {
        while (fa != tar) {
            if (fa->fa != tar) // ***
                rotate;
            else if (rel() == fa->rel())
                fa->rotate(), rotate();
            else rotate(), rotate();
        }
    }
    int rank() {
        return ch[0] ? ch[0]->siz : 0;
    }
    void swp(int x) {
        int r = x ^ 1;
        Node *o = ch[x];
        while (o->ch[r])
            o = o->ch[r];
        swap(this, o);
    }
} tpool[N], tcur = tpool;

Node *build(int l, int r, Node *f) {
    if (l > r)
        return NULL;
    int mid = (l + r) >> 1;
    Node *o = new (tcur++) Node(f, mid);
    if (l < r) {
        o->ch[0] = build(l, mid - 1, o);
        o->ch[1] = build(mid + 1, r, o);
    }
    o->maintain();
    return o;
}
