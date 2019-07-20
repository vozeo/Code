#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i)

const int N = 4e5 + 5;

int Ret, tot, a[N], b[N];

template<typename T>
void read(T &x) {
    char ch;
    while (!isdigit(ch = getchar()));
    for (x = ch - '0'; isdigit(ch = getchar()); x = x * 10 + ch - '0');
}

struct Node {
    struct Edge *head;
    Node *ls, *rs;
    int pos;
    Node() {}
    Node(Node *l, Node *r) : ls(l), rs(r) {
        maintain();
    }
    Node(Node *p) { if (p) *this = *p; }

    void maintain() {
        pos = min(ls ? ls->pos : 0, rs ? rs->pos : 0);
    }

    void query(int l, int r, int p) {
        if (l == r) return (void)(Ret = b[l]);
        int mid = (l + r) >> 1;
        if (ls->pos < p) ls->query(l, mid, p);
        else rs->query(mid + 1, r, p);
    }
} tpool[N * 30], *tcur = tpool, *root[N];

Node *build(int l, int r) {
    if (l == r) return new (++tcur) Node();
    int mid = (l + r) >> 1;
    return new (++tcur) Node(build(l, mid), build(mid + 1, r));
}

void insert(Node *&o, int l, int r, int p, int x) {
    o = new (++tcur) Node(o);
    if (l == r) return (void)(o->pos = x);
    int mid = (l + r) >> 1;
    if (p <= mid) insert(o->ls, l, mid, p, x);
    else insert(o->rs, mid + 1, r, p, x);
    o->maintain();
}

int cnt;

int main() {
    freopen("P4137.in", "r", stdin);
    int n, m, l, r;
    read(n), read(m);
    b[++cnt] = 0;
    rep (i, 1, n)
        read(a[i]), b[++cnt] = a[i], b[++cnt] = a[i] + 1;
    sort(b + 1, b + cnt + 1);
    tot = unique(b + 1, b + cnt + 1) - b - 1;
    root[0] = build(1, tot);
    rep (i, 1, n) {
        a[i] = lower_bound(b + 1, b + tot + 1, a[i]) - b;
        insert(root[i] = root[i - 1], 1, tot, a[i], i);
    }
    while (m--) {
        read(l), read(r), Ret = 0;
        root[r]->query(1, tot, l);
        printf("%d\n", Ret);
    }
}
