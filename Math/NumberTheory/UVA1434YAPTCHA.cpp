#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
typedef long long ll;

const int N = 3e6 + 15, M = 1e6;
int pri[M], s[M + 5];
bool vis[N];

int qpow(int x, int b, int p) {
	int ans = 1;
	for (; b; b >>= 1, x = 1LL * x * x % p)
		if (b & 1)
			ans = 1LL * ans * x % p;
	return ans;
}

int main() {
	int T, p, cnt = 0;
	rep (i, 2, N - 5) {
		if (!vis[i])
			pri[++cnt] = i;
		rep (j, 1, cnt) {
			if (i * pri[j] > N - 5)
				break;
			vis[i * pri[j]] = true;
			if (i % pri[j] == 0)
				break;
		}
	}
	rep (i, 1, M)
		s[i] = s[i - 1] + (vis[i * 3 + 7] ? 0 : 1);
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &p);
		printf("%d\n", s[p]);
	}
}
