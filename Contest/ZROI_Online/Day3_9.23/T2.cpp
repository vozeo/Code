#include <bits/stdc++.h>
using namespace std;
#define rep(i_,s_,t_) for(int i_=(s_);i_<=(t_);i_++)
#define N 200005
#define INF 0x3f3f3f3f

int n, m, tot, s, sum, d[N], head[N], ver[N], edge[N], Next[N], ans[N], eb[N], c[N], cx[N];
bool used[N];

int read()
{
	int x = 0;
	char c = getchar();
	while (!isdigit(c))
		c = getchar();
	while (isdigit(c))
		x = x * 10 + c - '0', c = getchar();
	return x;
}

int max(int x, int y)
{
	return x > y ? x : y;
}

void add(int x, int y, int z)
{
	ver[++tot] = y, edge[tot] = z, Next[tot] = head[x], head[x] = tot;
}

void dijkstra(bool first)
{
	memset(d, 0x3f, sizeof(d));
	memset(used, 0, sizeof(used));
	d[1] = 0;
	priority_queue<pair<int, int> > q;
	q.push(make_pair(0, 1));
	while (q.size())
	{
		int x = q.top().second;
		q.pop();
		if (used[x])
			continue;
		used[x] = true;
		for (int i = head[x]; i; i = Next[i])
		{
			int y = ver[i], z = edge[i];
			if (d[y] > d[x] + z)
			{
				d[y] = d[x] + z;
				if(first == true)
				{
					c[y] = i;
					cx[y] = x;
				}
			}
			q.push(make_pair(-d[y], y));
		}
	}
}

void find()
{
	int cur = n;
	while(true)
	{
		eb[++s] = c[cur];
		cur = cx[cur];
		if (cur == 1)
			break;
	}
}

int main()
{
	int u, v, w;
	scanf("%d%d", &n, &m);
	rep (i, 1, m)
	{
		u = read(), v = read(), w = read();
		add(u, v, w), add(v, u, w);
	}
	dijkstra(1);
	find();
	int disn = d[n];
	rep (i, 1, s)
	{	
		int temp = edge[eb[i]];
		if (eb[i] % 2 == 1)
		{
			edge[eb[i]] = edge[eb[i + 1]] = INF;
			dijkstra(0);
			if (d[n] > disn)
				ans[++sum] = eb[i];
			edge[eb[i]] = edge[eb[i + 1]] = temp;
		}
		else
		{
			edge[eb[i]] = edge[eb[i - 1]] = INF;
			dijkstra(0);
			if (d[n] > disn)
				ans[++sum] = eb[i];
			edge[eb[i]] = edge[eb[i - 1]] = temp;
		}
	}
	printf("%d\n", sum);
	rep (i, 1, sum)
		printf("%d ", ans[i]);
	return 0;
}
