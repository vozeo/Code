// luogu-judger-enable-o2
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<queue>
#include<cmath>
#define N 100010
#define M 20
#define ll long long
using namespace std;

int read(){
    int x=0;bool k=false;char a=getchar();
    while((a!='-')&&(a>'9'||a<'0')) a=getchar();
    if(a=='-') k=true,a=getchar();
    while(a>='0'&&a<='9') x=(x<<1)+(x<<3)+a-48,a=getchar();
    return k? -x:x;
}

int n,m,block;

struct que{
    int id,l,r;
}q[N];
bool operator <(que a,que b){
    return (a.l/block)==(b.l/block)? ((b.l/block)&1)?  (a.r<b.r) : (a.r>b.r) : a.l<b.l;
}

ll a[N],lf[N],rf[N],fl[N],fr[N],res[N];
int sta[N],top;

struct _ST{
    ll f[N][M];
    int k;

    void pre(){
        k=log2(n);
        for(int i=1;i<=n;i++) f[i][0]=i;

        for(int j=1;j<=k;j++){
            for(int i=1;i+(1<<j)-1<=n;i++){
                ll la=a[f[i][j-1]],lb=a[f[i+(1<<(j-1))][j-1]];
                if(la<lb){
                    f[i][j]=f[i][j-1];
                }
                else f[i][j]=f[i+(1<<(j-1))][j-1];
            }
        }
    }

    ll query(int l,int r){
        int p=log2(r-l+1);
        ll la=a[f[l][p]],lb=a[f[r-(1<<p)+1][p]];
        if(la<lb) return f[l][p];
        else return f[r-(1<<p)+1][p];
    }
}ST;

void get_left(){
    memset(sta,0,sizeof sta);
    top=0;
    for(int i=1;i<=n;i++){
        while(top&&a[i]<a[sta[top]]) top--;
        lf[i]=sta[top];
        sta[++top]=i;
    }
}

void get_right(){
    memset(sta,0,sizeof sta);
    top=0;
    for(int i=n;i>=1;i--){
        while(top&&a[i]<a[sta[top]]) top--;
        rf[i]=sta[top];
        sta[++top]=i;
    }
}

void dp(){
    fl[1]=a[1];
    for(int i=2;i<=n;i++){
        fl[i]=fl[lf[i]]+(i-lf[i])*a[i];
    }

    fr[n]=a[n];
    for(int i=n;i>=1;i--){
        fr[i]=fr[rf[i]]+(rf[i]-i)*a[i];
    }
}

ll call(int l,int r){
    int p=ST.query(l,r);
    return (r-p+1)*a[p]+fr[l]-fr[p];
}

ll calr(int l,int r){
    int p=ST.query(l,r);
    return (p-l+1)*a[p]+fl[r]-fl[p];
}


int main(){
//	freopen("LP3246.in","r",stdin);
//	freopen("LP3246.out","w",stdout);
    n=read(),m=read(),block=sqrt(n);
    for(int i=1;i<=n;i++) a[i]=read();

    ST.pre();
    get_left();
    get_right();
    dp();


    for(int i=1;i<=m;i++){
        q[i].l=read(),q[i].r=read();
        q[i].id=i;
    }
    sort(q+1,q+1+m);

    int r=0,l=1,qr,ql;
    ll ans=0;
    for(int i=1;i<=m;i++){
        qr=q[i].r,ql=q[i].l;
        while(r<qr) ans+=calr(l,++r);
        while(l>ql) ans+=call(--l,r);
        while(r>qr) ans-=calr(l,r--);
        while(l<ql) ans-=call(l++,r);
        res[q[i].id]=ans;
    }

    for(int i=1;i<=m;i++) printf("%lld\n",res[i]);
    return 0;
}
