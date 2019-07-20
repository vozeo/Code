#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define Ls (v<<1)
#define Rs ((v<<1)|1)
using namespace std;
struct Node
{
	int L,R,Lmax,Rmax,sum,ans;
}T[200005];
int a[50005];
inline Node operator+(const Node& a,const Node& b)
{
	Node ans;ans.L=a.L;ans.R=b.R;
	ans.Lmax=max(a.Lmax,a.sum+b.Lmax);
	ans.Rmax=max(b.Rmax,a.Rmax+b.sum);
	ans.sum=a.sum+b.sum;
	ans.ans=max(max(a.ans,b.ans),a.Rmax+b.Lmax);
	return ans;
}
inline void pushup(int v)
{
	T[v]=T[Ls]+T[Rs];return;
}
inline void Build(int L,int R,int v)
{
	T[v].L=L;T[v].R=R;
	if(L==R)
	{
		T[v].Lmax=T[v].Rmax=T[v].sum=T[v].ans=a[L];
		return;
	}
	int mid=(L+R)>>1;
	Build(L,mid,Ls);
	Build(mid+1,R,Rs);
	pushup(v);
	return;
}
inline void Modify(int x,int val,int v)
{
	if(x>T[v].R||x<T[v].L)return;
	if(T[v].L==T[v].R)
	{
		T[v].Lmax=T[v].Rmax=T[v].sum=T[v].ans=val;
		return;
	}
	Modify(x,val,Ls);
	Modify(x,val,Rs);
	pushup(v);
	return;
}
inline Node Query(int L,int R,int v)
{
	if(L==T[v].L&&R==T[v].R)return T[v];
	int mid=(T[v].L+T[v].R)>>1;
	if(R<=mid)return Query(L,R,Ls);
	if(L>mid)return Query(L,R,Rs);
	return Query(L,mid,Ls)+Query(mid+1,R,Rs);
}
int main(void)
{
	int i,n,m,cmd,L,R;
	scanf("%d",&n);
	for(i=1;i<=n;++i)scanf("%d",&a[i]);
	Build(1,n,1);
	scanf("%d",&m);
	for(i=1;i<=m;++i)
	{
		scanf("%d%d%d",&cmd,&L,&R);
		if(cmd==0)Modify(L,R,1);
		else printf("%d\n",Query(L,R,1).ans);
	}
	return 0;
}