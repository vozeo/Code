#include <bits/stdc++.h>
using namespace std;
#define rep(i, s, t) for (int i = (s); i <= (t); ++i)

const int INF = 0x3f3f3f3f;
int x, n, f[105][4];

int main() {
	scanf("%d", &n);
	rep (i, 1, n) {
		scanf("%d", &x);
		if (x == 0) {
			f[i][0] = min(f[i - 1][0], min(f[i - 1][1], f[i - 1][2])) + 1;
			f[i][1] = f[i][2] = INF;
		} else if (x == 1) {
			f[i][0] = min(f[i - 1][0], min(f[i - 1][1], f[i - 1][2])) + 1;
			f[i][1] = INF;
			f[i][2] = min(f[i - 1][0], f[i - 1][1]);
		} else if (x == 2) {
			f[i][0] = min(f[i - 1][0], min(f[i - 1][1], f[i - 1][2])) + 1;
			f[i][1] = min(f[i - 1][0], f[i - 1][2]);
			f[i][2] = INF;
		} else {
			f[i][0] = min(f[i - 1][0], min(f[i - 1][1], f[i - 1][2])) + 1;
			f[i][1] = min(f[i - 1][0], f[i - 1][2]);
			f[i][2] = min(f[i - 1][0], f[i - 1][1]);
		}
	}
	printf("%d\n", min(f[n][0], min(f[n][1], f[n][2])));
    return 0;
}
