#include <cstdio>
#include <algorithm>
#include <cctype>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

typedef long long ll;
const int N = 200005;
int tot, ret, a[N], b[N];

struct Node {
	int v;
	Node *lc, *rc;
	Node() {}
	Node(int x) : v(x), lc(NULL), rc(NULL) {}
	Node(Node *x, Node *y) : lc(x), rc(y) {}
	Node(Node *x) { *this = *x; }
	void maintain() { v = lc->v + rc->v; }
} tpool[N << 5], *tcur = tpool, *root[N];

void modify(Node *p, Node *&o, int l, int r, int x) {
	o = new (tcur++) Node(p);
	if (l == r) {
		o->v++;
		return;
	}
	int mid = (l + r) >> 1;
	if (x <= mid)
		modify(p->lc, o->lc, l, mid, x);
	else
		modify(p->rc, o->rc, mid + 1, r, x);
	o->maintain();
}

void query(Node *p, Node *o, int l, int r, int k) {
	if (l == r) {
		ret = l;
		return;
	}
	int t = o->lc->v - p->lc->v, mid = (l + r) >> 1;
	if (k <= t)
		query(p->lc, o->lc, l, mid, k);
	else
		query(p->rc, o->rc, mid + 1, r, k - t);
}

Node *build(int l, int r) {
	if (l == r)
		return new (tcur++) Node(0);
	int mid = (l + r) >> 1;
	return new (tcur++) Node(build(l, mid), build(mid + 1, r));
}

void read(int &x) {
	char c, f = 1;
	while (!isdigit(c = getchar()))
		if (c == '-')
			f = -1;
	for (x = c - '0'; isdigit(c = getchar()); x = x * 10 + c - '0');
	x *= f;
}

int main() {
	int n, m, l, r, k;
	//scanf("%d%d", &n, &m);
	read(n), read(m);
	for (int i = 1; i <= n; ++i)
		read(a[i]), b[i] = a[i];
	sort(a + 1, a + n + 1);
	tot = unique(a + 1, a + n + 1) - a - 1;
	rep (i, 1, n)
		b[i] = lower_bound(a + 1, a + tot + 1, b[i]) - a;
	root[0] = build(1, tot);
	rep (i, 1, n)
		modify(root[i - 1], root[i], 1, tot, b[i]);
	rep (i, 1, m) {
		scanf("%d%d%d", &l, &r, &k);
		ret = 0;
		query(root[l - 1], root[r], 1, tot, k);
		printf("%d\n", a[ret]);
	}
	return 0;
}
