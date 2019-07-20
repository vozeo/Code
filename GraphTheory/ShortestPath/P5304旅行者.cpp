#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

const int N = 1e5, M = 5e5;
bool vis[N];
int n, m, k, a[N];

struct graph {
    int d[N], id[N];
    struct Edge {
        int v, w;
        Edge *nxt;
        Edge() {}
        Edge(int x, int y, int z) : v(y), w(z) {}
    } epool[M], *head[N], *ecur = epool;

    void dij() {
        int u, v, w;
        priority_queue<pair<int, int> > q;
        memset(vis, 0, sizeof vis);
        memset(d, 0x3f, sizeof d);
        rep (i, 1, k)
            q.push(make_pair(d[a[i]] = 0, a[i])), id[a[i]] = a[i];
        while (!q.empty()) {
            u = q.top().second;
            q.pop();
            if (vis[u]) continue;
            vis[u] = true;
            for (Edge *e = head[u]; e; e = e->nxt)
                if (d[v = e->v] > (w = d[u] + e->w))
                    id[v] = id[u], q.push(make_pair(-(d[v] = w), v));
        }
    }

    void add(int x, int y, int z) {
        new (++ecur) Edge(x, y, z);
        ecur->nxt = head[x], head[x] = ecur;
    }

    void init() {
        memset(head, 0, sizeof head);
        ecur = epool;
    }
} g[2];

int main() {
    ios::sync_with_stdio(false);
    int T, ans, x, y, z;
    cin >> T;
    while (T--) {
        g[0].init(), g[1].init();
        ans = INT_MAX;
        cin >> n >> m >> k;
        rep (i, 1, m) {
            cin >> x >> y >> z;
            if (x ^ y)
                g[0].add(x, y, z), g[1].add(y, x, z);
        }
        rep (i, 1, k)
            cin >> a[i];
        g[0].dij(), g[1].dij();
        rep (u, 1, n)
            for (graph::Edge *e = g[0].head[u]; e; e = e->nxt) {
                int v = e->v;
                if (g[0].id[u] && g[1].id[v] && g[0].id[u] ^ g[1].id[v])
                    ans = min(ans, g[0].d[u] + g[1].d[v] + e->w);
            }
        cout << ans << endl;
    }
}
