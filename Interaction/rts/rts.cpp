#include "rts.h"
#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

const int N = 300005;
int vis[N];

int guess(int x, int y) {
    vis[x] = 1;
    while (x != y)
        x = explore(x, y), vis[x] = 1;
    return y;
}

void play(int n, int T, int type) {
    if (type == 3) {
        int l = 1, r = 2, now = 1;
        r = guess(1, 2);
        rep (i, 3, n) {
            if (vis[i]) continue;
            now = explore(l, i);
            if (vis[now]) r = guess(r, i);
            else vis[now] = 1, l = guess(now, i);
        }
    } else {
        int lst;
        rep (i, 2, n) {
            if (vis[i]) continue;
            lst = 1;
            while (i != lst)
                lst = explore(lst, i), vis[lst] = 1;
        }
    }
}
