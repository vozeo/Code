#include <bits/stdc++.h>
using namespace std;
#define MOD 1000000007

int n, m, l, f[2][205][205][2];
char a[1005], b[205];
int main()
{
    scanf("%d%d%d%s%s", &n, &m, &l, a + 1, b + 1);
    f[1][0][0][0] = f[0][0][0][0] = 1;
    bool t = 1;
    for (int i = 1; i <= n; i++, t ^= 1)
        for (int j = 1; j <= m; j++)
            for (int k = 1; k <= l; k++)
            {
                if (a[i] == b[j])
                    f[t][j][k][1] = (f[t ^ 1][j - 1][k - 1][1] + (f[t ^ 1][j - 1][k - 1][0] + f[t ^ 1][j - 1][k][1]) % MOD) % MOD;
                else
                    f[t][j][k][1] = 0;
                f[t][j][k][0] = (f[t ^ 1][j][k][1] + f[t ^ 1][j][k][0]) % MOD;
            }
    printf("%d", (f[n & 1][m][l][0] + f[n & 1][m][l][1]) % MOD);
    return 0;
}