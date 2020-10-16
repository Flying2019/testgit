### [链接](https://www.luogu.com.cn/problem/P3332)
首先考虑假如所有操作范围都是整个区间怎么办。很明显，直接用权值线段树/平衡树即可。

接下来考虑修改是一个子区间，很套路地套上一个线段树即可。

区间线段树套权值线段树，对区间线段树的每个节点开一颗动态开点权值线段树，然后修改时找到区间线段树的每个节点打修改 $tag$ 即可。

复杂度 $O(n\log^2 n)$。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
#define N 400010
#define M N*60
using namespace std;
int ls[M],rs[M],tag[M];
ll val[M];
int rt[N],cnt;
void push_down(int u,int l,int r)
{
	if(!tag[u]) return;
	int mid=(l+r)>>1;
	if(!ls[u]) ls[u]=++cnt;
	if(!rs[u]) rs[u]=++cnt;
	tag[ls[u]]+=tag[u];
	tag[rs[u]]+=tag[u];
	val[ls[u]]+=1ll*tag[u]*(mid-l+1);
	val[rs[u]]+=1ll*tag[u]*(r-mid);
	tag[u]=0;
}
void insert(int &u,int l,int r,int L,int R)
{
	if(!u) u=++cnt;
	if(L<=l && r<=R){tag[u]++;val[u]+=r-l+1;return;}
	push_down(u,l,r);
	int mid=(l+r)>>1;
	if(L<=mid) insert(ls[u],l,mid,L,R);
	if(R>mid) insert(rs[u],mid+1,r,L,R);
	val[u]=val[ls[u]]+val[rs[u]];
}
ll answer(int u,int l,int r,int L,int R)
{
	if(!u || L>R) return 0;
	if(L<=l && r<=R) return val[u];
	int mid=(l+r)>>1;
	push_down(u,l,r);
	ll res=0;
	if(L<=mid) res+=answer(ls[u],l,mid,L,R);
	if(R>mid) res+=answer(rs[u],mid+1,r,L,R);
	return res;
}
int n,m;
void insert(int u,int l,int r,int L,int R,int p)
{
	insert(rt[u],1,n,L,R);
	if(l==r) return;
	int mid=(l+r)>>1;
	if(p<=mid) insert(u<<1,l,mid,L,R,p);
	else insert(u<<1|1,mid+1,r,L,R,p);
}
int num[N],tot;
int answer(int u,int l,int r,int L,int R,ll p)
{
	if(l==r) return num[l];
	int mid=(l+r)>>1;
	ll res=answer(rt[u<<1|1],1,n,L,R);
	if(res<p) return answer(u<<1,l,mid,L,R,p-res);
	else return answer(u<<1|1,mid+1,r,L,R,p);
}
struct ques{
	int opt,l,r,k;
}q[N];
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d%d",&q[i].opt,&q[i].l,&q[i].r,&q[i].k);
		if(q[i].opt==1)num[++tot]=q[i].k;
	}
	sort(num+1,num+tot+1);
	tot=unique(num+1,num+tot+1)-num-1;
	for(int i=1;i<=m;i++)
	if(q[i].opt==1) q[i].k=lower_bound(num+1,num+tot+1,q[i].k)-num;
	for(int i=1;i<=m;i++)
	if(q[i].opt==1) insert(1,1,tot,q[i].l,q[i].r,q[i].k);
	else printf("%d\n",answer(1,1,tot,q[i].l,q[i].r,q[i].k));
	return 0;
}
```
