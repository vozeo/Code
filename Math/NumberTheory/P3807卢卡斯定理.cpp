#include <bits/stdc++.h>
using namespace std;
#define rep(i, s, t) for (int i = (s); i <= (t); ++i)
#define per(i, s, t) for (int i = (s); i >= (t); --i)

const int N = 2e5 + 5;
int inv[N], fac[N];
int qpow(int x, int a, int p) {
	int ans = 1;
	for (; a; x = 1LL * x * x % p, a >>= 1)
		if (a & 1)
			ans = 1LL * ans * x % p;
	return ans;
}

int C(int n, int m, int p) {
	if (n < m)
		return 0;
	if (n < p && m < p)
		return 1LL * fac[n] * inv[m] % p * inv[n - m] % p;
	return C(n / p, m / p, p) * C(n % p, m % p, p) % p;
}

void work(int x) {
	fac[0] = fac[1] = 1;
	rep (i, 2, x - 1)
		fac[i] = 1LL * fac[i - 1] * i % x;
	inv[0] = inv[1] = 1;
	inv[x - 1] = qpow(fac[x - 1], x - 2, x);
	per (i, x - 2, 2)
		inv[i] = 1LL * inv[i + 1] * (i + 1) % x;
}

int main() {
	freopen("P3807.in", "r", stdin);
	int T, n, m, p;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d%d", &n, &m, &p);
		work(p);
		if (n + m < m)
			puts("0");
		else
			printf("%d\n", C(n + m, m, p));
	}
}
