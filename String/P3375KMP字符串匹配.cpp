#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

const int N = 1e6 + 5;
char a[N], b[N];
int p[N];

int main() {
    freopen("P3375.in", "r", stdin);
    scanf("%s%s", b + 1, a + 1);
    int la = strlen(a + 1), lb = strlen(b + 1), j = 0;
    p[1] = 0;
    rep (i, 2, la) {
        while (j && a[j + 1] != a[i]) j = p[j];
        if (a[j + 1] == a[i]) ++j;
        p[i] = j;
    }
    j = 0;
    rep (i, 1, lb) {
        while (j && a[j + 1] != b[i]) j = p[j];
        if (a[j + 1] == b[i]) ++j;
        if (j == la) printf("%d\n", i - la + 1), j = p[j];
    }
    rep (i, 1, la)
        printf("%d ", p[i]);
    puts("");
}
