#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

const int N = 805, M = 8005;

struct Edge *head[N];
struct Edge {
    int v;
    Edge *nxt;
    Edge() {}
    Edge(int x, int y) : v(y), nxt(head[x]) {
        head[x] = this;
    }
} epool[N << 1], *ecur = epool;

void add(int x, int y) {
    new (++ecur) Edge(x, y);
}

template<typename T>
void read(T &x) {
    char ch;
    while (!isdigit(ch = getchar()));
    for (x = ch - '0'; isdigit(ch = getchar()); x = x * 10 + ch - '0');
}

int g[100], dfn[N], low[N], col[N], stk[N];
int n, m, top, Num, CntCol, a1, a2, x1, x2;
bool vis[N];

void readata() {
    char ch;
    while (!isalpha(ch = getchar()));
    a1 = g[ch - 'a'];
    read(x1);
    while (!isalpha(ch = getchar()));
    a2 = g[ch - 'a'];
    read(x2);
}

void dfs(int u) {
    dfn[u] = low[u] = ++Num;
    stk[++top] = u, vis[u] = true;
    int v;
    for (Edge *e = head[u]; e; e = e->nxt) {
        if (!dfn[v = e->v])
            dfs(v), low[u] = min(low[u], low[v]);
        else if (vis[v])
            low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u]) {
        ++CntCol;
        while (stk[top] != u)
            col[stk[top]] = CntCol, vis[stk[top--]] = false;
        col[u] = CntCol, vis[u] = false, --top;
    }
}

void work() {
    rep (i, 1, 2 * n)
        if (!dfn[i])
            dfs(i);
    rep (i, 1, n)
        if (col[i] == col[i + n]) {
            puts("BAD");
            return;
        }
    puts("GOOD");
}

void init() {
    memset(epool, 0, sizeof epool);// * (ecur - epool + 1));
    memset(head, 0, sizeof head);// * (ecur - epool + 1));
    ecur = epool;
    Num = top = CntCol = 0;
    memset(dfn, 0, sizeof dfn);
    memset(stk, 0, sizeof stk);
    memset(col, 0, sizeof col);
    memset(low, 0, sizeof low);
    memset(vis, 0, sizeof vis);
}

int main() {
    //freopen("P4171.in", "r", stdin);
    int T;
    read(T), g['m' - 'a'] = 1;
    while (T--) {
        read(n), read(m);
        rep(i, 1, m) {
            readata();
            //printf("%d %d %d %d\n", a1, x1, a2, x2);
            add(x1 + n * (a1 ^ 1), x2 + n * a2);
            add(x2 + n * (a2 ^ 1), x1 + n * a1);
        }
        work();
        if (T) init();
    }
}
