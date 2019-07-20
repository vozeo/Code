#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ll n, k, ans = 0;
	scanf("%lld%lld", &n, &k);
	for (int l = 1, r; l <= n; l = r + 1) {
		r = k / l ? min(n, k / (k / l)) : n;
		ans += (k / l) * (r - l + 1) * (l + r) / 2;
	}
	printf("%lld\n", n * k - ans);
}
