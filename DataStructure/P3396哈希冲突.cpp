#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

void prework() {
    rep (i, 1, n)
        b[i] = (i - 1) / L + 1;
    cnt = b[n];
    rep (i, 1, cnt)
        bl[i] = (i - 1) * L + 1, br[i] = i * L;
    br[cnt] = n;
    rep (i, 1, n)
        rep (i, 1, 
        g[b[i]][a[i] % 





}

int main() {
    read(n), read(m);
    rep (i, 1, n)
        read(a[i]);
    while (m--) {
        scanf("%s%d%d", s, &x, &y);
        if (s == "A")
            query(x, y);
        else modify(x, y);
    }
}
