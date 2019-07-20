#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define per(i_, s_, t_) for (int i_ = (s_); i_ >= (t_); --i_)

const int N = 2e6 + 5, P = 998244353;
typedef long long ll;

template <typename T>
void read(T &x) {
    char ch;
    while (!isdigit(ch = getchar()));
    for (x = ch - '0'; isdigit(ch = getchar()); x = x * 10 + ch - '0');
}

int main() {
    int n;
    scanf("%d", &n);
    if (n == 2) puts("Shi");
    else (n - (n >> 1)) & 1 ? puts("Yang") : puts("Shi");
}
