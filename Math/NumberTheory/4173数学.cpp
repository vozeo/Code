#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int P = 998244353;

ll sieve(ll n) {
	ll ans = n, m = sqrt(n);
	for (ll i = 2; i <= m; ++i)
		if (n % i == 0) {
			ans = ans / i * (i - 1);
			while (n % i == 0)
				n /= i;
		}
	if (n > 1)
		ans = ans / n * (n - 1);
	return ans;
}

int main() {
	ll m, n;
	scanf("%lld%lld", &m, &n);
	printf("%lld\n", sieve(m) % P * (sieve(n) % P) % P * (m % P) % P * (n % P) % P);
}
