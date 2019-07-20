#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

struct Node {
	int l, r;
	mutable int v;
	Node() {}
	Node(int x, int y = -1, int z = 0) : l(x), r(y), v(z) {}
	bool operator < (const Node &rhs) const { 
		return l < rhs.l;
	}
};

set<Node> s;
typedef set<Node>::iterator Iter; // NOT operator

Iter split(int p) {
	Iter it = s.lower_bound(Node(p));
	/* if (it->l == p && it != s.end()) // *** */
	if (it != s.end() && it->l == p)  // ***
		return it;
	--it;
	int l = it->l, r = it->r, v = it->v;
	s.erase(it);
	s.insert(Node(l, p - 1, v));
	return s.insert(Node(p, r, v)).first;
}

void assign(int l, int r, int v) {
	Iter itr = split(r + 1), itl = split(l);
	s.erase(itl, itr);
	s.insert(Node(l, r, v));
}

void reverse(int l, int r) {
	Iter itr = split(r + 1), itl = split(l);
	for (; itl != itr; ++itl)
		itl->v ^= 1;
}

int sum(int l, int r) {
	int ans = 0;
	Iter itr = split(r + 1), itl = split(l);
	for (; itl != itr; ++itl)
		if (itl->v)
			ans += itl->r - itl->l + 1;
	return ans;
}

int query(int l, int r) {
	int lst = 0, ans = 0, tot = 0;
	Iter itr = split(r + 1), itl = split(l);
	for (; itl != itr; ++itl) {
		if (itl->v) {
			tot = lst * tot + itl->r - itl->l + 1;
			ans = max(ans, tot); 
		}
		lst = itl->v;
	}
	return ans;
}

int main() {
	int n, m, op, x, y;
	scanf("%d%d", &n, &m);
	rep (i, 0, n - 1) {
		scanf("%d", &x);
		s.insert(Node(i, i, x));
	}
	rep (i, 1, m) {
		scanf("%d%d%d", &op, &x, &y);
		if (op == 0)
			assign(x, y, 0);
		else if (op == 1)
			assign(x, y, 1);
		else if (op == 2)
			reverse(x, y);
		else if (op == 3)
			printf("%d\n", sum(x, y));
		else
			printf("%d\n", query(x, y));
	}
}
