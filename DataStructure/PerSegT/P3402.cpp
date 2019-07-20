#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

const int N = 4e5 + 5;

template<typename T>
void read(T &x) {
    char ch;
    while (!isdigit(ch = getchar()));
    for (x = ch - '0'; isdigit(ch = getchar()); x = x * 10 + ch - '0');
}

struct Node {
    Node *lc, *rc;
    int v, siz;
    Node() {}
    Node(Node *l, Node *r) : lc(l), rc(r) {}
    Node(int x) : v(x), siz(1) {}
    Node(Node *p) { *this = *p; }
} tpool[N * 25], *tcur = tpool, *root[N], *segt;

Node *build(int l, int r) {
    if (l == r)
        return new (++tcur) Node(l);
    int mid = (l + r) >> 1;
    return new (++tcur) Node(build(l, mid), build(mid + 1, r));
}

int Rx, Rs, tot;

void query(Node *p, Node *&o, int l, int r, int x) {
    if (!o) o = new (++tcur) Node(p);
    if (l == r) {
        Rx = o->v, Rs = o->siz;
        return;
    }
    int mid = (l + r) >> 1;
    if (x <= mid)
        query(p->lc, o->lc, l, mid, x);
    else query(p->rc, o->rc, mid + 1, r, x);
}

void modify(Node *p, Node *&o, int l, int r, int x) {
    if (!o) o = new (++tcur) Node(p);
    if (l == r) {
        o->v = Rx, o->siz += Rs;
        return;
    }
    int mid = (l + r) >> 1;
    if (x <= mid)
        modify(p->lc, o->lc, l, mid, x);
    else modify(p->rc, o->rc, mid + 1, r, x);
}

int main() {
    freopen("P3402.in", "r", stdin);
    int n, m, op, x, y, sia, sib;
    read(n), read(m);
    segt = root[0] = build(1, n);
    rep (i, 1, m) {
        read(op), read(x);
        if (op == 1) {
            read(y);
            query(segt, segt, 1, n, x), sia = Rs;
            query(segt, segt, 1, n, y), sib = Rs;
            if (sia < sib) swap(x, y);
            Rx = y, Rs = 0;
            modify(segt, root[++tot], 1, n, x);
            Rs = sia;
            modify(root[tot], root[tot], 1, n, y);
            rep (j, 1, n) {
                query(root[0], root[0], 1, n, j), sib = Rx;
                cout << sib << endl;
            }
            segt = root[tot];
        } else if (op == 3) {
            read(y);
            query(segt, root[++tot], 1, n, x), sia = Rx;
            query(segt, root[tot], 1, n, y), sib = Rx;
            cout << sia << " " << sib << endl;
            printf("%d\n", sia == sib);
            segt = root[tot];
        } else segt = root[x];
    }
}

