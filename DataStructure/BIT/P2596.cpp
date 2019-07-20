#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= t_; ++i_)
#define per(i_, s_, t_) for (int i_ = (s_); i_ >= t_; --i_)

const int N = 8e5 + 5;
int t[N * 3], pos[N], id[N * 3];
int n, tail, head;

void ins(int x, int p) {
    for (; p <= N * 3; p += p & -p)
        t[p] += x;
}

void top(int x) {
    int p = pos[x];
    ins(-1, p);
    id[p] = 0;
    ins(1, --head);
    pos[x] = head, id[head] = x;
}

void bot(int x) {
    int p = pos[x];
    ins(-1, p);
    id[p] = 0;
    ins(1, ++tail);
    pos[x] = tail, id[tail] = x;
}


int ask(int x) {
    int ans = 0;
    for (; x; x -= x & -x)
        ans += t[x];
    return ans;
}

int find(int x) {
    int p = 0, cnt = 0;
    per(i, 19, 0) {
        p += (1 << i);
        if (p >= 3 * N || cnt + t[p] >= x)
            p -= (1 << i);
        else cnt += t[p];
    }
    return p + 1;
}
/*
int find(int x) {
    int l = 0, r = n * 3, mid;
    while (l < r) {
        mid = (l + r) >> 1;
        if (t[mid] >= x)
            r = mid;
        else l = mid + 1;
    }
    return l;
}
*/
void adj(int x, int op) {
    if (!op) return;
    int p = pos[x];
    int s = find(ask(p) + op);
    int r = id[s];
    swap(pos[x], pos[r]);
    swap(id[p], id[s]);
}

int main() {
    /* freopen("5.in", "r", stdin); */
    int m, x, y;
    scanf("%d%d", &n, &m);
    head = N + 1, tail = N + n;
    rep (i, 1, n) {
        scanf("%d", &id[N + i]), ins(1, N + i);
        pos[id[N + i]] = N + i;
    }
    char s[10];
    rep (i, 1, m) {
        scanf("%s%d", s, &x);
        switch (s[0]) {
            case 'T': top(x);break;
            case 'B': bot(x);break;
            case 'I': scanf("%d", &y), adj(x, y);break;
            case 'A': printf("%d\n", ask(pos[x]) - 1);break;
            case 'Q': printf("%d\n", id[find(x)]);break;
        }
    }
    /* rep (i, 1, 3 * n) */
    /*     printf("%d ", pos[i]); */
}
