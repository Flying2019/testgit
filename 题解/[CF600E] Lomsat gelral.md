### [链接](https://www.luogu.com.cn/problem/CF600E)
经典问题。考虑如果采用暴力的解法，用一个数组记录所有的颜色出现次数，记录最大值和价值，对于每个点都做一遍，$O(n^2)$。

考虑其实很多的点被重新计算了很多遍。可以发现一个点其实可以继承它某个儿子中的所有信息，这样就不必重新递归处理该儿子。很显然继承其重儿子的信息的效率最高。可以证明一个点到根节点的路径上的轻边（连接父节点与非重儿子的边）最多 $\log n$ 条，所以一个点最多会被访问 $\log n$ 次，总时间复杂度 $O(n\log n)$。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define N 100010
#define ll long long
using namespace std;
int nxt[N<<1],to[N<<1],head[N],cnt;
int son[N],c[N],siz[N];
void add(int u,int v)
{
	nxt[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
}
int fa[N];
void get_son(int u,int pre)
{
	fa[u]=pre;
	siz[u]=1;
	for(int i=head[u];i;i=nxt[i])
	{
		int v=to[i];
		if(v==pre) continue;
		get_son(v,u);
		siz[u]+=siz[v];
		if(siz[v]>siz[son[u]]) son[u]=v;
	}
}
ll ans[N],tot[N],res,sum;
void dfs(int u,bool esc=false)
{
	tot[c[u]]++;
	if(tot[c[u]]&gt;res) res=tot[c[u]],sum=c[u];
	else if(tot[c[u]]==res) sum+=c[u];
	for(int i=head[u];i;i=nxt[i])
	{
		int v=to[i];
		if(v==fa[u] || (esc && v==son[u])) continue;
		dfs(v);
	}
}
void clear(int u)
{
	tot[c[u]]--;c[u];
	for(int i=head[u];i;i=nxt[i])
	if(to[i]!=fa[u]) clear(to[i]);
}
void solve(int u)
{
	for(int i=head[u];i;i=nxt[i])
	{
		int v=to[i];
		if(v==son[u] || v==fa[u]) continue;
		solve(v);
		clear(v);
		res=cnt=0;
	}
	if(son[u]) solve(son[u]);
	dfs(u,true);
	ans[u]=sum;
}
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&c[i]);
	for(int i=1;i<n;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v),add(v,u);
	}
	get_son(1,0);
	solve(1);
	for(int i=1;i<=n;i++) printf("%lld ",ans[i]);
	return 0;
}
```
