### [链接](https://darkbzoj.tk/problem/3879)
很套路的题目，可以很好地学一学虚树。

首先看到后缀的lcp，先考虑SAM/SA。这道题SA也能做，不过我不太会。还是考虑更套路的SAM。

首先SAM的parent树本质上就是一个虚树，就是把所有子串的trie树的节点压缩后建成的树，总点数是 $O(n)$。

所以我们将SAM倒建，那么两个后缀的lcp对应就是两个后缀对应的节点在parent树上的lca。

那么接下来就很套路了：$m$ 次给你 $k$ 个点，问这 $k$ 个点两两lca的对应权值和。$\sum k\leq 10^6$。

一种做法是用树链剖分，但是复杂度 $O(k\log^2 n)$，直接爆炸。

考虑按照套路用栈建一颗虚树，然后简单的树形dp即可。

复杂度 $O(k\log n)$。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define N 110
using namespace std;
int fa[N];
namespace SAM{
	int ch[N][26],len[N],las=1,stot=1;
	int insert(int c)
	{
		int p=las,u=las=++stot;
		len[u]=len[p]+1;
		for(;p && !ch[p][c];p=fa[p]) ch[p][c]=u;
		if(!p) fa[u]=1;
		else
		{
			int np=ch[p][c];
			if(len[np]==len[p]+1) fa[u]=np;
			else
			{
				int nq=++stot;
				len[nq]=len[p]+1;
				memcpy(ch[nq],ch[np],sizeof(ch[np]));
				fa[nq]=fa[np];
				fa[np]=fa[u]=nq;
				for(;p && ch[p][c]==np;p=fa[p]) ch[p][c]=nq;
			}
		}
		return u;
	}
}
char s[N];
int pos[N];
int nxt[N<<1],to[N<<1],head[N],cnt;
void add(int u,int v)
{
	nxt[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
}
int son[N],siz[N],top[N],dep[N],id[N],itot;
void dfs1(int u)
{
	dep[u]=dep[fa[u]]+1;
	siz[u]=1;
	for(int i=head[u];i;i=nxt[i])
	{
		int v=to[i];
		dfs1(v);
		siz[u]+=siz[v];
		if(siz[son[u]]<siz[v]) son[u]=v;
	}
}
void dfs2(int u,int topp)
{
	top[u]=topp;
	id[u]=++itot;
	if(son[u]) dfs2(son[u],topp);
	for(int i=head[u];i;i=nxt[i])
	{
		int v=to[i];
		if(v!=son[u]) dfs2(v,v);
	}
}
int lca(int x,int y)
{
	for(;top[x]!=top[y];x=fa[top[x]]) if(dep[top[x]]<dep[top[y]]) swap(x,y);
	return dep[x]<dep[y]?x:y;
}
int cmp(int x,int y){return id[x]<id[y];}
int q[N],qtot;
int tn[N],ttot;
bool chs[N];
vector<int>rd[N];
void build()
{
	ttot=0;
	tn[++ttot]=1;
	for(int i=1;i<=qtot;i++)
	if(q[i]!=q[i-1])
	{
		int x=lca(tn[ttot],q[i]);
		if(x!=tn[ttot])
		{
			while(dep[x]<dep[tn[ttot-1]])
			{
				rd[tn[ttot-1]].push_back(tn[ttot]);
				--ttot;
			}
			rd[x].push_back(tn[ttot]);--ttot;
			if(x!=tn[ttot]) tn[++ttot]=x;
		}
		tn[++ttot]=q[i];
	}
	while(--ttot) rd[tn[ttot]].push_back(tn[ttot+1]);
}
#define ll long long
ll ans=0;
int solve(int u)
{
	int r=chs[u];
	ll res=0;
	for(int v:rd[u])
	{
		int t=solve(v);
		res=res+1ll*t*r;
		r+=t;
	}
	ans=ans+1ll*res*(SAM::len[u]);
	rd[u].clear();
	return r;
}
void init()
{
	scanf("%d",&qtot);
	for(int i=1;i<=qtot;i++) scanf("%d",&q[i]),chs[q[i]=pos[q[i]]]=true;
	q[0]=1;
	sort(q+1,q+qtot+1,cmp);
	build();
	solve(1);
}
void clear()
{
	for(int i=1;i<=qtot;i++) chs[q[i]]=false;
	ttot=ans=0;
}
int main()
{
	int n,m;
	scanf("%d%d%s",&n,&m,s+1);
	for(int i=n;i>=1;i--) pos[i]=SAM::insert(s[i]-'a');
	for(int i=2;i<=SAM::stot;i++) add(fa[i],i);
	dfs1(1);
	dfs2(1,1);
	for(int i=1;i<=m;i++)
	{
		init();
		printf("%lld\n",ans);
		clear();
	}
	return 0;
}
```
