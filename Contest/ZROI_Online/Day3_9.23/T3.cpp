#include <bits/stdc++.h>
using namespace std;
#define rep(i_,s_,t_) for(int i_=(s_);i_<=(t_);i_++)
typedef long long ll;

ll sum, n, m, s, t, a[100005];

ll read()
{
	ll x = 0;
	char c = getchar();
	while (!isdigit(c))
		c = getchar();
	while (isdigit(c))
		x = x * 10 + c - '0', c = getchar();
	return x;
}

int main()
{
	scanf("%lld%lld%lld%lld", &n, &m, &s, &t);
	rep (i, 1, n)
		a[i] = read();
	const long long MOD = 1 << m;
	rep (i, 1, t)
	{
		int tot = 0;
		rep (j, 1, n)
		{
			a[i] = (a[i] + 1) % MOD;
			tot ^= a[i];
		}
		if (tot == s)
			sum++;
	}
	printf("%lld", sum);
	return 0;
}
