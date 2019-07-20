#include <bits/stdc++.h>
typedef long long ll;

ll a[100010], b[100010];

inline ll exgcd(ll a, ll b, ll &x, ll &y)
{
	if (!b)
	{
		x = 1, y = 0;
		return a;
	}
	ll d = exgcd(b, a % b, y, x);
	y -= (a / b) * x;
	return d;
}

inline ll qmul(ll a, ll b, ll mod)
{
	ll ans = 0;
	while (b > 0)
	{
		if (b & 1)
			ans = (ans + a) % mod;
		a = (a + a) % mod;
		b >>= 1;
	}
	return ans;
}

int main()
{
	//freopen("testdata.in", "r", stdin);
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
		scanf("%lld%lld", &b[i], &a[i]);

	for (int i = 2; i <= n; ++i)
	{
		ll m, p;
		ll d = exgcd(b[i - 1], b[i], m, p);
		ll bg = b[i] / d;
		ll c = ((a[i] - a[i - 1]) % b[i] + b[i]) % b[i];
		m = qmul(m, c / d, bg);
		m = (m % bg + bg) % bg;

		//printf("%lld\n", m);
		//else m= m*c%bg
		//a[i] = m * b[i - 1] + a[i - 1];
		b[i] *= b[i - 1] / d;
		a[i] = qmul(m, b[i - 1], b[i]);

		a[i] = (a[i] % b[i] + b[i] + a[i - 1]) % b[i];
	}
	printf("%lld", a[n]);
}