#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define per(i_, s_, t_) for (int i_ = (s_); i_ >= (t_); --i_)

const int N = 1e5 + 1000;
int d[N];

template<typename T>
void read(T &x) {
    char ch;
    while (!isdigit(ch = getchar()));
    for (x = ch - '0'; isdigit(ch = getchar()); x = x * 10 + ch - '0');
}

struct Edge *head[N];
struct Edge {
    int v, w;
    Edge *nxt;
    Edge() {}
    Edge(int x, int y, int z) : v(y), w(z), nxt(head[x]) {
        head[x] = this;
    }
} epool[N << 1], *ecur = epool;

void add(int x, int y, int z) {
    new (++ecur) Edge(x, y, z);
    new (++ecur) Edge(y, x, z);
}

struct Node {
    Node *ch[2];
    Node() {}
} tpool[N * 30], *tcur = tpool, *root = tpool;

void insert(int x) {
    Node *o = root;
    per (i, 30, 0) {
        int v = (x >> i) & 1;
        if (!o->ch[v])
            o->ch[v] = new (++tcur) Node();
        o = o->ch[v];
    }
}

int query(int x) {
    Node *o = root;
    int ans = 0;
    per (i, 30, 0) {
        int v = (x >> i) & 1;
        if (o->ch[v ^ 1])
            ans += (1 << i), o = o->ch[v ^ 1];
        else o = o->ch[v];
    }
    return ans;
}

void dfs(int x, int f) {
    for (Edge *e = head[x]; e; e = e->nxt) {
        d[e->v] = d[x] ^ e->w, insert(d[e->v]);
        if (e->v != f) dfs(e->v, x);
    }
}

int main() {
    freopen("P4551.in", "r", stdin);
    int n, x, y, z;
    read(n);
    rep (i, 2, n)
        read(x), read(y), read(z), add(x, y, z);
    dfs(1, 0);
    int ans = 0;
    rep (i, 1, n)
        ans = max(ans, query(d[i]));
    printf("%d\n", ans);
}
