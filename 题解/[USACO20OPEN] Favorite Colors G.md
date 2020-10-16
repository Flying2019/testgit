### [链接](https://www.luogu.com.cn/problem/P6279)
转换题意：每次可以将一个一个点连入的所有点合并成一个点，问最后每个点的合并信息。

考虑最后剩下的点，每个点连入的最多只有一个点。所以我们不妨钦定一个点，将其他点合并到这个点上去。

所以我们枚举每个点，依次合并。当父节点合并了之后，子节点也需要递归合并。如果子节点是一个环可能还需要合并多次。

特别的，如果有自环（合并过后的环也算）需要特判。

看似复杂度很假，但是每次合并必然会合并两个点，所以合并次数是 $O(n)$ 的。

总复杂度 $O(n\cdot\alpha(n))$。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define N 200010
using namespace std;
int nxt[N<<1],to[N<<1],head[N],cnt;
void add(int u,int v)
{
	nxt[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
}
int f[N],tf[N],tot;
int find(int x){return x==f[x]?f[x]:(f[x]=find(f[x]));}
void dfs(int);
void merge(int u,int v)
{
	u=find(u),v=find(v);
	if(u==v) return;
	f[u]=v;
	if(!tf[u] || !tf[v]){tf[v]|=tf[u];return;}
	merge(tf[u],tf[v]);
}
bool sf[N];
void dfs(int u)
{
	if(tf[u]) return;
	for(int i=head[u];i;i=nxt[i])
	{
		int v=find(to[i]);
		if(!tf[u]) tf[u]=v;
		dfs(v);
		merge(tf[u],v);
	}
}
int vis[N];
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v);
	}
	for(int i=1;i<=n;i++) f[i]=i;
	for(int x=1;x<=n;x++)
	{
		int u=find(x);
		for(int i=head[x];i;i=nxt[i]) sf[u]|=find(to[i])==u;
		if(!sf[u]) u=(tf[u]?tf[u]:(tf[u]=to[head[x]]));
		for(int i=head[x];i;i=nxt[i]) merge(to[i],u);
	}
	int t=0;
	for(int i=1;i<=n;i++)
	{
		if(!vis[find(i)]) vis[find(i)]=++t;
		printf("%d\n",vis[find(i)]);
	}
	return 0;
}
/*
9 10
1 2
2 3
3 1
2 4
5 4
5 6
6 7
7 8
8 9
9 5
*/
```
