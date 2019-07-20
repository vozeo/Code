#include <cstdio>
#include <iostream>
#include <cstdilb>
using namespace std;

const int N = 100005;

struct Node {
	int val, size;
	Node *lc, *rc;
	bool rev;

	Node () {}
	Node (int v, Node *l, Node *r) : val(v), lc(l), rc(r), rev(false) {
		maintain();
	}
	void reverse() {
		swap(lc, rc);
		rev ^= 1;
	}
	void pushdown() {
		if (rev) {
			if (lc) lc->reverse();
			if (rc) rc->reverse();
			rev = false;
		}
	}
	void maintain() {
		size = (lc ? lc->size : 0) + 1 + (rc ? rc->size : 0);
	}
	void print() {
		pushdown();
		if (lc) lc->print();
		printf("%d ", val);
		if (rc) rc->print();
	}
} *treap, tpool[N], *tcur = tpool;

int size(const Node *u) {
	return u ? u->size : 0;
}

Node *build(int l, int r) {
	if (l > r) return NULL;
	int mid = (l + r) >> 1;
	return new (tcur++) Node(mid, build(l, mid - 1), build(mid + 1, r));
}

Node *merge(Node *a, Node *b) {
	if (!a) return b;
	if (!b) return a;
	if (rand() % (a->size + b->size) < a->size) {
		a->pushdown();
		a->rc = merge(a->rc, b);
		a->maintain();
		return a;
	} else {
		b->pushdown();
		b->lc = merge(a, b->lc);
		b->maintain();
		return b;
	}
}

typedef pair<Node *, Node *> Droot;

Droot spilt(Node *u, int pos) {
	Droot res(NULL, NULL);
	if (!u) return res;
	u->pushdown();
	if (pos <= size(u->lc)) {
		res = spilt(u->lc, pos);
		u->lc = res.second;
		u->maintain();
		res.second = u;
	} else {
		res = spilt(u->rc, pos - size(u->lc) - 1);
		u->rc = res.first;
		u->maintain();
		res.first = u;
	}
	return res;
}

void reverse(int l, int r) {
	Droot nl = spilt(treap, l - 1), nr = spilt(nl.second, r - l + 1);
	nr.first->reverse();
	treap = merge(merge(nl.first, nr.first), nr.second);
}

int main() {
	int n, m, l, r;
	scanf("%d%d", &n, &m);
	treap = build(1, n);
	for (int i = 1; i <= m; ++i) {
		scanf("%d%d", &l, &r);
		reverse(l, r);
	}
	treap->print();
	return 0;
}
