### [链接](https://codeforces.com/problemset/problem/1220/E)
首先一个环上可以任意走，那么环与环之间的边也可以任意走。

所以一个点只要可以不断地往后走，它就可以被经过。相反，如果有一些点是死胡同，即进去了之后出不来的，那么这些点中就只能选择一个走。

接下来就是考虑如何选择了。我们先按无向图拓扑排序一下，那么剩下的点就是可以任意到达的。注意这里我们拓扑排序需要去掉 $s$ ，因为 $s$ 显然可以被任意到达。

我们称被删掉的点是拓扑点，其中直接挂在可以被任意到达点上的点称为标记点。显然以标记点为根的拓扑点构成一系列有根森林，那么最后答案就是总 $w_i$ 的和减去这个森林中的 $w_i$ 的和加上一条最大的从根到叶子的路径 $w_i$ 和。因为我们只能选择走一条路径。

由于是无向图拓扑，这里可以直接处理出每个点唯一的转移点。如果这个转移点最后是可以任意到达的，那么它就是一个标记点。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define N 200010
#define ll long long
using namespace std;
int nxt[N<<1],to[N<<1],head[N],cnt;
int deg[N];
void add(int u,int v)
{
	nxt[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	deg[u]++;
}
queue<int>q;
ll w[N];
bool cut[N];
int fa[N];
void topo(int n,int x)
{
	for(int i=1;i<=n;i++)
	if(deg[i]==1 && i!=x) q.push(i);
	while(!q.empty())
	{
		int u=q.front();
		cut[u]=true;
		q.pop();
		for(int i=head[u];i;i=nxt[i])
		{
			int v=to[i];
			if(cut[v]) continue;
			fa[u]=v,deg[v]--;
			if(deg[v]==1) q.push(v);
		}
	}
}
ll sm;
ll dfs(int u)
{
	sm+=w[u];
	ll maxn=0;
	for(int i=head[u];i;i=nxt[i])
	{
		int v=to[i];
		if(!cut[v] || v==fa[u]) continue;
		maxn=max(maxn,dfs(v));
	}
	return maxn+w[u];
}
int main()
{
	int n,m,x;
	scanf("%d%d",&n,&m);
	ll ans=0,res=0;
	for(int i=1;i<=n;i++) scanf("%lld",&w[i]),ans+=w[i];
	for(int i=1;i<=m;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v),add(v,u);
	}
	scanf("%d",&x);deg[x]++;
	topo(n,x);
	for(int i=1;i<=n;i++)
	if(cut[i] && !cut[fa[i]]) res=max(res,dfs(i));
	printf("%lld\n",ans+res-sm);
	return 0;
}
```
