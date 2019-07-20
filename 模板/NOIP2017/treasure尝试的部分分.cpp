#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>
#define rep(i_, s_, t_) for(int i_ = (s_); i_ <= (t_); ++i_)
using namespace std;
typedef long long ll;
typedef const int cint;

int n, m, len, cur, fa[20], d[20], g[20][20];
ll cnt, mn;
bool vis[1005];

struct Edge *head[20];
struct Edge
{
	int u, v, w;
	Edge *nxt;
	Edge() {}
	Edge(cint x, cint y, cint z) : u(x), v(y), w(z), nxt(head[x]) { head[x] = this; }
} epool[1005], *ecur = epool;

inline void add(int u, int v, int w)
{
	*(ecur++) = Edge(u, v, w);
}

int find(int a)
{
	while (a != fa[a])
		a = fa[a] = fa[fa[a]];
	return a;
}

void work(int x)
{
	priority_queue<pair<int, int> > q;
	memset(vis, 0, sizeof(vis));
	memset(g, 0, sizeof(g));
	memset(d, 0, sizeof(d));
	int v, t;
	cnt = 0;
	rep (i, 1, n)
		fa[i] = i;
	
	q.push(make_pair(d[x] = 0, x));
	while(!q.empty())
	{
		int u = q.top().second;
		q.pop();
		if (vis[u])
			continue;
		vis[u] = true;
		for (Edge *e = head[u]; e; e = e->nxt)
			if (d[v = e->v] > (t = d[u] + e->w))
				q.push(make_pair(-(d[v] = t), v));
	}

	for (Edge *e = epool; e <= ecur; ++e)
		if (d[e->v] == d[e->u] + 1)
		{
			int a, b;
			if ((a = find(e->u)) != (b = find(e->v)))
				g[e->u][e->v] = 1, fa[a] = b;
		}
	
	memset(vis, 0, sizeof(vis));
	queue<pair<int, int> > q2;
	q2.push(make_pair(x, 1));
	while (!q2.empty())
	{
		int u = q2.front().first, num = q2.front().second;
		q.pop();
		if (vis[u])
			continue;
		vis[u] = true;
		rep (i, 1, n)
			if (g[u][i])
			{
				cnt += num * len;
				q2.push(make_pair(i, num + 1));
			}
	}
	mn = min(cnt, mn);
}

int main()
{
	freopen("treasure.in", "r", stdin);
	int u, v, w;
	scanf("%d%d", &n, &m);
	mn = 0x7fffffff;
	rep (i, 1, m)
	{
		scanf("%d%d%d", &u, &v, &w);
		add(u, v, 1), add(v, u, 1);
		len = w;
	}
	rep(i, 1, n)
	{
		cnt = 0;
		work(i);
	}
	printf("%lld\n", mn);
	return 0;
}
