#include <bits/stdc++.h>
using namespace std;
#define debug printf("%d %s\n",__LINE__,__FUNCTION__)

typedef long long ll;
ll d;

ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
bool chk(ll a, ll b) { return !(a % d) && !(b % d); }

int main() {
	int T;
	ll a, b, m, n;
	scanf("%d", &T);
	while (T--) {
		scanf("%lld%lld%lld%lld", &a, &b, &m, &n);
		d = gcd(a, b) << 1;
		if (chk(m, n) || chk(m + a, n + b) || chk(m + b, n + a) || chk(m + a + b, n + a + b))
			printf("Y\n");
		else
			printf("N\n");
	}
}
