#include <cstdio>
#include <cmath>
#define rep(i_, s_, t_) for(int i_ = (s_); i_ <= (t_); ++i_)
#define re(i_, s_, t_) for(int i_ = (s_); i_ < (t_); ++i_)
typedef long long ll;

char s[100005][11];
int out[100005];

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    re (i, 0, n)
        scanf("%d%s", &out[i], s[i]);
    int cnt = 0;
    rep (i, 1, m)
    {
        int r, num;
        scanf("%d%d", &r, &num);
        if (r)
        {
            if (out[cnt])
                cnt = (cnt - num + n) % n;
            else
                cnt = (cnt + num) % n;
        }
        else
        {
            if (out[cnt])
                cnt = (cnt + num) % n;
            else
                cnt = (cnt - num + n) % n;
        }
    }
    printf("%s\n", s[cnt]);
    return 0;
}