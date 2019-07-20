#include <cstdio>
#include <queue>
#include <cctype>
#include <algorithm>
#include <cstring>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

const int N = 1e3 + 5, M = 1e5 + 5;

int d[N], cnt[N];
bool vis[N];

struct Edge {
    int v, w;
    Edge *nxt;
    Edge() {}
    Edge(Edge *&p, int y, int z) : v(y), w(z), nxt(p) {
        p = this;
    }
} *head[N], *head2[N], epool[M], *ecur = epool, epool2[M], *ecur2 = epool2;


void add(int x, int y, int z) {
    new (++ecur) Edge(head[x], y, z);
}

void add2(int x, int y, int z) {
    new (++ecur2) Edge(head2[x], y, z);
}

void dij(int st) {
    memset(d, 0x3f, sizeof d);
    d[st] = 0;
    priority_queue<pair<int, int> > q;
    q.push(make_pair(0, st));
    int u, v, s;
    while (!q.empty()) {
        u = q.top().second;
        q.pop();
        if (vis[u]) continue;
        vis[u] = true;
        for (Edge *e = head2[u]; e; e = e->nxt)
            if (d[v = e->v] > (s = d[u] + e->w))
                q.push(make_pair(-(d[v] = s), v));
    }
}

int astar(int st, int ed, int k) {
    if (st == ed) ++k;
    priority_queue<pair<int, int> > q;
    q.push(make_pair(-d[st], st));
    int u, dis;
    while (!q.empty()) {
        u = q.top().second, dis = -q.top().first - d[u];
        q.pop();
        ++cnt[u];
        if (cnt[ed] == k)
            return dis;
        for (Edge *e = head[u]; e; e = e->nxt)
            if (cnt[e->v] < k)
                q.push(make_pair(-d[e->v] - dis - e->w, e->v));
    }
    return -1;
}

template<typename T>
void read(T &x) {
    char ch;
    while (!isdigit(ch = getchar()));
    for (x = ch - '0'; isdigit(ch = getchar()); x = x * 10 + ch - '0');
}

int main() {
    freopen("a.in", "r", stdin);
    int n, m, x, y, z, s, t, k;
    read(n), read(m);
    rep (i, 1, m)
        read(x), read(y), read(z), add(x, y, z), add2(y, x, z);
    read(s), read(t), read(k);
    dij(t);
    printf("%d\n", astar(s, t, k));
}
