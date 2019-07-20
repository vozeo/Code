#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

const int N = 2005, M = 200005;

template <typename T>
void read(T &x) {
    char ch;
    while (!isdigit(ch = getchar()));
    for (x = ch - '0'; isdigit(ch = getchar()); x = x * 10 + ch - '0');
}

struct Edge *head[N], *cur[N];
struct Edge {
    int v, c;
    Edge *nxt, *rev;
    Edge() {}
    Edge(int x, int y, int w) : v(y), c(w), nxt(head[x]) {
        head[x] = this;
    }
} epool[M << 1], *ecur = epool;

void add(int x, int y, int z) {
    new (++ecur) Edge(x, y, z);
    new (++ecur) Edge(y, x, 0);
    head[x]->rev = head[y];
    head[y]->rev = head[x];
}

int d[N], S, T;

bool bfs() {
    int u, v;
    queue<int> q;
    rep (i, 1, T)
        d[i] = 0, cur[i] = head[i];
    d[S] = 1, q.push(S);
    while (!q.empty()) {
        u = q.front(), q.pop();
        for (Edge *e = head[u]; e; e = e->nxt)
            if (e->c && !d[v = e->v]) {
                d[v] = d[u] + 1;
                if (v == T) return true;
                q.push(v);
            }
    }
    return false;
}

int dfs(int u, int f) {
    if (u == T || !f)
        return f;
    int r = f, p, v;
    for (Edge *&e = cur[u]; e; e = e->nxt)
        if (e->c && d[v = e->v] == d[u] + 1) {
            p = dfs(v, min(r, e->c));
            e->c -= p, e->rev->c += p;
            if (!(r -= p))
                return f;
        }
    d[u] = 0;
    return f - r;
}

int main() {
    freopen("P1402.in", "r", stdin);
    int n, m, k, x;
    read(n), read(m), read(k);
    S = m + k + n * 2 + 1, T = S + 1;
    rep (i, 1, m)
        add(S, i, 1);
    rep (i, 1, n)
        rep (j, 1, m) {
            read(x);
            if (x) add(j, m + k + i, 1);
        }
    rep (i, 1, n)
        add(m + k + i, m + k + n + i, 1);
    rep (i, 1, n)
        rep (j, 1, k) {
            read(x);
            if (x) add(m + k + n + i, m + j, 1);
        }
    rep (i, 1, k)
        add(m + i, T, 1);
    int ans = 0;
    while (bfs())
        ans += dfs(S, INT_MAX);
    printf("%d\n", ans);
}
