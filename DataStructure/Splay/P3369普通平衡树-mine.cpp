#include <cstdio>
#include <algorithm>
#include <climits>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

const int N = 1e5 + 5;

struct Node *root;
struct Node {
    Node *fa, *ch[2];
    int val, siz, cnt;
    Node() {}
    Node(Node *f, int x) : fa(f), val(x), siz(1), cnt(1) {}
    void maintain() {
        siz = cnt + (ch[0] ? ch[0]->siz : 0) + (ch[1] ? ch[1]->siz : 0);
    }
    int rel() {
        return fa ? (fa->ch[1] == this) : 0; // ***
    }
    void link(Node *o, Node *f, int r) {
        if (o) o->fa = f;
        if (f) f->ch[r] = o;
    }
    void rotate() {
        Node *f = fa;
        int r = rel();
        link(this, f->fa, f->rel());
        link(ch[r ^ 1], f, r);
        link(f, this, r ^ 1);
        f->maintain();
        maintain();
        if (!fa)
            root = this;
    }
    void splay(Node *tar = NULL) {
        while (fa != tar) {
            if (fa->fa == tar)
                rotate();
            else if (fa->rel() == rel())
                fa->rotate(), rotate();
            else
                rotate(), rotate();
        }
    }
    int rank() {
        return ch[0] ? ch[0]->siz : 0;
    }
    Node *pre() { // Predecessor
        /* splay(); */
        Node *o = ch[0];
        while (o->ch[1])
            o = o->ch[1];
        return o;
    }
    Node *suc() { // Successor
        /* splay(); */
        Node *o = ch[1];
        while (o->ch[0])
            o = o->ch[0];
        return o;
    }
} tpool[N], *tcur = tpool;

Node *insert(int x) {
    Node **o = &root, *fa = NULL;
    while (*o && (*o)->val != x) {
        fa = *o;
        ++fa->siz;
        o = &fa->ch[x >= fa->val]; // ***
    }
    if (*o)
        ++(*o)->cnt, ++(*o)->siz;
    else
        *o = new (tcur++) Node(fa, x);
    (*o)->splay();
    return root;
}

Node *find(int x) {
    Node *o = root;
    while (o && o->val != x)
        o = o->ch[x >= o->val]; // ***
    if (o) o->splay();
    return o;
}

void erase(Node *o) {
    Node *pr = o->pre(), *su = o->suc();
    pr->splay();
    su->splay(pr);
    if (o->siz > 1)
        --o->cnt, --o->siz;
    else
        su->ch[0] = NULL;
    su->maintain(), pr->maintain(); // ???
}

void erase(int x) {
    Node *o = find(x);
    if (!o) return;
    erase(o);
}

int rnk(int x) {
    Node *o = find(x);
    if (o) return o->rank();
    o = insert(x);
    int res = o->rank();
    erase(o);
    return res;
}

int pre(int x) {
    Node *o = find(x);
    if (o) return o->pre()->val;
    o = insert(x);
    int res = o->pre()->val;
    erase(o);
    return res;
}

int suc(int x) {
    Node *o = find(x);
    if (o) return o->suc()->val;
    o = insert(x);
    int res = o->suc()->val;
    erase(o);
    return res;
}

int kth(int k) { // select
    Node *o = root;
    while (true) {
        if (k < o->rank())
            o = o->ch[0];
        else if (k >= o->rank() + o->cnt) // ???
            k -= o->rank() + o->cnt, o = o->ch[1];
        else break;
    }
    o->splay();
    return o->val;
}

void init() {
    root = NULL;
    insert(INT_MAX);
    insert(INT_MIN);
}

int main() {
    freopen("P3369.in", "r", stdin);
    int n, op, x;
    init();
    scanf("%d", &n);
    rep (i, 1, n) {
        scanf("%d%d", &op, &x);
        switch(op) {
            case 1: insert(x); break;
            case 2: erase(x); break;
            case 3: printf("%d\n", rnk(x)); break;
            case 4: printf("%d\n", kth(x)); break;
            case 5: printf("%d\n", pre(x)); break;
            case 6: printf("%d\n", suc(x)); break;
        }
    }
}
