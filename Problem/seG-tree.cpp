#include <iostream>
#include <cstdio>
typedef long long ll;

struct Node {
    Node *lc, *rc;
    int len;
    long long sum, tag;
    Node () {}
    Node (ll val) : lc(NULL), rc(NULL), len(1), sum(val), tag(0) {}
    Node (Node *lc, Node *rc, int l) : lc(lc), rc(rc), len(l), tag(0) : {
        sum = lc->sum + rc->sum;
    }

    void add(ll d) {
        sum += len * d;
        tag += d;
    }

    void pushdown() {
        if (tag) {
            lc->add(tag);
            rc->add(tag);
            tag = 0;
        }
    }

    void modify(int l, int r, int nl, int nr, ll d) {
        if (nr < l || r < nl)
            return;
        if (l <= nl && nr <= r) {
            add(d);
            return;
        }
        int mid = (nl + nr) >> 1;
        lc->modify(l, r, nl, mid, d);
        rc->modify(l, r, mid + 1, nr, d);
        sum = lc->sum + rc->sum;
    }

    void query(int l, int r, int nl, int nr) {
        if (nr < l || r < nl)
            return;
        if (l <= nl && nr <= r) {
            ret += sum;
            return;
        }
        int mid = (nl + nr) >> 1;
        lc->query(l, r, nl, mid);
        rc->query(l, r, mid + 1, nr);
    }
} *segt, tpool[N << 1], *tcur = tpool;

Node *build(int l, int r) {
    if (l == r)
        return new(tcur++) Node(a[l]);
    int mid = (l + r) >> 1;
    return new(tcur++) Node(build(l, mid), build(mid + 1, r), r - l + 1);
}

int main() {
    
}