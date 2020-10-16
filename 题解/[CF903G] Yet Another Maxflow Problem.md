### [链接](https://codeforces.com/contest/903/problem/G)

首先很明显最小割=最大流，然后可以发现，因为边是单向的，A和B中的边只会割掉一条，然后剩余的代价就是中间的有效边的权值和。

这很像一个二位数点的加强版，但是注意到修改操作只改变A的值。而对于一个A来说，如果选择割掉了这条边，那么B中的最优策略是不会随着这条边的变化而变化的，也就是说这是个定值。而这个值可以通过线段树预处理出来。同样，修改操作也可以通过线段树预处理出来，$O(n\log n)$。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define N 200010
#define ll long long
using namespace std;
int nxt[N<<1],to[N<<1],head[N],cnt;
ll fw[N];
void add(int u,int v,ll w)
{
	nxt[++cnt]=head[u];
	to[cnt]=v;
	fw[cnt]=w;
	head[u]=cnt;
}
ll num[N<<2],tag[N<<2];
inline void set_tag(int u,ll v){num[u]+=v,tag[u]+=v;}
inline void update(int u){num[u]=min(num[u<<1],num[u<<1|1]);}
void push_down(int u)
{
	if(tag[u]==-1) return;
	set_tag(u<<1,tag[u]),set_tag(u<<1|1,tag[u]),tag[u]=0;
}
void build(int u,int l,int r,ll a[])
{
	tag[u]=0;
	if(l==r){num[u]=a[l];return;}
	int mid=(l+r)>>1;
	build(u<<1,l,mid,a);
	build(u<<1|1,mid+1,r,a);
	update(u);
}
void insert(int u,int l,int r,int L,int R,ll v)
{
	if(L>r || l>R) return;
	if(L<=l && r<=R){set_tag(u,v);return;}
	int mid=(l+r)>>1;
	push_down(u);
	insert(u<<1,l,mid,L,R,v);
	insert(u<<1|1,mid+1,r,L,R,v);
	update(u);
}
ll a[N],b[N],c[N];
int main()
{
	int n,m,q;
	scanf("%d%d%d",&n,&m,&q);
	for(int i=2;i<=n;i++) scanf("%lld%lld",&a[i-1],&b[i]);
	for(int i=1;i<=m;i++)
	{
		int u,v;
		ll w;
		scanf("%d%d%lld",&u,&v,&w);
		add(u,v,w);
	}
	build(1,1,n,b);
	for(int u=1;u<=n;u++)
	{
		for(int i=head[u];i;i=nxt[i]) insert(1,1,n,1,to[i],fw[i]);
		c[u]=a[u]+num[1];
	}
	build(1,1,n,c);
	printf("%lld\n",num[1]);
	while(q --> 0)
	{
		int u;
		ll v;
		scanf("%d%lld",&u,&v);
		insert(1,1,n,u,u,v-a[u]);
		a[u]=v;
		printf("%lld\n",num[1]);
	}
	return 0;
}

```

