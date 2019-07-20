#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

const int N = 3e6 + 5;
int num, cnt, top;
int low[N], dfn[N], stk[N], c[N];
bool vis[N];

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
    new (++ecur) Edge(x, y);
}

void tarjan(int x) {
    int y;
    low[x] = dfn[x] = ++num;
    stk[++top] = x, vis[x] = true;
    for (Edge *e = head[x]; e; e = e->nxt) {
        if (!dfn[y = e->v]) {
            tarjan(y);
            low[x] = min(low[x], low[y]);
        } else if (vis[y])
            low[x] = min(low[x], dfn[y]);
    }
    if (low[x] == dfn[x]) {
        ++cnt;
        do {
            y = stk[top--], vis[y] = false;
            c[y] = cnt;
        } while (x != y);
    }
}

int ex[N << 1], ey[N << 1];

int main() {
    int n, m, a, b, x, y;
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m;
    rep (i, 1, m) {
        cin >> x >> a >> y >> b;
        add(x + !a * n, y + b * n);
        add(y + !b * n, x + a * n);
    }
    rep (i, 1, 2 * n)
        if (!dfn[i])
            tarjan(i);
    rep (i, 1, n)
        if (c[i] == c[i + n]) {
            cout << "IMPOSSIBLE" << endl;
            return 0;
        }
    cout << "POSSIBLE" << endl;
    rep (i, 1, n)
        cout << (c[i] > c[i + n]) << " ";
    cout << endl;
}
