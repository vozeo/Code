#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for(int i_ = (s_); i_ <= (t_); ++i_)

const int M = 2005, N = 205;
int S, T, d[N];

struct Edge *head[N];
struct Edge {
	int u, v, c;
	Edge *nxt, *rev;

	Edge() {}
	Edge(int x, int y, int w) : u(x), v(y), c(w), nxt(head[x]) {
		head[x] = this;
	}
} epool[M << 1], *cur[N], *ecur = epool; //double it

void init() {}

void add(int x, int y, int w) {
	new (++ecur) Edge(x, y, w);
	ecur->rev = ecur + 1;
	new (++ecur) Edge(y, x, 0);
	ecur->rev = ecur - 1;
}

bool bfs() {
	memset(d, -1, sizeof(d));
	queue<int> q;
	q.push(S);
	d[S] = 0;
	while (!q.empty()) {
		int u = q.front(), v;
		q.pop();
		cur[u] = head[u];
		for (Edge *e = head[u]; e; e = e->nxt)
			if (e->c && d[v = e->v] == -1) {
				d[v] = d[u] + 1;
				q.push(v);
			}
	}
	return d[T] >= 0; // if can 
}

int dfs(int u, int f) {
	if (u == T)
		return f;
	int r = f, v, p;
	for (Edge *e = cur[u]; e; e = e->nxt)
		if (e->c && d[v = e->v] == d[u] + 1) {
			p = dfs(v, min(r, e->c));
			e->c -= p;
			e->rev->c += p;
			if (!(r -= p))
				return f; // rest flow is zero
		}
	d[u] = -1; // has used, save time
	return f - r; // used flow
}

map<string, int> c;
string st;
const int g[6][6] =
{0, 0, 0, 0, 0, 0,
 0, 0, 1, 1, 0, 0,
 0, 0, 0, 1, 0, 1,
 0, 0, 0, 0, 1, 1,
 0, 1, 1, 0, 0, 0,
 0, 1, 0, 0, 1, 0};
int a[N], b[N], ha[N], hb[N];


int main() {
	int n, m, ans = 0, J = 0;
	scanf("%d%d", &n, &m);
	S = 1, T = 2 * n + 2;
	c["J"] = 1, c["HK"] = 2, c["W"] = 3, c["YYY"] = 4, c["E"] = 5; 
	rep (i, 1, n) {
		cin >> st;
		a[i] = c[st];
	}
	rep (i, 1, n) {
		cin >> st;
		b[i] = c[st];
	}
	rep (i, 1, n) {
		scanf("%d", ha + i);
		if (a[i] == 4)
			J++;
	}
	rep (i, 1, n)
		if (a[i] == 1)
			ha[i] += J;
	J = 0;
	rep (i, 1, n) {
		scanf("%d", hb + i);
		if (b[i] == 4)
			J++;
	}
	rep (i, 1, n)
		if (b[i] == 1)
			hb[i] += J;
	rep (i, 2, n + 1) {
		add(S, i, ha[i - 1]);
		rep (j, n + 2, n * 2 + 1)
			if (g[a[i - 1]][b[j - n - 1]])
				add(i, j, 1);
	}
	rep (i, n + 2, 2 * n + 1)
		add(i, T, hb[i - n - 1]);
	while(bfs())
		ans += dfs(S, INT_MAX); // if T can be arrived, dfs
	printf("%d\n", min(m, ans));
	return 0;
}
