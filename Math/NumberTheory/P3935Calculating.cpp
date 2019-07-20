#include <bits/stdc++.h>
using namespace std;
#define debug printf("%d %s\n",__LINE__,__FUNCTION__)

typedef long long ll;
const int P = 998244353;

ll cal(ll n) {
	ll ans = 0;
	for (ll l = 1, r; l <= n; l = r + 1) {
		r = n / (n / l);
		ans = (ans + (r - l + 1) % P * (n / l % P)) % P;
	}
	return ans;
}

int main() {
	ll l, r;
	scanf("%lld%lld", &l, &r);
	printf("%lld\n", (cal(r) - cal(l - 1) + P) % P);
}
