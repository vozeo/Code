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

int main() {
	scanf("%d%d%d", &s, &m, &n);

    rep (i, 1, n)
        read(a[i]);
    rep (i, 1, n)
        read(b[i]);
    f[i][j + b[i]][k & (1 << l)] = f[i][j][k] + a[i];
    rep (i, 1, 90)
        rep (j, 0, 100)
            rep (k, 0，(1 << n))
                rep (l, 1, n) {
                    if (j > b[i])
                        f[i + 1][j - b[i]][k] = max(f[i][j][k] - a[i];
                    if (
                    f[i][j + b[i]][k & (1 << l)] = f[i][j][k] + a[i];
                }
    
    printf("%d\n", ans);
	return 0;
}
