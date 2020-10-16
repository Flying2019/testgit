### [����](https://darkbzoj.tk/problem/3879)
����·����Ŀ�����Ժܺõ�ѧһѧ������

���ȿ�����׺��lcp���ȿ���SAM/SA�������SAҲ�����������Ҳ�̫�ᡣ���ǿ��Ǹ���·��SAM��

����SAM��parent�������Ͼ���һ�����������ǰ������Ӵ���trie���Ľڵ�ѹ���󽨳ɵ������ܵ����� $O(n)$��

�������ǽ�SAM��������ô������׺��lcp��Ӧ����������׺��Ӧ�Ľڵ���parent���ϵ�lca��

��ô�������ͺ���·�ˣ�$m$ �θ��� $k$ ���㣬���� $k$ ��������lca�Ķ�ӦȨֵ�͡�$\sum k\leq 10^6$��

һ���������������ʷ֣����Ǹ��Ӷ� $O(k\log^2 n)$��ֱ�ӱ�ը��

���ǰ�����·��ջ��һ��������Ȼ��򵥵�����dp���ɡ�

���Ӷ� $O(k\log n)$��
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
