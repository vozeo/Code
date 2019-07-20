#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define per(i_, s_, t_) for (int i_ = (s_); i_ >= (t_); --i_)

const int N = 2e5 + 5, M = 4e5 + 5;
bool vis[N];
int n, m, cnt, lastans;
int d[N], fa[N], gr[N][22], dis[N + M], hi[N + M]; 

struct Edge *head[N];
struct Edge {
    int v, w;
    Edge *nxt;
    Edge() {}
    Edge(int x, int y, int z) : v(y), w(z), nxt(head[x]) {
        head[x] = this;
    }
} epool[M << 1], *ecur = epool;

void add(int x, int y, int z) {
    new (++ecur) Edge(x, y, z);
}

priority_queue<pair<int, int> > q;
void dij() {
    memset(d, 0x3f, sizeof d);
    memset(vis, 0, sizeof vis);
    d[1] = 0;
    q.push(make_pair(0, 1));
    while (!q.empty()) {
        int u = q.top().second, v, s;
        q.pop();
        if (vis[u]) continue;
        vis[u] = true;
        for (Edge *e = head[u]; e; e = e->nxt)
            if (d[v = e->v] > (s = d[u] + e->w))
                q.push(make_pair(-(d[v] = s), v));
    }
}

struct EdgeT {
    int u, v, w, a;
    bool operator < (const EdgeT &rhs) const {
        return a > rhs.a;
    }
} ed[M];

int find(int x) {
    while (fa[x] != x)
        x = fa[x] = fa[fa[x]];
    return x;
}

void dfs(int u, int dad) {
    dis[u] = d[u];
    for (Edge *e = head[u]; e; e = e->nxt) {
        gr[e->v][0] = u;
        dfs(e->v, u);
        dis[u] = min(dis[u], dis[e->v]);
    }
    /* cerr << "u = " << dad << "dis = " << dis[u] << endl; */
}

void clear() {
    memset(head, 0, sizeof head);
    ecur = epool;
}

void kruskal() {
    /* rep (i, 1, n) */
    /*     cout << d[i] << endl; */
    clear();
    sort(ed + 1, ed + m + 1);
    int u, v;
    rep (i, 1, m) {
        u = find(ed[i].u), v = find(ed[i].v);
        if (u != v) {
            fa[u] = fa[v] = ++cnt;
            fa[cnt] = cnt;
            hi[cnt] = ed[i].a;
            add(cnt, u, 1);
            add(cnt, v, 1);
        }
    }
    dfs(cnt, 0);
    /* rep (i, 1, cnt) */
    /*     cout << "dis = " << gr[i][0] << endl; */
    //gr[cnt][0] = cnt;
        rep (j, 1, 20)
            rep (i, 1, cnt)
                gr[i][j] = gr[gr[i][j - 1]][j - 1];
}

int query(int u, int p) {
    per (i, 20, 0)
        if (gr[u][i] && hi[gr[u][i]] > p)
            u = gr[u][i];
    return dis[u];
}

void init() {
    lastans = 0, cnt = n;
    rep (i, 1, n)
        fa[i] = i;
    memset(head, 0, sizeof head);
    memset(gr, 0, sizeof gr);
    memset(ed, 0, sizeof ed);
    memset(dis, 0x3f, sizeof dis);
    memset(hi, 0, sizeof hi);
    ecur = epool;
}

template<typename T>
void read(T &x) {
    char ch = 0;
    while (!isdigit(ch = getchar()));
    for (x = ch - '0'; isdigit(ch = getchar()); x = x * 10 + ch - '0');
}

int main() {
    freopen("return3.in", "r", stdin);
    freopen("return3.out", "w", stdout);
    int T, Q, K, S, v, p;
    read(T);
    while (T--) {
        read(n), read(m);
        init();
        rep (i, 1, m) {
           read(ed[i].u), read(ed[i].v);
           read(ed[i].w), read(ed[i].a);
           add(ed[i].u, ed[i].v, ed[i].w);
           add(ed[i].v, ed[i].u, ed[i].w);
        }
        dij();
        kruskal();
        read(Q), read(K), read(S);
        rep (i, 1, Q) {
            read(v), read(p);
            v = (v + K * lastans - 1) % n + 1;
            p = (p + K * lastans) % (S + 1);
            printf("%d\n", lastans = query(v, p));
        }
    }
}
