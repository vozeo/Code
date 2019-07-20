#include "interaction.h"
#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

vector<int> ans;

int main() {
    int n = get_num(), l, r, mid;
    rep (i, 0, n - 1) {
        l = 0, r = 1000000;
        while (l < r) {
            mid = (l + r) >> 1;
            if (guess(i, mid) < 0)
                l = mid + 1;
            else if (guess(i, mid) > 0)
                r = mid;
            else {
                ans.push_back(mid);
                break;
            }
        }
    }
    submit(ans);
}
