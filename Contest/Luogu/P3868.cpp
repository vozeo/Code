#include <bits/stdc++.h>
typedef long long ll;

int n;
ll ans, M = 1, a[15], b[15];

inline void exgcd(ll a, ll b, ll &x, ll &y)
{
	if (!b)
	{
		x = 1, y = 0;
		return;
	}
	exgcd(b, a % b, y, x);
	y -= (a / b) * x;
}

inline ll qmul(ll a, ll b)
{
	ll ans = 0;
	while (b)
	{
		if (b & 1)
			ans = (ans + a) % M;
		a = 2 * a % M;
		b >>= 1;
	}
	return ans;
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
		scanf("%lld", &a[i]);
	for (int i = 1; i <= n; ++i)
	{
		scanf("%lld", &b[i]);
		M *= b[i];
	}
	for (int i = 1; i <= n; ++i)
	{
		ll x, y, m = M / b[i];
		exgcd(m, b[i], x, y);
		//std::cout << x << std::endl;
		x = (x % b[i] + b[i]) % b[i];
		ll cnt = (a[i] % M + M) % M;
		cnt = qmul(cnt, m);
		cnt = qmul(cnt, x);
		ans += cnt;
		ans %= M;
	}
	//printf("%lld\n", M);
	printf("%lld", (ans + M) % M);
}