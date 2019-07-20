#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

const int N = 2e5 + 5, M = 4e5 + 5;

struct Edge *head[N];
struct Edge {
    int v;
    Edge *nxt;
    Edge() {}
    Edge(int x, int y) : v(y), nxt(head[x]) {
        head[x] = this;
    }
} epool[M << 1], *ecur = epool;

void add(int x, int y) {
    new (++ecur) Edge(x, y);
}

int dfn[N], low[N], stk[N], col[N], x[N], y[N], pos[10];
int n, m, r1, r2, Dat, Cnt, Num, Top;
char g[N], c[N], d[N];

void tarjan(int u) {
    dfn[stk[++Top] = u] = low[u] = ++Num;
    int v;
    for (Edge *e = head[u]; e; e = e->nxt) {
        if (!dfn[v = e->v])
            tarjan(v), low[u] = min(low[u], low[v]);
        else if (!col[v])
            low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u]) {
        ++Cnt;
        while (stk[Top + 1] != u)
            col[stk[Top--]] = Cnt;
    }
}

char ans[3][2] = {'B', 'C', 'A', 'C', 'A', 'B'};
int f[3][3] = {0, 0, 1, 0, 0, 1, 0, 1, 0};

void init() {
    memset(head, 0, sizeof(Edge) * ((n << 1) + 1));
    rep (i, 1, n << 1)
        dfn[i] = low[i] = col[i] = 0;
    ecur = epool, Num = Cnt = Top = 0;
}

void judge() {
    init();
    rep (i, 1, m) {
        if (g[x[i]] == c[i] + 32)
            continue;
        r1 = f[g[x[i]] - 'a'][c[i] - 'A'];
        r2 = f[g[y[i]] - 'a'][d[i] - 'A'];
        if (g[y[i]] == d[i] + 32)
            add(x[i] + r1 * n, x[i] + (r1 ^ 1) * n);
        else {
            add(x[i] + r1 * n, y[i] + r2 * n);
            add(y[i] + (r2 ^ 1) * n, x[i] + (r1 ^ 1) * n);
        }
    }
    rep (i, 1, n << 1)
        if (!dfn[i])
            tarjan(i);
    rep (i, 1, n)
        if (col[i] == col[i + n])
            return;
    rep (i, 1, n)
        printf("%c", ans[g[i] - 'a'][col[i] > col[i + n]]);
    exit(0);
}

void dfs(int s) {
    if (s == Dat + 1) {
        judge();
        return;
    }
    g[pos[s]] = 'a', dfs(s + 1);
    g[pos[s]] = 'b', dfs(s + 1);
}

void readchar() {
    scanf("%s", g + 1);
    int sum = 0, len = strlen(g + 1);
    rep (i, 1, len)
        if (g[i] == 'x')
            pos[++sum] = i;
}

int main() {
    freopen("P3825.in", "r", stdin);
    scanf("%d %d", &n, &Dat);
    readchar();
    scanf("%d", &m);
    rep (i, 1, m)
        scanf("%d %c %d %c", &x[i], &c[i], &y[i], &d[i]);
    dfs(1);
    printf("-1");
}
