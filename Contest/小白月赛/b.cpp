#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define per(i_, s_, t_) for (int i_ = (s_); i_ >= (t_); --i_)

const int N = 1005, P = 1e9 + 7;
typedef long long ll;
int a[N][N], s[N];

template <typename T>
void read(T &x) {
    char ch;
    while (!isdigit(ch = getchar()));
    for (x = ch - '0'; isdigit(ch = getchar()); x = x * 10 + ch - '0');
}

int main() {
    int n, m, x, y;
    scanf("%d%d", &n, &m);
    rep (i, 1, n) {
        a[i][1] = a[i][i] = i;
        rep (j, 2, i - 1)
            a[i][j] = (a[i - 1][j - 1] + a[i - 1][j]) % P;
        rep (j, 1, i)
            s[i] = (s[i] + a[i][j]) % P;
    }
    rep (i, 1, m) {
        int ans = 0;
        scanf("%d%d", &x, &y);
        rep (j, x, y)
            ans = (ans + s[j]) % P;
        printf("%d\n", ans);
    }
}
