### [链接](https://codeforces.com/contest/547/problem/E)
### 题目大意
给定 $n$ 个字符串 $s_{1 \dots n}s$。$q$ 次询问 $s_k$ 在 $s_{l\dots r}$ 中出现了多少次。
### 题解
很经典的问题。

按照套路，考虑如果有 $l=r$ 怎么做。很显然，将 $l$ 这个字符串建一个 $SAM$，预先统计每个节点的 $endpos$ 集合大小，将 $s_k$ 跑匹配就好了。

那么假如 $l=1,r=n$ 怎么做。很显然，直接建立广义 $SAM$ ，将放上去 $s_k$ 跑匹配。

再考虑原题。每个节点的 $endpos$ 的贡献是有一个位置的。只需要查询位置在 $[l,r]$ 的 $endpos$ 集合大小。

所以建出广义 $SAM$，然后线段树合并，注意这里线段树需要可持久化，不能直接在原版本上合并。

同时在建广义 $SAM$ 的时候记录一下每个字符串最终的位置，查询时直接在这个位置上的线段树上查询即可。

复杂度 $O(n\log n)$。
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#define N 400010
#define M N*40
using namespace std;
namespace SAM{
	int fa[N],len[N],ch[N][27],cnt=1;
	int insert(int c,int las)
	{
		int p=las,q=las=++cnt;
		len[q]=len[p]+1;
		for(;p && !ch[p][c];p=fa[p]) ch[p][c]=q;
		if(!p) fa[q]=1;
		else
		{
			int np=ch[p][c];
			if(len[np]==len[p]+1) fa[q]=np;
			else
			{
				int nq=++cnt;
				len[nq]=len[p]+1;
				memcpy(ch[nq],ch[np],sizeof(ch[nq]));
				fa[nq]=fa[np];
				fa[np]=fa[q]=nq;
				for(;p && ch[p][c]==np;p=fa[p]) ch[p][c]=nq;
			}
		}
		return q;
	}
}
int ls[M],rs[M],val[M],tot;
void insert(int &u,int l,int r,int p)
{
	if(!u) u=++tot;
	if(l==r){val[u]++; return ;}
	int mid=(l+r)>>1;
	if(p<=mid) insert(ls[u],l,mid,p);
	else insert(rs[u],mid+1,r,p);
	val[u]=val[ls[u]]+val[rs[u]];
}
int answer(int u,int l,int r,int L,int R)
{
	if(!u && L>R) return 0;
	if(L<=l && r<=R) return val[u];
	int mid=(l+r)>>1,ans=0;
	if(L<=mid) ans+=answer(ls[u],l,mid,L,R);
	if(R>mid) ans+=answer(rs[u],mid+1,r,L,R);
	return ans;
}
int new_node(int y){int x=++tot;ls[x]=ls[y];rs[x]=rs[y];val[x]=val[y];return x;}
int merge(int x,int y)
{
	if(!x || !y) return x+y;
	int u=++tot;
	val[u]=val[x]+val[y];
	ls[u]=merge(ls[x],ls[y]);
	rs[u]=merge(rs[x],rs[y]);
	return u;
}
int head[N<<1],to[N<<1],nxt[N<<1],cnt;
int id[N],rt[N];
void add(int u,int v)
{
	nxt[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
}
void dfs(int u)
{
	for(int i=head[u];i;i=nxt[i])
	{
		int v=to[i];
		if(SAM::len[u]==SAM::len[v]) id[v]=id[u];
		else id[v]=v;
		dfs(v);
		rt[u]=merge(rt[u],rt[v]);
	}
}
char s[N];
int p[N];
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%s",s+1);
		int l=strlen(s+1);
		p[i]=1;
		for(int j=1;j<=l;j++) p[i]=SAM::insert(s[j]-'a',p[i]),insert(rt[p[i]],1,n,i);
	}
	for(int i=2;i<=SAM::cnt;i++) add(SAM::fa[i],i);
	id[1]=1;
	dfs(1);
	while(m --> 0)
	{
		int l,r,v;
		scanf("%d%d%d",&l,&r,&v);
		printf("%d\n",answer(rt[id[p[v]]],1,n,l,r));
	}
	return 0;
}
```
