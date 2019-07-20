#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

const int N = 22000010;
char a[N] = "$#";
int cur = 1, mid, mx, ans, p[N];

int main() {
    while ((a[++cur] = getchar()) >= 'a')
        a[++cur] = '#';
    for (int i = 0; a[i] != '\0'; ++i) {
        p[i] = i < mx ? min(p[mid * 2 - i], mx - i) : 1;
        while (a[i + p[i]] == a[i - p[i]])
            ++p[i];
        if (i + p[i] > mx)
            mid = i, mx = i + p[i], ans = max(p[i], ans);
    }
    printf("%d\n", ans - 1);
}
