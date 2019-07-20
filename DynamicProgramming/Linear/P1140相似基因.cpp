#include <bits/stdc++.h>
using namespace std;

char s1[105], s2[105];
int n, m, a[105], b[105], f[105][105];
const int c[5][5] = {
    {5, -1, -2, -1, -3},
    {-1, 5, -3, -2, -4},
    {-2, -3, 5, -2, -2},
    {-1, -2, -2, 5, -1},
    {-3, -4, -2, -1, 0}};
map<char, int> h;

int main()
{
    h['A'] = 0, h['C'] = 1, h['G'] = 2, h['T'] = 3;
    scanf("%d%s%d%s", &n, s1 + 1, &m, s2 + 1);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            f[i][j] = -1e8;
    for (int i = 1; i <= n; i++)
    {
        a[i] = h[s1[i]];
        f[i][0] = f[i - 1][0] + c[a[i]][4];
    }
    for (int i = 1; i <= m; i++)
    {
        b[i] = h[s2[i]];
        f[0][i] = f[0][i - 1] + c[b[i]][4];
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            f[i][j] = max(f[i][j], f[i - 1][j] + c[a[i]][4]);
            f[i][j] = max(f[i][j], f[i][j - 1] + c[b[j]][4]);
            f[i][j] = max(f[i][j], f[i - 1][j - 1] + c[a[i]][b[j]]);
        }
    printf("%d", f[n][m]);
    return 0;
}