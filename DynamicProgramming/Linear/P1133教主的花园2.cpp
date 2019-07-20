#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

const int N = 1e5 + 5;
int n, mx, a[N][4], f[N][5], d[5];

void dp(int x) {
	rep (i, 2, n + 1) {
		f[i][1] = max(f[i - 1][2], f[i - 1][4]) + a[i][1];
		f[i][2] = f[i - 1][1] + a[i][2];
		f[i][3] = f[i - 1][4] + a[i][2];
		f[i][4] = max(f[i - 1][1], f[i - 1][3]) + a[i][3];
	}
	mx = max(mx, f[n + 1][x] - d[x]); 
}
int main() {
	scanf("%d", &n);
	rep (i, 1, n)
		rep (j, 1, 3)
			scanf("%d", &a[i][j]);
	rep (i, 1, 3)
		a[n + 1][i] = a[1][i];
	d[1] = a[1][1], d[2] = a[1][2], d[3] = a[1][2], d[4] = a[1][3];
	f[1][1] = a[1][1];dp(1);f[1][1] = 0;
	f[1][2] = a[1][2];dp(2);f[1][2] = 0;
	f[1][3] = a[1][2];dp(3);f[1][3] = 0;
	f[1][4] = a[1][3];dp(4);f[1][4] = 0;
	printf("%d\n", mx);
}
