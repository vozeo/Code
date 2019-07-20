#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define N 100005
#define M 200005

int n, m, s, tot, dis[N], head[N], edge[M], ver[M], Next[M];
bool used[N];
priority_queue<pair<int, int> > q;

inline void add(int x, int y, int z)
{
    ver[++tot] = y, edge[tot] = z;
    Next[tot] = head[x], head[x] = tot;
}

template <typename T>
inline void read(T &x)
{
    char c;
    while (!isdigit(c = getchar()));
    for (x = c - '0'; isdigit(c = getchar()); x = x * 10 + c - '0');
}

void dijkstra()
{
    memset(dis, 0x3f, sizeof(dis));
    dis[s] = 0;
    q.push(make_pair(0, s));
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
            if (dis[y] > dis[x] + z)
            {
                dis[y] = dis[x] + z;
                q.push(make_pair(-dis[y], y));
            }
        }
    }
}

int main()
{
    int u, v, w;
    read(n), read(m), read(s);
    rep(i, 1, m)
    {
        read(u), read(v), read(w);
        add(u, v, w);
    }
    dijkstra();
    rep(i, 1, n)
        printf("%d ", dis[i]);
    return 0;
}