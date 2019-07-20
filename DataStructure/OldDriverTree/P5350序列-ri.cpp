// luogu-judger-enable-o2
// luogu-judger-enable-o2
#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

typedef long long ll;
const int N = 3e5 + 5, P = 1e9 + 7;

struct Node {
    int l, r;
    mutable ll v;
    Node() {}
    Node(int x, int y = -1, ll z = 0) : l(x), r(y), v(z) {}
    bool operator < (const Node &rhs) const {
        return l < rhs.l;
    }
} q[N], *top;

typedef set<Node>::iterator Iter;
set<Node> s;

Iter split(int p) {
    Iter it = s.lower_bound(Node(p));
    if (it != s.end() && it->l == p)
        return it;
    --it;
    int l = it->l, r = it->r;
    ll val = it->v;
    s.erase(it);
    s.insert(Node(l, p - 1, val));
    return s.insert(Node(p, r, val)).first;
}

void assign(int l, int r, ll v) {
    Iter itr = split(r + 1), itl = split(l);
    s.erase(itl, itr);
    s.insert(Node(l, r, v));
}

void add(int l, int r, int val) {
    Iter itr = split(r + 1), itl = split(l);
    for (; itl != itr; ++itl)
        itl->v = (itl->v + val) % P;
}

ll sum(int l, int r) {
    Iter itr = split(r + 1), itl = split(l);
    ll ans = 0;
    for (; itl != itr; ++itl)
        ans = (ans + (itl->r - itl->l + 1) * itl->v) % P;
    return ans;
}

void copy(int l1, int r1, int l2, int r2) {
    int t = l2 - l1;
    Iter itr2 = split(r2 + 1), itl2 = split(l2);
    s.erase(itl2, itr2);
    //itl2 = s.insert(Node(l2, r2)).first;
    Iter itl1 = split(l1);
    if (r1 + 1 != l2)
        Iter itr1 = split(r1 + 1);
    //s.erase(itl2);

    for (; itl1->r <= r1; ++itl1)
        s.insert(Node(itl1->l + t, itl1->r + t, itl1->v));

}

void swp(int l1, int r1, int l2, int r2) {
    if (l1 > l2)
        swap(l1, l2), swap(r1, r2);
    
    int t = l2 - l1;
    top = q;

/*
    Iter itr2 = split(r2 + 1), itl2 = split(l2), it = itl2;
    for (; it != itr2; ++it)
        *(++top) = Node(it->l - t, it->r - t, it->v);
    s.erase(itl2, itr2);
    itl2 = s.insert(Node(l2, r2)).first;
    Iter itr1 = split(r1 + 1), itl1 = split(l1);
    it = itl1;
    s.erase(itl2);
  
    for (; it != itr1; ++it)
        s.insert(Node(it->l + t, it->r + t, it->v));
    s.erase(itl1, itr1);
    
    
    while (top > q)
        s.insert(*(top--));

*/
     
    Iter itr1 = split(r1 + 1), itl1 = split(l1), it = itl1;
    for (; it != itr1; ++it)
        *(++top) = Node(it->l + t, it->r + t, it->v);
    s.erase(itl1, itr1);
    //itl2 = s.insert(Node(l2, r2)).first;
    Iter itr2 = split(r2 + 1), itl2 = split(l2);
    it = itl2;
    //.erase(itl2);
  
    for (; it != itr2; ++it)
        s.insert(Node(it->l - t, it->r - t, it->v));
    s.erase(itl2, itr2);
    
    
    while (top > q)
        s.insert(*(top--));
}

void rev(int l, int r) {
    int t = l + r;
    Iter itr = split(r + 1), itl = split(l), it = itl;
    top = q;
    for (; it != itr; ++it)
        *(++top) = *it;
    s.erase(itl, itr);
    while (top > q)
        s.insert(Node(t - top->r, t - top->l, top->v)), --top;
}

char buf[1 << 21], *p1 = buf, *p2 = buf;
#define getc() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++)


template<typename T>
void read(T &x) {
    char ch;
    while (!isdigit(ch = getc()));
    for (x = ch - '0'; isdigit(ch = getc()); x = x * 10 + ch - '0');
}

int main() {
    int n, m, op, l, r, x, y;
    read(n), read(m);
    s.insert(Node(n + 1, n + 1, 0));
    rep (i, 1, n)
        read(x), s.insert(Node(i, i, x));
    rep (i, 1, m) {
        read(op), read(l), read(r);
        if (op == 1)
            printf("%lld\n", sum(l, r));
        else if (op == 2)
            read(x), assign(l, r, x);
        else if (op == 3)
            read(x), add(l, r, x);
        else if (op == 4)
            read(x), read(y), copy(l, r, x, y);
        else if (op == 5)
            read(x), read(y), swp(l, r, x, y);
        else rev(l, r);
    }
    Iter itr = split(n + 1), itl = split(1);
    for(; itl != itr; ++itl)
        rep (i, itl->l, itl->r)
            printf("%lld ", itl->v);
    puts("");
}
