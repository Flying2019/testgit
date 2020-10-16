### [链接](https://codeforces.com/problemset/problem/633/G)
首先看到“取模意义下的素数个数”就知道这题肯定不是什么常规题。通常先看一眼数据范围。

看到 $m\leq 1000$，说明其实模意义下的数字个数很少。

那就有了一种暴力的做法：首先子树很明显直接树剖，甚至都不用重链剖分，因为我们只需要子树内编号连续即可。

那么这样就变成了区间+，区间求本质不同素数个数。既然相同算一种那么就直接上bitset。用bitset 存下某个数字是否出现。

而模意义下的加对应bitset的循环位移。然后预处理出 $m$ 以内质数的对应bitset，最后直接把算出来的结果与上这个bitset，1的个数就是答案。

由于这里只有区间循环位移区间查，甚至可以直接标记永久化，减少常数。

总时间复杂度 $O(\frac{nm\log n}{\omega})$。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<bitset>
#define N 100010
#define M 1010
#define BT bitset<M>
using namespace std;
int n,m,w[N],head[N],nxt[N<<1],to[N<<1],cnt;
void add(int u,int v)
{
	nxt[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
}
BT o[M],rm;
BT p[N<<2];
BT operator +(BT a,int v){return a>>v|(a&o[v])<<(m-v);}
int tag[N<<2];
void insert(int u,int l,int r,int L,int R,int v)
{
	if(L<=l && r<=R){tag[u]=(tag[u]+v+m)%m;return;}
	int mid=(l+r)>>1;
	if(L<=mid) insert(u<<1,l,mid,L,R,v);
	if(R>mid) insert(u<<1|1,mid+1,r,L,R,v);
	p[u]=(p[u<<1]+tag[u<<1])|(p[u<<1|1]+tag[u<<1|1]);
}
BT ans;
void answer(int u,int l,int r,int L,int R,int v=0)
{
	v=(v+tag[u])%m;
	if(L<=l && r<=R){ans|=p[u]+v;return;}
	int mid=(l+r)>>1;
	if(L<=mid) answer(u<<1,l,mid,L,R,v);
	if(R>mid) answer(u<<1|1,mid+1,r,L,R,v);
}
int id[N],nid[N],siz[N],tot;
void build(int u,int l,int r)
{
	if(l==r){p[u].set(w[nid[l]]);return;}
	int mid=(l+r)>>1;build(u<<1,l,mid),build(u<<1|1,mid+1,r);
	p[u]=p[u<<1]|p[u<<1|1];
}
void dfs(int u,int f)
{
	siz[u]=1;
	nid[id[u]=++tot]=u;
	for(int i=head[u];i;i=nxt[i])
	{
		int v=to[i];
		if(v==f) continue;
		dfs(v,u);
		siz[u]+=siz[v];
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&w[i]),w[i]%=m;
	for(int i=1;i<=m;i++) o[i]=o[i-1]<<1,o[i].set(0);
	for(int i=1;i<n;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v),add(v,u);
	}
	for(int i=2;i<m;i++)
	{
		bool can=true;
		for(int j=2;j*j<=i;j++) can&=(i%j!=0);
		if(can) rm.set(i);
	}
	dfs(1,0);
	build(1,1,n);
	int q;
	scanf("%d",&q);
	while(q --> 0)
	{
		int opt,u,v;
		scanf("%d%d",&opt,&u);
		if(opt==1) scanf("%d",&v),insert(1,1,n,id[u],id[u]+siz[u]-1,m-v%m);
		else
		{
			ans.reset();
			answer(1,1,n,id[u],id[u]+siz[u]-1);
			printf("%d\n",(int)(ans&rm).count());
		}
	}
	return 0;
}
```
