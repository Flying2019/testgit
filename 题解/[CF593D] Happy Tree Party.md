### [链接](https://codeforces.com/problemset/problem/593/D)
考虑询问全部都是除+下取整，而除一个 $>1$ 的数字最多只会除60次就变成0。所以暴力是可行的。

那么问题就在于修改边权和1了。对于边权我们可以换成点权，这样可以直接跳lca求。而对于1我们直接用一个类似于并查集的东西，将它指向第一个点权不是1的点。

这样一次操作是 $O(n\log a+n\alpha)$ 的，显然可以通过。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define N 200010
#define ll long long
using namespace std;
int nxt[N<<1],to[N<<1],head[N],cnt=1;
int ids[N];
ll wr[N<<1];
void add(int u,int v,ll w1)
{
	nxt[++cnt]=head[u];
	to[cnt]=v;
	wr[cnt]=w1;
	head[u]=cnt;
}
int dep[N],fa[N],ffa[N];
ll w[N];
void dfs(int u,int f)
{
	dep[u]=dep[fa[u]=f]+1;
	ffa[u]=w[u]==1?ffa[fa[u]]:u;
	for(int i=head[u];i;i=nxt[i])
	{
		int v=to[i];
		if(v==f) continue;
		w[v]=wr[i];
		ids[i/2]=v;
		dfs(v,u);
	}
}
int find(int x){return ffa[x]==x?x:(ffa[x]=find(ffa[x]));}
#define MM 1000000000000000001ll
ll work(int x,int y,ll w1)
{
	ll ans=w1;
	for(;x!=y;x=find(fa[x]))
	{
		if(dep[x]<dep[y]) swap(x,y);
		ans=ans/w[x];
		if(!ans) return 0;
	}
	return ans;
}
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<n;i++)
	{
		int u,v;
		ll w;
		scanf("%d%d%lld",&u,&v,&w);
		add(u,v,w),add(v,u,w);
	}
	dfs(1,0);
	for(int i=1;i<=m;i++)
	{
		int opt;
		ll x,y,z;
		scanf("%d%lld%lld",&opt,&x,&y);
		if(opt==1)
		{
			scanf("%lld",&z);
			printf("%lld\n",work(x,y,z));
		}
		else
		{
			x=ids[x];
			w[x]=y;
			if(y==1) ffa[x]=ffa[fa[x]];
		}
	}
	return 0;
}
```
