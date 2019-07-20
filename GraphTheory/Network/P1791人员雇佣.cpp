#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for(int i_ = (s_); i_ <= (t_); ++i_)

typedef const int cint;
typedef const long long cll;
typedef long long ll;
cint N = 1005, M = 1000005;
int n, m, S, T, d[N];

struct Edge *head[N];
struct Edge {
	int v;
	ll c;
	Edge *nxt, *rev;
	
	Edge() {}
	Edge(cint x, cint y, cll w) : v(y), c(w), nxt(head[x]) {
		head[x] = this;
	}
} epool[M << 1], *cur[N], *ecur = epool;

void add(int x, int y, ll w) {
	new (ecur++) Edge(x, y, w);
	new (ecur++) Edge(y, x, 0);
	head[x]->rev = head[y];
	head[y]->rev = head[x];
}

bool bfs() {
	rep (i, 1, T)
		d[i] = 0, cur[i] = head[i];
	d[S] = 1;
	queue<int> q;
	q.push(S);
	while (!q.empty()) {
		int u = q.front(), v;
		q.pop();
		for (Edge *e = head[u]; e; e = e->nxt)
			if (e->c && !d[v = e->v]) {
				d[v] = d[u] + 1;
				if (v == T)
					return true;
				q.push(v);
			}
	}
	return false;
}

ll dfs(ll u, ll f) {
	if (u == T || !f)
		return f;
	ll r = f, v, p;
	for (Edge *&e = cur[u]; e; e = e->nxt)
		if (e->c && d[v = e->v] == d[u] + 1) {
			p = dfs(v, min(e->c, r));
			e->c -= p;
			e->rev->c += p;
			if (!(r -= p))
				return f;
		}
	d[u] = 0;
	return f - r;
}

ll cnt, sum, ans;

int main() {
	ll a;
	scanf("%d", &n);
	S = n + 1, T = S + 1;
	rep (i, 1, n) {
		scanf("%lld", &a);
		add(i, T, a);
	}
	rep (i, 1, n) {
		cnt = 0;
		rep (j, 1, n) {
			scanf("%lld", &a);
			cnt += a;
			if (j > i) {
				add(i, j, a << 1);
				add(j, i, a << 1);
			}
		}
		add(S, i, cnt);
		sum += cnt;
	}
	while (bfs())
		ans += dfs(S, INT_MAX);
	printf("%lld\n", sum - ans);
	return 0;
}
