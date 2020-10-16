### [链接](http://codeforces.com/problemset/problem/527/E)
构造好题。

首先考虑判断最小加边数。可以发现“每个点出入度都是偶数”意味着无向图中每个点的度数都是偶数，这相当于一条欧拉回路。

所以显然先把所有奇度数的点之间两两连边，这样就可以得到一张欧拉回路图。

可以发现，如果总边数是偶数，那么我们只需要把欧拉回路中的边每相邻两条方向不同即可。

如果总边数不是偶数，把某个点向自己连一条自环即可。

跑欧拉回路时顺便输出方案。复杂度 $O(n+m)$。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define N 200010
using namespace std;
int nxt[N<<3],to[N<<3],head[N],cnt=1;
int vis[N<<3],deg[N];
void add(int u,int v)
{
	nxt[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	nxt[++cnt]=head[v];
	to[cnt]=u;
	head[v]=cnt;
	deg[u]++,deg[v]++;
}
void dfs(int u,int &p)
{
	for(int &i=head[u];i;i=nxt[i])
	if(!vis[i])
	{
		int v=to[i];
		vis[i]=vis[i^1]=true;
		dfs(v,p);
		p^=1;
		if(p) printf("%d %d\n",u,v);
		else printf("%d %d\n",v,u);
	}
}
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
	int pre=0,p=m;
	for(int i=1;i<=n;i++)
	if(deg[i]&1){if(pre) add(pre,i),++p,pre=0;else pre=i;}
	if(p&1) add(1,1),++p;
	printf("%d\n",p);
	dfs(1,p=0);
	return 0;
}
```
