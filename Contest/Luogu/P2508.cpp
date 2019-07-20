#include <bits/stdc++.h>
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
long long ans, r;

long long gcd(long long a, long long b)
{
	return !b ? a : gcd(b, a % b);
}

int main()
{
	scanf("%lld", &r);
	rep(i, 1, (int)sqrt(2 * r))
	{
		if ((2 * r) % i == 0)
			// rep(j, 1, (int)sqrt(2 * r / i))
			for (int j = 1; j <= (int)sqrt(2 * r / i); j++)
				if (gcd(j, sqrt((2 * r) / i) - j * j) == 1 && j < 2 * r - j)
					ans++;
	}
	printf("%lld", ans * 4 + 4);
	return 0;
}