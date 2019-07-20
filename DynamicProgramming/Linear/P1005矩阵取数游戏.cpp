#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

int n, m, a[100];
__int128 ans, res, f[85][85], two[85];

void print(__int128 x) {
	if (x > 9)
		print(x / 10);
	putchar(x % 10 + '0');
}

int main() {
	scanf("%d%d", &m, &n);
	two[0] = 1;
	rep (i, 1, 82)
		two[i] = two[i - 1] * 2;
	rep (l, 1, m) {
		rep (i, 1, n)
			scanf("%d", a + i);
		rep (i, 1, n + 1)
			rep (j, 1, n + 1)
				f[i][j] = 0;
		res = 0;
		//f[1][n - 1] = a[n], f[2][n] = a[1];
		rep (k, 2, n)
			rep (i, 1, k) {
				int j = i + n - k;
				f[i][j] = max(f[i - 1][j] + a[i - 1] * two[k - 1], f[i][j + 1] + a[j + 1] * two[k - 1]);
			}
		rep (i, 1, n)
			res = max(res, f[i][i] + a[i] * two[n]);
		ans += res;
	}
	print(ans);
	putchar('\n');
	return 0;
}
