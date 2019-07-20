#include <cstdio>
#include <iostream>
#include <queue>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

int a[200005], f[200005], n, l, r, ans;

struct form {
    int num, val;
};
deque<form> q;
//f[i] = max{f[j]} + a[i];
int main() {
    scanf("%d%d%d", &n, &l, &r);
    rep(i, 0, n)
        scanf("%d", &a[i]);
    rep(i, l, n) {
        while (q.size() && q.back().val < f[i - l])
            q.pop_back();
        q.push_back((form){i - l, f[i - l]});
        while (q.front().num + r < i)
            q.pop_front();
        f[i] = q.front().val + a[i];
    }
    rep(i, n - r, n)
        ans = max(ans, f[i]);
    printf("%d\n", ans);
}