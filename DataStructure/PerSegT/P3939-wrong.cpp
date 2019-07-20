#include <bits/stdc++.h>
using namespace std;
#define rep(i, s, t) for (int i = (s); i <= (t); ++i)

const int N = 3e5 + 5;
int ret;

struct Node {
	int c;
	Node *lc, *rc;
	Node() {}
	Node(Node *x) { *this = *x; }
	Node(Node *l, Node *r) : c(0), lc(l), rc(r) {}
	void query(int k, int l, int r) {
		if (l == r)
			return (void)(ret = c);
		int mid = (l + r) >> 1;
		if (k <= mid)
			lc->query(k, l, mid);
		else
			rc->query(k, mid + 1, r);
	}
	void modify(int k, int l, int r, int x) {
		if (l == r)
			return (void)(ret = c);
		int mid = (l + r) >> 1;
		if (k <= mid)
			lc->query(k, l, mid);
		else
			rc->query(k, mid + 1, r);
	}
} tpool[N << 5], *tcur = tpool, *root[N];

void modify(Node *p, Node *&o, int k, int l, int r) {
	o = new (tcur++) Node(p);
	if (l == r)
		return (void)o->c++;
	int mid = (l + r) >> 1;
	if (k <= mid)
		modify(p->lc, o->lc, k, l, mid);
	else
		modify(p->rc, o->rc, k, mid + 1, r);
}

Node* build(int l, int r) {
	if (l == r)
		return new (tcur++) Node();
	int mid = (l + r) >> 1;
	return new (tcur++) Node(build(l, mid), build(mid + 1, r));
}

void read(int &x) {
	char c;
	while (!isdigit(c = getchar()));
	for (x = c - '0'; isdigit(c = getchar()); x = x * 10 + c - '0');
}

int main() {
	freopen("P3939.in", "r", stdin);
	int n, m, x, op, ans, l, r, tot = N - 5;
	read(n), read(m);
	root[0] = build(1, tot);
	rep (i, 1, n) {
		read(x);
		modify(root[i - 1], root[i], x, 1, tot);
	}
	rep (i, 1, m) {
		read(op);
		if (op == 1) {
			read(l), read(r), read(x);
			root[l - 1]->query(x, 1, tot), ans = ret;
			root[r]->query(x, 1, tot);
			printf("%d\n", ret - ans);
		} else {
			read(x);
			printf("%d", x);
			swap(root[x], root[x + 1]);
		}
	}
} 









