#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define per(i_, s_, t_) for (int i_ = (s_); i_ >= (t_); --i_)

const int N = 2005;
char a[N][N];
int le[N][N], ri[N][N];

int sqr(int x) { return x * x; }

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    rep (i, 1, n)
        rep (j, 1, m)
            cin >> a[i][j];
    rep (i, 1, n) {
        rep (j, 1, m)
            le[i][j] = (a[i][j] == 'F') ? le[i][j - 1] + 1 : 0;
        per (j, m, 1)
            ri[i][j] = (a[i][j] == 'F') ? ri[i][j + 1] + 1 : 0;
    }
    int ans = 0;
    const int INF = INT_MAX;
    rep (j, 1, m) {
        int up = 0, l = INF, r = INF;
        rep (i, 1, n) {
            if (a[i][j] != 'F')
                up = 0, l = r = INF;
            else ++up, l = min(l, le[i][j]), r = min(r, ri[i][j]);
            ans = max(ans, up * (r + l - 1));
        }
    }
    printf("%d\n", 3 * ans);
}
