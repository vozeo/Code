#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

const int N = 1e4 + 5, M = 1e5 + 5;
typedef pair<int, int> pii;

template<typename T>
void read(T &x) {
    char ch;
    while (!isdigit(ch = getchar()));
    for (x = ch - '0'; isdigit(ch = getchar()); x = x * 10 + ch - '0');
}

priority_queue<pii> q;

struct Edge *head[N];
struct Edge {
    int v;
    Edge *nxt;
    Edge() {}
    Edge(int x, int y) : v(y), nxt(head[x]) {
        head[x] = this;
    }
} epool[M << 1], *ecur = epool;

void add(int x, int y) {
    new (++ecur) Edge(x, y);
}

int n, m, top, in[N], a[N], ind[N], stk[N];

void solve1() {
    int u;
    memcpy(in + 1, ind + 1, n * sizeof(int));
    rep (i, 1, n)
        if (!in[i])
            q.push(pii(a[i], i));
    while (!q.empty()) {
        u = stk[++top] = q.top().second, q.pop();
        for (Edge *e = head[u]; e; e = e->nxt)
            if (!(--in[e->v]))
                q.push(pii(a[e->v], e->v));
    }
    while (top)
        printf("%d ", stk[top--]);
    puts("");
}

void solve2() {
    int u, ans;
    rep (x, 1, n) {
        memcpy(in + 1, ind + 1, n * sizeof(int));
        ans = n;
        rep (i, 1, n)
            if (!in[i])
                q.push(pii(a[i], i));
        while (!q.empty()) {
            u = q.top().second, q.pop();
            if (u == x) continue;
            if (a[u] < ans) {
                while (!q.empty()) q.pop();
                break;
            }
            --ans;
            for (Edge *e = head[u]; e; e = e->nxt)
                if (!(--in[e->v]))
                    q.push(pii(a[e->v], e->v));
        }
        printf("%d ", ans);
    }
    puts("");
}

int main() {
    freopen("P1954.in", "r", stdin);
    read(n), read(m);
    rep (i, 1, n)
        read(a[i]);
    int x, y;
    rep (i, 1, m)
        read(x), read(y), add(y, x), ++ind[x];
    solve1(), solve2();
}
