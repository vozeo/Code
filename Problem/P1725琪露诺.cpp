#include <cstdio>
#include <iostream>
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

int a[200005], f[200005], n, l, r, ans;

struct table {
    int p, cnt;
} s[200005];

int main() {
    scanf("%d%d%d", &n, &l, &r);
    rep(i, 0, n)
        scanf("%d", &a[i]);
    int head = 0, tail = 0;
    rep(i, l, n) {
        if (s[head].cnt + r < i)
            head++;
        while (s[tail - 1].p < f[i - l] && tail > head)
            tail--;
        s[tail].p = f[i - l];
        s[tail++].cnt = i - l;
        f[i] = s[head].p + a[i];
    }
    rep(i, n - r, n)
        ans = std::max(ans, f[i]);
    printf("%d\n", ans);
}