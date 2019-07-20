#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define per(i_, s_, t_) for (int i_ = (s_); i_ >= (t_); --i_)

const int N = 2e6 + 5, P = 1e9 + 7;
typedef long long ll;

template <typename T>
void read(T &x) {
    char ch;
    while (!isdigit(ch = getchar()));
    for (x = ch - '0'; isdigit(ch = getchar()); x = x * 10 + ch - '0');
}

int a[10][10];
bool f[10][10][2005];

int main() {
    //freopen("d.in", "r", stdin);
    int n, S = 1000;
    read(n);
    rep (i, 1, n)
        rep (j, 1, n)
            read(a[i][j]);
    f[1][1][a[1][1]] = true;
    rep (i, 1, n)
        rep (j, 1, n)
            rep (k, 1, S) {
                if (f[i][j][k]) f[i + 1][j][a[i + 1][j] + k] = 1;
                if (f[i][j][k]) f[i][j + 1][a[i][j + 1] + k] = 1;
            }
    int ans = 0;
    rep (i, 1, S)
        ans += f[2][2][i];
    printf("%d\n", ans);
}
