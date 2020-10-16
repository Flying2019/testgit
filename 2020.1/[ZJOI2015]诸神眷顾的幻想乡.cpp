#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define N 100010
#define M N*20
#define CR 12
using namespace std;
struct trie{
	int ch[M][CR],cr[M],fa[M],cnt;
	trie(){cnt=1;}
	int insert(int u,int c)
	{
		if(!ch[u][c]) ch[u][c]=++cnt,cr[cnt]=c,fa[cnt]=u;
		return ch[u][c];
	}
}t;
int C;
struct SAM{
	int ch[M][CR],fa[M],len[M],pos[M],cnt;
	SAM(){cnt=1;}
	int insert(int c,int last)
	{
		int p=last,q=++cnt;
		len[q]=len[p]+1;
		for(;p && !ch[p][c];p=fa[p]) ch[p][c]=q;
		if(!p) fa[q]=1;
		else
		{
			int np=ch[p][c];
			if(len[p]+1==len[np]) fa[q]=np;
			else
			{
				int nq=++cnt;
				len[nq]=len[p]+1;
				memcpy(ch[nq],ch[np],sizeof(ch[nq]));
				fa[nq]=fa[np];
				for(;p && ch[p][c]==np;p=fa[p]) ch[p][c]=nq;
				fa[q]=fa[np]=nq;
			}
		}
		return q;
	}
	queue<int>q;
	void build()
	{
		for(int i=0;i<C;i++)
		if(t.ch[1][i])q.push(t.ch[1][i]);
		pos[1]=1;
		while(!q.empty())
		{
			int u=q.front();
			q.pop();
			pos[u]=insert(t.cr[u],pos[t.fa[u]]);
			for(int i=0;i<C;i++)
			if(t.ch[u][i]) q.push(t.ch[u][i]);
        }
	}
	long long answer()
	{
		long long ans=0;
		for(int i=2;i<=cnt;i++) ans+=len[i]-len[fa[i]];
		return ans;
	}
}sam;
int color[N];
int nxt[N<<1],to[N<<1],head[N],cnt;
int in[N];
void add(int u,int v)
{
	nxt[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	in[v]++;
}
void dfs(int u,int fa,int x)
{
	int y=t.insert(x,color[u]);
	for(int i=head[u];i;i=nxt[i])
	{
		int v=to[i];
		if(v!=fa) dfs(v,u,y);
	}
}
int main()
{
	int n;
	scanf("%d%d",&n,&C);
	for(int i=1;i<=n;i++)scanf("%d",&color[i]);
	for(int i=1;i<n;i++)
	{
    	int u,v;
    	scanf("%d%d",&u,&v);
    	add(u,v);
    	add(v,u);
	}
	for(int i=1;i<=n;i++)
	if(in[i]==1) dfs(i,0,1);
	sam.build();
	printf("%lld",sam.answer());
	return 0;
}

