#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

const int N = 1e5 + 5, M = 2e5 + 5;
int d[N];
bool vis[N];

struct Edge *head[N];
struct Edge {
    int v, w;
    Edge *nxt;
    Edge() {}
    Edge(int x, int y, int z) : v(y), w(z), nxt(head[x]) {
        head[x] = this;
    }
} epool[M], *ecur = epool;

void add(int x, int y, int z) {
    new (++ecur) Edge(x, y, z);
}

void dij(int s) {
    priority_queue<pair<int, int> > q;
    q.push(make_pair(0, s));
    memset(d, 0x3f, sizeof d);
    d[s] = 0;
    while (!q.empty()) {
        int u = q.top().second, v;
        q.pop();
        if (vis[u])
            continue;
        vis[u] = true;
        for (Edge *e = head[u]; e; e = e->nxt)
            if (d[v = e->v] > d[u] + e->w)
                q.push(make_pair(-(d[v] = d[u] + e->w), v));
    }
}

int main() {
    int n, m, s, x, y, z;
    ios::sync_with_stdio(false);
    cin >> n >> m >> s;
    rep (i, 1, m)
        cin >> x >> y >> z, add(x, y, z);
    dij(s);
    rep (i, 1, n)
        cout << d[i] << " ";
    cout << endl;
}
