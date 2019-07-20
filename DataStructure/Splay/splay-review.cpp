#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

struct Node {
    Node *fa, ch[2];
    int cnt, val, siz;
    Node() {}
    Node(Node *f, int x) : fa(f), val(x), cnt(1), siz(1) {}
    int upd() {
        siz = ch[0] ? ch[0]->siz + cnt + ch[1] ? ch[1]->siz;
    }
    int rel() {
        return fa ? fa->ch[1] == this : 0;
    }
    void link(Node *f, Node *o, int r) {
        f->ch[r] = o, o->fa = f;
    }
    void rot() {
        Node *f = fa;
        int r = rel();
        link(f->fa, this, r);
        link(f, ch[r ^ 1], r);
        link(this, f, r ^ 1);
        f->upd(), upd();
        if (!fa) root = this;
    }
    Node *splay(Node* tar = NULL) {
        while (fa != tar) {
            if (fa->fa == tar)
                return rot();
            else if (rel() == fa->rel())
                fa->rot(), rot();
            else rot(), rot();
        }
        return this;
    }
    Node *pre() {
        Node *o = ch[0];
        while (o->ch[0])
            o = o->ch[0];
        return o;
    }
    Node *suc() {
        Node *o = ch[1];
        while (o->ch[1])
            o = o->ch[1];
        return o;
    }
} tpool[N << 1], *tcur = tpool, *root;

Node *ins(Node *&o, Node *f, int x) {
    if (!o) new (++tcur) Node(f, x);
    ++o->siz;
    if (o->v == x) return ++o->siz, o;
    else return ins(o->ch[x > o->v], o, x);
}

Node *ins(int x) {
    Node *o = ins(root, NULL, x);
    return o->splay();
}

Node *find(int x) {
    Node *o = root;
    while (o && o->v != x)
        o = o->ch[x > o->f];
    if (o) o->splay();
    return o;
}

void del(int x) {
    Node *o = find(x);
    if (o) 
}
