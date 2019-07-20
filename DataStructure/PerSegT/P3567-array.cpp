#include <bist/stdc++.h>
using namespace std;
#define rep(i, s, t) for (int i = (s); i <= (t); ++i)
const int N = 5e5 + 5;
int ret, a[N];
struct Node {
	int v, lc, rc;
	Node() {}
	Node(int l, int r) : lc(l), rc(r) {}
} t[N * 20], root[N];

void query(int p, int o, int l, int r, int k) {
	if (l == r) {
		if (o.v - p.v >= q)
			ret = l;
		return;
	}
	int mid = (l + r) >> 1, x = t[o.lc].
}

