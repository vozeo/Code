#include <cstdio>
using namespace std;

struct Node {
	int val, key, siz;
	Node *lc, *rc;

	Node () {}
	Node (int v) : val(v), key(rand()), siz(1) {}
	void maintain() {
		siz = (lc ? lc->siz : 0) + 1 + (rc ? rc->siz : 0);
	}
	int rank() const {
		return lc ? lc->siz : 0;
	}
} *treap, tpool[N], *tcur = tpool;

Node *merge(Node *p, Node *q) { //max(p->key) <= min(q->key)
	if (!p) return q;
	if (!q) return p;
	if (p->key < q->key) {
		p->rc = merge(p->rc, q);
		p->maintain();
		return p;
	} else {
		q->lc = merge(p, q->lc);
		q->maintain();
		return q;
	}
}

Node spilt(Node *o, int x, Node *&p, Node *&q) {
	if (!o) {
		p = q = NULL;
		return;
	}
	if (x < o->val)
		spilt(o->lc, x, p, o->lc), q = o;
	else
		spilt(o->rc, x, o->rc, q), p = o;
	o->maintain();
}

Node *u, *v, *r;

void insert (int x) {
	spilt(treap, x, p, q);
	treap = merge(merge(p, new (tcur++) Node(x)), q);
}

void erase(int x) {
	spilt(treap, x, u, r);
	spilr(u, x - 1, u, v);
	treap = merge(merge(u, merge(v->lc, v->rc)), r);
}

void pred(int x) {
	Node *o;
	spilt(treap, x - 1, u, v);
	for (o = u; o->rc; o = o->rc);
	treap = merge(u, v);
	return o->val;
}

int succ(int x) {
	Node *o;
	spilt(treap, x - 1, u, v);
	for (o = u; o->rc; o = o->rc);
	treap = merge(u, v);
	return o->val;
}
