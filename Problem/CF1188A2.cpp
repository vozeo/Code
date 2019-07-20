#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

const int N = 1005;
int stk[5][5], ans[5005][4];

void read(int &x) {
    char ch;
    while (!isdigit(ch = getchar()));
    for (x = ch - '0'; isdigit(ch = getchar()); x = x * 10 + ch - '0');
}

struct Edge *head[N];
struct Edge {
    int v, w;
    bool vis;
    Edge *nxt, *rev;
    Edge() {}
    Edge(int x, int y, int z) : v(y), w(z), vis(false), nxt(head[x]) {
        head[x] = this;
    }
} epool[N << 1], *ecur = epool;

void add(int x, int y, int z) {
    new (++ecur) Edge(x, y, z);
    new (++ecur) Edge(y, x, z);
}

int tot[5], deg[N];

void dfs(int num, int x, int y, int fa) {
    if (tot[num] >= 2) return;
    if (deg[x] == 1) {
        stk[num][++tot[num]] = x;
        return;
    }
    for (Edge *e = head[x]; e; e = e->nxt)
        if (e->v != fa && e->v != y)
            dfs(num, e->v, y, x);
}
int Tot;

void adp(int x, int y, int z) {
    ans[++Tot][1] = x, ans[Tot][2] = y, ans[Tot][3] = z;
}

bool vis[N];

void cal(int x, int fa) {
    for (Edge *e = head[x]; e; e = e->nxt) {
        if (e->v == fa) continue;
        tot[1] = 0, dfs(1, x, e->v, x);
        tot[2] = 0, dfs(2, e->v, x, e->v);
        if (tot[1] == 1 && tot[2] == 1) {
            adp(stk[1][1], stk[2][1], e->w);
        } else if (tot[1] == 2 && tot[2] == 2) {
            adp(stk[1][1], stk[2][1], e->w >> 1);
            adp(stk[1][2], stk[2][2], e->w >> 1);
            adp(stk[2][1], stk[2][2], -(e->w >> 1));
            adp(stk[1][1], stk[1][2], -(e->w >> 1));
        }
        else if (tot[1] == 1 && tot[2] == 2) {
            adp(stk[1][1], stk[2][1], e->w >> 1);
            adp(stk[1][1], stk[2][2], e->w >> 1);
            adp(stk[2][1], stk[2][2], -(e->w >> 1));
        }
        else if (tot[1] == 2 && tot[2] == 1) {
            adp(stk[1][1], stk[2][1], e->w >> 1);
            adp(stk[1][2], stk[2][1], e->w >> 1);
            adp(stk[1][1], stk[1][2], -(e->w >> 1));
        }
        cal(e->v, x);
    }
}


int main() {
    freopen("1188A2.in", "r", stdin);
    int n, x, y, z;
    read(n);
    rep (i, 2, n) {
        read(x), read(y), read(z), add(x, y, z);
        ++deg[x], ++deg[y];
    }
    rep (i, 1, n)
        if (deg[i] == 2) {
            puts("NO");
            return 0;
        }
    puts("YES");
    cal(1, 1);
    printf("%d\n", Tot);
    rep (i, 1, Tot)
        printf("%d %d %d\n", ans[i][1], ans[i][2], ans[i][3]);
}
