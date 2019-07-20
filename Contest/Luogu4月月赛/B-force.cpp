#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

const int N = 15;
int n, k;
unsigned long long a[N], b[N];

void judge() {
    unsigned long long mul = 1;
    rep (i, 1, n)
        mul *= b[i];
    mul = sqrt(mul);
    rep (i, 1, n)
        printf("%lld ", mul / b[i]);
    puts("");
}

int main() {
    int T;
    scanf("%d%d", &T, &k);
    n = k * (k - 1) / 2;
    while (T--) {
        rep (i, 1, n)
            scanf("%lld", &a[i]);
        rep (i, 1, n)
            scanf("%lld", &b[i]);
        if (k == 2) {
            printf("%lld %lld\n", a[1], b[1]);
            continue;
        }
        judge();
    }
}
