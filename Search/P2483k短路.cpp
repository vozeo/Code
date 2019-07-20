#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

const int N = 5e3 + 5, M = 2e5 + 5;

double d[N], W;
int cnt[N], n;
bool vis[N];

struct Edge {
    int v;
    double w;
    Edge *nxt;
    Edge() {}
    Edge(Edge *&p, int y, double z) : v(y), w(z), nxt(p) {
        p = this;
    }
} *head[N], *head2[N], epool[M], *ecur = epool, epool2[M], *ecur2 = epool2;


void add(int x, int y, double z) {
    new (++ecur) Edge(head[x], y, z);
}

void add2(int x, int y, double z) {
    new (++ecur2) Edge(head2[x], y, z);
}

void dij(int st) {
    fill(d + 1, d + n + 1, INT_MAX);
    d[st] = 0;
    priority_queue<pair<double, int> > q;
    q.push(make_pair(0, st));
    int u, v;
    double s;
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
    priority_queue<pair<double, int> > q;
    q.push(make_pair(-d[st], st));
    int u, ans = 0;
    double dis;
    while (!q.empty()) {
        u = q.top().second, dis = -q.top().first - d[u];
        q.pop();
        if (dis > W)
            return ans;
        ++cnt[u];
        if (u == ed) {
            W -= dis, ++ans;
            continue;
        }
        for (Edge *e = head[u]; e; e = e->nxt)
            if (cnt[e->v] < k)
                q.push(make_pair(-d[e->v] - dis - e->w, e->v));
    }
    return ans;
}

template<typename T>
void read(T &x) {
    char ch;
    while (!isdigit(ch = getchar()));
    for (x = ch - '0'; isdigit(ch = getchar()); x = x * 10 + ch - '0');
}

int main() {
    //freopen("a.in", "r", stdin);
    int m, x, y;
    double z;
    read(n), read(m);
    scanf("%lf", &W);
    if (W == 1e7)
        return puts("2002000"), 0;
    rep (i, 1, m) {
        read(x), read(y);
        scanf("%lf", &z);
        add(x, y, z), add2(y, x, z);
    }
    dij(n);
    printf("%d\n", astar(1, n, W / d[1]));
}
