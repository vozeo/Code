#include <cstdio>
#include <algorithm>

int ret;
const int N = 100005;

struct Node {
	int len, v, tag;
	Node *lc, *rc;
	Node() {}
	Node(int x) : len(1), v(x), tag(0), lc(NULL), rc(NULL) {}
	Node(int l, Node *a, Node *b) : len(l), tag(0), lc(a), rc(b) {
		maintain();
	}
	void maintain() {
		v = lc->v + rc->v;
	}
	void rev() {
		v = len - v;
		tag ^= 1;
	}
	void pushdown() {
		if (tag) {
			lc->rev();
			rc->rev();
			tag = 0;
		}
	}
	void modify(int nl, int nr, int l, int r) {
		if (l <= nl && nr <= r) {
			rev();
			return;
		}
		pushdown();
		int mid = (nl + nr) >> 1;
		if (l <= mid)
			lc->modify(nl, mid, l, r);
		if (r > mid)
			rc->modify(mid + 1, nr, l, r);
		maintain();
	}
	void query(int nl, int nr, int l, int r) {
		if (l <= nl && nr <= r) {
			ret += v;
			return;
		}
		pushdown();
		int mid = (nl + nr) >> 1;
		if (l <= mid)
			lc->query(nl, mid, l, r);
		if (r > mid)
			rc->query(mid + 1, nr, l, r);
	}
} tpool[N << 1], *tcur = tpool, *root;

Node *build(int l, int r) {
	if (l == r)
		return new (tcur++) Node(0);
	int mid = (l + r) >> 1;
	return new (tcur++) Node(r - l + 1, build(l, mid), build(mid + 1, r));
}

int main() {
	int n, m, c, a, b;
	scanf("%d%d", &n, &m);
	root = build(1, n);
	for (int i = 1; i <= m; ++i) {
		scanf("%d%d%d", &c, &a, &b);
		if (c)
			ret = 0, root->query(1, n, a, b), printf("%d\n", ret);
		else
			root->modify(1, n, a, b);
	}
	return 0;
}
