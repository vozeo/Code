#include <bits/stdc++.h>
using namespace std;
#define rep(i, s, t) for (int i = (s); i <= (t); ++i)
const int N = 5e5 + 5;
int ret, a[N], q;
bool flag;
struct Node{
	int v;
	Node *lc, *rc;
	Node() {}
	Node(Node *x) { *this = *x; }
	Node(Node *l, Node *r) : v(0), lc(l), rc(r) {}
	void maintain() { v = lc->v + rc->v; }
} epool[N * 20], *ecur = epool, *root[N];

void query(Node *p, Node *o, int l, int r, int k) {
	if (l == r) {
		if (o->v - p->v >= q)
			ret = l;
		return;
	}
	int mid = (l + r) >> 1, x = o->lc->v - p->lc->v;
	if (k <= x)
		query(p->lc, o->lc, l, mid, k);
	else
		query(p->rc, o->rc, mid + 1, r, k - x);
}

void modify(Node *p, Node *&o, int l, int r, int k) {
	if (ecur >= &epool[N * 20 - 5])
		exit(0);
	o = new (ecur++) Node(p);
	if (l == r) {
		o->v++;
		return;
	}
	int mid = (l + r) >> 1;
	if (k <= mid)
		modify(p->lc, o->lc, l, mid, k);
	else
		modify(p->rc, o->rc, mid + 1, r, k);
	o->maintain();
}

Node *build(int l, int r) {
	if (l == r)
		return new (ecur++) Node();
	int mid = (l + r) >> 1;
	return new (ecur++) Node(build(l, mid), build(mid + 1, r));
}

int main() {
	freopen("P3567.in", "r", stdin);
	int n, m, ql, qr;
	scanf("%d%d", &n, &m);
	root[0] = build(1, n);
	rep (i, 1, n) {
		scanf("%d", &a[i]);
		modify(root[i - 1], root[i], 1, n, a[i]);
	}
	rep (i, 1, m) {
		scanf("%d%d", &ql, &qr);
		q = (qr - ql + 1) >> 1;
		ret = 0, query(root[ql - 1], root[qr], 1, n, q += 1);
		printf("%d\n", ret);
	}
}
