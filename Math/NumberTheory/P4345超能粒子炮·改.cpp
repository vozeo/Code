#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (long long i_ = (s_); i_ <= (t_); ++i_)
#define per(i_, s_, t_) for (long long i_ = (s_); i_ >= (t_); --i_)
typedef long long ll;

const int N = 2400, P = 2333;
ll fac[N], inv[N], a[10], b[10], c[N][N], s[N][N];

ll qpow(ll x, ll k = P - 2) {
	ll ans = 1;
	for (; k; k >>= 1, x = x * x % P)
		if (k & 1)
			ans = ans * x % P;
	return ans;
}

void init() {
	fac[0] = fac[1] = 1;
	rep (i, 2, P - 1)
		fac[i] = fac[i - 1] * i % P;
	inv[0] = inv[1] = 1, inv[P - 1] = qpow(fac[P - 1]);
	per (i, P - 2, 2)
		inv[i] = inv[i + 1] * (i + 1) % P;
	rep (i, 0, P)
		rep (j, 0, i)
			c[i][j] = fac[i] * inv[j] * inv[i - j] % P;
	rep (i, 0, P)
		s[i][0] = 1;
	rep (i, 0, P)
		rep (j, 1, P)
			s[i][j] = (c[i][j] + s[i][j - 1]) % P;
	rep (i, 0, 10) {
		rep (j, 0, 10)
			printf("%lld ", s[i][j]);
		puts("");
	}
}

ll C(ll n, ll k) {
	/* if (n < k) */
	/* 	return 0; */
	if (n < P && k < P)
		return c[n][k];
	return C(n / P, k / P) * c[n % P][k % P] % P;
}

ll F(ll n, ll k) {
	/* if (n < k) */
	/* 	return 0; */
	if (n < P && k < P)
		return s[n][k];
	return (F(n / P, k / P - 1) * F(n % P, P - 1) % P +
			C(n / P, k / P) * s[n % P][k % P] % P) % P;
}

int main() {
	int T;
	ll n, k;
	init();
	scanf("%d", &T);
	while (T--) {
		scanf("%lld%lld", &n, &k);
		printf("%lld\n", F(n, k));
	}
}
