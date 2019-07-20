#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
typedef long long ll;

const int N = 1e5 + 5;

int n;
ll p[N], a[N], s[N];
multiset<ll> w;
multiset<ll>::iterator it;

void init() {
	w.clear();
}

ll exgcd(ll k, ll r, ll &x, ll &y) {
	if (!r) {
		x = 1, y = 0;
		return k;
	}
	ll d = exgcd(r, k % r, y, x);
	y -= (k / r) * x;
	return d;
}

ll mul(ll k, ll r, ll MOD) {
	ll ans = 0;
	for (; r; k = (k << 1) % MOD, r >>= 1)
		if (r & 1)
			ans = (ans + k) % MOD;
	return ans;
}

ll work() {
	ll x, y, k, c, m = 1, d = 0, mx = 0;
	p[0] = 1;
	rep (i, 1, n) {
		it = w.upper_bound(a[i]);
		if (it != w.begin())
			it--;
		k = (*it), w.erase(it), w.insert(s[i]);
		mx = max(mx, (a[i] - 1) / k + 1);

		a[i] %= p[i], k %= p[i]; // ***
		if (!k && !a[i])
			continue;
		if ((!k && a[i]) || a[i] % (c = exgcd(k, p[i], x, y)))
			return -1;
		p[i] /= c;
		/* a[i] = mul(a[i] / c, x, p[i]); */
		a[i] = mul(a[i] / c, (x % p[i] + p[i]) % p[i], p[i]);
		
		if ((a[i] - d) % (c = exgcd(m, p[i], x, y)))
			return -1;
		m = m / c * p[i];
		d = (d + mul(mul(m / p[i], ((a[i] - d) % m + m) % m, m), (x % m + m) % m, m)) % m;
		/* a[i] = a[i] - x * p[i]; */
		/* p[i] = p[i] / c * p[i - 1]; */
	}
	/* return a[n]; */
	return d >= mx ? d : d + m * ((mx - d - 1) / m + 1);
}


int main() {
	freopen("dragon1.in", "r", stdin);
	int T, m;
	ll t;
	scanf("%d", &T);
	while (T--) {
		init();
		scanf("%d%d", &n, &m);
		rep (i, 1, n)
			scanf("%lld", a + i);
		rep (i, 1, n)
			scanf("%lld", p + i);
		rep (i, 1, n)
			scanf("%lld", s + i);
		rep (i, 1, m)
			scanf("%lld", &t), w.insert(t);
		printf("%lld\n", work());
	}
}
