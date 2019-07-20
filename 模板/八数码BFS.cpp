#include <iostream>
#include <cstdio>
#include <map>
#include <queue>
using namespace std;
queue<int> q;
map<int, int> m;
int a, f[5][5], dx[5] = {0, 0, 1, -1}, dy[5] = {1, -1, 0, 0};

int main()
{
    scanf("%d", &a);
    q.push(a);
    m[a] = 0;
    while (q.size())
    {
        int x = 0, y = 0, qf, k = q.front();
        qf = k;
        q.pop();
        if (k == 123804765)
            break;
        for (int i = 2; i >= 0; --i)
            for (int j = 2; j >= 0; --j)
            {
                f[i][j] = k % 10, k /= 10;
                if (!f[i][j])
                    x = i, y = j;
            }
        /*
        for (int i = 0; i <= 2; ++i)
            for (int j = 0; j <= 2; ++j)
                printf("%d", f[i][j]);
        printf("\n");
        printf("x=%d, y=%d\n", x, y);
*/
        for (int i = 0; i < 4; ++i)
        {
            int cx = x + dx[i], cy = y + dy[i];
            if (cx < 0 || cx > 2 || cy < 0 || cy > 2)
                continue;
            swap(f[x][y], f[cx][cy]);
            int p = 0;
            for (int l = 0; l <= 2; ++l)
                for (int j = 0; j <= 2; ++j)
                {
                    p += f[l][j];
                    if (l < 2 || j < 2)
                        p *= 10;
                }
            swap(f[x][y], f[cx][cy]);

            //printf("p = %d\n", p);

            if (m[p])
                continue;
            else
            {
                q.push(p);
                m[p] = m[qf] + 1;
                //printf("k = %d, p = %d\n", qf, p);
            }
        }
    }
    printf("%d\n", m[123804765]);
    return 0;
}