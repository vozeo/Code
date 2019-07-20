#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

const int N = 1000005;
string a, b;
int na, nb, p[N];

int main() {
    cin >> a >> b;
    na = a.size(), nb = b.size();
    a = "0" + a, b = "0" + b;
    p[1] = 0;
    int j = 0;
    rep (i, 2, nb) {
        while (j && b[i] != b[j + 1]) j = p[j];
        if (b[i] == b[j + 1]) ++j;
        p[i] = j;
    }
    j = 0;
    rep (i, 1, na) {
        while (j && a[i] != b[j + 1]) j = p[j];
        if (a[i] == b[j + 1]) ++j;
        if (j == nb)
            printf("%d\n", i - j + 1), j = p[j];
    }
    rep (i, 1, nb)
        printf("%d ", p[i]);
    puts("");
}
