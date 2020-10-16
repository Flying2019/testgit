### [链接](https://codeforces.com/problemset/problem/1172/E)
首先，维护链颜色数，显然就是LCT了。

考虑题目要求维护所有链的颜色数总和，显然我们可以对每种颜色单独算贡献，即算经过某种颜色的路径数。

考虑这个也很难算。正难则反，用总路径数减去不通过某种颜色的路径数即可。可以发现，这本质是去掉某些路径后的联通块大小的平方和。

显然可以对每种颜色建一课LCT，对于非该颜色的边连边，统计每条链的大小和大小的平方

但是旋转时不能直接修改，这样复杂度会炸，因为一种颜色可能连了多条边。

考虑“断点”其实比较复杂，不妨把点的颜色改成它连向父亲的边的颜色，这样既不会干扰，同时修改也变得很简单，本质就是断一条边和加一条边。

同时因为断边会导致该点也被断掉（只是没有在LCT上体现）所以应当取它子树的大小。由于已经在cut的时候将其旋至根节点，所以子树位于其右子树。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#define N 500010
#define ll long long
#define P pair<int,int>
#define MP make_pair
#define fi first
#define se second
using namespace std;
int nxt[N<<1],to[N<<1],head[N],cnt;
int n,m;
struct LCT{
	int ch[N][2],fa[N],cnt;
	ll val[N],sum[N],s[N];
	void init(int n){for(int i=1;i<=n;i++) s[i]=1;}
	bool is_root(int u){return !fa[u] || (ch[fa[u]][0]!=u && ch[fa[u]][1]!=u);}
	void update(int u)
	{
		s[u]=val[u]+1;
		if(ch[u][0]) s[u]+=s[ch[u][0]];
		if(ch[u][1]) s[u]+=s[ch[u][1]];
	}
	void rotate(int u)
	{
		int f=fa[u],ff=fa[f];
		int k=ch[f][1]==u,v=ch[u][!k];
		if(!is_root(f)) ch[ff][ch[ff][1]==f]=u;
		ch[f][k]=v;
		ch[u][!k]=f;
		if(v) fa[v]=f;
		fa[f]=u;
		fa[u]=ff;
		update(f),update(u);
	}
	void splay(int x)
	{
		while(!is_root(x))
		{
			int f=fa[x],ff=fa[f];
			if(!is_root(f)) rotate((ch[ff][1]==f)^(ch[f][1]==x)?x:f);
			rotate(x);
		}
	}
	void access(int x)
	{
		for(int y=0;x;y=x,x=fa[x])
		{
			splay(x);
			int &v=ch[x][1];
			if(v) val[x]+=s[v],sum[x]+=1ll*s[v]*s[v];
			v=y;
			if(v) val[x]-=s[v],sum[x]-=1ll*s[v]*s[v];
		}
	}
	int find_root(int x)
	{
		access(x);
		splay(x);
		while(ch[x][0]) x=ch[x][0];
		splay(x);
		return x;
	}
	void link(int x,int y)
	{
		access(y);
		splay(y);
		splay(x);
		fa[x]=y;
		val[y]+=s[x];
		sum[y]+=1ll*s[x]*s[x];
		update(y);
	}
	void cut(int x,int y)
	{
		access(y);
		splay(y);
		splay(x);
		fa[x]=0;
		val[y]-=s[x];
		sum[y]-=1ll*s[x]*s[x];
		update(y);
	}
}t;
int fa[N];
void dfs(int u,int pre)
{
	fa[u]=pre;
	for(int i=head[u];i;i=nxt[i])
	if(to[i]!=pre) dfs(to[i],u);
}
void add(int u,int v)
{
	nxt[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt; 
}
vector<P > q[N];
bool df[N];
ll answer(int u)
{
	int f=t.find_root(u);
	if(df[f]) return 1l*t.s[t.ch[f][1]]*t.s[t.ch[f][1]];
	else return 1ll*t.s[f]*t.s[f];
}
ll change(int u)
{
	df[u]^=1;
	if(df[u])
	{
		if(u==1){t.access(1);return t.sum[1]-1ll*t.s[1]*t.s[1];}
		ll r=-answer(u);
		t.cut(u,fa[u]);
		t.access(u);
		r+=t.sum[u];
		if(!df[fa[u]]) r+=answer(fa[u]);
		return r;
	}
	else
	{
		if(u==1){t.access(1);return 1ll*t.s[1]*t.s[1]-t.sum[1];}
		t.access(u);
		ll r=-t.sum[u];
		if(!df[fa[u]]) r-=answer(fa[u]);
		t.link(u,fa[u]);
		r+=answer(u);
		return r;
	}
}
ll ans[N];
void solve(int col)
{
	for(int i=0;i<q[col].size();i++) ans[q[col][i].fi]+=change(q[col][i].se);
	for(int i=(int)q[col].size()-1;i>=0;i--) change(q[col][i].se);
}
int col[N];
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&col[i]);
	for(int i=1;i<n;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v),add(v,u);
	}
	dfs(1,0);
	t.init(n);
	for(int i=1;i<=n;i++) t.link(i,fa[i]);
	for(int i=1;i<=n;i++) q[col[i]].push_back(MP(0,i));
	for(int i=1;i<=m;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		q[col[u]].push_back(MP(i,u));
		col[u]=v;
		q[col[u]].push_back(MP(i,u));
	}
	for(int i=1;i<=n;i++) solve(i);
	for(int i=1;i<=m;i++) ans[i]+=ans[i-1];
	for(int i=0;i<=m;i++) printf("%lld\n",-ans[i]);
	return 0;
}
```
