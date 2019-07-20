#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

const int N = 1e5 + 5;
int n, p, t[N], f[N];
char a[N];

bool comp(const int x, const int y) {
    if (x < y) {
        if (f[x] >= y)
            return true;
        return a[f[x] + 1] < a[f[x]];
    } else {
        if (f[y] >= x)
            return false;
        return a[f[y]] < a[f[y] + 1];
    }
}

int main() {
    scanf("%d", &n);
    scanf("%s", a + 1);
    rep (i, 1, n) {
        t[i] = i;
        if (p < i) p = i;
        while (p < n && a[p] == a[p + 1])
            ++p;
        f[i] = p;
    }
    sort(t + 1, t + n + 1, comp);
    rep (i, 1, n)
        printf("%d ", t[i]);
    puts("");
}
