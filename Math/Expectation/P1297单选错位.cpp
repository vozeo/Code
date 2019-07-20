#include <cstdio>
#include <iostream>
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
using namespace std;

int n, A, B, C, a[10000005];
double ans;

/*
template <typename T>
void read(T &xx)
{
    char cc;
    while (!isdigit(cc = getchar()));
    for (xx = cc - '0'; isdigit(cc = getchar()); xx = xx * 10 + cc - '0');
}
*/

int main()
{
    scanf("%d%d%d%d%d", &n, &A, &B, &C, a + 1);
    rep(i, 2, n)
        a[i] = ((long long)a[i - 1] * A + B) % 100000001;
    rep(i, 1, n)
        a[i] = a[i] % C + 1;
    rep(i, 2, n)
    {
        if (a[i - 1] > a[i])
            ans += (double)a[i] / a[i - 1];
        else
            ans += 1.0 / a[i];
    }
    if (a[n] > a[1])
        ans += (double)a[1] / a[n];
    else
        ans += 1.0 / a[1];
    printf("%.3f\n", ans);
    return 0;
}