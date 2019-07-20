#include <iostream>
#include <cstdio>
#include <queue>
#include <cstdlib>
#define rep(i_, s_, t_) for(int i_ = s_; i_ <= t_; ++i_)
using namespace std;
const int N = 10005;
const int M = 100005;

bool vis[N];
int co[N], n, m, dep[N];

struct Edge {
    int v;
    Edge *nxt;
} *head[N], epool[N << 1], *ecur = epool;

void add(int u, int v) {
    *(++ecur) = (Edge){v, head[u]};
    head[u] = ecur;
}

int bfs(int x) {
    int cnt[2] = {0, 1};
    queue<int> q;
    q.push(x);
    co[x] = 1;
    while(q.size()) {
        int u = q.front();
        q.pop();
        if (vis[u])
            continue;
        vis[u] = true;
        for (Edge *e = head[u]; e; e = e->nxt) {
            int v = e->v;
            //printf("%d %d %d\n", u, e->v, co[u]);
            
            if (vis[v] && co[v] == co[u]) {
                printf("Impossible\n");
                exit(0);
            }
            q.push(v);
            if (!vis[v]) {
                co[v] = co[u] ^ 1;
                cnt[co[v]]++;
            }
        }
    }
    return min(cnt[0], cnt[1]);
}

int main() {
    scanf("%d%d", &n, &m);
    int x, y;
    rep (i, 1, m) {
        scanf("%d%d", &x, &y);
        add(x, y);
        add(y, x);
        dep[x]++, dep[y]++;
    }
    int cnt = 0;
    rep (i, 1, n)
        if (!vis[i])
            cnt += bfs(i);
    printf("%d\n", cnt);
    return 0;
}