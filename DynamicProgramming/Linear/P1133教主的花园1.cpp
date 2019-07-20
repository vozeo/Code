#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

const int N = 1e5 + 5;
int n, mx, f[N][4][4], a[N][4];
void dp(int x, int y) {
	rep (i, 2, n + 1) {
		f[i][1][2] = max(f[i - 1][2][1], f[i - 1][3][1]) + a[i][2];
		f[i][1][3] = max(f[i - 1][2][1], f[i - 1][3][1]) + a[i][3];
		f[i][2][1] = f[i - 1][1][2] + a[i][1];
		f[i][2][3] = f[i - 1][3][2] + a[i][3];
		f[i][3][1] = max(f[i - 1][1][3], f[i - 1][2][3]) + a[i][1];
		f[i][3][2] = max(f[i - 1][1][3], f[i - 1][2][3]) + a[i][2];
	}
	mx = max(mx, f[n + 1][x][y] - a[1][y]);
}

int main() {
	scanf("%d", &n);
	rep (i, 1, n) {
		rep (j, 1, 3)
			scanf("%d", &a[i][j]);
	}
	rep (i, 1, 3)
		a[n + 1][i] = a[1][i];
	rep (i, 1, 3)
		rep (j, 1, 3) {
			f[1][i][j] = a[1][j];
			dp(i, j);
			f[1][i][j] = 0;
		}
	printf("%d\n", mx);
}
