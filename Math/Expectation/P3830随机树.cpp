#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

double f[105];

int main() {
    int op, n;
    scanf("%d%d", &op, &n);
    if (op == 1) {
        f[1] = 0;
        rep (i, 2, n)
            f[i] = (f[i - 1] * (i - 1) + f[i - 1] + 2) / i;
        printf("%.6f\n", f[n]);
    }

}
