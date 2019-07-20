#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for(int i_ = (s_); i_ <= (t_); ++i_)
typedef long long ll;

int n, a[1005], T;
bool f[25005];
int main()
{
    scanf("%d", &T);
    while(T--)
    {
        memset(f, 0, sizeof(f));
        scanf("%d", &n);
        int sum = 0;
        rep (i, 1, n)
            scanf("%d", &a[i]);
        sort(a + 1, a + n + 1);
        f[0] = true;
        rep (i, 1, n)
            if (!f[a[i]])
            {
                rep (j, a[i], a[n])
                    f[j] |= f[j - a[i]];
                sum++;
            }
        printf("%d\n", sum);
    }
    return 0;
}