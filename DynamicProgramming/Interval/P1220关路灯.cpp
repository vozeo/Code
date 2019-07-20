#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define per(i_, s_, t_) for (int i_ = (s_); i_ >= (t_); --i_)

const int N = 1005;
int f[N][N][2], s[N], p[N], a[N];

int main() {
	freopen("P1220.in", "r", stdin);
	int n, c, r;
	scanf("%d%d", &n, &c);
	rep (i, 1, n)
		scanf("%d%d", p + i, a + i), s[i] = s[i - 1] + a[i];
	memset(f, 0x3f, sizeof f);
	f[c][c][0] = f[c][c][1] = 0;
	rep (i, 1, n - 1)
		rep (l, 1, n - i) {
			r = l + i;
			f[l][r][0] = min(f[l][r][0], f[l + 1][r][0] + (s[l] + s[n] - s[r]) * (p[l + 1] - p[l]));
			f[l][r][0] = min(f[l][r][0], f[l + 1][r][1] + (s[l] + s[n] - s[r]) * (p[r] - p[l]));
			f[l][r][1] = min(f[l][r][1], f[l][r - 1][1] + (s[l - 1] + s[n] - s[r - 1]) * (p[r] - p[r - 1]));
			f[l][r][1] = min(f[l][r][1], f[l][r - 1][0] + (s[l - 1] + s[n] - s[r - 1]) * (p[r] - p[l]));
		}
	printf("%d\n", min(f[1][n][0], f[1][n][1]));
}
