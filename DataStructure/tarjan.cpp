#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
const int SIZE = 100010;
int head[SIZE], ver[SIZE * 2], Next[SIZE * 2], c[SIZE * 2];
int dfn[SIZE], low[SIZE], stack[SIZE], new_id[SIZE];
int n, m, tot, num, top, cnt, tc, root;
bool cut[SIZE];
vector<int> dcc[SIZE];
int hc[SIZE], vc[SIZE * 2], nc[SIZE * 2];

void add(int x, int y)
{
    ver[++tot] = y, Next[tot] = head[x], head[x] = tot;
}

void add_c(int x, int y)
{
    vc[++tc] = y, nc[tc] = hc[x], hc[x] = tc;
}

void tarjan(int x)
{
    dfn[x] = low[x] = ++num;
    stack[++top] = x;
    if (x == root && head[x] == 0)
    { // 孤立点
        dcc[++cnt].push_back(x);
        return;
    }
    int flag = 0;
    for (int i = head[x]; i; i = Next[i])
    {
        int y = ver[i];
        if (!dfn[y])
        {
            tarjan(y);
            low[x] = min(low[x], low[y]);
            if (low[y] >= dfn[x])
            {
                flag++;
                if (x != root || flag > 1)
                    cut[x] = true;
                cnt++;
                int z;
                do
                {
                    z = stack[top--];
                    dcc[cnt].push_back(z);
                } while (z != y);
                dcc[cnt].push_back(x);
            }
        }
        else
            low[x] = min(low[x], dfn[y]);
    }
}

int main()
{
    cin >> n;
    m = n - 1;
    tot = 1;
    for (int i = 1; i <= m; i++)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        if (x == y)
            continue;
        add(x, y), add(y, x);
    }
    for (int i = 1; i <= n; i++)
        if (!dfn[i])
            root = i, tarjan(i);
    for (int i = 1; i <= n; i++)
        if (cut[i])
            printf("%d ", i);
    puts("are cut-vertexes");
    for (int i = 1; i <= cnt; i++)
    {
        printf("e-DCC #%d:", i);
        for (int j = 0; j < (int)dcc[i].size(); j++)
            printf(" %d", dcc[i][j]);
        puts("");
    }
    // 给每个割点一个新的编号(编号从cnt+1开始)
    num = cnt;
    for (int i = 1; i <= n; i++)
        if (cut[i])
            new_id[i] = ++num;
    // 建新图，从每个v-DCC到它包含的所有割点连边
    tc = 1;
    for (int i = 1; i <= cnt; i++)
        for (int j = 0; j < (int)dcc[i].size(); j++)
        {
            int x = dcc[i][j];
            if (cut[x])
            {
                add_c(i, new_id[x]);
                add_c(new_id[x], i);
            }
            else
                c[x] = i; // 除割点外，其它点仅属于1个v-DCC
        }
    printf("缩点之后的森林，点数 %d，边数 %d\n", num, tc / 2);
    printf("编号 1~%d 的为原图的v-DCC，编号 >%d 的为原图割点\n", cnt, cnt);
    for (int i = 2; i < tc; i += 2)
        printf("%d %d\n", vc[i ^ 1], vc[i]);
}
