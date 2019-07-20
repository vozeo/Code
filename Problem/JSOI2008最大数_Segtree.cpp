/*******************************************************************************
 * Author		: Vozeo
 * Last modified: 2018-12-18 23:37
 * Filename		: P1198JSOI2008_Segtree.cpp
 * Description	: 
*******************************************************************************/
#include <bits/stdc++.h>
using namespace std;
const int N = 200005;
const int INF = 0x7fffffff;

int M;
long long n, cur = 0, t, MOD;
char c;

struct Node {
	Node *lc, *rc;
	int l, r;
	long long sum;

	Node () {}
	Node (int pos) : lc(NULL), rc(NULL), l(pos), r(pos), sum(-INF) {}
	Node (Node *lc, Node *rc) : lc(lc), rc(rc), l(lc->l), r(rc->r), sum(-INF) {}
	
	void modify(int l, int r, int x, long long d) {
		if (l == r) {
			this->sum = ((d + t) % MOD + MOD) % MOD;
			return;
		}
		int mid = (l + r) >> 1;
		if (x <= mid)
			lc->modify(l, mid, x, d);
		else
			rc->modify(mid + 1, r, x, d);
		sum = max(lc->sum, rc->sum);
	}

	long long query(int l, int r) {
		if (l > this->r || r < this->l)
			return -INF;
		if (l <= this->l && r >= this->r)
			return sum;
		return max(lc->query(l, r), rc->query(l, r));
	}
} *root = NULL, tpool[N << 1], *tcur = tpool;

Node *build(int l, int r)
{
	if (l == r)
		return new(tcur++) Node(l);
	int mid = l + ((r - l) >> 1);
	return new(tcur++) Node(build(l, mid), build(mid + 1, r));
}

int main() {
	scanf("%d%lld", &M, &MOD);
	root = build(1, M);
	for (int i = 1; i <= M; ++i) {
		c = 0;
		while(c != 'A' && c != 'Q')
			c = getchar();
		scanf("%lld", &n);
		if (c == 'A')
			cur++, root->modify(1, M, cur, n);
		else
			printf("%lld\n", t = root->query(cur - n + 1, cur));
	}
	return 0;
}
