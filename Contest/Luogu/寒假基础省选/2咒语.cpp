#include <bits/stdc++.h>
#define rep(i_, s_, t_) for(int i_ = (s_); i_ <= (t_); ++i_)
typedef const int cint;
using namespace std;

cint N = 10005;
int n, T, k, t, p, d[N];
char s[N];

void init() {
	scanf("%d%d", &n, &k);
	scanf("%s", s);
	memset(d, 0, sizeof(d));
	t = 0;
}

bool cmp(cint &a, cint &b) {
	return strncmp(s + a, s + b, k) <= 0;
}

void work() {
	rep (i, 1, n - k) {
		if (strncmp(s + i, s + d[t], k) >= 0) {
			if (abs(i - d[t]) >= k)
				d[++t] = i;
		} else {
			p = lower_bound(d, d + d[t], i, cmp) - d;
			if (abs(i - d[p - 1]) >= k)
				d[p] = i;
		}
	}
	printf("%d\n", t + 1);
}

int main() {
	scanf("%d", &T);
	while (T--) {
		init();
		work();
	}
	return 0;
}
