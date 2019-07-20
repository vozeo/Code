#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define per(i_, s_, t_) for (int i_ = (s_); i_ >= (t_); --i_)

const int N = 1005;
int g[N];

struct Rub {
	int t, f, h;
	bool operator < (const Rub &rhs) const {
		return t < rhs.t;
	}
} r[N];

int main() {
	freopen("P1156.in", "r", stdin);
	int n, m;
	scanf("%d%d", &n, &m);
	rep (i, 1, m)
		scanf("%d%d%d", &r[i].t, &r[i].f, &r[i].h);
	sort(r + 1, r + m + 1);
	memset(g, -1, sizeof g);
	g[0] = 10;
	rep (i, 1, m)
		per (j, n, 0)
			if (g[j] >= r[i].t) {
				if (j + r[i].h >= n) {
					printf("%d\n", r[i].t);
					return 0;
				}
				g[j + r[i].h] = max(g[j + r[i].h], g[j]);
				g[j] += r[i].f;
			}
	printf("%d\n", g[0]);
}
