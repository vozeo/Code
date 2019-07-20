#include <cstdio>
#include <algorithm>
#include <climits>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= t_; ++i_)

const int N = 8e4 + 5;
int a[N];

struct Node *root;
struct Node {
    Node *fa, *ch[2];
    int v, siz;
    Node() {}
    Node(Node *f, int x) : fa(f), v(x), siz(1) {}
    int rel() {
        return fa ? fa->ch[1] == this : 0;
    }
    void upd() {
        siz = 1 + lc() + (ch[1] ? ch[1]->siz : 0);
    }
    void link(Node *o, Node *f, int r) {
        if (o) o->fa = f;
        if (f) f->ch[r] = o;
    }
    void rot() {
        Node *f = fa;
        int r = rel();
        link(this, f->fa, f->rel()); // ***
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
    int lc() {
        return ch[0] ? ch[0]->siz : 0;
        
    }
    Node *adj(int x) {
        if (!x) return this;
        if (x == -1) x = 0;
        int r = x ^ 1;
        Node *o = ch[x];
        if (!o) return o;
        while (o->ch[r])
            o = o->ch[r];
        return o;
    }
} tpool[N], *tcur = tpool, *pos[N];

void del(int x) {
    Node *o = pos[x], *p = o->adj(-1), *s = o->adj(1);
    p->splay(), s->splay(p);
    s->ch[0] = NULL;
    s->upd(), p->upd();
}

/* int rnk(int x) { */
/*     Node *o = pos[x]; */
/*     int ans = 0; */
/*     while (o != root) { */
/*         ans += o->fa->lc() * o->rel(); */
/*         o = o->fa; */
/*     } */
/*     return ans + o->lc(); */
/* } */

int rnk(int x) {
    pos[x]->splay();
    return root->lc();
}

int kth(int x) {
    Node *o = root;
    while (o->lc() != x) {
        if (o->lc() > x)
            o = o->ch[0];
        else if (o->lc() < x)
            x -= o->lc() + 1, o = o->ch[1];
    }
    return o->v;
}

void mdy(Node *&o, int x) {
    o->splay();
    swap(*o, *o->adj(x));
}

/*
void plc(Node *o, int x) {
    o->splay();
    o->link(o->ch[x], o->adj(x), x);
    o->ch[x] = NULL;
}
*/

void plc(int x, int r) {
    del(x);
    Node *o = root;
    while (o->ch[r])
        o = o->ch[r];
    pos[x] = o->ch[r] = new (tcur++) Node(o, x);
    o->ch[r]->splay();
}

Node *build(int l, int r, Node *f) {
    if (l > r) return NULL;
    int mid = (l + r) >> 1;
    Node *o = new (tcur++) Node(f, a[mid]);
    pos[a[mid]] = o;
    if (l < r) {
        o->ch[0] = build(l, mid - 1, o); // ***
        o->ch[1] = build(mid + 1, r, o); // ***
    }
    o->upd();
    return o;
}

/*
Node *ins(Node *&o, Node *f, int x) {
    if (!o)
        return o = new (tcur++) Node(f, x);
    return ins(o->ch[x > o->v], o, x);
}

void ins(int x) {
    Node *o = ins(root, NULL, x);
    o->splay();
}
*/
int main() {
    int n, m, x, t;
    char s[10];
    scanf("%d%d", &n, &m);
    rep (i, 1, n)
        scanf("%d", &a[i]);
    root = build(1, n, root);
    rep (i, 1, m) {
        scanf("%s%d", s, &x);
        switch (s[0]) {
            case 'T': plc(x, 0);break;
            case 'B': plc(x, 1);break;
            case 'I': scanf("%d", &t), mdy(pos[x], t);break;
            case 'A': printf("%d\n", rnk(x));break;
            case 'Q': printf("%d\n", kth(x));break;
        }
    }
}
