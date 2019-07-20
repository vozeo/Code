#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

typedef long long ll;
const int N = 6e5 + 5, M = 1005;
ll a[N], s[N], t[M * M], ans;
int cnt;

char buf[1 << 21], *p1 = buf, *p2 = buf;
#define getc() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++)

template<typename T>
void read(T &x) {
    char ch = 0;
    while (!isdigit(ch = getchar()));
    for (x = ch - '0'; isdigit(ch = getchar()); x = x * 10 + ch - '0');
}

struct Trie *tcur, *nil;
struct Trie {
    Trie *ch[2];
    Trie() {}
    Trie(Trie *l, Trie *r) {
        ch[0] = l, ch[1] = r;
    }
    Trie *insert(int x, int k = W) {
        if (k < 0) return new (++tcur) Trie(nil, nil);
        if ((x >> k) & 1)
            return new (++tcur) Trie(ch[0], ch[1]->insert(x, k - 1));
        else return new (++tcur) Trie(ch[0]->insert(x, k - 1), ch[1]);
    }
} tpool[N * 24], *root[N];

void init() {
    tcur = tpool;
    nil = tcur;
    *nil = Trie(nil, nil);
}

int query(int x, int y, int z) {
    Trie *l = x ? root[x - 1] : nil, *r = root[y];
    int res = 0, v;
    for (int k = W; ~k; --k) {
        v = !((z >> k) & 1);
        if (l->ch[v] == r->ch[v])
            l = l->ch[!v], r = r->ch[!v], res <<= 1;
        else l = l->ch[v], r = r->ch[v], res = (res << 1) | 1;
    }
    return res;
}

int n, m, l, r, x, xs;
char op[5];

int main() {
    freopen("P4735.in", "r", stdin);
    init();
    read(n), read(m);
    root[0] = nil->insert(0);
    rep (i, 1, n)
        read(x), root[i] = root[i - 1]->insert(xs ^= x);
    while (m--) {
        scanf("%s", op);
        if (op[0] == 'A')
            ++n, read(x), root[n] = root[n - 1]->insert(xs ^= x);
        else {
            read(l), read(r), read(x);
            printf("%d\n", query(l - 1, r - 1, xs ^ x));
        }
    }
}
