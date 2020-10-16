### [链接](https://www.luogu.com.cn/problem/P4137)
挺经典的问题，自然有很多做法：

#### 离线做法
直接套用莫队，线段树处理整体 $\operatorname{mex}$，复杂度 $O(n\sqrt{n}\log n)$，有点卡常。

考虑如何优化。事实上我们只需要进行 $O(m)$ 次查询，所以线段树 $O(\log n)$ 的查询并不是很有必要。

考虑用值域分块，修改 $O(1)$，查询 $O(\sqrt{n})$。总时间复杂度 $O(m\sqrt{n})$，可以通过。
#### 在线做法
考虑一种转化，即如果查询区间中没有数字 $x$，那么答案一定 $\leq x$。

再考虑如何处理。可以发现，如果把一段极长的连续区间 $[l,r]$ 看成一个点 $(l,r)$，可以发现查询 $[L,R]$ 等同于查询 $l\leq L\ ,\ r\geq R$ 的点中最小值。

显然就是一个经典二维数点问题，时空复杂度 $O(n\log^2 n)$。~~被卡空间了~~。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 200010
#define M N*200
#define B 556
using namespace std;
/*
int a[N];
int val[M]={100000000},ls[M],rs[M],root[N],tot;
void insert(int &u,int l,int r,int p,int v)
{
	if(!u) val[u=++tot]=1e8;
	if(l==r){val[u]=min(val[u],v);return;}
	int mid=(l+r)>>1;
	if(p<=mid) insert(ls[u],l,mid,p,v);
	else insert(rs[u],mid+1,r,p,v);
	val[u]=min(val[ls[u]],val[rs[u]]);
}
int answer(int u,int l,int r,int L,int R)
{
	if(!u) return 1e8;
	if(L<=l && r<=R) return val[u];
	int mid=(l+r)>>1,ans=1e8;
	if(L<=mid) ans=min(ans,answer(ls[u],l,mid,L,R));
	if(R>mid) ans=min(ans,answer(rs[u],mid+1,r,L,R));
	return ans;
}
int n;
void add(int x,int y,int v){for(;x<=n;x+=(x&(-x))) insert(root[x],0,n,y,v);}
int query(int x,int y)
{
	int ans=n;
	for(;x;x-=(x&(-x)))
	ans=min(ans,answer(root[x],0,n,y,n));
	return ans;
}
int pre[N];
int main()
{
	int m;
	scanf("%d%d",&n,&m);
	++n;
	for(int i=1;i<n;i++)
	{
		scanf("%d",&a[i]);
		a[i]=min(a[i],n);
		add(pre[a[i]]+1,i-1,a[i]);
		pre[a[i]]=i;
	}
	for(int i=0;i<=n;i++)
		add(pre[i]+1,n,i);
	for(int i=1;i<=m;i++)
	{
		int l,r;
		scanf("%d%d",&l,&r);
		printf("%d\n",query(l,r));
	}
	return 0;
}
*/
int a[N],ans[N];
int cnt[B][B],res[B];
void add(int x)
{
	int p=a[x]/B;
	res[p]+=!cnt[p][a[x]-p*B];
	cnt[p][a[x]-p*B]++;
}
void del(int x)
{
	int p=a[x]/B;
	cnt[p][a[x]-p*B]--;
	res[p]-=!cnt[p][a[x]-p*B];
}
int bl[N];
struct ques{
	int l,r,id;
	bool operator <(const ques a)const{return bl[l]==bl[a.l]?r<a.r:bl[l]<bl[a.l];}
}q[N];
int sq[N];
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]),a[i]=min(a[i],n+1),bl[i]=i/B;
	for(int i=1;i<=m;i++) scanf("%d%d",&q[i].l,&q[i].r),q[i].id=i;
	sort(q+1,q+m+1);
	int l=1,r=0;
	for(int i=1;i<=m;i++)
	{
		while(r<q[i].r) add(++r);
		while(r>q[i].r) del(r--);
		while(l>q[i].l) add(--l);
		while(l<q[i].l) del(l++);
		for(int j=0;j<B;j++)
		if(res[j]!=B)
		{
			for(int k=0;k<B;k++)
			if(!cnt[j][k]){ans[q[i].id]=j*B+k;break;}
			break;
		}
	}
	for(int i=1;i<=m;i++) printf("%d\n",ans[i]);
	return 0;
}
```
