#include <bits/stdc++.h>
using namespace std;
void pushdown(int x) { //下传标记
    cov[ls[x]] += cov[x];
    cov[rs[x]] += cov[x];
    sum[ls[x]] += cov[x] * num[ls[x]];
    sum[rs[x]] += cov[x] * num[rs[x]];
    cov[x] = 0;
}
void update(int x) { //上传值
    size[x] = size[ls[x]] + size[rs[x]] + 1;
    sum[x] = sum[ls[x]] + sum[rs[x]];
}
int merge(int x, int y) {
    if (!x || !y)
        return x | y;      //两边有一边为空
    if (ran[x] > ran[y]) { // ran表示treap的随机权值
        pushdown(x);
        rs[x] = merge(rs[x], y);
        update(x);
        return x;
    } else {
        pushdown(y);
        ls[y] = merge(x, ls[y]);
        update(y);
        return y;
    }
}
//把z分成x和y两棵子树，中序遍历的第k个给x，第k+1个给y
void split(int z, int &x, int &y, int k) {
    if (!z) {
        x = 0;
        y = 0;
        return;
    }
    pushdown(z);
    if (size[ls[z]] >= k) {
        y = z;
        split(ls[z], x, ls[y], k);
        update(y);
    } //第k个点在左儿子
    else {
        x = z;
        split(rs[z], rs[x], y, k - size[ls[z]] - 1);
        update(x);
    } //第k个点在根或右儿子
}
int main() {}