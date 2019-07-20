#include <cstdio>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
typedef long long ll;
#define N 1000005

int n, k, b[N], c[N];
char a[N];

bool judge(int x)
{
    for (int i = 1; i + x - 1 <= n; i++)
        if (k * (b[i + x - 1] - b[i - 1]) == c[i + x - 1] - c[i - 1])
            return true;
    return false;
}

int main()
{
    scanf("%d%d%s", &n, &k, a + 1);
    rep(i, 1, n)
    {
        b[i] = b[i - 1] + (a[i] == '1');
        c[i] = c[i - 1] + (a[i] == '0');
    }
    int l = 0, r = n / (k + 1);
    while (l < r)
    {
        int mid = (l + r + 1) / 2;
        if (judge(mid * (k + 1)))
            l = mid;
        else
            r = mid - 1;
    }
    printf("%d", l * (k + 1));
    return 0;
}