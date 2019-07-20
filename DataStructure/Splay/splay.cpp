#include <cstdio>
#include <algorithm>
#include <climits>
using namespace std;

const int N = 1e5 + 5;

struct Node *root;
struct Node {
    Node *fa, *ch[2];
    int v, cnt, siz;
    Node() {}
    Node(Node *f, int x) : fa(f), v(x), cnt(1), siz(1) {}
    void upd() {
        siz = cnt + (ch[0] ? ch[0]->siz : 0) + (ch[1] ? ch[1]->siz : 0);
    }
    int rel() {
        return fa ? fa->ch[1] == this : 0;
    }
    void link(Node *o, Node *f, int r) {
        if (o) o->fa = f;
        if (f) f->ch[r] = o;
    }
    void rot() {
       Node *f = fa;
       int r = rel();
       link(this, f->fa, f->rel());
       link(ch[r ^ 1], f, r);
       link(f, this, r ^ 1);
       f->upd(), upd();
       if (!fa) root = this;
    }
    void splay(Node *tar = NULL) {
        while (fa != tar) {
            if (fa->fa == tar) rot();
            else if (rel() == fa->rel())
                fa->rot(), rot();
            else rot(), rot();
        }
    }
    int rnk() {
        return ch[0] ? ch[0]->siz : 0;
    }
    Node *pre() {
        Node *o = ch[0];
        while (o->ch[1])
            o = o->ch[1];
        return o;
    }
    Node *suc() {
        Node *o = ch[1];
        while (o->ch[0])
            o = o->ch[0];
        return o;
    }
} tpool[N], *tcur = tpool;

Node *find(int x) {
    Node *o = root;
    while (o && o->v != x)
        o = o->ch[x > o->v];
    if (o) o->splay(); // ***
    return o;
}
/*
Node *ins(int x) {
    Node *o = root, *f = NULL;
    while (true) {
        if (!o) {
            o = new (tcur++) Node(f, x);
            break;
        }
        ++o->siz;
        if (o->v == x) {
            ++o->cnt;
            break;
        }
        else f = o, o = f->ch[x > o->v];
    }
    o->splay();
    return root;
}
*/
/*
Node *ins(Node *&o, Node *f, int x) {
    if (!o)
        return o = new (tcur++) Node(f, x);
    ++o->siz; // 可不加，会在splay的时候更新，但是可能会错。
    if (o->v == x)
        return ++o->cnt, o;
    return ins(o->ch[x > o->v], o, x);
}

Node *ins(int x) {
    Node *o = ins(root, NULL, x);
    o->splay();
    return o;
}
*/

Node *ins(int x) {
    Node **o = &root, *fa = NULL;
    while (*o && (*o)->v != x) {
        fa = *o;
        //++fa->siz;
        o = &fa->ch[x > fa->v]; // ***
    }
    if (*o)
        ++(*o)->cnt;
    else
        *o = new (tcur++) Node(fa, x);
    (*o)->splay();
    return root;
}

void del(Node *o) {
    Node *p = o->pre(), *s = o->suc();
    p->splay(), s->splay(p); // ***
    if (o->cnt > 1)
        --o->cnt, --o->siz;
    else s->ch[0] = NULL;
    s->upd(), p->upd();
}

void del(int x) {
    Node *o = find(x);
    if (o) del(o);
}

int rnk(int x) {
    Node *o = find(x);
    if (o) return o->rnk();
    o = ins(x);
    int ans = o->rnk();
    del(o);
    return ans;
}

int kth(int k) {
    Node *o = root;
    while (true) {
        if (k < o->rnk())
            o = o->ch[0];
        else if (k >= o->rnk() + o->cnt)
            k -= o->rnk() + o->cnt, o = o->ch[1];
        else break;
    }
    o->splay();
    return o->v;
}

int pre(int x) {
    Node *o = find(x);
    if (o) return o->pre()->v;
    o = ins(x);
    int ans = o->pre()->v;
    del(o);
    return ans;
}

int suc(int x) {
    Node *o = find(x);
    if (o) return o->suc()->v;
    o = ins(x);
    int ans = o->suc()->v;
    del(o);
    return ans;
}

void init() {
    ins(INT_MAX);
    ins(INT_MIN);
}

int main() {
    freopen("P3369.in", "r", stdin);
    freopen("P3369.out", "w", stdout);
    int n, op, x;
    init();
    scanf("%d", &n);
    while (n--) {
        scanf("%d%d", &op, &x);
        switch(op) {
            case 1: ins(x);break;
            case 2: del(x);break;
            case 3: printf("%d\n", rnk(x));break;
            case 4: printf("%d\n", kth(x));break;
            case 5: printf("%d\n", pre(x));break;
            case 6: printf("%d\n", suc(x));break;
        }
    }
}
