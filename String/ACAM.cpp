#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

const int N = 1e6 + 5, C = 26;

struct Node {
    Node *ch[C], *fail, *nxt;
    int cnt;
    Node() {}
} tpool[N], *tcur = tpool, *root = tpool;

void insert(char s[]) {
    int len = strlen(s) - 1;
    cout << len << endl;

    Node *o = root;
    rep (i, 0, len) {
        if (!o->ch[s[i] - 'a'])
            o->ch[s[i] - 'a'] = new (++tcur) Node();
        o = o->ch[s[i] - 'a'];
    }
    ++o->cnt;
}

void getfail() {
    queue<Node*> q;
    rep (i, 0, 25)
        if (root->ch[i])
            root->ch[i]->fail = root, q.push(root->ch[i]);
    Node *o;
    while (!q.empty()) {
        o = q.front(), q.pop();
        rep (i, 0, 25) {
            if (o->ch[i])
                o->ch[i]->fail = o->fail->ch[i] ? o->fail->ch[i] : root, q.push(o->ch[i]);
            else o->ch[i] = o->fail->ch[i] ? o->fail->ch[i] : root;
        }
    }
}

int query(char s[]) {
    int ans = 0, len = strlen(s) - 1, id;
    Node *o = root;
    rep (i, 0, len) {
        id = s[i] - 'a';
        while (!o->ch[id] && o != root)
            o = o->fail;
        o = o->ch[id] ? o->ch[id] : root;
        for (Node *p = o; p != root && p->cnt != -1; p = p->fail)
            ans += p->cnt, p->cnt = -1;
    }
    return ans;
}

char s[N];

int main() {
    int n;
    scanf("%d", &n);
    rep (i, 1, n)
        scanf("%s", s), insert(s);
    getfail();
    scanf("%s", s);
    printf("%d\n", query(s));
}
