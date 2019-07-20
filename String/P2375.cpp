#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

int main() {
    scanf("%s", a + 1);
    int len = strlen(a + 1);
    p[1] = 0;
    rep (i, 1, len) {
        while (j && p[j + 1] != p[i])
            j = p[j];
        if (p[j + 1] == p[i]) ++j;
        p[i] = j;
    }
}
