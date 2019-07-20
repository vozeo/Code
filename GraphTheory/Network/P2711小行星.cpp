#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

const int N = 4005, M = 2e5 + 5, R = 5e4 + 5;
int d[N], S, T;

struct Edge *head[N];
struct Edge {
    int v, c;
    Edge *nxt, *rev;
    Edge() {}
    Edge(int x, int y, int w) : v(y), c(w), nxt(head[x]) {
        head[x] = this;
    }
} epool[M << 1], *cur[N], *ecur = epool;

void add(int x, int y, int z) {
    new (++ecur) Edge(x, y, z);
    new (++ecur) Edge(y, x, 0);
    head[x]->rev = head[y];
    head[y]->rev = head[x];
}

bool bfs() {
    rep (i, 1, T)
        d[i] = 0, cur[i] = head[i];
    d[S] = 1;
    queue<int> q;
    q.push(S);
    while (!q.empty()) {
        int u = q.front(), v;
        q.pop();
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
    int r = f, v, p;
    for (Edge *&e = cur[u]; e; e = e->nxt)
        if (e->c && d[v = e->v] == d[u] + 1) {
            p = dfs(v, min(e->c, r));
            e->c -= p;
            e->rev->c += p;
            if (!(r -= p))
                return f;
        }
    d[u] = 0;
    return f - r;
}

int a[R], b[R], c[R];

template <typename T>
void read(T &x) {
    char ch = 0;
    while (!isdigit(ch = getchar()));
    for (x = ch - '0'; isdigit(ch = getchar()); x = x * 10 + ch - '0');
}

int main() {
    freopen("P2065.in", "r", stdin);
    int n, m;
    read(n), m = 500;
    rep (i, 1, n)
        read(a[i]), read(b[i]), read(c[i]);
    S = 4 * m + 1, T = S + 1;
    rep (i, 1, m) {
        add(S, i, 1);
        add(i + m, i + 2 * m, 1);
        add(i + 3 * m, T, 1);
    }
    rep (i, 1, n) {
        add(a[i], b[i] + m, INT_MAX);
        add(b[i] + 2 * m, c[i] + 3 * m, INT_MAX);
    }
    int ans = 0;
    while (bfs())
        ans += dfs(S, INT_MAX);
    printf("%d\n", ans);
}
