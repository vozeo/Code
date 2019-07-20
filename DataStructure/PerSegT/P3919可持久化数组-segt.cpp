#include <cstdio>
#include <algorithm>

typedef long long ll;
const int N = 100005;
int lo, ret, a[N];

struct Node {
	int v;
	Node *lc, *rc;
	Node() {}
	Node(int x) : v(x), lc(NULL), rc(NULL) {}
	Node(Node *x, Node *y) : lc(x), rc(y) {}
	Node(Node *x) { *this = *x; }
	void query(int l, int r) {
		if (l == r) {
			ret = v;
			return;
		}
		int mid = (l + r) >> 1;
		if (lo <= mid)
			lc->query(l, mid);
		else
			rc->query(mid + 1, r);
	}
} tpool[N << 5], *tcur = tpool, *root[N];

void modify(Node *p, Node *&o, int l, int r, int x) {
	o = new (tcur++) Node(p);
	if (l == r) {
		o->v = x;
		return;
	}
	int mid = (l + r) >> 1;
	if (lo <= mid)
		modify(p->lc, o->lc, l, mid, x);
	else
		modify(p->rc, o->rc, mid + 1, r, x);
}

Node *build(int l, int r) {
	if (l == r)
		return new (tcur++) Node(a[l]);
	int mid = (l + r) >> 1;
	return new (tcur++) Node(build(l, mid), build(mid + 1, r));
}

int main() {
	int n, m, v, op, k;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i)
		scanf("%d", a + i);
	root[0] = build(1, n);
	for (int i = 1; i <= m; ++i) {
		scanf("%d%d%d", &v, &op, &lo);
		root[i] = new (tcur++) Node(root[v]);
		if (op == 1) {
			scanf("%d", &k);
			modify(root[v], root[i], 1, n, k);
		} else
			ret = 0, root[i]->query(1, n), printf("%d\n", ret);
	}
	return 0;
}
