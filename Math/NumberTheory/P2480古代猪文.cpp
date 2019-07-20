#include <bits/stdc++.h>
using namespace std;
#define rep(i, s, t) for (int i = (s); i <= (t); ++i)
#define per(i, s, t) for (int i = (s); i >= (t); --i)

typedef long long ll;
const int N = 1e5 + 5;
int inv[N], fac[N];

int qpow(int x, int a, int p) {
	int ans = 1;
	for (; a; x = 1LL * x * x % p, a >>= 1)
		if (a & 1)
			ans = 1LL * ans * x % p;
	return ans;
}

/* int C(int n, int m, int p) { */
/* 	if (n <= p && m <= p) */
/* 		return 1LL * fac[n] * inv[m] % p * inv[n - m] % p; */
/* 	return C(m / p, n / p, p) * C(m % p, n % p, p) % p; */
/* } */

int C(int n, int m, int p) {
	if (n < m)
		return 0;
	if (n < p && m < p)
		return 1LL * fac[n] * inv[m] % p * inv[n - m] % p;
	return C(n / p, m / p, p) * C(n % p, m % p, p) % p;
}

int work(int n, int x) {
	/* fac[0] = fac[1] = 1; */
	/* rep (i, 2, x) */
	/* 	fac[i] = fac[i - 1] * i % x; */
	/* inv[0] = inv[1] = 1; */
	/* inv[x] = qpow(fac[x], x - 2, x); */
	/* per (i, x - 1, 2) */
	/* 	inv[i] = inv[i + 1] * i % x; */
	fac[0] = fac[1] = 1;
	rep (i, 2, x - 1)
		fac[i] = 1LL * fac[i - 1] * i % x;
	inv[0] = inv[1] = 1;
	inv[x - 1] = qpow(fac[x - 1], x - 2, x);
	per (i, x - 2, 2)
		inv[i] = 1LL * inv[i + 1] * (i + 1) % x;
	int ans = 0;
	for (int i = 1; i * i < n; ++i)
		if (n % i == 0) {
			ans = (ans + C(n, i, x)) % x;
			ans = (ans + C(n, n / i, x)) % x;
		}
	int s = sqrt(n);
	if (s * s == n && n % (int)sqrt(n) == 0)
		ans = (ans + C(n, sqrt(n), x)) % x;
	/* printf("%d\n", ans); */
	return ans;
}

int main() {
	// 2, 3, 4679, 35617
	int d[10], m[10] = {0, 2, 3, 4679, 35617};
	int M = 999911658, G, n, ans = 0;
	scanf("%d%d", &n, &G);
	if (G % (M + 1) == 0) {
		puts("0");
		return 0;
	}
	rep (i, 1, 4)
		d[i] = M / m[i];
	rep (i, 1, 4)
		ans = (ans + 1LL * work(n, m[i]) * d[i] % M * qpow(d[i], m[i] - 2, m[i]) % M) % M;
	printf("%d\n", qpow(G, ans, M + 1));
}
