#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define re(i_, s_, t_) for (int i_ = (s_); i_ < (t_); ++i_)
typedef long long ll;
#define N 500005

int n, a[N], b[N], f[4005][4005];

template <typename T>
inline void read(T &x)
{
    char c;
    while (!isdigit(c = getchar()));
    for (x = c - '0'; isdigit(c = getchar()); x = x * 10 + c - '0');
}

int main()
{
    read(n);
    rep(i ,1, n)
        read(a[i]);
    rep(i, 1, n)
        read(b[i]);
    f[0][0] = 1;
    rep(i, 1, n)
        rep(j, 1, n)
            if (a[i] == b[j])
                f[i][j] = f[i - 1][j - 1] + 1;
            else f[i][j] = max(f[i - 1][j], f[i][j - 1]);
    printf("%d", n + f[n][n]);
    return 0;
}