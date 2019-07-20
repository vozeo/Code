#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>
#define rep(i_, s_, t_) for(int i_ = (s_); i_ <= (t_); ++i_)
using namespace std;
typedef long long ll;
typedef const int cint;

int n, m, M_S, cur;
ll cnt, mn;
bool vis[1005];

struct Edge *head[20];
struct Edge
{
	int v, w;
	Edge *nxt;
	Edge() {}
	Edge(cint x, cint y, cint z) : v(y), w(z), nxt(head[x]) { head[x] = this; }
} epool[1005], *ecur = epool;

inline void add(int u, int v, int w)
{
	*(ecur++) = Edge(u, v, w);
}

void dfs(int x, int num)
{
	int c_s, v;
	ll s;
	printf("%d ", x);
	vis[x] = true;
	cur += (c_s = 1 << (x - 1));
	if (cur == M_S)
	{
		mn = min(mn, cnt);
		cur -= c_s;
		return;
	}
	for (Edge *e = head[x]; e; e = e->nxt)
		if (!vis[v = e->v])
		{
			cnt += (s = (ll)num * e->w);
			dfs(v, num + 1);
			cnt -= s;
		}
	vis[x] = false;
	cur -= c_s;
}

int main()
{
	freopen("treasure.in", "r", stdin);
	int u, v, w;
	scanf("%d%d", &n, &m);
	M_S = (1 << n) - 1;
	mn = 0x7fffffffffffffff;
	rep (i, 1, m)
	{
		scanf("%d%d%d", &u, &v, &w);
		add(u, v, w), add(v, u, w);
	}
	rep(i, 1, n)
	{
		cnt = 0;
		dfs(i, 1);
	}
	printf("%lld\n", mn);
	return 0;
}
