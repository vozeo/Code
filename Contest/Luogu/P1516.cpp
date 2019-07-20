#include <bits/stdc++.h>
typedef long long ll;
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

int main()
{
	ll a, b, m, n, l, x, y;
	scanf("%lld%lld%lld%lld%lld", &a, &b, &m, &n, &l);
	m -= n;
	ll d = b - a;
	if (m < 0)
	{
		m = -m;
		d = -d;
	}
	ll c = exgcd(m, l, x, y);
	l /= c;
	if (d % c)
		printf("Impossible");
	else
		printf("%lld", ((x * d / c) % l + l) % l);
	return 0;
}