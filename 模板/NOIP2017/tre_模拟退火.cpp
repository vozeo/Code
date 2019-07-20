#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>
#define inf 2147483647
using namespace std;

int n, m, map[13][13], depth[13];
bool vis[13];

struct edge
{
    int u, v;
};
bool operator<(struct edge a, struct edge b)
{
    return depth[a.u] * map[a.u][a.v] > depth[b.u] * map[b.u][b.v];
}
int search(int source)
{
    memset(depth, 0, sizeof(depth));
    memset(vis, 0, sizeof(vis));
    priority_queue<edge> heap;
    edge e, e2, past[1000];
    int p = 0, cost = 0;
    depth[source] = 1;
    vis[source] = true;
    for (int i = 1; i <= n; ++i)
        if (map[source][i] < inf)
        {
            e.u = source;
            e.v = i;
            heap.push(e);
        }
    for (int i = 1; i < n; ++i)
    {
        e = heap.top();
        heap.pop();
        while (!heap.empty() && (vis[e.v] || rand() % n < 1))
        { //注意这里的判断条件rand()%n<1,即对于一个当前最近点，不选择的几率随着n的增大而减小。
            if (!vis[e.v])
                past[p++] = e;
            //对于跳过了的边，以后还用得上，等待选择结束后再压回优先队列中
            e = heap.top();
            heap.pop();
        }
        vis[e.v] = true;
        depth[e.v] = depth[e.u] + 1;

        while (p--)
            heap.push(past[p]);

        for (int i = 1; i <= n; ++i)
            if (map[e.v][i] < inf && !vis[i])
            {
                e2.u = e.v;
                e2.v = i;
                heap.push(e2);
            }
        cost += map[e.u][e.v] * depth[e.u];
    }
    return cost;
}

int main()
{
    int a, b, c, MIN = inf;
    memset(map, 0xff, sizeof(map));
    srand(201208);
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; ++i)
    {
        scanf("%d%d%d", &a, &b, &c);
        map[a][b] = map[b][a] = c;
    }

    for (int j = 1; j <= 1000; ++j)
        //1000次运行是绝对万无一失的，事实上，400次就够了
        for (int i = 1; i <= n; ++i)
            MIN = min(MIN, search(i));
    printf("%d", MIN);
    return 0;
}