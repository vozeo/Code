#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

const int N = 1e4 + 5, M = 5e4 + 5;
int tail, num, cnt;
int dfn[N], low[N], stk[N], c[N], s[N], w[N], ans[N];
bool vis[N];

struct Edge *head[N], *hscc[N];
struct Edge {
    int v;
    Edge *nxt;
    Edge() {}
    Edge(int y, Edge *&p) : v(y), nxt(p) {
        p = this;
    }
} epool[M], escc[M], *ecur = epool, *sccr = escc;

void add(int x, int y) {
    new (++ecur) Edge(y, head[x]);
}

void addscc(int x, int y) {
    new (++sccr) Edge(y, hscc[x]);
}

void tarjan(int x) {
    dfn[x] = low[x] = ++num;
    stk[++tail] = x, vis[x] = true;
    int y;
    for (Edge *e = head[x]; e; e = e->nxt) {
        if (!dfn[y = e->v]) {
            tarjan(y);
            low[x] = min(low[x], low[y]);
        } else if (vis[y])
            low[x] = min(low[x], dfn[y]);
    }
    if (dfn[x] == low[x]) {
        cnt++;
        do {
            y = stk[tail--], vis[y] = false;
            c[y] = cnt;
        } while (x != y);
    }
}

int dfs(int x) {
    if (ans[x] > 0)
        return ans[x];
    int tp = 0;
    for (Edge *e = hscc[x]; e; e = e->nxt)
        tp = max(tp, dfs(e->v));
    return ans[x] = s[x] + tp;
}

int ex[M], ey[M], out[N], in[N], fans, sans;

int main() {
    //freopen("scc.in", "r", stdin);
    ios::sync_with_stdio(false);
    int n, y, m = 0;
    cin >> n;
    rep (i, 1, n)
        while (true) {
            cin >> y;
            if (!y) break;
            ++m;
            ex[++m] = i, ey[m] = y;
            add(i, y);
        }
    rep (i, 1, n)
        if (!dfn[i])
            tarjan(i);
    rep (i, 1, m)
        if (c[ex[i]] != c[ey[i]])
            addscc(c[ex[i]], c[ey[i]]), ++out[c[ex[i]]], ++in[c[ey[i]]];
    rep (i, 1, cnt) {
        if (!in[i])
            ++fans;
        if (!out[i])
            ++sans;
    }
    cout << fans << endl;
    if (cnt > 1)
        cout << max(fans, sans) << endl;
    else cout << 0 << endl;

}
