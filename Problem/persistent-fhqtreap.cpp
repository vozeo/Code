#include <cstdio>
#include <algorithm>
using namespace std;

const int N = 200005;

int rand() {
	static int seed = 703;
	return seed = 48271LL * seed % 2147483647;
}

struct Node {
	int v, key, siz;
	Node *lc, *rc;
	Node() {}
	Node(const int val) : v(val), key(rand()), siz(1) {}
	Node(const Node *x) { *this = *x; }
	void maintain() {
		siz = (lc ? lc->siz : 0) + 1 + (rc ? rc->siz : 0);
	}
	int rank() {
		return lc ? lc->siz : 0;
	}
} tpool[N], *tcur = tpool, *root[N];

Node *merge(Node *p, Node *q) {
	if (!p)
		return q;
	if (!q)
		return p;
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

void split(int x, Node *o, Node *&p, Node *&q) {
	if (!o) {
		p = new (tcur++) Node(), q = new (tcur++) Node();
		return;
	}
	if (x >= o->v)
		p = new (tcur++) Node(o), split(x, p->rc, p->rc, q), p->maintain();
	else
		q = new (tcur++) Node(o), split(x, q->lc, p, q->lc), q->maintain();
}

struct Treap {
	Node *p, *q, *r;
	int res, d;
	void insert(int x) {
		split(x, root[d], p, q);
		root[d] = merge(merge(p, new (tcur++) Node(x)), q);
	}
	void erase(int x) {
		split(x, root[d], p, r);
		split(x - 1, p, p, q);
		root[d] = merge(merge(p, merge(q->lc, q->rc)), r);
	}
	int rank(int x) {
		split(x - 1, root[d], p, q);
		res = p ? p->siz : 0;
		root[d] = merge(p, q);
		return res + 1;
	}
	int kth(Node *o, int k) {
		while (true) {
			if (k <= o->rank())
				o = o->lc;
			else if (k == o->rank() + 1)
				return o->v;
			else
				k -= o->rank() + 1, o = o->rc;
		}
	}
	int pre(int x) {
		split(x - 1, root[d], p, q);
		res = kth(p, p->siz);
		//for (o = p; o->rc; o = o->rc);
		root[d] = merge(p, q);
		return res;
	}
	int suc(int x) {
		split(x, root[d], p, q);
		res = kth(q, 1);
		//for (o = q; o->lc; o = o->lc);
		root[d] = merge(p, q);
		return res;
	}
} T;

int main() {
	//freopen("testdata.in", "r", stdin);
	//freopen("answer.out", "w", stdout);
	int n, op, x, v;
	scanf("%d", &n);
	root[0] = new Node();
	for (int i = 1; i <= n; ++i) {
		scanf("%d%d%d", &v, &op, &x);
		root[i] = new Node();
		T.d = i, *root[i] = *root[v];
		if (op == 1)
			T.insert(x);
		if (op == 2)
			T.erase(x);
		if (op == 3)
			printf("%d\n", T.rank(x));
		if (op == 4)
			printf("%d\n", T.kth(root[i], x));
		if (op == 5)
			printf("%d\n", T.pre(x));
		if (op == 6)
			printf("%d\n", T.suc(x));
	}
	return 0;
}
