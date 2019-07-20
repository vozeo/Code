#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

const int N = 805, P = 1e9 + 7;
int f[N][N][16][2], a[N][N];

int main() {
	freopen("P1373.in", "r", stdin);
	int n, m, s, ans = 0;
	scanf("%d%d%d", &n, &m, &s);
    s++;
	rep (i, 1, n)
		rep (j, 1, m)
			scanf("%d", &a[i][j]), f[i][j][a[i][j] % s][0] = 1;
	rep (i, 1, n)
		rep (j, 1, m)
			rep (k, 0, s - 1) {
                f[i][j][k][0] += f[i][j - 1][(k - a[i][j] + s) % s][1];
                f[i][j][k][0] %= P;
                f[i][j][k][0] += f[i - 1][j][(k - a[i][j] + s) % s][1];
                f[i][j][k][0] %= P;
                f[i][j][k][1] += f[i][j - 1][(k + a[i][j]) % s][0];
                f[i][j][k][1] %= P;
                f[i][j][k][1] += f[i - 1][j][(k + a[i][j]) % s][0];
				f[i][j][k][1] %= P;
                //f[i][j + 1][(k + a[i][j + 1]) % s][1] = (f[i][j + 1][(k + a[i][j + 1]) % s][1] + f[i][j][k][0]) % s;
				//f[i + 1][j][(k + a[i + 1][j]) % s][1] = (f[i + 1][j][(k + a[i + 1][j]) % s][1] + f[i][j][k][0]) % s;
				//f[i][j + 1][(k + a[i][j + 1]) % s][0] = (f[i][j + 1][(k + a[i][j + 1]) % s][0] + f[i][j][k][1]) % s;
				//f[i + 1][j][(k + a[i + 1][j]) % s][0] = (f[i + 1][j][(k + a[i + 1][j]) % s][0] + f[i][j][k][1]) % s;
			}
	rep (i, 1, n)
		rep (j, 1, m)
			ans = (ans + f[i][j][0][1]) % P;
	printf("%d\n", ans);
}
