#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
#define N 100010
#define M 300010
#define inf 1000000000
using namespace std;
namespace dinic{
	struct node{
		int nxt,to,w;
	}road[N<<2];
	int head[N],cnt=1;
	void add(int u,int v,int w)
	{
		road[++cnt]=(node){head[u],v,w};
		head[u]=cnt;
		road[++cnt]=(node){head[v],u,0};
		head[v]=cnt;
	}
	int dep[N],cur[N];
	queue<int>q;
	bool bfs(int s,int t)
	{
		memset(dep,127,sizeof(dep));
		memcpy(cur,head,sizeof(cur));
		dep[s]=1;
		q.push(s);
		while(!q.empty())
		{
			int u=q.front();
			q.pop();
			for(int i=head[u];i;i=road[i].nxt)
			{
				int v=road[i].to;
				if(dep[v]>=inf && road[i].w)
				{
					dep[v]=dep[u]+1;
					q.push(v);
				}
			}
		}
		return dep[t]<=inf;
	}
	int dfs(int u,int t,int flow)
	{
		if(u==t || !flow) return flow;
		int ans=0;
		for(int i=head[u];i;i=road[i].nxt)
		{
			int v=road[i].to,f=0;
			if(dep[v]==dep[u]+1 && (f=dfs(v,t,min(flow,road[i].w))))
			{
				flow-=f;
				ans+=f;
				road[i].w-=f;
				road[i^1].w+=f;
				if(!flow) break;
			}
		}
		return ans;
	}
	int dinic(int s,int t)
	{
		int ans=0;
		while(bfs(s,t))
		ans+=dfs(s,t,inf);
		return ans;
	}
}
int col[N];
namespace tarjan{
	int nxt[M],to[M],head[N],cnt;
	int dfn[N],low[N],idn;
	int sta[N],top;
	int id[N],tot;
	bool in[N];
	void add(int u,int v)
	{
		nxt[++cnt]=head[u];
		to[cnt]=v;
		head[u]=cnt;
	}
	void tarjan(int u)
	{
		dfn[u]=low[u]=++idn;
		sta[++top]=u;
		in[u]=true;
		for(int i=head[u];i;i=nxt[i])
		{
			int v=to[i];
			if(!dfn[v])
			{
				tarjan(v);
				low[u]=min(low[u],low[v]);
			}
			else if(in[v]) low[u]=min(low[u],dfn[v]);
		}
		if(dfn[u]==low[u])
		{
			++tot;
			int x;
			do{
				x=sta[top--];
				in[x]=0;
				id[x]=tot;
			}while(u!=x);
		}
	}
	#define P pair<int,int>
	#define MP make_pair
	vector<P >ans;
	void work(int s,int t,int n)
	{
		for(int u=1;u<=t;u++)
			for(int i=dinic::head[u];i;i=dinic::road[i].nxt)
			if(dinic::road[i].w)
			add(u,dinic::road[i].to);
		for(int u=1;u<=t;u++)
			if(!dfn[u]) tarjan(u);
		for(int u=1;u<=n;u++)
		if(!col[u])
		{
			for(int i=dinic::head[u];i;i=dinic::road[i].nxt)
			{
				int v=dinic::road[i].to;
				if(dinic::road[i].w) continue;
				if(id[u]!=id[v] && v!=s) ans.push_back(MP(min(u,v),max(u,v)));
			}
		}
		sort(ans.begin(),ans.end());
		printf("%d\n",ans.size());
		for(int i=0;i<ans.size();i++) printf("%d %d\n",ans[i].first,ans[i].second);
	}
}
int nxt[M],to[M],head[N],cnt;
void add(int u,int v)
{
	nxt[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
}
void dfs(int u,int c)
{
	col[u]=c;
	for(int i=head[u];i;i=nxt[i])
	{
		int v=to[i];
		if(col[v]==-1) dfs(v,c^1);
	}
}
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	int s=n+1,t=s+1;
	for(int i=1;i<=n;i++) col[i]=-1;
	for(int i=1;i<=m;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v);
		add(v,u);
	}
	for(int i=1;i<=n;i++)
	if(col[i]==-1) dfs(i,1);
	for(int i=1;i<=n;i++)
	if(!col[i]) dinic::add(s,i,1);
	else dinic::add(i,t,1);
	for(int u=1;u<=n;u++)
	if(!col[u])
	{
		for(int i=head[u];i;i=nxt[i])
		{
			int v=to[i];
			dinic::add(u,v,1);
		}
	}
	dinic::dinic(s,t);
	tarjan::work(s,t,n);
	return 0;
}
