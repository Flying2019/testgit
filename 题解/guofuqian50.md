### [链接](https://zjusummer.contest.codeforces.com/group/clkkguw3vK/contest/102657/problem/C)
### 题目大意
给定一个无向图，每条边有正边权，每个点有点权 $w_i$。有一些点被标记。假设某一天能见度为 $r_i$，那么定义一个点 $u$ 的危险度就是 $\sum{[\ v\text{被标记}\ ]\ [\ dis(v,u)\leq r_i\ ]}$。

如果一个点的危险度小于它的点权，那么称这个点是安全的。

接下来有 $n$ 天，第 $i$ 天能见度为 $r_i$。对于每个点，输出有多少天该点事安全的。
### 题解
看似条件有很多，其实可以发现对于一个点 $i$，只要第 $t$ 天的能见度 $r_t$ 小于离 $i$ 第 $w_i$ 近的标记点到 $i$ 的最短距离，那么它就是安全的。

所以我们只要找到距离 $i$ 第 $w_i$ 近的点即可。

考虑如果 $w_i=1$，我们只需要把每个标记点压入优先队列，跑一边最短路即可。

可以发现这道题中 $w_i\leq 20$，考虑在转移中加上一维，即该点是以哪一个点 $u$ 为起点转移过来的。如果该点已经 $u$ 被转移过了那么直接跳过。

显然，如果一个点 $i$ 已经被20个不同的起点转移到了，那么显然之后转移到它的其他点不会成为离 $i$ 第 $w_i$ 近的点，也不会对 $i$ 之后的点产生贡献，直接跳过即可。

可以发现，这种情况下一个点只会被压入优先队列至多 $20$ 次，时间复杂度 $O(w\times m\log n)$。
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<queue>
#include<algorithm>
#include<map>
#define N 100010
#define M 200010
#define ll long long
using namespace std;
int nxt[M<<1],to[M<<1],head[N],cnt;
ll w[M<<1];
void add(int u,int v,ll w1)
{
	nxt[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=w1;
	head[u]=cnt;
}
map<int,ll>dis[N];
struct node{
	ll a;
	int s,u;
	node(int S=0,int U=0,ll A=0):a(A),s(S),u(U){}
	bool operator <(const node b)const{return a>b.a;}
};
priority_queue<node>q;
bool in[N],sp[N];
int tot,n,m;
struct pnode{
	int x;
	ll v;
	bool operator <(const pnode a)const{return v<a.v;}
}swp[23];
int kth[N];
ll kth_dis[N];
void dij()
{
	for(int i=1;i<=n;i++)
	if(sp[i]) q.push(node(i,i,0));
	while(!q.empty())
	{
		node p=q.top();
		q.pop();
		int u=p.u;
		if(dis[u].count(p.s)) continue;
		if(dis[u].size()>20) continue;
		dis[u][p.s]=p.a;
		for(int i=head[u];i;i=nxt[i])
		{
			int v=to[i];
			if(dis[v].count(p.s)) continue;
			q.push((node){p.s,v,p.a+w[i]});
		}
	}
	for(int i=1;i<=n;i++)
	{
		tot=0;
		for(auto u:dis[i]) swp[++tot]=(pnode){u.first,u.second};
		sort(swp+1,swp+tot+1);
		kth_dis[i]=kth[i]>tot?1e18:swp[kth[i]].v;
	}
}
ll num[N];
int ptot;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int u,v;
		ll w;
		scanf("%d%d%lld",&u,&v,&w);
		add(u,v,w);
		add(v,u,w);
	}
	int k;
	scanf("%d",&k);
	for(int i=1,a;i<=k;i++) scanf("%d",&a),sp[a]=true;
	for(int i=1;i<=n;i++) scanf("%d",&kth[i]);
	dij();
	scanf("%d",&ptot);
	for(int i=1;i<=ptot;i++) scanf("%lld",&num[i]);
	sort(num+1,num+ptot+1);
	for(int i=1;i<=n;i++) printf("%lld ",lower_bound(num+1,num+ptot+1,kth_dis[i])-num-1);
	return 0;
}
```
