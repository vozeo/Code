#include <cstdio>
#include <cctype>
#include <cstring>
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

int a, ai, n, mx;
long long sum;

void read(int &xx)
{
    char cc;
    while (!isdigit(cc = getchar()));
    for (xx = cc - '0'; isdigit(cc = getchar()); xx = xx * 10 + cc - '0');
}

int main()
{
    //freopen("phantasm.in", "r", stdin);
    //freopen("phantasm.out", "w", stdout);
    scanf("%d", &n);
    rep(i, 1, n)
    {
        read(a);
        if (a >= mx)
        {
            mx = a;
            ai = i;
        }
        sum += i - ai;
    }
    printf("%lld\n", sum);
    return 0;
}