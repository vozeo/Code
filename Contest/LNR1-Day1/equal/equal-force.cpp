#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define per(i_, s_, t_) for (int i_ = (s_); i_ >= (t_); --i_)

const int N = 2e6 + 5, P = 998244353;
char s[N];
int a[N];
bool b[N];

template <typename T>
void read(T &x) {
    char ch;
    while (!isdigit(ch = getchar()));
    for (x = ch - '0'; isdigit(ch = getchar()); x = x * 10 + ch - '0');
}

int cnt[100];

int main() {
    freopen("equal1.in", "r", stdin);
    //freopen("alone3.out", "w", stdout);
    scanf("%s", s + 1);
    int n = strlen(s + 1), ans = 0;
    rep (i, 1, n)
        if (s[i] == '<')
            b[i] = true;
    rep (i, 1, n + 1)
        a[i] = i;
    do {
        rep (i, 1, n)
            if ((a[i] < a[i + 1]) != b[i])
                goto A;
        ++ans;
        if (ans > P) ans -= P;
        rep (i, 1, n + 1)
            cout << a[i];
        cout << endl;
        ++cnt[a[1]];
A:;
    } while (next_permutation(a + 1, a + n + 2));
    rep (i, 1, n)
        cout << cnt[i] << " ";
    cout << endl;
    printf("%d\n", ans);
}
