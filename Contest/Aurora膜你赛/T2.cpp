#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

const int N = 6e5 + 5;

template <typename T>
void read(T &x) {
    char ch = 0;
    while (!isdigit(ch = getchar()));
    for (x = ch - '0'; isdigit(ch = getchar()); x = x * 10 + ch - '0');
}

int n, a[N], f[N];

int main() {
    freopen("remove7.in", "r", stdin);
    freopen("remove7.out", "w", stdout);
    read(n);
    rep (i, 1, n)
        read(a[i]), f[i] = 0x3f3f3f3f;
    f[0] = 0;
    rep (i, 1, n)
        rep (j, 1, i - 1)
            f[i] = min(f[i], f[j - 1] + abs(a[i] - a[j]));
    printf("%d\n", f[n]);
}
