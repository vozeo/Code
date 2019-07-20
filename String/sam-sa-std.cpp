#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
#include<cmath>
using namespace std;
const int N = 1e6 + 10; 
int sa[N], rnk[N], s[N], n;
void readchar() {
    char ch = getchar(); int x = 0;
    while(ch < 'a' || ch > 'z') ch = getchar();
    while(ch >= 'a' && ch <= 'z') {s[++x] = ch - 'a'; ch = getchar();}
    n = x;
} 
struct SAM {
    int ch[N][26], pos[N], len[N], fa[N], last, sz;
    bool val[N];
    SAM() : last(1), sz(1) {}
    void Extend(int c, int po) {
        int p = last, np = last = ++sz;
        pos[np] = po; val[np] = true; len[np] = len[p] + 1;
        for(;p && !ch[p][c]; p = fa[p]) ch[p][c] = np;
        if(!p) fa[np] = 1;
        else {
            int q = ch[p][c];
            if(len[q] == len[p] + 1) fa[np] = q;
            else {
                int nq = ++sz; len[nq] = len[p] + 1;
                memcpy(ch[nq], ch[q], sizeof(ch[q]));
                fa[nq] = fa[q]; pos[nq] = pos[q];
                fa[q] = fa[np] = nq;
                for(;ch[p][c] == q; p = fa[p]) ch[p][c] = nq;
            }
        } 
    }
}sam;

struct Suffix_Tree {
    int ch[N][26], pos[N], tp;
    bool val[N];
    void Add(int u, int v, int c) {ch[u][c] = v;}
    void Build() {
        for(int i = 1;i <= sam.sz; ++i) val[i] = sam.val[i], pos[i] = sam.pos[i];
        for(int i = 2;i <= sam.sz; ++i) 
            Add(sam.fa[i], i, s[pos[i] + sam.len[sam.fa[i]]]);
    }
    void Dfs(int u) {
        if(val[u]) sa[rnk[pos[u]] = ++tp] = pos[u];
        for(int i = 0 ;i < 26; ++i) 
        if(ch[u][i]) Dfs(ch[u][i]);
    }
}suftree;

int main() {
    readchar();
    for(int i = n; i >= 1; --i) sam.Extend(s[i], i);
    suftree.Build();
    suftree.Dfs(1);
    for(int i = 1;i <= n; ++i) printf("%d ", sa[i]);
    putchar('\n');
    return 0;
}
