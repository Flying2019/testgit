### [链接](https://codeforces.com/contest/1083/problem/C)
一个很特殊的求mex的方式。

由于题目中强调这棵树是 $1$ 到 $n$ 的排列，对应每个数字只出现一次。

换句话说，假如对于某个 $x$，$1$ 到 $x$ 的所有数字不能用一条链覆盖，那么答案一定 $\leq x$。

那么显然就有了一个二分的思路：

对于区间 $[l,r]$，我们尝试用一条链去覆盖 $l$ 到 $\frac {l+r} 2$，如果不存在那么再二分左半边，否则求出最短的链，然后判断右半边。

可以发现，假如我们求出 $[l,a]$ 和 $[a+1,r]$ 的链，是可以在 $O(\log n)$ 时间内求出 $[l,r]$ 的最短的链或说明不存在。具体可以求lca实现。

再套上二分答案，这样总时间复杂度 $O(n\log^3 n)$，T飞了。

考虑二分可以在线段树上完成，即查找左子树能否找到可以合并当前值得链，如果可以就将链合并上，查找右子树，否则直接找左子树即可。

复杂度 $O(n\log^2 n)$。
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
int fa[N],dep[N],siz[N],son[N];
void dfs(int u,int p)
{
	dep[u]=dep[p]+1;
	fa[u]=p;siz[u]=1;
	for(int i=head[u];i;i=nxt[i])
	{
		int v=to[i];
		if(v==p) continue;
		dfs(v,u);
		siz[u]+=siz[v];
		if(siz[son[u]]<siz[v]) son[u]=v;
	}
}
int top[N],id[N],nid[N],tot;
void dfs2(int u,int topp)
{
	top[u]=topp;
	nid[id[u]=++tot]=u;
	if(son[u]) dfs2(son[u],topp);
	for(int i=head[u];i;i=nxt[i])
	{
		int v=to[i];
		if(v!=fa[u] && v!=son[u]) dfs2(v,v);
	}
}
int lca(int u,int v)
{
	while(top[u]!=top[v])
	{
		if(dep[top[u]]<dep[top[v]]) swap(u,v);
		u=fa[top[u]];
	}
	return dep[u]<dep[v]?u:v;
}
struct line{
	int l,r;//l->r
	line(int L=0,int R=0):l(L),r(R){}
};
inline bool is_f(int x,int y){return id[y]>=id[x] && id[y]<=id[x]+siz[x]-1;}//x is the ancestor of y
bool operator &(const line a,const line b)
{
	int l=lca(a.l,a.r);
	return is_f(l,b.l) && is_f(l,b.r) && (is_f(b.l,a.l) || is_f(b.l,a.r)) && (is_f(b.r,a.l) || is_f(b.r,a.r));
}
line operator +(const line a,const line b)
{
	if(a.l==0 || b.l==0) return line(a.l|b.l,a.r|b.r);
	if(a.l==-1 || b.l==-1) return line(-1,-1);
	if(line(a.l,a.r)&line(b.l,b.r)) return line(a.l,a.r);
	if(line(a.l,b.r)&line(b.l,a.r)) return line(a.l,b.r);
	if(line(b.l,a.r)&line(a.l,b.r)) return line(b.l,a.r);
	if(line(b.l,b.r)&line(a.l,a.r)) return line(b.l,b.r);
	if(line(a.l,b.l)&line(a.r,b.r)) return line(a.l,b.l);
	if(line(a.r,b.r)&line(a.l,b.l)) return line(a.r,b.r);
	return line(-1,-1);
}
int w[N],wp[N];
line val[N<<2];
void build(int u,int l,int r)
{
	if(l==r){val[u]=(line){wp[l],wp[l]};return;}
	int mid=(l+r)>>1;
	build(u<<1,l,mid);
	build(u<<1|1,mid+1,r);
	val[u]=val[u<<1]+val[u<<1|1];
}
void insert(int u,int l,int r,int p)
{
	if(l==r){val[u]=(line){wp[l],wp[l]};return;}
	int mid=(l+r)>>1;
	if(p<=mid) insert(u<<1,l,mid,p);
	else insert(u<<1|1,mid+1,r,p);
	val[u]=val[u<<1]+val[u<<1|1];
}
int answer(int u,int l,int r,line v)
{
	if(l==r) return l;
	line w=v+val[u<<1];
	int mid=(l+r)>>1;
	if(w.l!=-1) return answer(u<<1|1,mid+1,r,w);
	else return answer(u<<1,l,mid,v);
}
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&w[i]),wp[++w[i]]=i;
	for(int i=2;i<=n;i++)
	{
		scanf("%d",&fa[i]);
		add(fa[i],i);
	}
	dfs(1,0);
	dfs2(1,1);
	build(1,1,n);
	int m;
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
	{
		int opt;
		scanf("%d",&opt);
		if(opt==1)
		{
			int u,v;
			scanf("%d%d",&u,&v);
			swap(wp[w[u]],wp[w[v]]),swap(w[u],w[v]);
			insert(1,1,n,w[u]),insert(1,1,n,w[v]);
		}
		else printf("%d\n",(val[1].l==-1?answer(1,1,n,line()):n+1)-1);
	}
	return 0;
}
```
