#include <iostream>
#include <cstdio>
#include <queue>

struct Edge *head[N];
struct Edge
{
	int v, w;
	Edge *nxt;
	Edge() {}
	Edge(cint u, cint v, cint w) : v(v), w(w), nxt(head[u]) { head[u] = this; }
} epool[M], *ecur = epool;

inline void add(int u, int v, int w)
{
	*(ecur++) = Edge(u, v, w);
}

inline void init()
{
	memset(vis, 0, sizeof(bool) * n);
	memset(head, 0, sizeof(int) * n);
	memset(d, 0x3f, sizeof(int) * n);
	ecur = epool;
}

void dijkstra()
{
	priority_queue<pair<int, int> > q;
	q.push(make_pair(d[1] = 0, 1));
	while(!q.empty())
	{
		int u = q.top().second;
		q.pop();
		if (vis[u])
			continue;
		vis[u] = true;
		int v, t;
		for (Edge *e = head[u]; e; e->nxt)
			if (d[v = e->v] > (t = d[u] + e->w))
				q.push(make_pair(-(d[v] = t), v));
	}
}

void bfs()
{

	cnt[1] = 1;
	queue<int> q;
	q.push(1);
	while(!q.empty())
	{
		int u = q.top(), v;
		q.pop();
		for (Edge *e = head[u]; e; e->nxt)
		{
			v = e->v;
			if (dis[u] + e->w <= d[n] + k)
			{
				cnt[v] = cnt[u] + cnt[v] % MOD;
				dis[ 
			}
		}
	}
}

void work()
{
	int a, b, c;
	scanf("%d%d%d%d", &n, &m, &k, &p);
	rep (i, 1, m)
	{
		scanf("%d%d%d", &a, &b, &c);
		add(a, b, c);
	}
}

int main()
{
	int T;
	while(T--)
	{
		init();
		work();
	}
}
