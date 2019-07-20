#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define per(i_, s_, t_) for (int i_ = (s_); i_ >= (t_); --i_)

const int N = 10010;
int d[N], to[N], g[N][2], mh[N];
bool vis[N];

template<typename T>
void read(T &x) {
    char ch;
    while (!isdigit(ch = getchar()));
    for (x = ch - '0'; isdigit(ch = getchar()); x = x * 10 + ch - '0');
}

bool dfs(int u) {
    rep (i, 0, 1) {
        int v = g[u][i];
        if (vis[v]) continue;
        vis[v] = true;
        if (mh[v] == -1 || dfs(mh[v])) {
            mh[v] = u, to[u] = v;
            return true;
        }
    }
    return false;
}

int main() {
    //freopen("P4551.in", "r", stdin);
    int n, a, b, ans = 0;
    memset(mh, -1, sizeof(mh));
    read(n);
    rep (i, 0, n - 1) {
        read(d[i]);
        a = (i - d[i] + n) % n, b = (i + d[i]) % n;
        if (a > b) swap(a, b);
        g[i][0] = a, g[i][1] = b;
    }
    per (i, n - 1, 0) {
        memset(vis, 0, sizeof vis);
        if (dfs(i))
            ++ans;
    }
    if (ans < n)
        puts("No Answer");
    else {
        rep (i, 0, n - 2)
            printf("%d ", to[i]);
        printf("%d\n", to[n - 1]);
    }
}
