#include<cstdio>
#include<algorithm>
#define C const int
#define R register int
#define getchar() (S==T&&(T=(S=BB)+fread(BB,1,1<<20,stdin),S==T)?EOF:*S++)
C N=500001;
char BB[1<<20],*S=BB,*T=BB;
int rk[N],rt[N],num[N],ord;
struct p{int x,id;}a[N];
struct T{int l,r,v;}tree[N*20];
inline bool cmp(const p u,const p v){return u.x<v.x;}
int build(C s,C t){
    C r=++ord;
    if(s!=t){int mid=(s+t)>>1;tree[r].l=build(s,mid),tree[r].r=build(mid+1,t);}
    return r;
}
int insert(C pre,C x,C s,C t){
    C r=++ord;
    tree[r].l=tree[pre].l,tree[r].r=tree[pre].r,tree[r].v=tree[pre].v+1;
    if(s!=t){
        C mid=(s+t)>>1;
        if(x<=mid) tree[r].l=insert(tree[pre].l,x,s,mid);
        else tree[r].r=insert(tree[pre].r,x,mid+1,t);
    }
    return r;
}
int query(C y,C x,C s,C t,C k){
    if(s==t) return s;
    C mid=(s+t)>>1;
    if(tree[tree[y].l].v-tree[tree[x].l].v>=k)
        return query(tree[y].l,tree[x].l,s,mid,k);
    else if(tree[tree[y].r].v-tree[tree[x].r].v>=k)
        return query(tree[y].r,tree[x].r,mid+1,t,k);
    else return 0;
}
inline int read(){
    R x=0;
    register char ch=getchar();
    while(ch<48) ch=getchar();
    while(ch>47) x=x*10+(ch^48),ch=getchar();
    return x;
}
inline void write(C x){if(x>9) write(x/10);putchar(x%10^48);}
int main(){
    C n=read();
    R m=read(),s=0,x,y;
    for(R i=1;i<=n;++i) a[i].x=read(),a[i].id=i;
    std::sort(a+1,a+n+1,cmp);
    for(R i=1;i<=n;++i){if(a[i].x!=a[i-1].x) a[++s].x=a[i].x;rk[a[i].id]=s;}
    build(1,s);
    for(R i=1;i<=n;++i) rt[i]=insert(rt[i-1],rk[i],1,s);
    while(m--){
        x=read(),y=read();
        write(a[query(rt[y],rt[x-1],1,s,(y-x+3)>>1)].x),putchar('\n');
    }
    return 0;
}
