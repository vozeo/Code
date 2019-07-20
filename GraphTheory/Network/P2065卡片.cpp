#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

const int N = 4005, M = 1e6 + 5;
int S, T, cnt, d[M], a[N], b[N];

struct Edge *head[N], *cur[N];
struct Edge {
    int v, c;
    Edge *nxt, *rev;
    Edge() {}
    Edge(int x, int y, int z) : v(y), c(z), nxt(head[x]) { head[x] = this; }
} epool[M << 1], *ecur = epool;

void add(int x, int y) {
    new (++ecur) Edge(x, y, 1);
    new (++ecur) Edge(y, x, 0);
    head[x]->rev = head[y];
    head[y]->rev = head[x];
}

bool bfs() {
    queue<int> q;
    fill(d, d + cnt + 1, 0);
    rep (i, 1, cnt)
        cur[i] = head[i];
    q.push(S), d[S] = 1;
    while (!q.empty()) {
        int u = q.front(), v;
        q.pop();
        for (Edge *e = head[u]; e; e = e->nxt) {
            if (!d[v = e->v] && e->c) {
                q.push(v), d[v] = d[u] + 1; // *****
                if (v == T) return true;
            }
        }
    }
    return false;
}

int dfs(int u, int f) {
    if (u == T || !f) return f;
    int r = f, v, p;
    for (Edge *&e = cur[u]; e; e = e->nxt)
        if (e->c && d[v = e->v] == d[u] + 1) {
            p = dfs(v, min(e->c, r));
            e->c -= p, e->rev->c += p;
            if (!(r -= p)) return f;
        }
    d[u] = 0;
    return f - r;
}

void init() {
    memset(head, 0, sizeof head);
    ecur = epool;
}

void addnum(int id, int x, int op) {
    for (int i = 2; i * i <= x; ++i) {
        if (x % i == 0) {
            if (!ver[i]) ver[i] = ++cnt;
            if (op) add(id, ver[i]);
            else add(ver[i], id);
            while (x % i == 0) x /= i;
        }
    }
    if (x > 1) {
        if (!ver[x]) ver[x] = ++cnt;
        if (op) add(id, ver[x]);
        else add(ver[x], id);
    }
}

const int LIM = 1e7 + 5;
int vis[LIM], pri[LIM], tot;
/*
void sieve(int n) {
    rep (i, 2, n) {
        if (!vis[i])
            pri[++tot] = i;
        rep (j, 1, tot) {
            if (i * pri[j] > n)
                break;
            vis[i * pri[j]] = true;
            if (i % pri[j] == 0)
                break;
        }
    }
}
*/
void work() {
    int n, m, ans = 0;
    scanf("%d%d", &m, &n);
    S = 0, T = 1, cnt = m + n + 1;
    rep (i, 1, m) {
        scanf("%d", &a[i]);
        add(S, i + 1);
        addnum(i + 1, a[i], 1);
    }
    rep (i, 1, n) {
        scanf("%d", &b[i]);
        add(i + m + 1, T);
        addnum(i + m + 1, b[i], 0);
    }
    while (bfs())
        ans += dfs(S, INT_MAX);
    printf("%d\n", ans);
}

int main() {
    /* freopen("P2065.in", "r", stdin); */
    int K;
    scanf("%d", &K);
    while (K--) {
        init();
        work();
    }
}
