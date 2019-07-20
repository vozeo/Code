#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>
#define rep(i_, s_, t_) for(int i_ = (s_); i_ <= (t_); ++i_)
using namespace std;
typedef long long ll;
typedef long double ld;

int cur, n, h, r, x[1005], y[1005], z[1005], st[1005];
ll dis;
bool fi[1005] ,vis[1005];

inline bool judge(int a, int b)
{
	return dis >= (ll)(x[a] - x[b]) * (x[a] - x[b]) + (ll)(y[a] - y[b]) * (y[a] - y[b]) + (ll)(z[a] - z[b]) * (z[a] - z[b]);
}

bool bfs()
{
	queue<int> q;
	rep(i, 1, cur)
		q.push(st[i]);
	while(!q.empty())
	{
		int c = q.front();
		q.pop();
		if (fi[c])
			return true;
		if (vis[c])
			continue;
		vis[c] = true;
		rep (i, 1, n)
			if (!vis[i] && judge(i, c))
				q.push(i);
	}
	return false;
}

void init()
{
	memset(vis, 0, sizeof(vis));
	memset(fi, 0, sizeof(fi));
	cur = 0;
}

int main()
{
	freopen("cheese.in", "r", stdin);
	int T;
	scanf("%d", &T);
	while(T--)
	{
		init();
		scanf("%d%d%d", &n, &h, &r);
		dis = (ll)r * r * 4;
		rep (i, 1, n)
		{
			scanf("%d%d%d", &x[i], &y[i], &z[i]);
			if (r >= z[i])
				st[++cur] = i;
			if (z[i] + r >= h)
				fi[i] = true;
		}
		if(bfs())
			printf("Yes\n");
		else
			printf("No\n");
	}
	return 0;
}
