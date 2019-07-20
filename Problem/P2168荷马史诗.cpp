#include <cstdio>
#include <queue>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= t_; ++i_)
typedef long long ll;
typedef const long long cll;
typedef const int cint;

struct Node {
	ll w;
	int h;
	Node() {}
	Node(cll x, cint y) : w(x), h(y) {}

	bool operator <(const Node &rhs) const {
		return w == rhs.w ? h > rhs.h : w > rhs.w;
	}
};

priority_queue<Node> q;

int main() {
	int n, k, x;
	ll ans = 0;
	scanf("%d%d", &n, &k);
	rep (i, 1, n) {
		scanf("%d", &x);
		q.push(Node(x, 1));
	}
	while ((q.size() - 1) % (k - 1) != 0)
		q.push(Node(0, 1));
	while (q.size() > 1) {
		int h = 0;
		ll w = 0;
		rep (i, 1, k) {
			Node y = q.top();
			q.pop();
			h = max(h, y.h);
			w += y.w;
		}
		ans += w;
		q.push(Node(w, h + 1));
	}
	printf("%lld\n%d\n", ans, q.top().h - 1);
	return 0;
}
