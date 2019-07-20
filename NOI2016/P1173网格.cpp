#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

const int N = 2e5 + 5;
typedef long long ll;

template<typename T>
void read(T &x) {
    char ch;
    while (!isdigit(ch = getchar()));
    for (x = ch - '0'; isdigit(ch = getchar()); x = x * 10 + ch - '0');
}

struct Edge *head[N];
struct Edge {
    int v;
    Edge *nxt;
    Edge() {}
    Edge(int x, int y) : v(y), nxt(head[x]) {
        head[x] = this;
    }
} epool[N << 1], *ecur = epool;

void add(int x, int y) {
    if (x == y) return;
    new (++ecur) Edge(x, y);
    new (++ecur) Edge(y, x);
}

struct Pot {
    int x, y;
    Pot() {}
    Pot(int a, int b) : x(a), y(b) {}
    bool operator < (const Pot &rhs) const {
        return x < rhs.x || (x == rhs.x && y < rhs.y);
    }
} p[N];

map<Pot, int> g;

int n, m, in;
bool Hs, vis[N];
int dx[8] = {1, -1, 0, 0, 1, 1, -1, -1}, dy[8] = {0, 0, 1, -1, 1, -1, 1, -1};

void dfs(int u, int f) {
    //if (Hs) cout << "True";
    /* if (u == in && f != in) { */
    /*     Hs = true; */
    /*     return; */
    /* } */
    //if (Hs) return;
    cout << u;
    vis[u] = true;
    for (Edge *e = head[u]; e; e = e->nxt)
        if (e->v != f) {
            if (e->v == in) {
                Hs = true;
                return;
            }
            else dfs(e->v, u);
        }
}

int cal(int x, int y) {
    if (x < 1 || y < 1 || x > n || y > m)
        return 0;
    int ans = (x == 1) + (y == 1) + (x == n) + (y == m);
    rep (i, 0, 4)
        ans += (g[Pot(x + dx[i], y + dy[i])] > 0);
    return ans;
}

void init() {
    Hs = false;
    g.clear();
    memset(vis, 0, sizeof vis);
    memset(head, 0, sizeof head);
    memset(p, 0, sizeof p);
    ecur = epool;
}


int main() {
    freopen("P1173-1.in", "r", stdin);
    int T, K, S, x, y, c, ans;
    scanf("%d\n", &T);
    while (T--) {
        init();
        read(n), read(m), read(K);
        rep (i, 1, K)
            read(p[i].x), read(p[i].y);
        S = K + 1;
        if (1ll * n * m <= 2) {
            puts("-1");
            continue;
        }
        if (!K) {
            if (n == 1 || m == 1)
                puts("1");
            else puts("2");
            continue;
        }
        rep (i, 1, K) {
            x = p[i].x, y = p[i].y, g[p[i]] = i;
            if (x == 1 || y == 1 || x == n || y == m)
                add(S, i);
            rep (j, 0, 7) {
                c = g[Pot(x + dx[j], y + dy[j])];
                if (c) add(c, i);
            }
        }
        rep (i, 1, K) {
            if (!vis[i])
                in = i, dfs(i, i), cout << "f = " << i;
            if (Hs) break;
        }
        if (Hs) {
            puts("0");
            continue;
        } else if (1ll * n * m - K <= 2) {
            puts("-1");
            continue;
        }

        ans = 4;
        rep (i, 1, K)
            rep (j, 0, 4)
                ans = min(ans, 4 - cal(p[i].x + dx[j], p[i].y + dy[j]));
        printf("%d\n", ans);
    }
}
