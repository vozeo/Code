#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define per(i_, s_, t_) for (int i_ = (s_); i_ >= (t_); --i_)

const int N = 1e6 + 100, C = 26;
int buc[N << 1];
long long Ans;

struct Node {
    Node *ch[C], *nxt;
    int len, cnt;
    Node() {}
    Node(int l, int x) : len(l), cnt(x) {}
    Node(Node *p, int l) {
        *this = *p, len = l, cnt = 0;
    }
} tpool[N << 1], *tpo[N << 1], *tcur = tpool, *root = tpool, *last = tpool;

void calc() {
    int mxl = 0;
    for (Node *p = tpool; p <= tcur; ++p)
        mxl = max(mxl, p->len), ++buc[p->len];
    rep (i, 1, mxl)
        buc[i] += buc[i - 1];
    for (Node *p = tpool; p <= tcur; ++p)
        tpo[--buc[p->len]] = p, cout << buc[p->len] << endl;
    per (i, tcur - tpool, 1) {
        Node *p = tpo[i];
        p->nxt->cnt += p->cnt;
        if (p->cnt != 1)
            Ans = max(Ans, 1ll * p->cnt * p->len);
    }
}

void extend(int c) {
    Node *u = new (++tcur) Node(last->len + 1, 1), *v = last;
    for (; v && !v->ch[c]; v = v->nxt)
        v->ch[c] = u;
    if (!v)
        u->nxt = root;
    else if (v->len + 1 == v->ch[c]->len) // ***
        u->nxt = v->ch[c];
    else {
        Node *n = new (++tcur) Node(v->ch[c], v->len + 1), *o = v->ch[c];
        u->nxt = o->nxt = n;
        for (; v && v->ch[c] == o; v = v->nxt)
            v->ch[c] = n;
    }
    last = u;
}

char s[N];

int main() {
    //freopen("P3804.in", "r", stdin);
    scanf("%s", s);
    int len = strlen(s) - 1;
    root = tpool;
    rep (i, 0, len)
        extend(s[i] - 'a');
    calc();
    printf("%lld\n", Ans);
}
