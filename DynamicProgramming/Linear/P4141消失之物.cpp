#include <bits/stdc++.h>
using namespace std;
#define rep(i, s, t) for (int i = (s); i <= t; ++i)
#define per(i, s, t) for (int i = (s); i >= t; --i)

const int N = 2005;
int f[N], g[N], v[N];

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	rep (i, 1, n)
		scanf("%d", &v[i]);
	f[0] = g[0] = 1;
	rep (i, 1, n)
		per (j, m, v[i])
			f[j] = (f[j] + f[j - v[i]]) % 10;
	rep (i, 1, n) {
		rep (j, 1, m) {
			if (j >= v[i])
				g[j] = (f[j] - g[j - v[i]] + 10) % 10;
			else
				g[j] = f[j];
			printf("%d", g[j]);
		}
		puts("");
	}
}
