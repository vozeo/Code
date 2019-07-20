#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

int main() {
    int n, L, G, w, h;
    scanf("%d%d%d", &n, &L, &G);
    rep (i, 1, n) {
        scanf("%d%d", &w, &h);
        while(w > G || h > G)
            w >>= 1, h >>= 1;
        if (w < L || h < L)
            puts("Too Young");
        else if(w != h)
            puts("Too Simple");
        else puts("Sometimes Naive");
    }
}
