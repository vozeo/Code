// luogu-judger-enable-o2
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<queue>
#include<cstring>
#define N 1000100
using namespace std;

typedef unsigned int ui;
    ui randNum(ui& seed, ui last, ui m) {
    seed = seed * 17 + last;
    return seed % m + 1;
}

struct node{
    int w,t;
};

bool operator >(node a,node b){
    if(a.w==b.w) return a.t<b.t;
    return a.w>b.w;
}

bool operator <(node a,node b){
    if(a.w==b.w) return a.t>b.t;
    return a.w<b.w;
}

bool operator !=(node a,node b){
    return (a.w!=b.w)||(a.t!=b.t);
}

int fa[N],ch[N][2],size[N],cnt[N];
node val[N];
int ac[N],at[N];
ui seed,last,m;
int n,rt,tot,T;

void up(int x){
    size[x]=size[ch[x][1]]+size[ch[x][0]]+cnt[x];
}

void rot(int x){
    int y=fa[x],z=fa[fa[x]];
    int k=(ch[y][1]==x);
    fa[x]=z;
    ch[z][ch[z][1]==y]=x;
    fa[ch[x][k^1]]=y;
    ch[y][k]=ch[x][k^1];
    fa[y]=x;
    ch[x][k^1]=y;
    up(y),up(x);
}

void splay(int x,int g){
    while(fa[x]!=g){
        int y=fa[x],z=fa[fa[x]];
        if(z!=g)
            (ch[y][1]==x)^(ch[z][1]==y)? rot(x):rot(y);
        rot(x);
    }
    if(g==0) rt=x;
}

void ins(node x){
    int u=rt,ff=0;
    while(u&&x!=val[u]) ff=u,u=ch[u][x>val[u]];
    if(u) cnt[u]++;
    else{
        u=++tot;
        if(ff) ch[ff][x>val[ff]]=u;
        fa[u]=ff;
        size[u]=cnt[u]=1;
        ch[u][1]=ch[u][0]=0;
        val[u]=x;
    }
    splay(u,0);
}

int find(node x){
    int u=rt;
    while(val[u]!=x) u=ch[u][x>val[u]];
    return u;
}

int get(node x,int c){
    int u=find(x);
    splay(u,0);
    u=ch[u][c];
    while(ch[u][c^1]) u=ch[u][c^1];
    return u;
}

void del(node x){
    int mm=get(x,0),nn=get(x,1);
    splay(mm,0);
    splay(nn,mm);
    int dd=ch[nn][0];
    if(cnt[dd]>1){
        cnt[dd]--;
        splay(dd,0);
    }
    else ch[nn][0]=0;
}

int kth(node x){
    int u=find(x);
    splay(u,0);
    return size[ch[u][1]];
}

void clear(){
    memset(ac,0,sizeof ac);
    memset(at,0,sizeof at);
    memset(val,0,sizeof val);
    memset(fa,0,sizeof fa);
    memset(ch,0,sizeof ch);
    memset(size,0,sizeof size);
    memset(cnt,0,sizeof cnt);
    rt=0;
    tot=0;
}

int main(){
//	freopen("test.in","r",stdin);
//	freopen("test.out","w",stdout);
    scanf("%d",&T);
    last=7;
    while(T--){
        cin>>m>>n>>seed;
        ins((node){0,1<<30});
        ins((node){1<<30,0});
        while(n--){
            int kx=randNum(seed,last,m),ky=randNum(seed,last,m);
            cin>>kx>>ky;
            node his=(node){ac[kx],at[kx]};
            if(his.w!=0||his.t!=0) del(his);
            ac[kx]+=1,at[kx]+=ky;
            his.w+=1,his.t+=ky;
            ins(his);
            last=kth(his)-1;
            printf("%d\n",last);
        }
        clear();
    }
    return 0;
}
