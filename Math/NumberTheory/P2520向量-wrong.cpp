#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define debug printf("%d %s\n",__LINE__,__FUNCTION__)

ll exgcd(ll a, ll b, ll &x, ll &y) {
	if (!b) {
		x = 1, y = 0;
		return a;
	}
	ll d = exgcd(b, a % b, y, x);
	y -= (a / b) * x;
	return d;
}

int main() {
	ll a, b, m, n, d, x1, x2, y1, y2;
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%lld%lld%lld%lld", &a, &b, &m, &n);
		d = exgcd(a, b, x1, y1);
		if (m % d) {
			printf("N\n");
			continue;
		}
		x1 = x1 / d * m, y1 = y1 / d * m;
		printf("d = %lld, x = %lld, y = %lld\n", d, x1, y1);
	 	d = exgcd(a, b, x2, y2);
		if (n % d) {
			printf("N\n");
			continue;
		}
		x2 = x2 / d * n, y2 = y2 / d * n;
		printf("d = %lld, x = %lld, y = %lld\n", d, x2, y2);
		if (abs(x1 - x2) % 2 || abs(y1 - y2) % 2)
			printf("N\n");
		else
			printf("Y\n");
	}
}
