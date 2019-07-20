#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define re(i_, s_, t_) for (int i_ = (s_); i_ < (t_); ++i_)
#define per(i_, s_, t_) for (int i_ = (s_); i_ >= (t_); --i_)

template <typename T>
void read(T &x) {
	char c;
	while (!isdigit(c = getchar()));
	for (x = c - '0'; isdigit(c = getchar()); x = x * 10 + c - '0');
}

int ans, s, m, n, a[15], b[15];
bool vis[15];
int cou;

void dfs(int e, int d, int cnt) {
    /* printf("%d %d %d\n", e, d, cnt); */
    if (e <= s || d >= 100) {
        ans = max(ans, cnt);
        return;
    }
    int t = e / s;
    e -= t * s, d -= t * m;
    if (d < 0) d = 0;
    dfs(e, d, cnt + t);
    rep (i, 1, n) {
        if (vis[i])
            continue;
        vis[i] = true;
        int p = e + a[i] > 100 ? 100 : e + a[i]; 
        dfs(p, d + b[i], cnt + t);
        vis[i] = false;
    }
}

int main() {
	scanf("%d%d%d", &s, &m, &n);
    rep (i, 1, n)
        read(a[i]);
    rep (i, 1, n)
        read(b[i]);
    dfs(100, 0, 0);
    printf("%d\n", ans);
	return 0;
}
