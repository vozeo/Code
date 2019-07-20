#include <cstdio>
#include <algorithm>
#include <climits>
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
} tpool[N * 60], *tcur = tpool, *root[N];

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
		//p = new (tcur++) Node(), q = new (tcur++) Node();
		p = q = NULL;
		return;
	}
	if (x >= o->v) {
		p = new (tcur++) Node(o);
		split(x, p->rc, p->rc, q);
		p->maintain();
	} else {
		q = new (tcur++) Node(o);
		split(x, q->lc, p, q->lc);
		q->maintain();
	}
	//o->maintain();
}

struct Treap {
	Node *p, *q, *r;
	int res;
	void insert(int d, int x) {
		split(x, root[d], p, q);
		root[d] = merge(merge(p, new (tcur++) Node(x)), q);
	}
	void erase(int d, int x) {
		split(x, root[d], p, r);
		split(x - 1, p, p, q);
		if (q)
			root[d] = merge(merge(p, merge(q->lc, q->rc)), r);
		else
			root[d] = merge(merge(p, q), r);
	}
	int rank(int d, int x) {
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
	int pre(int d, int x) {
		split(x - 1, root[d], p, q);
		if (!p)
			return -INT_MAX;
		res = kth(p, p->siz);
		root[d] = merge(p, q);
		return res;
	}
	int suc(int d, int x) {
		split(x, root[d], p, q);
		if (!q)
			return INT_MAX;
		res = kth(q, 1);
		root[d] = merge(p, q);
		return res;
	}
} T;

int main() {
	//freopen("testdata.in", "r", stdin);
	//freopen("answer.out", "w", stdout);
	int n, v, op, x;
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d%d%d", &v, &op, &x);
		if (root[v])
			root[i] = new (tcur++) Node(root[v]);
		if (op == 1)
			T.insert(i, x);
		if (op == 2)
			T.erase(i, x);
		if (op == 3)
			printf("%d\n", T.rank(i, x));
		if (op == 4)
			printf("%d\n", T.kth(root[i], x));
		if (op == 5)
			printf("%d\n", T.pre(i, x));
		if (op == 6)
			printf("%d\n", T.suc(i, x));
	}
	return 0;
}
