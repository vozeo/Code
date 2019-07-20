#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

int main() {
    int a, b;
    cin >> a >> b;
    if (!b) cout << 1 << endl;
    else cout << min(b, a - b) << endl;
}
