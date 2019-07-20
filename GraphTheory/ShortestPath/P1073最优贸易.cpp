#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

const int N = 2e5 + 5, M = 6e5 + 5;
int d[N * 3], a[N];
bool vis[N * 3];

struct Edge *head[N];
struct Edge {
    int v, w;
    Edge *nxt;
    Edge() {}
    Edge(int x, int y, int z) : v(y), w(z), nxt(head[x]) {
        head[x] = this;
    }
} epool[M * 6 + N * 2], *ecur = epool;

void add(int x, int y, int z) {
    new (++ecur) Edge(x, y, 0);
    if (z) new (++ecur) Edge(y, x, 0);
}

void arc(int x, int y, int z) {
    new (++ecur) Edge(x, y, z);
}

void spfa() {
    memset(d, -0x3f, sizeof d);
    queue<int> q;
    q.push(1);
    d[1] = 0, vis[1] = true;
    while (!q.empty()) {
        int u = q.front(), v;
        q.pop(), vis[u] = false;
        for (Edge *e = head[u]; e; e = e->nxt)
            if (d[v = e->v] < d[u] + e->w) { 
                d[v] = d[u] + e->w;
                if (!vis[v])
                    q.push(v), vis[v] = true;
            }
    }
}

int main() {
    int n, m, T, x, y, z;
    scanf("%d%d", &n, &m);
    T = n * 3 + 1;
    rep (i, 1, n)
        scanf("%d", &a[i]);
    rep (i, 1, n) {
        arc(i, i + n, -a[i]);
        arc(i + n, i + n * 2, a[i]);
    }
    add(n, T, 0), add(T - 1, T, 0);
    rep (i, 1, m) {
        scanf("%d%d%d", &x, &y, &z), --z;
        add(x, y, z);
        add(x + n, y + n, z);
        add(x + n * 2, y + n * 2, z);
    }
    spfa();
    printf("%d\n", d[T]);
}
