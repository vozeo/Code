#include<bits/stdc++.h>

#define maxn 1000010
using namespace std;

struct tree{
	int l,r;
	int dat,val;
	int size,cnt;
}tre[maxn];

int root,tot,n,INF=0x7fffffff;

int New(int val){
    ++tot;
	tre[tot].cnt=tre[tot].size=1;
	tre[tot].val=val;
	tre[tot].dat=rand();
	return tot;
}
void update(int x){
	tre[x].size=tre[tre[x].l].size+tre[tre[x].r].size+tre[x].cnt;
	return;
}
void zig(int &p){
	int q=tre[p].l;
	tre[p].l=tre[q].r,tre[q].r=p;
	p=q;
	update(tre[p].r),update(p);
	return;
}
void zag(int &p){
	int q=tre[p].r;
	tre[p].r=tre[q].l,tre[q].l=p;
	p=q;
	update(tre[p].l),update(p);
	return;
}
void build(){
	New(-INF),New(INF);
	tre[1].r=2;
	root=1;
	update(1);
}
void insert(int &p,int val){
	if(p==0){
		p=New(val);
		return;
	}
	if(val==tre[p].val){
		tre[p].cnt++;
		update(p);
		return;
	}
	if(val<tre[p].val){
		insert(tre[p].l,val);
		if(tre[p].dat<tre[tre[p].l].dat)zig(p);
		
	}
	else{
		insert(tre[p].r,val);
		if(tre[p].dat<tre[tre[p].r].dat)zag(p);
	}
	update(p);
}
void remove(int &p,int val){
	if(p==0){
		return;
	}
	if(val==tre[p].val){
		if(tre[p].cnt>1){
			tre[p].cnt--;
			update(p);
			return;
		}
		if(tre[p].l||tre[p].r){
			if(tre[p].r==0||tre[tre[p].l].dat>tre[tre[p].r].dat){
				zig(p),remove(tre[p].r,val);
			}
			else{
				zag(p),remove(tre[p].l,val);
			}
			update(p);
		}
		else p=0;
        return;
	} 
	if(val<tre[p].val){
		remove(tre[p].l,val);
	}
	else{
		remove(tre[p].r,val);
	}
	update(p);
}
int getrank(int p,int val){
	//smaller
	if(p==0)return 0;
	if(val==tre[p].val){
		return tre[tre[p].l].size+1;
	}
	if(val<tre[p].val){
		return getrank(tre[p].l,val);
	}
	return getrank(tre[p].r,val)+tre[tre[p].l].size+tre[p].cnt;
}
int getval(int p,int x){
	if(p==0)return INF;
	if(tre[tre[p].l].size>=x){
		return getval(tre[p].l,x);
	}
	if(tre[tre[p].l].size+tre[p].cnt>=x){
		return tre[p].val;
	}
	return getval(tre[p].r,x-tre[tre[p].l].size-tre[p].cnt);
}
int getpre(int val){
	int ans=1;
	int p=root;
	while(p){
		if(val==tre[p].val){
			if(tre[p].l>0){
				p=tre[p].l;
				while(tre[p].r>0){
					p=tre[p].r;
				}
				ans=p;
			}
			break;
		}
		if(tre[p].val<val&&tre[p].val>tre[ans].val){
			ans=p;
		}
		if(tre[p].val>val){
			p=tre[p].l;
		}
		else{
			p=tre[p].r;
		}
		
	}
	return tre[ans].val;
}
int getnext(int val){
	int ans=2;
	int p=root;
	while(p){
		if(tre[p].val==val){
			if(tre[p].r){
				p=tre[p].r;
				while(tre[p].l){
					p=tre[p].l;
				}
				ans=p;
			}
			break;
		}
		if(tre[p].val>val&&tre[ans].val>tre[p].val){
			ans=p;
		}
		if(tre[p].val>val){
			p=tre[p].l;
		}
		else{
			p=tre[p].r;
		}
	} 
	return tre[ans].val;
}
int main(){
	build();
    /* cout << tre[2].val << endl; */
	cin>>n;
	while(n--){
		int caozuo,x;
		scanf("%d%d",&caozuo,&x);
		if(caozuo==1){
			insert(root,x);
			continue;
		}
		if(caozuo==2){
			remove(root,x);
			continue;
		}
		if(caozuo==3){
			cout<<getrank(root,x) - 1<<endl;//in fact getrank(root,x)-1;
			continue;
		}
		if(caozuo==4){
			cout<<(getval(root,x+1))<<endl;
			continue;
		}
		if(caozuo==5){
			cout<<getpre(x)<<endl;
			continue;
		}
		if(caozuo==6){
			cout<<getnext(x)<<endl;
			continue;
		}
		
	} 
	
	return 0;
} 
