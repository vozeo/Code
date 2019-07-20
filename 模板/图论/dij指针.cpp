#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

typedef const int cint;
cint N = 100005;
int n, m, s, d[N];
bool vis[N];

template <typename T>
inline void read(T &x)
{
    char c;
    while (!isdigit(c = getchar()));
    for (x = c - '0'; isdigit(c = getchar()); x = x * 10 + c - '0');
}

struct Edge *head[N];
struct Edge
{
    int v, w;
    Edge *nxt;
    Edge() {}
    Edge(cint u, cint v, cint w) : v(v), w(w), nxt(head[u]) { head[u] = this; }
} epool[N * 2], *ecur = epool;

void add(int u, int v, int w)
{
    *(++ecur) = Edge(u, v, w);
}

priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
void dijkstra()
{
    memset(d + 1, 0x3f, sizeof(int) * n);
    q.push(make_pair(d[s] = 0, s));
    while (!q.empty())
    {
        int u = q.top().second;
        q.pop();
        if (vis[u])
            continue;
        vis[u] = true;
        int v, t;
        for (Edge *e = head[u]; e; e = e->nxt)
            if (d[v = e->v] > (t = d[u] + e->w))
                q.push(make_pair(d[v] = t, v));
    }
}

int main()
{
    read(n), read(m), read(s);
    int u, v, w;
    rep(i, 1, m)
    {
        read(u), read(v), read(w);
        add(u, v, w);
    }
    dijkstra();
    rep(i, 1, n)
        printf("%d ", d[i]);
    putchar("\n");
    return 0;
}