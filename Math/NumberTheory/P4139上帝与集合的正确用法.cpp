#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
typedef long long ll;

const int N = 1e7 + 5;
int phi[N];

int qpow(int x, int b, int p) {
	int ans = 1;
	for (; b; b >>= 1, x = 1LL * x * x % p)
		if (b & 1)
			ans = 1LL * ans * x % p;
	return ans;
}

int solve(int x) {
	if (x == 1)
		return 0;
	return qpow(2, solve(phi[x]) + phi[x], x);

}

int main() {
	int T, p;
	phi[1] = 1;
	rep (i, 2, N - 5)
		if (!phi[i])
			for (int j = i; j <= N - 5; j += i) {
				if (!phi[j])
					phi[j] = j;
				phi[j] = phi[j] / i * (i - 1);
			}
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &p);
		printf("%d\n", solve(p));
	}
}
