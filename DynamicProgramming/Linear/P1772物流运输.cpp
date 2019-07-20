#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

const int N = 25, M = 505;
int n, d, dis[N];
long long f[105], co[105][105];
bool bl[N], s[N][105];

struct Edge *head[N];
struct Edge{
	int v, w;
	Edge *nxt;
	Edge() {}
	Edge(int x, int y, int z) : v(y), w(z), nxt(head[x]) {
		head[x] = this;
	}
} epool[M << 1], *ecur = epool;

void add(int x, int y, int z) {
	new (ecur++) Edge(x, y, z);
}

int dij(int x, int y) {
	memset(bl, 0, sizeof bl);
	rep (i, x, y)
		rep (j, 1, n)
			if (s[j][i])
				bl[j] = true;
	memset(dis, 0x3f, sizeof dis);
	dis[1] = 0;
	priority_queue<pair<int, int> > q;
	q.push(make_pair(1, 0));
	while (!q.empty()) {
		int u = q.top().first, v;
		q.pop();
		for (Edge *e = head[u]; e; e = e->nxt)
			if (dis[v = e->v] > dis[u] + e->w && !bl[v]) {
				dis[v] = dis[u] + e->w;
				q.push(make_pair(v, -dis[v]));
			}
	}
	return dis[n];
}


int main() {
	int t, m, x, y, z, h;
	scanf("%d%d%d%d", &d, &n, &t, &m);
	rep (i, 1, m) {
		scanf("%d%d%d", &x, &y, &z);
		add(x, y, z), add(y, x, z);
	}
	scanf("%d", &h);
	rep (i, 1, h) {	
		scanf("%d%d%d", &x, &y, &z);
		rep (j, y, z)
			s[x][j] = true;
	}
	rep (i, 1, d)
		rep (j, i, d)
			co[i][j] = dij(i, j);
	memset(f, 0x3f, sizeof f);
	rep (i, 1, d)
		f[i] = co[1][i] * i;
	rep (i, 1, d)
		rep (j, 1, i - 1)
			f[i] = min(f[i], f[j] + 1ll * co[j + 1][i] * (i - j) + t);
	printf("%lld\n", f[d]);
}
