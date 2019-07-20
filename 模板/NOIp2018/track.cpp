#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define re(i_, s_, t_) for (int i_ = (s_); i_ < (t_); ++i_)
using namespace std;
typedef long long ll;
const int N = 50005;

int n, m, cur, vend, ver[N << 1], edge[N << 1], nxt[N << 1], head[N], w[N];
bool vis[N], flower = true;
ll d[N], all_ans, sum;

inline void add(int x, int y, int z)
{
    ver[++cur] = y, edge[cur] = z;
    nxt[cur] = head[x], head[x] = cur;
}

void bfs(int s)
{
    memset(vis, 0, sizeof(vis));
    memset(d, 0, sizeof(d));
    queue<int> q;
    q.push(s);
    while (q.size())
    {
        int x = q.front();
        q.pop();
        if (vis[x])
            continue;
        vis[x] = true;
        for (int i = head[x]; i; i = nxt[i])
        {
            int y = ver[i];
            if (vis[y])
                continue;
            q.push(y);
            d[y] = d[x] + edge[i];
        }
    }
    ll cnt = 0, cur = 0;
    rep(i, 1, n)
        if (d[i] > cnt)
            cnt = d[i], cur = i;
    vend = cur, all_ans = cnt;
}

void solve_1()
{
    bfs(1);
    bfs(vend);
}

int judge(ll s)
{
    int cur = 0, cnt = 0;
    rep (i, 1, n)
    {
        cur += w[i];
        if (cur >= s)
            cur = 0, cnt++;
    }
    return cnt;
}

void solve_2()
{
    sort(w + 1, w + n + 1);
    ll l = 0, r = sum, mid;
    while(l < r)
    {
        mid = (l + r + 1) >> 1;
        if (judge(mid) < m)
            r = mid - 1;
        else
            l = mid;
    }
    all_ans = l;
}

int main()
{
    scanf("%d%d", &n, &m);
    int x, y;
    rep (i, 1, n - 1)
    {
        scanf("%d%d%d", &x, &y, &w[i]);
        add(x, y, w[i]), add(y, x, w[i]);
        sum += w[i];
        if (x != 1)
            flower = false;
    }
    if (m == 1)
        solve_1();
    else if (flower)
        solve_2();
    printf("%lld\n", all_ans);
    return 0;
}