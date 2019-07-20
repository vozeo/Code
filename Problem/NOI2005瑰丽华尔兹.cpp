#include <cstdio>
#include <iostream>
#include <queue>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define per(i_, s_, t_) for (int i_ = (s_); i_ >= (t_); --i_)

int f[2][205][205], n, m, x, y, t, ans;
char a[205][205];

struct form {
    int num, val;
} s[200005];

deque<form> q;

void dp(int len, int d) {
    if (d == 1) {
        rep (i, 1, m) {
            q.clear();
            q.push_back((form){1, f[d ^ 1][n][i]});
            per (j, n, 1) {
                if (a[j][i] == 'x') {
                    q.clear();
                    continue;
                }
                if (q.front().num + len < j)
                    q.pop_front();
                while (q.size() && q.back().val < f[d ^ 1][j][i])
                    q.pop_back();
                q.push_back((form){j, f[d ^ 1][j][i]});
                f[d ^ 1][j][i] = q.front().val + j -  q.front().num + 1;
            }
        }
    }
    if (d == 2) {
        rep (i, 1, m) {
            q.clear();
            q.push_back((form){1, f[d ^ 1][1][i]});
            rep (j, 1, n) {
                if (a[j][i] == 'x') {
                    q.clear();
                    continue;
                }
                if (q.front().num + len < j)
                    q.pop_front();
                while (q.size() && q.back().val < f[d ^ 1][j][i])
                    q.pop_back();
                q.push_back((form){j, f[d ^ 1][j][i]});
                f[d ^ 1][j][i] = q.front().val + j -  q.front().num + 1;
            }
        }
    }
    if (d == 3) {
        rep (j, 1, n) {
            q.clear();
            q.push_back((form){1, f[d ^ 1][j][n]});
            per (i, n, 1) {
                if (a[j][i] == 'x') {
                    q.clear();
                    continue;
                }
                if (q.front().num + len < j)
                    q.pop_front();
                while (q.size() && q.back().val < f[d ^ 1][j][i])
                    q.pop_back();
                q.push_back((form){j, f[d ^ 1][j][i]});
                f[d ^ 1][j][i] = q.front().val + j -  q.front().num + 1;
            }
        }
    }
    if (d == 4) {
        rep (j, 1, n) {
            q.clear();
            q.push_back((form){1, f[d ^ 1][j][1]});
            rep (i, 1, n) {
                if (a[j][i] == 'x') {
                    q.clear();
                    continue;
                }
                if (q.front().num + len < j)
                    q.pop_front();
                while (q.size() && q.back().val < f[d ^ 1][j][i])
                    q.pop_back();
                q.push_back((form){j, f[d ^ 1][j][i]});
                f[d ^ 1][j][i] = q.front().val + j -  q.front().num + 1;
            }
        }
    }
}

int main() {
    scanf("%d%d%d%d%d", &n, &m, &x, &y, &t);
    rep (i, 1, n)
        scanf("%s", a + 1);
    rep (i, 1, t) {
        int l, r, d;
        scanf("%d%d%d", &l, &r, &d);
        dp (r - l + 1, d);
    }
    rep (i ,1, n)
        rep(j ,1, m)
            ans = max(f[t ^ 1][i][j], ans);
    printf("%d\n", ans);
    return 0;
}