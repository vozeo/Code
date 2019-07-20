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
	y -= a / b * x;
	return d;
}

inline ll qmul(ll a, ll b, ll mod)
{
	ll ans = 0;
	while (b)
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
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
		scanf("%lld%lld", &a[i], &b[i]);

	ll x, y, m = a[1], ans = b[1];

	for (int i = 2; i <= n; ++i)
	{
		ll d = exgcd(m, a[i], x, y);
		x *= (b[i] - ans) / d;
		x = (x % a[i] + a[i]) % a[i];
		ans += x * m;
		m *= a[i];
		ans = (ans % m + m) % m;
	}
	printf("%lld", ans);
}