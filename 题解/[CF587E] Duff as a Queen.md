### [链接](https://codeforces.com/contest/587/problem/E)
又是一道数据结构。

首先看到“不同子集数量”，想到线性基。由于线性基求的是线性无关组，可以发现基底之间互相异或之后不改变结果。答案就是 $2^{\text{基底}}$。

所以我们可以直接取差分后的结果，即 $b_i=a_{i-1}\operatorname{xor}a_i$。那么这样可以发现查询 $[l,r]$ 等同于查 $a_l,b_{l+1},b_{l+2}\cdots b_r$，修改就是对于 $b_i$ 就是单修区查。

但是线性基十分恶心，只能支持插入。

考虑如果查询的是整个区间怎么处理。有一种做法是线段树分治，即将查询与询问离线，统计每一种询问对之后的贡献。

但是这样没有办法处理区间的情况。考虑用线段树套线性基，即每个线段树的节点是一个线性基。表示的是这段区间内的线性基情况。

而线性基是支持合并的。主要原因是线性基的基个数是 $\log \text{值域}$ 的，所以我们可以直接暴力将一个线性基的元素插入到另一个线性基中。

这样一次对 $b_i$ 的单点修改可以通过重构线段树上的一系列点完成。一次操作 $O(log^2 a\log n)$。

而查询可以先查 $b$ 中 $(l,r]$ 的线性基，再将 $a_l$ 插入。一次查询 $O(\log^2 a\log n)$。

总时间复杂度 $O(m\log^2 a\log n)$，由于 $m$ 不大，可以勉强通过。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define N 200010
using namespace std;
struct base{
	#define B 30
	int b[B+2],tot;
	base(){memset(b,0,sizeof(b));tot=0;}
	void clear(){memset(b,0,sizeof(b));tot=0;}
	void insert(int x)
	{
		for(int i=B;i>=0;i--)
		if((x>>i)&1){if(b[i]) x^=b[i]; else{b[i]=x;++tot;return;}}
	}
};
base operator +(base a,base b)
{
	for(int i=0;i<B;i++)
	if(b.b[i]) a.insert(b.b[i]);
	return a;
}
base val[N<<2];
int a[N],b[N];
void build(int u,int l,int r)
{
	if(l==r){val[u].insert(b[l]);return;}
	int mid=(l+r)>>1;
	build(u<<1,l,mid),build(u<<1|1,mid+1,r);
	val[u]=val[u<<1]+val[u<<1|1];
}
void insert(int u,int l,int r,int p,int v)
{
	if(l==r){val[u].clear();val[u].insert(v);return;}
	int mid=(l+r)>>1;
	if(p<=mid) insert(u<<1,l,mid,p,v);
	else insert(u<<1|1,mid+1,r,p,v);
	val[u]=val[u<<1]+val[u<<1|1];
}
base ans;
void answer(int u,int l,int r,int L,int R)
{
	if(L<=l && r<=R){ans=ans+val[u];return;}
	int mid=(l+r)>>1;
	if(L<=mid) answer(u<<1,l,mid,L,R);
	if(R>mid) answer(u<<1|1,mid+1,r,L,R);
}
namespace t2{
	int val[N<<2];
	void build(int u,int l,int r)
	{
		if(l==r){val[u]=b[l];return;}
		int mid=(l+r)>>1;
		build(u<<1,l,mid),build(u<<1|1,mid+1,r);
		val[u]=val[u<<1]^val[u<<1|1];
	}
	void insert(int u,int l,int r,int p,int v)
	{
		if(l==r){val[u]=v;return;}
		int mid=(l+r)>>1;
		if(p<=mid) insert(u<<1,l,mid,p,v);
		else insert(u<<1|1,mid+1,r,p,v);
		val[u]=val[u<<1]^val[u<<1|1];
	}
	int answer(int u,int l,int r,int L,int R)
	{
		if(L<=l && r<=R) return val[u];
		int mid=(l+r)>>1,ans=0;
		if(L<=mid) ans^=answer(u<<1,l,mid,L,R);
		if(R>mid) ans^=answer(u<<1|1,mid+1,r,L,R);
		return ans;
	}
}
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]),b[i]=a[i-1]^a[i];
	build(1,1,n);
	t2::build(1,1,n);
	for(int i=1;i<=m;i++)
	{
		int opt,l,r,v;
		scanf("%d%d%d",&opt,&l,&r);
		if(opt==1)
		{
			scanf("%d",&v);
			b[l]^=v;
			b[r+1]^=v;
			insert(1,1,n,l,b[l]);
			insert(1,1,n,r+1,b[r+1]);
			t2::insert(1,1,n,l,b[l]);
			t2::insert(1,1,n,r+1,b[r+1]);
		}
		else
		{
			ans.clear();
			if(l!=r) answer(1,1,n,l+1,r);
			ans.insert(t2::answer(1,1,n,1,l));
			printf("%lld\n",1ll<<ans.tot);
		}
	}
	return 0;
}
```
