#include <bits/stdc++.h>
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
using namespace std;
int a[10000] = {0, 2, 3, 4, 5}, b[10000] = {0, 2, 5};
bool f[10000], g[10000];

int main()
{

    int n = 1005;
    memset(f, 1, sizeof(f));
    memset(g, 1, sizeof(g));
    f[0] = 0;
    rep(i, 1, n)
    {
        rep(j, 1, 4)
            if (i - a[j] >= 0)
                f[i] = 1 - min(f[i], g[i - a[j]]);
        rep(j, 1, 2)
            if (i - a[i] >= 0)
                g[i] = 1 - min(g[i], f[i - b[j]]);
    }
    rep(i, 1, 100)
        printf("%d %d\n", f[i], g[i]);
    return 0;
}