#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
typedef long long ll;

const int N = 1e5 + 5, P = 1e9 + 7;
int a[N];
ll seed;

ll qpow(ll o, int x, int mod) {
	ll res = 1;
	o %= mod; // ***
	for (; x; o = o * o % mod, x >>= 1)
		if (x & 1)
			res = res * o % mod;
	return res;
}

struct Node {
	int l, r;
	mutable ll v;
	Node() {}
	Node(int x, int y = -1, ll z = 0) : l(x), r(y), v(z) {}
	bool operator < (const Node &rhs) const {
		return l < rhs.l;
	}
};

typedef set<Node>::iterator Iter;
set<Node> s;

Iter split(int p) {
	Iter it = s.lower_bound(Node(p));
	if (it != s.end() && it->l == p)
		return it;
	it--;
	// ***
	int l = it->l, r = it->r;
	ll val = it->v;
	s.erase(it);
	s.insert(Node(l, p - 1, val));
	return s.insert(Node(p, r, val)).first;
}

void assign(int l, int r, ll v = 0) {
	Iter itr = split(r + 1), itl = split(l);
	s.erase(itl, itr);
	s.insert(Node(l, r, v));
}

void add(int l, int r, int val) {
	Iter itr = split(r + 1), itl = split(l);
	for (; itl != itr; ++itl)
		itl->v += val;
}

ll kth(int l, int r, int k) {
	vector<pair<ll, int> > t;
	Iter itr = split(r + 1), itl = split(l);
	t.clear();
	for (; itl != itr; ++itl)
		t.push_back(make_pair(itl->v, itl->r - itl->l + 1)); // ***
	sort(t.begin(), t.end());
	/* for (Iter it = t.begin(); it != t.end(); ++it) { */
	for (vector<pair<ll, int> >::iterator it = t.begin(); it != t.end(); ++it) {
		k -= it->second;
		if (k <= 0)
			return it->first;
	}
	return -1;
}

ll sum(int l, int r, int x, int mod) {
	Iter itr = split(r + 1), itl = split(l);
	ll ans = 0;
	for (; itl != itr; ++itl)
		ans = (ans + 1ll * (itl->r - itl->l + 1) * qpow(itl->v, x, mod) % mod) % mod;
	return ans;
}

int rnd() {
	ll ret = seed;
	seed = (seed * 7 + 13) % P;
	return ret;
}

int main() {
	freopen("CF896C.out", "w", stdout);
	int n, m, vmax, op, l, r, x, y = 0;
	scanf("%d%d%lld%d", &n, &m, &seed, &vmax);
	rep (i, 1, n) {
		a[i] = rnd() % vmax + 1;
		s.insert(Node(i, i, a[i]));
	}
	s.insert(Node(n + 1, n + 1, 0));
	rep (i, 1, m) {
		op = rnd() % 4 + 1;
		l = rnd() % n + 1;
		r = rnd() % n + 1;
		if (l > r)
			swap(l, r);
		if (op == 3)
			x = rnd() % (r - l + 1) + 1;
		else
			x = rnd() % vmax + 1;
		if (op == 4)
			y = rnd() % vmax + 1;
		if (op == 1)
			add(l, r, x);
		else if (op == 2)
			assign(l, r, x);
		else if (op == 3)
			printf("%lld\n", kth(l, r, x));
		else
			printf("%lld\n", sum(l, r, x, y));
	}
}









