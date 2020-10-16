### [链接](https://codeforces.com/contest/629/problem/E)
一个环要包含 $u\rightarrow v$ 的路径，显然其两端需要分别在删去这条路径后 $u$ 和 $v$ 的联通块中。

可以发现，只需要统计出 $u$ 联通块内的所有点到 $u$ 的距离和除以联通块大小，加上 $v$ 的同样处理，再加上路径长度+1就是答案。

显然当 $u$ 和 $v$ 不存在祖先关系时答案就是 $u$ 的子树信息。

而如果存在祖先关系，可以发现此时 $u$ 的范围会减去 $v$ 的所在子树，加上 $u$ 的父亲。直接再dfs处理一次即可。

复杂度 $O(n\log n)$（处理lca复杂度）。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define N 200010
#define ll long long
using namespace std;
int nxt[N<<1],to[N<<1],head[N],cnt;
void add(int u,int v)
{
	nxt[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
}
int fa[N],son[N];
ll dep[N],siz[N],dsiz[N];
int top[N],n;
void dfs(int u,int f)
{
	fa[u]=f;
	dep[u]=dep[f]+1,siz[u]=1,dsiz[u]=dep[u];
	for(int i=head[u];i;i=nxt[i])
	{
		int v=to[i];
		if(v==f) continue;
		dfs(v,u);
		siz[u]+=siz[v];
		dsiz[u]+=dsiz[v];
		if(siz[son[u]]<siz[v]) son[u]=v;
	}
}
void dfs2(int u,int topp)
{
	top[u]=topp;
	dsiz[u]=dsiz[u]-dep[u]*siz[u];
	if(son[u]) dfs2(son[u],topp);
	for(int i=head[u];i;i=nxt[i])
	{
		int v=to[i];
		if(v!=fa[u] && v!=son[u]) dfs2(v,v);
	}
}
ll qsiz[N];
void dfs3(int u,ll pre)
{
	qsiz[u]=pre;
	for(int i=head[u];i;i=nxt[i])
	{
		int v=to[i];
		if(v!=fa[u]) dfs3(v,pre+dsiz[u]-dsiz[v]-siz[v]+n-siz[v]);
	}
}
int lca(int x,int y,int &pre)
{
	int u=dep[x]<dep[y]?x:y;
	for(;top[x]!=top[y];x=fa[top[x]])
	{
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		pre=top[x];
	}
	if(dep[x]>dep[y]) swap(x,y);
	if(x!=u) pre=0;
	if(pre && (x!=y || fa[pre]!=x)) pre=son[x];
	return x;
}
int main()
{
	int m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<n;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v),add(v,u);
	}
	dfs(1,0);
	dfs2(1,1);
	dfs3(1,0);
	for(int i=1;i<=m;i++)
	{
		int x,y;
		ll s1,z1,s2,z2;
		scanf("%d%d",&x,&y);
		if(dep[x]>dep[y]) swap(x,y);
		int p=x;
		int l=lca(x,y,p),d=dep[x]+dep[y]-2*dep[l];
		if(!p) s1=dsiz[x],z1=siz[x],s2=dsiz[y],z2=siz[y];
		else z1=n-siz[p],s1=qsiz[x]+dsiz[x]-dsiz[p]-siz[p],s2=dsiz[y],z2=siz[y];
		printf("%.8lf\n",(double)s1/z1+(double)s2/z2+d+1);
	}
	return 0;
}
```
