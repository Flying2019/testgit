### [链接](http://codeforces.com/problemset/problem/553/D)
看到最大化最小值，首先二分最小值 $x$。

可以发现，假如我们认为所有点都选上后某个点 $u$ 的结果还是 $<x$ ，那么 $u$ 一定不能选。

那么我们考虑将这些不能选的点插入队列中依次对其相邻的点进行处理，如果不能选继续插入队列。

假如最后还有点选上，那么答案就合法，否则不合法。

注意精度问题。

时间复杂度 $O(n\log n)$。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define N 100010
using namespace std;
queue<int>q;
int nxt[N<<1],to[N<<1],head[N],cnt;
int deg[N],in[N],n;
bool cut[N];
void add(int u,int v)
{
	nxt[++cnt]=head[u];
	to[cnt]=v;
	deg[u]++;
	head[u]=cnt;
}
bool check(double x)
{
	for(int i=1;i<=n;i++) in[i]=cut[i]?0:deg[i];
	if(x<=1e-8) return true;
	for(int u=1;u<=n;u++)
	if(in[u])
		for(int i=head[u];i;i=nxt[i])
		if(cut[to[i]]) in[u]--;
	for(int i=1;i<=n;i++)
	if(in[i] && 1.0*in[i]/deg[i]<x) q.push(i),in[i]=0;
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		for(int i=head[u];i;i=nxt[i])
		{
			int v=to[i];
			if(!in[v]) continue;
			in[v]--;
			if(1.0*in[v]/deg[v]<x) q.push(v),in[v]=0;
		}
	}
	for(int i=1;i<=n;i++)
	if(in[i]) return true;
	return false;
}
int ans[N];
int main()
{
	int m,k;
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=k;i++)
	{
		int a;
		scanf("%d",&a);
		cut[a]=true;
	}
	for(int i=1;i<=m;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v),add(v,u);
	}
	double l=0,r=1;
	while(r-l>=1e-9)
	{
		double mid=(l+r)/2;
		if(check(mid)) l=mid,memcpy(ans,in,sizeof(ans));
		else r=mid;
	}
	int cnt=0;
	for(int i=1;i<=n;i++)
	if(ans[i]) ++cnt;
	printf("%d\n",cnt);
	for(int i=1;i<=n;i++)
	if(ans[i]) printf("%d ",i);
	return 0;
}
```
